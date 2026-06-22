// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_PUGICAST_H_07810DF7954D411EB14A16C3ED2A7548
#define FS_PUGICAST_H_07810DF7954D411EB14A16C3ED2A7548

#include <boost/lexical_cast.hpp>

namespace pugi {
	template<typename T>
	T cast(const pugi::char_t* str)
	{
		T value;
		try {
			value = boost::lexical_cast<T>(str);
		} catch (boost::bad_lexical_cast&) {
			value = T();
		}
		return value;
	}
}

#endif
