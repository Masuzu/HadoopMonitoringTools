#pragma once

#include <string>
#include "json/json.h"

namespace Hadoop
{
	namespace Tools
	{
		class ClusterApplication
		{
		public:
			enum State
			{
				NEW,
				NEW_SAVING,
				SCHEDULED,
				SUBMITTED,
				ACCEPTED,
				RUNNING,
				SUCCEEDED,
				FINISHED,
				FAILED,
				KILL_WAIT,
				KILLED
			};

			static const int64_t kUndefinedInt64 = INT64_MIN;

		protected:
			std::string id_;
			std::string name_;
			std::string user_;
			State state_;
			float progress_;
			int64_t start_time_;
			int64_t finish_time_;
			std::string queue_;

			static State ParseState(const char *state);

		public:
			ClusterApplication(const Json::Value &resource_manager_json_response);

			__forceinline const std::string &id() const { return id_; }
			__forceinline const std::string &name() const { return name_; }
			__forceinline const std::string &user() const { return user_; }
			__forceinline State state() const { return state_; }
			__forceinline float progress() const { return progress_; }
			__forceinline int64_t start_time() const { return start_time_; }
			__forceinline int64_t finish_time() const { return finish_time_; }
			__forceinline const std::string &queue() const { return queue_; }
		};
	}
}