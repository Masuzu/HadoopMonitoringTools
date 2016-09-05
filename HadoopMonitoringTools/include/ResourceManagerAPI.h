#pragma once

#include "ServerAPI.h"

namespace Hadoop
{
	namespace Tools
	{
		class ResourceManagerAPI : public ServerAPI
		{
		public:
			ResourceManagerAPI(const std::string &resourceManagerUrl);
			virtual ~ResourceManagerAPI();

			// See https://hadoop.apache.org/docs/stable/hadoop-yarn/hadoop-yarn-site/ResourceManagerRest.html#Cluster_Application_API for a list of supported query parameters
			std::vector<ClusterApplication*> GetAllApps(const std::initializer_list<const char *> &query_parameters) override;
		};
	}
}