#pragma once
#include "Global.h"
#include <DynamicCommandAPI.h>
#define REG_PLUGIN_NAME PLUGIN_NAME

#ifdef PAPI_EXPORTS
#define PAPI_API __declspec(dllexport)
#else
#define PAPI_API __declspec(dllimport)
#endif

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
	
	PAPI_API static void registerPlaceholder(PlaceholderAPI a0);
	PAPI_API static string getValue(string name,Player* sp);
	PAPI_API static string getValue(string name);
	PAPI_API static void translateString(string& a0, Player* sp = nullptr);

	PAPI_API static void registerStaticPlaceholder(string name, string value, string PluginName = "");
	PAPI_API static void registerStaticPlaceholder(string name, string(*Func)(), string PluginName);
	PAPI_API static void registerStaticPlaceholder(string name, std::function<string()> callback, string PluginName="");
	PAPI_API static void registerStaticPlaceholder(string name, int UpdateInterval, string(*Func)(), string PluginName);
	PAPI_API static void registerStaticPlaceholder(string name, int UpdateInterval, std::function<string()> callback, string PluginName = "");
	
	PAPI_API static void registerPlayerPlaceholder(string name, std::function<string(class Player*)> callback, string PluginName = "");
	PAPI_API static void registerPlayerPlaceholder(string name, std::function<string(class Player*, std::unordered_map<string, string>)> callback, string PluginName = "");

	PAPI_API static void registerServerPlaceholder(string name, std::function<string()> callback, string PluginName = "");
	PAPI_API static void registerServerPlaceholder(string name, std::function<string(std::unordered_map<string, string>)> callback, string PluginName = "");
	
	PAPI_API static bool unRegisterPlaceholder(string name);
	
	PAPI_API static void Update(PlaceholderAPI a1);
	PAPI_API static std::unordered_set<string> getPAPIPluginsList();
	PAPI_API static std::vector<PlaceholderAPI> getPAPIInfoList();
	PAPI_API inline string getValue() {
		return mValue;
	}
	PAPI_API inline string getPluginName() {
		return mPluginName;
	}
};