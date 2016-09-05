#pragma once

#include <vector>
#include <string>

std::vector<std::string> &Split(const std::string &s, const std::string &delim, std::vector<std::string> &elems);

std::vector<std::string> Split(const std::string &s, const std::string &delim);