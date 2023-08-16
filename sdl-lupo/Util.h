#pragma once
#include <string>

namespace Util {

	std::string mString(const char data[8]) {
        char d[9];
        d[8] = 0;
        memcpy(d, data, 8);
        for (int i = 0; i < 8; i++)
        {
            d[i] = static_cast<char>(toupper(d[i]));
        }
        return std::string(d);
	}

};

