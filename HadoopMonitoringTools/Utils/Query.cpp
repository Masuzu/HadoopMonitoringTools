#include "Query.h"

#include "StringUtils.h"

namespace Hadoop
{
	namespace Tools
	{
		CurlOutput::CurlOutput()
		{
			length = 0;
			data = (char*)malloc(length+1);
			if (data == nullptr) {
				fprintf(stderr, "malloc() failed\n");
				exit(EXIT_FAILURE);
			}
			data[0] = '\0';
		}

		std::string CurlOutput::GetHeaderValue(const std::string &key)
		{
			std::vector<std::string> splits = Split(data, "\r\n");
			size_t key_length = key.length();
			for(const auto &split : splits)
			{
				if (split.compare(0, key_length, key) == 0)
					return split.substr(split.find(':') + 2);
			}
			return "";
		}

#pragma region Callbacks
		size_t __cdecl OutputCallback(void *buffer, size_t size, size_t nmemb, void *userdata)
		{
			/* received output is nmemb * size long in 'buffer' NOT ZERO TERMINATED */
			size_t output_size = size * nmemb;
			struct CurlOutput *s = (struct CurlOutput*)userdata;
			size_t new_len = s->length + output_size;
			s->data = (char*)realloc(s->data, new_len+1);
			if (s->data == NULL) {
				fprintf(stderr, "realloc() failed\n");
				exit(EXIT_FAILURE);
			}
			memcpy(s->data+s->length, buffer, output_size);
			s->data[new_len] = '\0';
			s->length = new_len;

			return output_size;
		}

		size_t __cdecl NoopCallback(void *ptr, size_t size, size_t nmemb, void *userdata)
		{
			return size*nmemb;
		}

#pragma endregion Callbacks

		static void BindOutputAndHeaderAndExecute(CURL *curl, CurlOutput *output, CurlOutput *header)
		{
			if (output)
			{
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &OutputCallback);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)output);
			}
			else
			{
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &NoopCallback);
			}
			if (header)
			{
				curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &OutputCallback);
				curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void*)header);
			}
			else
			{
				curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &NoopCallback);
			}

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}

		void Query::ExecutePutWithNegotiate(const char *url, const std::string &body, CurlOutput *output, CurlOutput *header)
		{
			CURL *curl = curl_easy_init();
			if(curl)
			{
				curl_easy_setopt(curl, CURLOPT_USERNAME, "");	// Enable any user
				curl_easy_setopt(curl, CURLOPT_URL, url);  
				curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_NEGOTIATE);
				curl_easy_setopt(curl, CURLOPT_PUT);

				curl_slist *http_header = nullptr;
				http_header = curl_slist_append(http_header, "Content-Type: application/json");
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_header);
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

				BindOutputAndHeaderAndExecute(curl, output, header);
			}
		}

		void Query::ExecuteWithNegotiate2(const char *url, CurlOutput *output, CurlOutput *header)
		{
			CURL *curl = curl_easy_init();
			if (curl)
			{
				curl_easy_setopt(curl, CURLOPT_USERNAME, "");	// Enable any user
				curl_easy_setopt(curl, CURLOPT_URL, url);
				curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_NEGOTIATE);

				BindOutputAndHeaderAndExecute(curl, output, header);
			}
		}

		std::string Query::FollowRedictionWithNegotiate(const char *url, size_t max_retries)
		{
			std::string location = url;
			std::string final_url = url;
			for(size_t attempt = 0; attempt < max_retries; ++attempt)
			{
				struct CurlOutput header;
				ExecuteWithNegotiate2(location.c_str(), nullptr, &header);
				location = header.GetHeaderValue("Location");
				if(!location.empty() && location != final_url)
					final_url = location;
				else
				{
					std::string refresh_url = header.GetHeaderValue("Refresh");
					if (!refresh_url.empty() && refresh_url != final_url)
					{
						size_t start_pos = refresh_url.find_first_of("url=") + 4;
						final_url = refresh_url.substr(start_pos);
					}
					else
						break;
				}
			}
			return final_url;
		}
	}
}