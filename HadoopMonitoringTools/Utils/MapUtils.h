#pragma once

#include <map>

namespace Hadoop
{
	namespace Tools
	{
		template<typename A, typename B>
		std::pair<B, A> FlipPair(const std::pair<A, B> &p)
		{
			return std::pair<B, A>(p.second, p.first);
		}

		template<typename A, typename B>
		std::multimap<B, A> FlipMap(const std::map<A, B> &src)
		{
			std::multimap<B, A> dst;
			std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), FlipPair<A, B>);
			return dst;
		}
	}
}