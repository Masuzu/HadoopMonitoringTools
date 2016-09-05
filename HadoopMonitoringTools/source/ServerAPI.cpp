#include "ServerAPI.h"

#include "ClusterApplication.h"
#include "json/json.h"

namespace Hadoop
{
	namespace Tools
	{
		ServerAPI::ServerAPI(const std::string &server_url)
		{
			query_ = new Query();
			std::string final_url = query_->FollowRedictionWithNegotiate(server_url.c_str());
			server_url_ = final_url.substr(0, final_url.find_last_of('/'));
		}

		ServerAPI::~ServerAPI()
		{
			if (query_)
			{
				delete query_;
			}
		}

		std::string ServerAPI::Request(const std::string &request, const std::initializer_list<const char *> &query_parameters)
		{
			CurlOutput output;

			std::string additional_parameters = "?";
			for (auto &query_parameter : query_parameters)
			{
				additional_parameters += query_parameter;
				additional_parameters += "&";
			}

			std::string url = server_url_ + "/" + request + additional_parameters;
			query_->ExecuteWithNegotiate2(url.c_str(), &output);
			return output.data;
		}
	}
}