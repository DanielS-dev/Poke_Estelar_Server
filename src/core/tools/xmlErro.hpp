// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_XML_ERRO_H_5F9A9742DA194628830AA1C64909AE43
#define FS_XML_ERRO_H_5F9A9742DA194628830AA1C64909AE43

#include <string>

#include <pugixml.hpp>

void printXMLError(const std::string& where, const std::string& fileName, const pugi::xml_parse_result& result);

#endif
