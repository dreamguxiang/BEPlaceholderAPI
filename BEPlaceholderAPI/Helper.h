#pragma once
#include "Global.h"
#include <regex>
#include <windows.h>
#include <Pdh.h>
#include <PdhMsg.h>
#include <psapi.h>
#include "PlaceholderAPI.h"

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
struct Vec4 {
	Vec3 vc;
	char dimid;

	string toStr() const {
		return "(" + std::to_string(vc.x) + " , " + std::to_string(vc.y) + " , " + std::to_string(vc.z) + " , " +
			std::to_string(dimid) + " , " + ")";
	}

	void teleport(ServerPlayer* wp) {
		wp->teleport(vc, dimid);
	}

	Vec4() {}
	
	Vec4(ServerPlayer* wp) {
		vc = wp->getPosition();
		dimid = wp->getDimensionId();
	}

	Vec4(Vec3 x, int dim) : vc(x), dimid(dim) {}
	
	Vec4(const Vec4& vc4) {
		vc = vc4.vc;
		dimid = vc4.dimid;
	}
	bool operator<(const Vec4& s) const {
		if (vc.x < s.vc.x) return true;
		if (s.vc.x < vc.x) return false;
		if (vc.y < s.vc.y) return true;
		if (s.vc.y < vc.y) return false;
		if (vc.z < s.vc.z) return true;
		if (s.vc.z < vc.z) return false;
		if (dimid < s.dimid) return true;
		if (s.dimid < dimid) return false;
		return false;
	}
	bool operator==(const Vec4& s) const {
		return vc.x == s.vc.x && vc.y == s.vc.y && vc.z == s.vc.z && dimid == s.dimid;
	}
	bool operator!=(const Vec4& s) const {
		return vc.x != s.vc.x || vc.y != s.vc.y || vc.z != s.vc.z || dimid != s.dimid;
	}
};



enum class BlockActorType {
	Undefined = 0x0,
	Furnace = 0x1,
	Chest = 0x2,
	NetherReactor = 0x3,
	Sign = 0x4,
	MobSpawner = 0x5,
	Skull = 0x6,
	FlowerPot = 0x7,
	BrewingStand = 0x8,
	EnchantTable = 0x9,
	DaylightDetector = 0xa,
	Music = 0xb,
	Comparator = 0xc,
	Dispenser = 0xd,
	Dropper = 0xe,
	Hopper = 0xf,
	Cauldron = 0x10,
	ItemFrame = 0x11,
	PistonArm = 0x12,
	MovingBlock = 0x13,
	ChalkboardBlock = 0x14,
	Beacon = 0x15,
	EndPortal = 0x16,
	EnderChest = 0x17,
	EndGateway = 0x18,
	ShulkerBox = 0x19,
	CommandBlock = 0x1a,
	Bed = 0x1b,
	Banner = 0x1c,
	StructureBlock = 0x20,
	Jukebox = 0x21,
	ChemistryTable = 0x22,
	Conduit = 0x23,
	JigsawBlock = 0x24,
	Lectern = 0x25,
	BlastFurnace = 0x26,
	Smoker = 0x27,
	Bell = 0x28,
	Campfire = 0x29,
	Barrel = 0x2a,
	Beehive = 0x2b,
	Lodestone = 0x2c,
	SculkSensor = 0x2d,
	SporeBlossom = 0x2e,
	GlowItemFrame = 0x2f,
	SculkCatalyst = 0x30,
	SculkShrieker = 0x31
};
#include <ScheduleAPI.h>
#include <algorithm>
namespace Helper {
	inline SYSTEMTIME Timet2SystemTime(time_t t)
	{
		FILETIME ft;
		SYSTEMTIME pst;
		LONGLONG nLL = Int32x32To64(t, 10000000) + 116444736000000000;
		ft.dwLowDateTime = (DWORD)nLL;
		ft.dwHighDateTime = (DWORD)(nLL >> 32);
		FileTimeToSystemTime(&ft, &pst);
		return pst;
	}

	inline string getTime(string format,std::time_t inTime = -1)
	{
		std::time_t nowTime;
		SYSTEMTIME st;
		//Specified time
		if (inTime == -1) {
			nowTime = std::time(0);
		}
		else {
			nowTime = inTime;
		}
		st = Timet2SystemTime(nowTime);
		
		ReplaceStr(format, "%ms", S(st.wMilliseconds));
		string formatTime[21] = {"y","Y","m","d","H","M","S","a","A","b","B","c","I","j","p","U","w","W","x","X","Z"};
		for (string i : formatTime) {
			ReplaceStr(format, i, fmt::format("{:%"+i+"}", fmt::localtime(nowTime)));
		}
		return format;
	}

	inline string removeBrackets(string a1) {
		//a1.erase(std::remove(a1.begin(), a1.end(), '%'), a1.end());
		a1.erase(a1.find_last_not_of("%") + 1);
		return a1;
	}

	inline string removeAllBrackets(string a1) {
		a1.erase(std::remove(a1.begin(), a1.end(), '%'), a1.end());
		return a1;
	}

	inline vector<string> getPAPIPlugins() {
		vector<string> v;
		auto sets = PlaceholderAPI::getPAPIPluginsList();
		v.assign(sets.begin(), sets.end());
		return v;
	}

	inline vector<string> getPAPIInfoList() {
		vector<string> out;
		auto v = getPAPIPlugins();
		
		auto list = PlaceholderAPI::getPAPIInfoList();
		for (auto& i : list) {
			v.push_back(removeAllBrackets(i.mName));
		}
		return v;
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
	
	inline bool isParameters(std::string str) {
		std::regex reg("[<]([^<>]+)[>]");
		return std::regex_search(removeBrackets(str), reg);

	}
	inline vector<string> getBrackets(std::string str) {
		std::regex reg("[{]([^{}]+)[}]");
		vector<string> result;
		for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), reg); i != std::sregex_iterator(); ++i) {
			result.push_back((*i).str());
		}
		return result;
	}

	inline vector<string> getPercentage(std::string str) {
		std::regex reg("[%]([^%]*)[%]");
		vector<string> result;
		for (std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), reg); i != std::sregex_iterator(); ++i) {
			result.push_back((*i).str());
		}
		return result;
	}

	inline void Backets2Percentage(string& str) {
		ReplaceStr(str, "{", "%"); ReplaceStr(str, "}", "%");
	}
	inline bool isSame(std::vector<std::string> a1, std::vector<std::string> a2, int a3) {
		if (a1.size() != a2.size())
			return false;
		for (int i = 0; i < a3; i++) {
			if (a1[i] != a2[i])
				return false;
		}
		return true;
	}
	
	inline std::tuple<bool, std::unordered_map<string, string>> FindPlaceholder(std::string str, std::string str2) {
		std::unordered_map<string,string> map;
		std::vector<std::string> ori = split(str, "_");
		std::vector<std::string> input = split(str2, "_");
		if (ori.size() != input.size()) return std::make_tuple(false,map);
		for (int i = 0; i < ori.size(); i++) {			
			if (ori[i] != input[i]) {
				if (isSame(ori, input, i)) {
					if (isParameters(ori[i])) {
						map.emplace(std::pair{ removeBrackets(ori[i]),removeBrackets(input[i]) });
						ori[i] = input[i];
						if (ori[i].find("%") != string::npos) {
							return std::make_tuple(true, map);
						}
					}
				}
			}
		}
		if (map.empty() || !isSame(ori, input, ori.size()))
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


