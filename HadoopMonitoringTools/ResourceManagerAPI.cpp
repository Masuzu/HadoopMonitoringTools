#include "ResourceManagerAPI.h"

#include "ClusterApplication.h"
#include "json/json.h"

namespace Hadoop
{
	namespace Tools
	{
		ResourceManagerAPI::ResourceManagerAPI(const std::string &resource_manager_url)
		{
			query_ = new Query();
			std::string final_url = query_->FollowRedictionWithNegotiate(resource_manager_url.c_str());
			resource_manager_url_ = final_url.substr(0, final_url.find_last_of('/'));
		}

		ResourceManagerAPI::~ResourceManagerAPI()
		{
			if(query_)
			{
				delete query_;
			}
		}

		std::vector<ClusterApplication*> ResourceManagerAPI::GetAllApps(const std::initializer_list<const char *> &query_parameters)
		{
			std::vector<ClusterApplication*> result;

			std::string additional_parameters = "?";
			for (auto &query_parameter : query_parameters)
			{
				additional_parameters += query_parameter;
				additional_parameters += "&";
			}
			std::string url = "ws/v1/cluster/apps" + additional_parameters;
			std::string response = Request(url.c_str());
			Json::Value root;
			bool parsing_successful = Json::Reader().parse(response.c_str(), root);
			if (!parsing_successful)
				return result;

			Json::Value applications = root.get("apps", "").get("app", "");
			size_t num_applications = applications.size();
			
			for (size_t i = 0; i < num_applications; ++i)
				result.push_back(new ClusterApplication(applications.get(i, "")));

			return result;
		}

		std::string ResourceManagerAPI::Request(const std::string &request)
		{
			CurlOutput output;
			std::string url = resource_manager_url_ + "/" + request;
			query_->ExecuteWithNegotiate(url.c_str(), &output);
			return output.data;
		}
	}
}