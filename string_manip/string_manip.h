#pragma once

#include <vector>
#include <sstream>

namespace bps
{
	std::vector<std::string> split(const std::string& s, char delim)
	{
		std::vector<std::string> elems;
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim))
		{
			// Skip empty strings
			if (item.compare("") != 0)
				elems.push_back(item);
		}
		return elems;
	};
}

