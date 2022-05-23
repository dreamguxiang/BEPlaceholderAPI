#pragma once
#include "Global.h"
#include <DynamicCommandAPI.h>
#define REG_PLUGIN_NAME PLUGIN_NAME
class PlaceholderAPI {
public:
	string mValue;
	string mName;
private:
	string mPluginName;
	int mUpdateInterval;
	bool mAutoUpdate;
	bool mProcessPlayer;
	bool mProcessParameters;
	std::function<string(class Player*)>  mCallback;
	std::function<string(class Player*,std::unordered_map<string,string>)>  mCallbackWithParameters;
	
public:
	PlaceholderAPI() {};
	PlaceholderAPI(string Name,int UpdateInterval,bool AutoUpdate,bool mProcessPlayer, bool mProcessParameters ,string PluginName,std::function<string(class Player*)> callback, std::function<string(class Player*, std::unordered_map<string, string>)> CallbackWithParameters);
	~PlaceholderAPI() { };
	
	static void registerPlaceholder(PlaceholderAPI a0);
	static string getValue(string name,Player* sp);
	static string getValue(string name);
	static void translateString(string& a0, Player* sp = nullptr);

	static void registerStaticPlaceholder(string name, string value, string PluginName = "");
	static void registerStaticPlaceholder(string name, string(*Func)(), string PluginName);
	static void registerStaticPlaceholder(string name, std::function<string()> callback, string PluginName="");
	static void registerStaticPlaceholder(string name, int UpdateInterval, string(*Func)(), string PluginName);
	static void registerStaticPlaceholder(string name, int UpdateInterval, std::function<string()> callback, string PluginName = "");
	
	static void registerPlayerPlaceholder(string name, std::function<string(class Player*)> callback, string PluginName = "");
	static void registerPlayerPlaceholder(string name, std::function<string(class Player*, std::unordered_map<string, string>)> callback, string PluginName = "");

	static void registerServerPlaceholder(string name, std::function<string()> callback, string PluginName = "");
	static void registerServerPlaceholder(string name, std::function<string(std::unordered_map<string, string>)> callback, string PluginName = "");
	
	static bool unRegisterPlaceholder(string name);
	
	static void Update(PlaceholderAPI a1);
	static std::unordered_set<string> getPAPIPluginsList();
	static std::vector<PlaceholderAPI> getPAPIInfoList();
	inline string getValue() {
		return mValue;
	}
	inline string getPluginName() {
		return mPluginName;
	}
};