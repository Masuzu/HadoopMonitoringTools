#include "Job.h"

namespace Hadoop
{
	namespace Tools
	{
		static const char *kApiFinishTime = "finishTime";
		static const char *kApiMapsTotal = "mapsTotal";
		static const char *kApiAvgMapTime = "avgMapTime";
		static const char *kApiReducesTotal = "reducesTotal";
		static const char *kApiAvgReduceTime = "avgReduceTime";

		Job::Job(const Json::Value &job_history_json_response) : ClusterApplication(job_history_json_response)
		{
			progress_ = 100;
			finish_time_ = job_history_json_response.get(kApiFinishTime, "0").asInt64();
			maps_total_ = job_history_json_response.get(kApiMapsTotal, "0").asInt();
			reduces_total_ = job_history_json_response.get(kApiReducesTotal, "0").asInt();
			average_map_time_ = job_history_json_response.get(kApiAvgMapTime, "0").asInt64();
			average_reduce_time_ = job_history_json_response.get(kApiAvgReduceTime, "0").asInt64();
		}
	}
}