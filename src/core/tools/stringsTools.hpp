// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_STRINGS_TOOLS_H_5F9A9742DA194628830AA1C64909AE43
#define FS_STRINGS_TOOLS_H_5F9A9742DA194628830AA1C64909AE43

#include <cstdint>
#include <string>
#include <vector>

typedef std::vector<std::string> StringVec;
typedef std::vector<int32_t> IntegerVec;

void replaceString(std::string& str, const std::string& sought, const std::string& replacement);
void trim_right(std::string& source, char t);
void trim_left(std::string& source, char t);
void toLowerCaseString(std::string& source);
std::string asLowerCaseString(std::string source);
std::string asUpperCaseString(std::string source);
void trimString(std::string& str);
StringVec explodeString(const std::string& inString, const std::string& separator, int32_t limit = -1);
IntegerVec vectorAtoi(const StringVec& stringVector);
std::string getFirstLine(const std::string& str);
std::string ucfirst(std::string str);
std::string ucwords(std::string str);
bool booleanString(const std::string& str);
std::string convertIPToString(uint32_t ip);

#endif
