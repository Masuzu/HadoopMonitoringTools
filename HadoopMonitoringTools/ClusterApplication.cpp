#include "ClusterApplication.h"

namespace Hadoop
{
	namespace Tools
	{
		static const char *kApiId = "id";
		static const char *kApiName = "name";
		static const char *kApiUser = "user";
		static const char *kApiState = "state";
		static const char *kApiProgress = "progress";
		static const char *kApiFinishedTime = "finishedTime";

		ClusterApplication::State ClusterApplication::ParseState(const char *state)
		{
			if (strcmp(state, "NEW") == 0)
				return NEW;
			else if (strcmp(state, "NEW_SAVING") == 0)
				return NEW_SAVING;
			else if (strcmp(state, "SUBMITTED") == 0)
				return SUBMITTED;
			else if (strcmp(state, "ACCEPTED") == 0)
				return ACCEPTED;
			else if (strcmp(state, "RUNNING") == 0)
				return RUNNING;
			else if (strcmp(state, "FINISHED") == 0)
				return FINISHED;
			else if (strcmp(state, "FAILED") == 0)
				return FAILED;
			return KILLED;
		}

		ClusterApplication::ClusterApplication(const Json::Value &resource_manager_json_response)
		{
			id_ = resource_manager_json_response.get(kApiId, "").asString();
			name_ = resource_manager_json_response.get(kApiName, "").asString();
			user_ = resource_manager_json_response.get(kApiUser, "").asString();
			state_ = ParseState(resource_manager_json_response.get(kApiState, "").asCString());
			progress_ = resource_manager_json_response.get(kApiProgress, "").asFloat();
			finished_time_ = resource_manager_json_response.get(kApiFinishedTime, "").asInt64();
		}
	}
}