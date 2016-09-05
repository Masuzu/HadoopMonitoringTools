#include "Application.h"

namespace Hadoop
{
	namespace Tools
	{
		static const char *kApiProgress = "progress";
		static const char *kApiFinishedTime = "finishedTime";

		Application::Application(const Json::Value &job_history_json_response) : ClusterApplication(job_history_json_response)
		{
			progress_ = job_history_json_response.get(kApiProgress, "0").asInt64();;
			finish_time_ = job_history_json_response.get(kApiFinishedTime, "0").asInt64();
		}
	}
}