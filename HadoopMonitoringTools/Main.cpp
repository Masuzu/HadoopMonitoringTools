#include "ResourceManagerAPI.h"
#include "HistoryServerAPI.h"
#include "Job.h"

#include <iostream>

using namespace Hadoop::Tools;

int main()
{
	ServerAPI *server_API = new HistoryServerAPI("http://jobhistory.pa4.hpc.criteo.prod/");
	// ServerAPI *server_API = new ResourceManagerAPI("http://resourcemanager.pa4.hpc.criteo.prod");
	auto apps = server_API->GetAllApps({ "user=recocomputer" });
	std::multimap<std::string, int64_t> runtime_per_job;
	for (const ClusterApplication *application : apps)
	{
		Job *job = (Job*)application;
		runtime_per_job.insert(std::make_pair(job->name(), job->average_map_time() * job->maps_total() + job->average_reduce_time() * job->reduces_total()));
	}
	std::map<std::string, int64_t> aggregated_runtime_per_job;
	for (const auto &entry : runtime_per_job)
	{
		const std::string &job_name = entry.first;

		int64_t total_runtime = 0;
		auto value_bounds = runtime_per_job.equal_range(job_name);
		for (auto it = value_bounds.first; it != value_bounds.second; ++it)
			total_runtime += it->second;

		aggregated_runtime_per_job.insert(std::make_pair(job_name, total_runtime / runtime_per_job.count(job_name)));
	}

	for (const auto &entry : aggregated_runtime_per_job)
		std::cout << entry.first << " " << (entry.second / 1000 / 60 ) << " minutes\n" << std::endl;

	delete server_API;
}