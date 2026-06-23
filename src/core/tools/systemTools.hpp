// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_SYSTEM_TOOLS_H_5F9A9742DA194628830AA1C64909AE43
#define FS_SYSTEM_TOOLS_H_5F9A9742DA194628830AA1C64909AE43

#include <chrono>
#include <cstdint>

inline bool hasBitSet(uint32_t flag, uint32_t flags) {
	return (flags & flag) != 0;
}

inline int64_t OTSYS_TIME()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

#endif
