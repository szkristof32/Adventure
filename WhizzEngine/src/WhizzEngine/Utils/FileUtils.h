#pragma once

#include <string>

#include "WhizzEngine/Core/Core.h"

namespace WhizzEngine {

	std::string ReadFile(std::string path)
	{
		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				WZ_CORE_ERROR("Could not read from file '{0}'", path);
			}
		}
		else
		{
			WZ_CORE_ERROR("Could not open file '{0}'", path);
		}

		return result;
	}

}