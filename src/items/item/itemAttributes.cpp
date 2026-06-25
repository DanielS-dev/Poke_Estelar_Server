// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../item.hpp"

std::string ItemAttributes::emptyString;

const std::string& ItemAttributes::getStrAttr(itemAttrTypes type) const
{
	if (!isStrAttrType(type)) {
		return emptyString;
	}

	const Attribute* attr = getExistingAttr(type);
	if (!attr) {
		return emptyString;
	}
	return *attr->value.string;
}

void ItemAttributes::setStrAttr(itemAttrTypes type, const std::string& value)
{
	if (!isStrAttrType(type)) {
		return;
	}

	if (value.empty()) {
		return;
	}

	Attribute& attr = getAttr(type);
	delete attr.value.string;
	attr.value.string = new std::string(value);
}

void ItemAttributes::removeAttribute(itemAttrTypes type)
{
	if (!hasAttribute(type)) {
		return;
	}

	auto prev_it = attributes.cbegin();
	if ((*prev_it).type == type) {
		attributes.pop_front();
	} else {
		auto it = prev_it, end = attributes.cend();
		while (++it != end) {
			if ((*it).type == type) {
				attributes.erase_after(prev_it);
				break;
			}
			prev_it = it;
		}
	}
	attributeBits &= ~type;
}

int64_t ItemAttributes::getIntAttr(itemAttrTypes type) const
{
	if (!isIntAttrType(type)) {
		return 0;
	}

	const Attribute* attr = getExistingAttr(type);
	if (!attr) {
		return 0;
	}
	return attr->value.integer;
}

void ItemAttributes::setIntAttr(itemAttrTypes type, int64_t value)
{
	if (!isIntAttrType(type)) {
		return;
	}

	getAttr(type).value.integer = value;
}

void ItemAttributes::increaseIntAttr(itemAttrTypes type, int64_t value)
{
	if (!isIntAttrType(type)) {
		return;
	}

	getAttr(type).value.integer += value;
}

const ItemAttributes::Attribute* ItemAttributes::getExistingAttr(itemAttrTypes type) const
{
	if (hasAttribute(type)) {
		for (const Attribute& attribute : attributes) {
			if (attribute.type == type) {
				return &attribute;
			}
		}
	}
	return nullptr;
}

ItemAttributes::Attribute& ItemAttributes::getAttr(itemAttrTypes type)
{
	if (hasAttribute(type)) {
		for (Attribute& attribute : attributes) {
			if (attribute.type == type) {
				return attribute;
			}
		}
	}

	attributeBits |= type;
	attributes.emplace_front(type);
	return attributes.front();
}
