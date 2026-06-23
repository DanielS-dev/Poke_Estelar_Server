// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_CHECKSUM_H_5F9A9742DA194628830AA1C64909AE43
#define FS_CHECKSUM_H_5F9A9742DA194628830AA1C64909AE43

#include <cstddef>
#include <cstdint>

uint32_t adlerChecksum(const uint8_t* data, size_t len);

#endif