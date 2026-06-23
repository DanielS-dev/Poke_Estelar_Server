// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_RANDOM_H_5F9A9742DA194628830AA1C64909AE43
#define FS_RANDOM_H_5F9A9742DA194628830AA1C64909AE43

#include <random>
#include <cstdint>

std::mt19937& getRandomGenerator();
int32_t uniform_random(int32_t minNumber, int32_t maxNumber);
int32_t normal_random(int32_t minNumber, int32_t maxNumber);
bool boolean_random(double probability = 0.5);

#endif