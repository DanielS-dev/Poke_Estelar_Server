// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "baseevents.hpp"

#include "../core/logger.hpp"
#include "../core/pugicast.hpp"
#include "../core/tools/systemTools.hpp"
#include "../core/tools/xmlErro.hpp"

extern LuaEnvironment g_luaEnvironment;

bool BaseEvents::loadFromXml()
{
	if (loaded) {
		LOG_ERROR("Scripts", "Attempted to load " + getScriptBaseName() + " twice.");
		return false;
	}

	std::string scriptsName = getScriptBaseName();
	std::string basePath = "data/" + scriptsName + "/";
	if (getScriptInterface().loadFile(basePath + "lib/" + scriptsName + ".lua") == -1) {
		LOG_WARN("Scripts", "Could not load " + basePath + "lib/" + scriptsName + ".lua");
	}

	std::string filename = basePath + scriptsName + ".xml";

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.c_str());
	if (!result) {
		printXMLError("Error - BaseEvents::loadFromXml", filename, result);
		return false;
	}

	loaded = true;
	uint32_t configuredEvents = 0;
	uint32_t loadedEvents = 0;

	for (auto node : doc.child(scriptsName.c_str()).children()) {
		Event* event = getEvent(node.name());
		if (!event) {
			continue;
		}
		++configuredEvents;

		if (!event->configureEvent(node)) {
			LOG_WARN("Scripts", "Failed to configure " + scriptsName + " event node <" + std::string(node.name()) + ">.");
			delete event;
			continue;
		}

		bool success;

		pugi::xml_attribute scriptAttribute = node.attribute("script");
		if (scriptAttribute) {
			std::string scriptFile = "scripts/" + std::string(scriptAttribute.as_string());
			success = event->checkScript(basePath, scriptsName, scriptFile) && event->loadScript(basePath + scriptFile);
		} else {
			success = event->loadFunction(node.attribute("function"));
		}

		if (!success || !registerEvent(event, node)) {
			delete event;
			continue;
		}
		++loadedEvents;
	}

	LOG_INFO("Scripts", "Loaded " + std::to_string(loadedEvents) + "/" + std::to_string(configuredEvents) +
		" " + scriptsName + " events from " + filename);
	return true;
}

bool BaseEvents::reload()
{
	loaded = false;
	clear();
	return loadFromXml();
}

Event::Event(LuaScriptInterface* interface) : scriptInterface(interface) {}

Event::Event(const Event* copy) :
	scripted(copy->scripted), scriptId(copy->scriptId), scriptInterface(copy->scriptInterface) {}

bool Event::checkScript(const std::string& basePath, const std::string& scriptsName, const std::string& scriptFile) const
{
	LuaScriptInterface* testInterface = g_luaEnvironment.getTestInterface();
	testInterface->reInitState();

	if (testInterface->loadFile(std::string(basePath + "lib/" + scriptsName + ".lua")) == -1) {
		LOG_WARN("Scripts", "Could not load " + basePath + "lib/" + scriptsName + ".lua while validating " + scriptFile);
	}

	if (scriptId != 0) {
		LOG_ERROR("Scripts", "Validation failed for " + scriptFile + ": scriptId already set to " + std::to_string(scriptId));
		return false;
	}

	if (testInterface->loadFile(basePath + scriptFile) == -1) {
		LOG_WARN("Scripts", "Could not load script during validation: " + scriptFile);
		LOG_ERROR("Lua", testInterface->getLastLuaError());
		return false;
	}

	int32_t id = testInterface->getEvent(getScriptEventName());
	if (id == -1) {
		LOG_WARN("Scripts", "Event " + getScriptEventName() + " not found in " + scriptFile);
		return false;
	}
	return true;
}

bool Event::loadScript(const std::string& scriptFile)
{
	if (!scriptInterface || scriptId != 0) {
		LOG_ERROR("Scripts", "Failed to load " + scriptFile + ": invalid script interface or scriptId=" + std::to_string(scriptId));
		return false;
	}

	if (scriptInterface->loadFile(scriptFile) == -1) {
		LOG_WARN("Scripts", "Could not load script: " + scriptFile);
		LOG_ERROR("Lua", scriptInterface->getLastLuaError());
		return false;
	}

	int32_t id = scriptInterface->getEvent(getScriptEventName());
	if (id == -1) {
		LOG_WARN("Scripts", "Event " + getScriptEventName() + " not found in " + scriptFile);
		return false;
	}

	scripted = true;
	scriptId = id;
	return true;
}

bool CallBack::loadCallBack(LuaScriptInterface* interface, const std::string& name)
{
	if (!interface) {
		LOG_ERROR("Scripts", "Failed to load callback " + name + ": scriptInterface is null.");
		return false;
	}

	scriptInterface = interface;

	int32_t id = scriptInterface->getEvent(name.c_str());
	if (id == -1) {
		LOG_WARN("Scripts", "Callback event " + name + " not found.");
		return false;
	}

	callbackName = name;
	scriptId = id;
	loaded = true;
	return true;
}
