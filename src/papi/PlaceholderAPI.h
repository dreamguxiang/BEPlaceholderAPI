#pragma once
#include "Global.h"

//#define REG_PLUGIN_NAME

#ifdef PAPI_EXPORTS
#define PAPI_API __declspec(dllexport)
#else
#define PAPI_API __declspec(dllimport)
#endif

class PlaceholderAPI {
public:
    std::string mValue;
    std::string mName;
private:
    std::string mPluginName;
    int mUpdateInterval;
    bool mAutoUpdate;
    bool mProcessPlayer;
    bool mProcessParameters;
    std::function<std::string(Player*)>  mCallback;
    std::function<std::string(Player*,std::unordered_map<std::string,std::string>)>  mCallbackWithParameters;

public:
    PlaceholderAPI() {};
    PlaceholderAPI(std::string Name,int UpdateInterval,bool AutoUpdate,bool mProcessPlayer, bool mProcessParameters ,std::string PluginName,std::function<std::string(Player*)> callback, std::function<std::string(Player*, std::unordered_map<std::string, std::string>)> CallbackWithParameters);
    ~PlaceholderAPI() { };

    PAPI_API static void registerPlaceholder(PlaceholderAPI a0);
    PAPI_API static std::string getValue(std::string name,Player* sp);
    PAPI_API static std::string getValue(std::string name);
    PAPI_API static void translateString(std::string& a0, Player* sp = nullptr);

    PAPI_API static void registerStaticPlaceholder(std::string name, std::string value, std::string PluginName = "");
    PAPI_API static void registerStaticPlaceholder(std::string name, std::string(*Func)(), std::string PluginName);
    PAPI_API static void registerStaticPlaceholder(std::string name, std::function<std::string()> callback, std::string PluginName="");
    PAPI_API static void registerStaticPlaceholder(std::string name, int UpdateInterval, std::string(*Func)(), std::string PluginName);
    PAPI_API static void registerStaticPlaceholder(std::string name, int UpdateInterval, std::function<std::string()> callback, std::string PluginName = "");

    PAPI_API static void registerPlayerPlaceholder(std::string name, std::function<std::string(Player*)> callback, std::string PluginName = "");
    PAPI_API static void registerPlayerPlaceholder(std::string name, std::function<std::string(Player*, std::unordered_map<std::string, std::string>)> callback, std::string PluginName = "");

    PAPI_API static void registerServerPlaceholder(std::string name, std::function<std::string()> callback, std::string PluginName = "");
    PAPI_API static void registerServerPlaceholder(std::string name, std::function<std::string(std::unordered_map<std::string, std::string>)> callback, std::string PluginName = "");

    PAPI_API static bool unRegisterPlaceholder(std::string name);

    PAPI_API static void Update(PlaceholderAPI a1);
    PAPI_API static std::unordered_set<std::string> getPAPIPluginsList();
    PAPI_API static std::vector<PlaceholderAPI> getPAPIInfoList();
    PAPI_API inline std::string getValue() {
        return mValue;
    }
    PAPI_API inline std::string getPluginName() {
        return mPluginName;
    }
};