#pragma once

#include "ClusterApplication.h"

namespace Hadoop
{
	namespace Tools
	{
		class Application : public ClusterApplication
		{
		public:
			Application(const Json::Value &resource_manager_json_response);
		};
	}
}