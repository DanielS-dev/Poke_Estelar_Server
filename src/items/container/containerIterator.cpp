// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../container.hpp"

ContainerIterator Container::iterator() const
{
	ContainerIterator cit;
	if (!itemlist.empty()) {
		cit.over.push_back(this);
		cit.cur = itemlist.begin();
	}
	return cit;
}

Item* ContainerIterator::operator*()
{
	return *cur;
}

void ContainerIterator::advance()
{
	if (Item* i = *cur) {
		if (Container* c = i->getContainer()) {
			if (!c->empty()) {
				over.push_back(c);
			}
		}
	}

	++cur;

	if (cur == over.front()->itemlist.end()) {
		over.pop_front();
		if (!over.empty()) {
			cur = over.front()->itemlist.begin();
		}
	}
}

