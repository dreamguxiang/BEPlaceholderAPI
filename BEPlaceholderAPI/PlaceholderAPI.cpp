#include "Global.h"
#include "PlaceholderAPI.h"
#include "ScheduleAPI.h"
#include "Helper.h"
std::unordered_map<string, PlaceholderAPI>  GlobalPAPI;
std::unordered_map<string, PlaceholderAPI>  updatePlaceholders;
#define EXPORTAPI(T) RemoteCall::exportAs(PLUGIN_NAME, Helper::ReplaceStr(#T,"RemoteCall::","") , T);

PlaceholderAPI::PlaceholderAPI(string Name, int UpdateInterval, bool AutoUpdate, bool ProcessParameters,string PluginName,std::function<string(class Player*)> callback) {
	for (auto& i : GlobalPAPI) {
		if (i.second.mName == Name) {
			logger.warn("Placeholder {} tried to register which is already used", i.second.mName);
			return;
		}
	}
	
	mName = "{"+Name+"}";
	mUpdateInterval = UpdateInterval;
	mAutoUpdate = AutoUpdate;
	mProcessParameters = ProcessParameters;
	mCallback = callback;
	if (PluginName.empty()) {
		mPluginName = REG_PLUGIN_NAME;
	}else{
		mPluginName = PluginName;
	}
}

void PlaceholderAPI::Update(PlaceholderAPI a1) {
	Schedule::repeat([a1]() {
		if (GlobalPAPI.find(a1.mName) != GlobalPAPI.end()) {
			GlobalPAPI.at(a1.mName).mValue = a1.mCallback(nullptr);
		}
		}, a1.mUpdateInterval);
}

void PlaceholderAPI::registerPlaceholder(PlaceholderAPI a1) {
	GlobalPAPI.emplace(std::pair{ a1.mName,a1 });

	if (a1.mUpdateInterval > 0 && a1.mAutoUpdate) {
		updatePlaceholders.emplace(std::pair{ a1.mName,a1 });
	}
}

void PlaceholderAPI::registerStaticPlaceholder(string name, string(*Func)(), string PluginName)
{
	PlaceholderAPI a1(name, -1, false, false,"", [Func](Player* sp) {
		return Func();
		});
	registerPlaceholder(a1);
}

void PlaceholderAPI::registerStaticPlaceholder(string name, string value, string PluginName)
{
	PlaceholderAPI a1(name, -1, false, false, "", [value](Player* sp) {
		return value;
		});
	registerPlaceholder(a1);
}

void PlaceholderAPI::registerStaticPlaceholder(string name, int UpdateInterval, string(*Func)(), string PluginName)
{
	PlaceholderAPI a1(name, UpdateInterval, true, false, "", [Func](Player* sp) {
		return Func();
		});
	registerPlaceholder(a1);
}

void PlaceholderAPI::registerServerPlaceholder(string name, std::function<string()> callback, string PluginName) {
	PlaceholderAPI a1(name, -1, false, false, "", [callback](Player* sp) {
		return callback();
		});
	registerPlaceholder(a1);
}


void  PlaceholderAPI::registerPlayerPlaceholder(string name, std::function<string(class Player*)> callback,string PluginName) {
	PlaceholderAPI a1(name, -1, false, true, PluginName, callback);
	registerPlaceholder(a1);
}

//void  PlaceholderAPI::registerPlayerPlaceholder(string name, int UpdateInterval, bool AutoUpdate, std::function<string(class Player*)> callback) {
//	PlaceholderAPI a1(name, UpdateInterval, AutoUpdate, true, callback);
//	registerPlaceholder(a1);
//}

string PlaceholderAPI::getValue(string a1,Player* sp) {
	a1 = Helper::checkPAPIName(a1);
	if (GlobalPAPI.find(a1) != GlobalPAPI.end()) {
		auto& papi = GlobalPAPI.at(a1);
		if (papi.mProcessParameters) {
			return GlobalPAPI.at(a1).mCallback(sp);
		}
		else {
			if (papi.mAutoUpdate) {
				return papi.mValue;
			}
			else {
				return papi.mCallback(nullptr);
			}
		}
	}
	return "NULL";
}

string PlaceholderAPI::getValue(string a1) {
	a1 = Helper::checkPAPIName(a1);
	
	if (GlobalPAPI.find(a1) != GlobalPAPI.end()) {
		auto& papi = GlobalPAPI.at(a1);
		if (!papi.mProcessParameters) {
			if (papi.mAutoUpdate) {
				return papi.mValue;
			}
			else {
				return papi.mCallback(nullptr);
			}
		}
		else
			return "Unknown Player";
	}
	return "NULL";
}

void PlaceholderAPI::translateString(string& a0,Player* sp) {
	for (auto& i : GlobalPAPI) {
		ReplaceStr(a0, i.first, getValue(i.first, sp));
	}
	
}
std::unordered_set<string> PlaceholderAPI::getPAPIList() {
	std::unordered_set<string> list;
	for (auto& i : GlobalPAPI) {
		list.insert(i.second.getPluginName());
	}
	return list;
}

std::vector<PlaceholderAPI> PlaceholderAPI::getPAPIInfoList() {
	std::vector<PlaceholderAPI> list;
	for (auto& i : GlobalPAPI) {
		list.push_back(i.second);
	}
	return list;
}

void updatePlaceholder() {
	Schedule::repeat([] {
		for (auto& i : updatePlaceholders) {
			PlaceholderAPI::Update(i.second);
		}
		updatePlaceholders.clear();
		},20);
}


namespace RemoteCall {
	std::string GetValue(std::string const& from)
	{
		return	PlaceholderAPI::getValue(from);
	}
	std::string GetValueWithPlayer(std::string const& a1, std::string const& a2)
	{
		return	PlaceholderAPI::getValue(a1, Level::getPlayer(a2));
	}

	std::string registerInit(std::string const& PluginName, std::string const& FuncName, std::string const& PAPIName)
	{
		auto Call = RemoteCall::importAs<string(std::string const& arg)>(PluginName, FuncName);
		PlaceholderAPI::registerPlayerPlaceholder(PAPIName, [Call](Player* sp) {
			return Call(sp->getXuid());
			}, PluginName);
		return "success";
	}
}

void debug() {

	Event::PlayerChatEvent::subscribe_ref([](Event::PlayerChatEvent& ev) {
		auto& str = ev.mMessage;
		PlaceholderAPI::translateString(str, ev.mPlayer);
		ev.mMessage = str;
		return true;
		});

}


void PAPIinit() {
	
	updatePlaceholder();
	EXPORTAPI(RemoteCall::registerInit);
	EXPORTAPI(RemoteCall::GetValue);
	EXPORTAPI(RemoteCall::GetValueWithPlayer);
	debug();
}