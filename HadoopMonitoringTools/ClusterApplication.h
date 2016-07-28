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
				SUBMITTED,
				ACCEPTED,
				RUNNING,
				FINISHED,
				FAILED,
				KILLED
			};

		private:
			std::string id_;
			std::string name_;
			std::string user_;
			State state_;
			float progress_;
			int64_t finished_time_;

			static State ParseState(const char *state);

		public:
			ClusterApplication(const Json::Value &resource_manager_json_response);
			__forceinline const std::string &id() const { return id_; }
			__forceinline const std::string &name() const { return name_; }
			__forceinline const std::string &user() const { return user_; }
			__forceinline State state() const { return state_; }
			__forceinline float progress() const { return progress_; }
			__forceinline int64_t finished_time() const { return finished_time_; }
		};
	}
}