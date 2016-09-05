#include "HistoryServerAPI.h"

#include "Job.h"

#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for.h>

namespace Hadoop
{
	namespace Tools
	{
		static const char *kApiId = "id";
		
		HistoryServerAPI::HistoryServerAPI(const std::string &history_server_url) : ServerAPI(history_server_url)
		{
		}

		HistoryServerAPI::~HistoryServerAPI()
		{
		}

		std::vector<ClusterApplication*> HistoryServerAPI::GetAllApps(const std::initializer_list<const char *> &query_parameters)
		{
			std::vector<ClusterApplication*> result;

			std::string response = Request("ws/v1/history/mapreduce/jobs", query_parameters);
			Json::Value root;
			bool parsing_successful = Json::Reader().parse(response.c_str(), root);
			if (!parsing_successful)
				return result;

			Json::Value applications = root.get("jobs", "").get("job", "");
			size_t num_applications = applications.size();

			tbb::concurrent_vector <ClusterApplication*> temp_result;
			tbb::parallel_for(size_t(0), num_applications, [&](size_t i)
			{
				std::string job_id = applications.get(i, "").get(kApiId, "").asString();
				temp_result.push_back(GetApplication(job_id));
			});
			for (auto application : temp_result)
				result.push_back(application);
			return result;
		}

		ClusterApplication *HistoryServerAPI::GetApplication(const std::string &id)
		{
			std::string response = Request("ws/v1/history/mapreduce/jobs/" + id);
			Json::Value root;
			bool parsing_successful = Json::Reader().parse(response.c_str(), root);
			if (!parsing_successful)
				return nullptr;
			return new Job(root.get("job", ""));
		}
	}
}