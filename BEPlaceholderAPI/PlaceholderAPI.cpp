#include "Global.h"
#include "PlaceholderAPI.h"
#include "ScheduleAPI.h"
#include "Helper.h"

std::unordered_map<string, PlaceholderAPI>  GlobalPAPI;
std::unordered_map<string, PlaceholderAPI>  updatePlaceholders;
#define EXPORTAPI(T) RemoteCall::exportAs(PLUGIN_NAME, Helper::ReplaceStr(#T,"RemoteCall::","") , T);

PlaceholderAPI::PlaceholderAPI(string Name, int UpdateInterval, bool AutoUpdate, bool ProcessPlayer,bool ProcessParameters,string PluginName,std::function<string(class Player*)> callback, std::function<string(class Player*, std::unordered_map<string, string>)> CallbackWithParameters) {	
	mName = "%" + Name + "%";
	mUpdateInterval = UpdateInterval;
	mAutoUpdate = AutoUpdate;
	mProcessParameters = ProcessParameters;
	mProcessPlayer = ProcessPlayer;
	mCallback = callback;
	mCallbackWithParameters = CallbackWithParameters;
	if (PluginName.empty()) {
		mPluginName = REG_PLUGIN_NAME;
	}else{
		mPluginName = PluginName;
	}
}

void PlaceholderAPI::Update(PlaceholderAPI a1) {
	Schedule::repeat([a1]() {
		if (GlobalPAPI.find(a1.mName) != GlobalPAPI.end()) {
			if (!a1.mProcessParameters) {
				GlobalPAPI.at(a1.mName).mValue = a1.mCallback(NULL);
			}
		}
		}, a1.mUpdateInterval);
}

void PlaceholderAPI::registerPlaceholder(PlaceholderAPI a1) {
	for (auto& i : GlobalPAPI) {
		if (i.second.mName == a1.mName) {
			logger.warn("Placeholder {} tried to register which is already used", i.second.mName);
			return;
		}
	}
	GlobalPAPI.emplace(std::pair{ a1.mName,a1 });
	if (a1.mUpdateInterval > 0 && a1.mAutoUpdate) {
		updatePlaceholders.emplace(std::pair{ a1.mName,a1 });
	}
}

////---------------------------------------Static------------------------------------------

void PlaceholderAPI::registerStaticPlaceholder(string name, string value, string PluginName)
{
	PlaceholderAPI a1(name, -1, false, false, false, PluginName, [value](Player* sp) {
		return value;
		}, nullptr);
	registerPlaceholder(a1);
}

void PlaceholderAPI::registerStaticPlaceholder(string name, std::function<string()> callback, string PluginName)
{
	PlaceholderAPI a1(name, -1, false, false, false, PluginName, [callback](Player* sp) {
		return callback();
		}, nullptr);
	registerPlaceholder(a1);
}
void PlaceholderAPI::registerStaticPlaceholder(string name, string(*Func)(), string PluginName)
{
	PlaceholderAPI a1(name, -1, false, false, false, PluginName, [Func](Player* sp) {
		return Func();
		}, nullptr);
	registerPlaceholder(a1);
}

void PlaceholderAPI::registerStaticPlaceholder(string name, int UpdateInterval, string(*Func)(), string PluginName)
{
	PlaceholderAPI a1(name, UpdateInterval, true, false, false, PluginName, [Func](Player* sp) {
		return Func();
		}, nullptr);
	registerPlaceholder(a1);
}

void PlaceholderAPI::registerStaticPlaceholder(string name, int UpdateInterval, std::function<string()> callback, string PluginName)
{
	PlaceholderAPI a1(name, UpdateInterval, true, false, true, PluginName, [callback](Player* sp) {
		return callback();
		}, nullptr);
	registerPlaceholder(a1);
}


//---------------------------------------Server------------------------------------------
void PlaceholderAPI::registerServerPlaceholder(string name, std::function<string()> callback, string PluginName) {
	PlaceholderAPI a1(name, -1, false, false, false, PluginName, [callback](Player* sp) {
		return callback();
		}, nullptr);
	registerPlaceholder(a1);
}

void PlaceholderAPI::registerServerPlaceholder(string name, std::function<string(std::unordered_map<string, string>)> callback, string PluginName) {
	PlaceholderAPI a1(name, -1, false, false, true, PluginName, nullptr, [callback](Player* sp, std::unordered_map<string, string> map) {
		return callback(map);
		});
	registerPlaceholder(a1);
}


//---------------------------------------Player------------------------------------------
void  PlaceholderAPI::registerPlayerPlaceholder(string name, std::function<string(class Player*)> callback,string PluginName) {
	PlaceholderAPI a1(name, -1, false, true, false ,PluginName, callback,nullptr);
	registerPlaceholder(a1);
}

void  PlaceholderAPI::registerPlayerPlaceholder(string name, std::function<string(class Player*, std::unordered_map<string, string>)> callback, string PluginName) {
	PlaceholderAPI a1(name, -1, false, true, true, PluginName, nullptr, callback);
	registerPlaceholder(a1);
}

bool PlaceholderAPI::unRegisterPlaceholder(string name) {
	string a1 = Helper::checkPAPIName(name);
	bool isremove = false;
	a1 = Helper::checkPAPIName(a1);
	if (GlobalPAPI.find(a1) != GlobalPAPI.end()) {
		GlobalPAPI.erase(a1);
		return true;
	}
	else {
		for (auto& i : GlobalPAPI) {
			if (i.second.getPluginName() == name) {
				GlobalPAPI.erase(Helper::checkPAPIName(i.first));
				isremove = true;
			}
		}
		if(isremove) return true;		
	}
	return false;
}

string PlaceholderAPI::getValue(string a1,Player* sp) {
	a1 = Helper::checkPAPIName(a1);
	if (GlobalPAPI.find(a1) != GlobalPAPI.end()) {
		auto& papi = GlobalPAPI.at(a1);
		if (!papi.mProcessParameters) {
			if (papi.mProcessPlayer) {
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
	}
	else {
		for (auto& i : GlobalPAPI) {
			if (i.second.mProcessParameters) {
				auto [out, map] = Helper::FindPlaceholder(i.first, a1);
				if (out) {
					return i.second.mCallbackWithParameters(sp, map);
				}
			}
		}
	}
	return a1;
}

string PlaceholderAPI::getValue(string a1) {
	a1 = Helper::checkPAPIName(a1);	
	if (GlobalPAPI.find(a1) != GlobalPAPI.end()) {
		auto& papi = GlobalPAPI.at(a1);
		if (!papi.mProcessParameters) {
			if (!papi.mProcessPlayer) {
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
	}
	else {
		for (auto& i : GlobalPAPI) {
			if (i.second.mProcessParameters) {
				auto [out, map] = Helper::FindPlaceholder(i.first, a1);
				if (out) {
					return i.second.mCallbackWithParameters(nullptr, map);
				}
			}
		}
	}
	return a1;
}

void PlaceholderAPI::translateString(string& a0,Player* sp) {
	auto list = Helper::getPercentage(a0);
	for (auto& i : list) {
		ReplaceStr(a0, i, getValue(i, sp));
	}
}


std::unordered_set<string> PlaceholderAPI::getPAPIPluginsList() {
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

//---------------------------------------RemoteCall------------------------------------------
namespace RemoteCall {
	std::string GetValue(std::string const& from)
	{
		return	PlaceholderAPI::getValue(from);
	}
	std::string GetValueWithPlayer(std::string const& a1, std::string const& a2)
	{
		return	PlaceholderAPI::getValue(a1, Level::getPlayer(a2));
	}

	std::string registerPlayerPlaceholder(std::string const& PluginName, std::string const& FuncName, std::string const& PAPIName)
	{
		if (RemoteCall::hasFunc(PluginName, FuncName)) {
			if (Helper::isParameters(PAPIName)) {
				auto Call = RemoteCall::importAs<string(std::string const& arg, std::unordered_map<string, string>)>(PluginName, FuncName);
				PlaceholderAPI::registerPlayerPlaceholder(PAPIName, [Call](Player* sp, std::unordered_map<string, string> map) {
					return Call(sp->getXuid(), map);
					}, PluginName);
			}
			else {
				auto Call = RemoteCall::importAs<string(std::string const& arg)>(PluginName, FuncName);
				PlaceholderAPI::registerPlayerPlaceholder(PAPIName, [Call](Player* sp) {
					return Call(sp->getXuid());
					}, PluginName);
			}
		}
		else {
			logger.error("Function no find({}:{})", PluginName, FuncName);
			return "Function no find";
		}
		return "Register Success";
	}
	
	std::string registerServerPlaceholder(std::string const& PluginName, std::string const& FuncName, std::string const& PAPIName)
	{
		if (RemoteCall::hasFunc(PluginName, FuncName)) {
			if (Helper::isParameters(PAPIName)) {
				auto Call = RemoteCall::importAs<string(std::unordered_map<string, string>)>(PluginName, FuncName);
				PlaceholderAPI::registerServerPlaceholder(PAPIName, [Call](std::unordered_map<string, string> map) {
					return Call(map);
					}, PluginName);
			}
			else {
				auto Call = RemoteCall::importAs<string()>(PluginName, FuncName);
				PlaceholderAPI::registerServerPlaceholder(PAPIName, [Call]() {
					return Call();
					}, PluginName);
			}
		}
		else {
			logger.error("Function no find({}:{})", PluginName, FuncName);
			return "Function no find";
		}
		return "Register Success";
	}
	
	std::string registerStaticPlaceholder(std::string const& PluginName, std::string const& FuncName, std::string const& PAPIName,int num)
	{
		if (RemoteCall::hasFunc(PluginName, FuncName)) {
			if (Helper::isParameters(PAPIName)) {
				auto Call = RemoteCall::importAs<string()>(PluginName, FuncName);
				if (num == -1) {
					PlaceholderAPI::registerStaticPlaceholder(PAPIName, [Call] {
						return Call();
						}, PluginName);
				}
				else {
					PlaceholderAPI::registerStaticPlaceholder(PAPIName, num, [Call] {
						return Call();
						}, PluginName);
				}
			}
		}
		else{
			logger.error("Function no find({}:{})", PluginName, FuncName);
			return "Function no find";
		}
		return "Register Success";
	}

	std::string translateString(std::string const& str, std::string const& xuid) 
	{
		return	PlaceholderAPI::getValue(str, Level::getPlayer(xuid));
	}

	bool unRegisterPlaceholder(std::string const& str)
	{
		return PlaceholderAPI::unRegisterPlaceholder(str);
	}
}

void EventInit() {

	Event::PlayerChatEvent::subscribe_ref([](Event::PlayerChatEvent& ev) {
		if (Settings::Chat::Enabled) {
			auto& str = ev.mMessage;
			//if (Settings::Chat::CanUseBrackets) {
			//	Helper::Backets2Percentage(str);
			//}
			PlaceholderAPI::translateString(str, ev.mPlayer);
			ev.mMessage = str;
		}
		return true;
		});
}

void  RegPAPInit();
void initSchedule();

void PAPIinit() {
	Translation::load("plugins/BEPlaceholderAPI/lang/"+ Settings::LangCode +".json");
	updatePlaceholder();
	EXPORTAPI(RemoteCall::registerPlayerPlaceholder);
	EXPORTAPI(RemoteCall::registerServerPlaceholder);
	EXPORTAPI(RemoteCall::registerStaticPlaceholder);
	EXPORTAPI(RemoteCall::GetValue);
	EXPORTAPI(RemoteCall::GetValueWithPlayer);
	EXPORTAPI(RemoteCall::translateString);
	EXPORTAPI(RemoteCall::unRegisterPlaceholder);
	EventInit();
	RegPAPInit();
	initSchedule();
	
}