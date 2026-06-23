// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"
#include "dateTools.hpp"


std::string formatDate(time_t time)
{
	const tm* tms = localtime(&time);
	if (!tms) {
		return {};
	}

	char buffer[20];
	int res = sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", tms->tm_mday, tms->tm_mon + 1, tms->tm_year + 1900, tms->tm_hour, tms->tm_min, tms->tm_sec);
	if (res < 0) {
		return {};
	}
	return {buffer, 19};
}

std::string formatDateShort(time_t time)
{
	const tm* tms = localtime(&time);
	if (!tms) {
		return {};
	}

	char buffer[12];
	size_t res = strftime(buffer, 12, "%d %b %Y", tms);
	if (res == 0) {
		return {};
	}
	return {buffer, 11};
}
