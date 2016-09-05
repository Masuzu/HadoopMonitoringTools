#pragma once

#include "ClusterApplication.h"

namespace Hadoop
{
	namespace Tools
	{
		class Job : public ClusterApplication
		{
		protected:
			int maps_total_;
			int reduces_total_;
			int64_t average_map_time_;
			int64_t average_reduce_time_;

		public:
			Job(const Json::Value &resource_manager_json_response);
			__forceinline int maps_total() const { return maps_total_; }
			__forceinline int reduces_total() const { return reduces_total_; }
			__forceinline int64_t average_map_time() { return average_map_time_; }
			__forceinline int64_t average_reduce_time() { return average_reduce_time_; }
		};
	}
}