#pragma once
#include "Global.h"

namespace Helper {
	inline string gettime(string format)
	{
		time_t rawtime;
		tm* LocTime;
		char timestr[20];
		time(&rawtime);
		LocTime = localtime(&rawtime);
		strftime(timestr, 20, format.c_str(), LocTime);
		return string(timestr);
	}
	inline string checkPAPIName(string x) {
		if (x.find('{') != x.npos && x.find('}') != x.npos) return x;
		else return "{" + x + "}";
	}
	inline string ReplaceStr(string str, const string& old_value, const string& new_value) {
		for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
			if ((pos = str.find(old_value, pos)) != string::npos)
				str.replace(pos, old_value.length(), new_value);
			else
				break;
		}
		return str;
	}
	inline class LevelData& getLevelData() {
		class LevelData& (Level:: * rv)();
		*((void**)&rv) = dlsym("?getLevelData@Level@@UEAAAEAVLevelData@@XZ");
		return (Global<Level>->*rv)();
	}

	inline int getActiveAndInProgressPlayerCount(class mce::UUID a1) {
		return SymCall("?_getActiveAndInProgressPlayerCount@ServerNetworkHandler@@AEBAHVUUID@mce@@@Z", int, ServerNetworkHandler*, mce::UUID)(Global<ServerNetworkHandler>, a1);
	}
}