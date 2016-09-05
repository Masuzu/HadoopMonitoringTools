#pragma once

#include "Utils/Query.h"
#include "ClusterApplication.h"

#include <vector>
#include <initializer_list>

namespace Hadoop
{
	namespace Tools
	{
		class ServerAPI
		{
		protected:
			Query *query_;
			// Final server URL after following the possible redirections
			std::string server_url_;

		public:
			ServerAPI(const std::string &history_server_url);
			virtual ~ServerAPI();

			virtual std::vector<ClusterApplication*> GetAllApps(const std::initializer_list<const char *> &query_parameters) = 0;
			virtual ClusterApplication *GetApplication(const std::string &id) { return nullptr; }

			__forceinline std::string Request(const std::string &request)
			{
				return Request(request, {});
			}
			std::string Request(const std::string &request, const std::initializer_list<const char *> &query_parameters);
		};
	}
}