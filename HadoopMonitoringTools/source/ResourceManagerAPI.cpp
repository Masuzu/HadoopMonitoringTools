#include "ResourceManagerAPI.h"

#include "Application.h"

namespace Hadoop
{
	namespace Tools
	{
		ResourceManagerAPI::ResourceManagerAPI(const std::string &resource_manager_url) : ServerAPI(resource_manager_url)
		{

		}

		ResourceManagerAPI::~ResourceManagerAPI()
		{

		}

		std::vector<ClusterApplication*> ResourceManagerAPI::GetAllApps(const std::initializer_list<const char *> &query_parameters)
		{
			std::vector<ClusterApplication*> result;

			std::string response = Request("ws/v1/cluster/apps", query_parameters);
			Json::Value root;
			bool parsing_successful = Json::Reader().parse(response.c_str(), root);
			if (!parsing_successful)
				return result;

			Json::Value applications = root.get("apps", "").get("app", "");
			size_t num_applications = applications.size();
			
			for (size_t i = 0; i < num_applications; ++i)
				result.push_back(new Application(applications.get(i, "")));

			return result;
		}
	}
}