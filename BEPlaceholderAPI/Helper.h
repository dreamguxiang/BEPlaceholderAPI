#pragma once
#include "Global.h"

namespace Helper {
	inline string gettime()
	{
		time_t rawtime;
		tm* LocTime;
		char timestr[20];
		time(&rawtime);
		LocTime = localtime(&rawtime);
		strftime(timestr, 20, "%Y-%m-%d %H:%M:%S", LocTime);
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
}