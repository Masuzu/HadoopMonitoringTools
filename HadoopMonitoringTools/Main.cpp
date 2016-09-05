#include "ResourceManagerAPI.h"
#include "HistoryServerAPI.h"
#include "Job.h"

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace Hadoop::Tools;

#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))

template<typename A, typename B>
std::pair<B, A> FlipPair(const std::pair<A, B> &p)
{
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> FlipMap(const std::map<A, B> &src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), FlipPair<A, B>);
	return dst;
}

int main()
{
	ServerAPI *server_API = new HistoryServerAPI("http://jobhistory.pa4.hpc.criteo.prod/");
	// ServerAPI *server_API = new ResourceManagerAPI("http://resourcemanager.pa4.hpc.criteo.prod");
	auto apps = server_API->GetAllApps({ "user=recocomputer" });

	int64_t min_timestamp = INT64_MAX;
	int64_t max_timestamp = INT64_MIN;
	std::multimap<std::string, int64_t> runtime_per_job;
	for (const ClusterApplication *application : apps)
	{
		Job *job = (Job*)application;
		runtime_per_job.insert(std::make_pair(job->name(), job->average_map_time() * job->maps_total() + job->average_reduce_time() * job->reduces_total()));
		min_timestamp = min(min_timestamp, job->start_time());
		max_timestamp = max(max_timestamp, job->finish_time());
	}
	std::map<std::string, int64_t> aggregated_runtime_per_job;
	int64_t total_runtime_for_user = 0;

	// Iterate over unique job names
	for (
		auto job_entries = runtime_per_job.begin(), end = runtime_per_job.end();
		job_entries != end;
		job_entries = runtime_per_job.upper_bound(job_entries->first)
		)
	{
		const std::string &job_name = job_entries->first;

		int64_t total_runtime = 0;
		auto value_bounds = runtime_per_job.equal_range(job_name);
		for (auto it = value_bounds.first; it != value_bounds.second; ++it)
			total_runtime += it->second;

		int64_t job_average_runtime = total_runtime / runtime_per_job.count(job_name) / (1000 * 60); // In minutes
		aggregated_runtime_per_job.insert(std::make_pair(job_name, job_average_runtime));
		total_runtime_for_user += job_average_runtime;
	}
	
	// Sort the jobs by runtime
	std::multimap<int64_t, std::string> user_jobs_sorted_by_runtime = FlipMap(aggregated_runtime_per_job);

	for (const auto &entry : user_jobs_sorted_by_runtime)
	{
		int64_t runtime = entry.first;
		auto value_bounds = user_jobs_sorted_by_runtime.equal_range(runtime);
		std::cout << entry.second << " " << ((double)runtime / total_runtime_for_user * 100) << "%" << std::endl;
	}

	std::cout << "Over " << (max_timestamp - min_timestamp) / (1000 * 60) << " minutes";

	delete server_API;
}