// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../container.hpp"

std::string Container::getContentDescription() const
{
	std::ostringstream os;
	return getContentDescription(os).str();
}

std::ostringstream& Container::getContentDescription(std::ostringstream& os) const
{
	bool firstitem = true;
	for (ContainerIterator it = iterator(); it.hasNext(); it.advance()) {
		Item* item = *it;

		Container* container = item->getContainer();
		if (container && !container->empty()) {
			continue;
		}

		if (firstitem) {
			firstitem = false;
		} else {
			os << ", ";
		}

		os << item->getNameDescription();
	}

	if (firstitem) {
		os << "nothing";
	}
	return os;
}

Item* Container::getItemByIndex(size_t index) const
{
	if (index >= size()) {
		return nullptr;
	}
	return itemlist[index];
}

uint32_t Container::getItemHoldingCount() const
{
	uint32_t counter = 0;
	for (ContainerIterator it = iterator(); it.hasNext(); it.advance()) {
		++counter;
	}
	return counter;
}

bool Container::isHoldingItem(const Item* item) const
{
	for (ContainerIterator it = iterator(); it.hasNext(); it.advance()) {
		if (*it == item) {
			return true;
		}
	}
	return false;
}

