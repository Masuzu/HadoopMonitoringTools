#include "ClusterApplication.h"

namespace Hadoop
{
	namespace Tools
	{
		static const char *kApiId = "id";
		static const char *kApiName = "name";
		static const char *kApiUser = "user";
		static const char *kApiState = "state";
		static const char *kApiStartTime = "startedTime";
		static const char *kApiQueue = "queue";
		static const char *kApiMemorySeconds = "memorySeconds";

		ClusterApplication::State ClusterApplication::ParseState(const char *state)
		{
			if (strcmp(state, "NEW") == 0)
				return NEW;
			else if (strcmp(state, "NEW_SAVING") == 0)
				return NEW_SAVING;
			else if (strcmp(state, "SCHEDULED") == 0)
				return SCHEDULED;
			else if (strcmp(state, "SUBMITTED") == 0)
				return SUBMITTED;
			else if (strcmp(state, "ACCEPTED") == 0)
				return ACCEPTED;
			else if (strcmp(state, "RUNNING") == 0)
				return RUNNING;
			else if (strcmp(state, "SUCCEEDED") == 0)
				return SUCCEEDED;
			else if (strcmp(state, "FINISHED") == 0)
				return FINISHED;
			else if (strcmp(state, "FAILED") == 0)
				return FAILED;
			else if (strcmp(state, "KILL_WAIT") == 0)
				return KILL_WAIT;
			return KILLED;
		}

		ClusterApplication::ClusterApplication(const Json::Value &resource_manager_json_response)
		{
			id_ = resource_manager_json_response.get(kApiId, "").asString();
			name_ = resource_manager_json_response.get(kApiName, "").asString();
			user_ = resource_manager_json_response.get(kApiUser, "").asString();
			state_ = ParseState(resource_manager_json_response.get(kApiState, "").asCString());
			queue_ = resource_manager_json_response.get(kApiQueue, "").asString();
			start_time_ = resource_manager_json_response.get(kApiStartTime, "0").asInt64();
		}
	}
}