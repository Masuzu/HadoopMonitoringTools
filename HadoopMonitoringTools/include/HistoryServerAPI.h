#pragma once

#include "ServerAPI.h"

namespace Hadoop
{
	namespace Tools
	{
		class HistoryServerAPI : public ServerAPI
		{
		public:
			HistoryServerAPI(const std::string &history_server_url);
			virtual ~HistoryServerAPI();

			// See https://hadoop.apache.org/docs/r2.4.1/hadoop-yarn/hadoop-yarn-site/HistoryServerRest.html#Jobs_API for a list of supported query parameters
			std::vector<ClusterApplication*> GetAllApps(const std::initializer_list<const char *> &query_parameters);

			virtual ClusterApplication *GetApplication(const std::string &id) override;
		};
	}
}