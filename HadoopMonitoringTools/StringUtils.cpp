#include "StringUtils.h"

#include <sstream>

std::vector<std::string> &Split(const std::string &s, const std::string &delimiter, std::vector<std::string> &elems)
{
	size_t pos_begin = 0;
	size_t pos_end = 0;
	size_t delimiter_length = delimiter.length();
	std::string token;
	while ((pos_end = s.find(delimiter, pos_begin)) != std::string::npos) {
		if(pos_begin != pos_end)
		{
			token = s.substr(pos_begin, pos_end - pos_begin);
			elems.push_back(token);
		}
		pos_begin += token.length() + delimiter_length;
	}
	return elems;
}


std::vector<std::string> Split(const std::string &s, const std::string &delimiter)
{
	std::vector<std::string> elems;
	Split(s, delimiter, elems);
	return elems;
}
