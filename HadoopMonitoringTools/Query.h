#pragma once

#include <curl/curl.h>
#include <string>

namespace Hadoop
{
	namespace Tools
	{
		struct CurlOutput {
			char *data;
			size_t length;

			CurlOutput();

			std::string GetHeaderValue(const std::string &key);
		};

		class Query
		{
		protected:
			CURL* curl_;

		public:
			Query();
			virtual ~Query();

			void ExecuteWithNegotiate(const char *url, CurlOutput *output = nullptr, CurlOutput *header = nullptr);

			// Return the final URL starting from 'url' and following up to 'max_retries' redirections
			std::string FollowRedictionWithNegotiate(const char *url, size_t max_retries = 50);
		};
	}
}