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
		public:
			Query() {}
			virtual ~Query() {}

			void ExecutePutWithNegotiate(const char *url, const std::string &body, CurlOutput *output = nullptr, CurlOutput *header = nullptr);
			void ExecuteWithNegotiate2(const char *url, CurlOutput *output = nullptr, CurlOutput *header = nullptr);

			// Return the final URL starting from 'url' and following up to 'max_retries' redirections
			std::string FollowRedictionWithNegotiate(const char *url, size_t max_retries = 50);
		};
	}
}