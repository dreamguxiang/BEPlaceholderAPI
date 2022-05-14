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
	bool mProcessParameters;
	std::function<string(class Player*)>  mCallback;
	
public:
	PlaceholderAPI() {};
	PlaceholderAPI(string Name,int UpdateInterval,bool AutoUpdate,bool ProcessParameters, string PluginName,std::function<string(class Player*)> callback);
	~PlaceholderAPI() { };
	
	static void registerPlaceholder(PlaceholderAPI a0);
	static string getValue(string name,Player* sp);
	static string getValue(string name);
	static void translateString(string& a0, Player* sp = nullptr);

	static void registerStaticPlaceholder(string name, string(*Func)(), string PluginName = "");
	static void registerStaticPlaceholder(string name, string value, string PluginName = "");
	static void registerStaticPlaceholder(string name, int UpdateInterval , string(*Func)(), string PluginName = "");
	static void registerPlayerPlaceholder(string name, std::function<string(class Player*)> callback, string PluginName = "");
	static void Update(PlaceholderAPI a1);
	static std::unordered_set<string> getPAPIList();
	static std::vector<PlaceholderAPI> getPAPIInfoList();
	inline string getValue() {
		return mValue;
	}
	inline string getPluginName() {
		return mPluginName;
	}
};