#pragma once
#include "Global.h"
#include <DynamicCommandAPI.h>

class PlaceholderAPI {
public:
	string mValue;
	string mName;
private:
	int mUpdateInterval;
	bool mAutoUpdate;
	bool mProcessParameters;
	std::function<string(class Player*)>  mCallback;
	
public:
	PlaceholderAPI() {};
	PlaceholderAPI(string Name,int UpdateInterval,bool AutoUpdate,bool ProcessParameters, std::function<string(class Player*)> callback);
	~PlaceholderAPI() { };
	
	static void registerPlaceholder(PlaceholderAPI a0);
	static string getValue(string name,Player* sp);
	static string getValue(string name);
	static void translateString(string& a0, Player* sp = nullptr);

	static void registerStaticPlaceholder(string name, string(*Func)());
	static void registerStaticPlaceholder(string name, string value);
	static void registerStaticPlaceholder(string name, int UpdateInterval , string(*Func)());
	static void registerPlayerPlaceholder(string name, std::function<string(class Player*)> callback);
	static void Update(PlaceholderAPI a1);
	
	inline string getValue() {
		return mValue;
	}
};