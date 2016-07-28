#pragma once

#include "Query.h"
#include "ClusterApplication.h"
#include <vector>
#include <initializer_list>

namespace Hadoop
{
	namespace Tools
	{
		class ResourceManagerAPI
		{
		protected:
			Query *query_;
			// Final resource manager URL after following the possible redirections
			std::string resource_manager_url_;

		public:
			ResourceManagerAPI(const std::string &resourceManagerUrl);
			virtual ~ResourceManagerAPI();

			// See https://hadoop.apache.org/docs/stable/hadoop-yarn/hadoop-yarn-site/ResourceManagerRest.html#Cluster_Application_API for a list of supported query parameters
			std::vector<ClusterApplication*> GetAllApps(const std::initializer_list<const char *> &query_parameters);
			
			std::string Request(const std::string &request);
		};
	}
}