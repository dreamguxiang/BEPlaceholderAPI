#pragma once
#include "Global.h"
#include <regex>
#include <windows.h>
#include <Pdh.h>
#include <PdhMsg.h>
#include <psapi.h>

#pragma comment(lib,"psapi.lib")
typedef std::chrono::high_resolution_clock timer_clock;
#define TIMER_START auto start = timer_clock::now();
#define TIMER_END                                                      \
    auto elapsed = timer_clock::now() - start;                         \
    long long timeReslut =                                             \
        std::chrono::duration_cast<std::chrono::microseconds>(elapsed) \
            .count();

class ChunkPos2 {
	int       x, z;
public:
	class ChunkPos2& operator=(class ChunkPos2 const&) = default;
	ChunkPos2(class ChunkPos2 const&) = default;
	ChunkPos2() = default;
	bool operator<(const ChunkPos2& rhs) const {
		if (x < rhs.x) return true;
		if (rhs.x < x) return false;
		return z < rhs.z;
	}
};

namespace Helper {
	inline string getTime(string format)
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
		if (x.find('%') != x.npos && x.find('%') != x.npos) 
			return x;
		else 
			return '%' + x + '%';
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

	inline std::vector<std::string> split(std::string str, std::string pattern)
	{
		std::string::size_type pos;
		std::vector<std::string> result;
		str += pattern;
		int size = str.size();
		for (int i = 0; i < size; i++)
		{
			pos = str.find(pattern, i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}

	inline string removeBrackets(string a1) {
		//a1.erase(std::remove(a1.begin(), a1.end(), '%'), a1.end());
		a1.erase(a1.find_last_not_of("%") + 1);
		return a1;
	}
	
	inline bool isParameters(std::string str) {
		std::regex reg("[<]([^>]+)[>]");
		return std::regex_match(removeBrackets(str), reg);

	}
	inline vector<string> getBrackets(std::string str) {
		std::regex reg("[{]([^}]+)[}]");
		vector<string> result;
		for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), reg); i != std::sregex_iterator(); ++i) {
			result.push_back((*i).str());
		}
		return result;
	}

	inline vector<string> getPercentage(std::string str) {
		std::regex reg("[%]([^%]*)([^_]*)[%]");
		vector<string> result;
		for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), reg); i != std::sregex_iterator(); ++i) {
			result.push_back((*i).str());
		}
		return result;
	}

	inline void Backets2Percentage(string& str) {
		ReplaceStr(str, "{", "%"); ReplaceStr(str, "}", "%");
	}
	inline std::tuple<bool, std::map<string, string>> FindPlaceholder(std::string str, std::string str2) {
		std::map<string,string> map;
		std::vector<std::string> ori = split(str, "_");
		std::vector<std::string> input = split(str2, "_");
		if (ori.size() != input.size()) return std::make_tuple(false,map);
		for (int i = 0; i < ori.size(); i++) {			
			if (ori[i] != input[i]) {
				if (isParameters(ori[i])) {
					map.emplace(std::pair{ removeBrackets(ori[i]),removeBrackets(input[i])});
					if (ori[i].find("%") != string::npos) {
						return std::make_tuple(true, map);
					}
				}
			}		
		}
		if (map.empty())
			return std::make_tuple(false, map);
		else
			return std::make_tuple(true, map);
	}

	inline std::unordered_map<string, string> getRam() {
		MEMORYSTATUSEX statusex;
		statusex.dwLength = sizeof(statusex);
		GlobalMemoryStatusEx(&statusex);

		HANDLE handle = GetCurrentProcess();
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
		std::unordered_map<string, string> ram;
		ram.emplace("all", std::to_string(statusex.ullTotalPhys / 1024 / 1024));
		ram.emplace("canuse", std::to_string(statusex.ullAvailPhys / 1024 / 1024));
		ram.emplace("percent", std::to_string(statusex.dwMemoryLoad));
		ram.emplace("used", std::to_string((statusex.ullTotalPhys - statusex.ullAvailPhys) / 1024 / 1024));
		
		ram.emplace("bdsused", std::to_string(pmc.WorkingSetSize / 1024 / 1024));

		return ram;
	}
}


