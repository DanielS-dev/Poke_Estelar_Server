// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"
#include "xmlErro.hpp"

void printXMLError(const std::string& where, const std::string& fileName, const pugi::xml_parse_result& result)
{
	std::cout << '[' << where << "] Failed to load " << fileName << ": " << result.description() << std::endl;

	FILE* file = fopen(fileName.c_str(), "rb");
	if (!file) {
		return;
	}

	char buffer[32768];
	uint32_t currentLine = 1;
	std::string line;

	size_t offset = static_cast<size_t>(result.offset);
	size_t lineOffsetPosition = 0;
	size_t index = 0;
	size_t bytes;
	do {
		bytes = fread(buffer, 1, 32768, file);
		for (size_t i = 0; i < bytes; ++i) {
			char ch = buffer[i];
			if (ch == '\n') {
				if ((index + i) >= offset) {
					lineOffsetPosition = line.length() - ((index + i) - offset);
					bytes = 0;
					break;
				}
				++currentLine;
				line.clear();
			} else {
				line.push_back(ch);
			}
		}
		index += bytes;
	} while (bytes == 32768);
	fclose(file);

	std::cout << "Line " << currentLine << ':' << std::endl;
	std::cout << line << std::endl;
	for (size_t i = 0; i < lineOffsetPosition; i++) {
		if (line[i] == '\t') {
			std::cout << '\t';
		} else {
			std::cout << ' ';
		}
	}
	std::cout << '^' << std::endl;
}
