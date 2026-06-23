// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_AUTHS_H_5F9A9742DA194628830AA1C64909AE43
#define FS_AUTHS_H_5F9A9742DA194628830AA1C64909AE43

#include <cstdint>
#include <string>

std::string transformToSHA1(const std::string& input);
std::string generateToken(const std::string& secret, uint32_t ticks);

#endif
