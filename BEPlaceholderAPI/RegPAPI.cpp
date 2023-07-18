#include "Global.h"
#include "PlaceholderAPI.h"
#include "Helper.h"
#include <ctime>

namespace TPS {
	bool isMSPTing = false;
	double mspt = 0;
	int tps = 0;
}

std::time_t startTime = 0;

void regPlayerInit() {
	
	PlaceholderAPI::registerPlayerPlaceholder("player_realname", [](Player* sp) {
		return sp->getRealName();
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_uuid", [](Player* sp) {
		return sp->getUuid();
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_ping", [](Player* sp) {
		return S(sp->getAvgPing());
		});	
	
	PlaceholderAPI::registerPlayerPlaceholder("player_health", [](Player* sp) {
		return S(sp->getHealth());
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_max_health", [](Player* sp) {
		return S(sp->getMaxHealth());
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_gamemode", [](Player* sp) {
		return S((int)sp->getPlayerGameType());
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_x", [](Player* sp) {
		return S(sp->getPos().x);
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_y", [](Player* sp) {
		return S(sp->getPos().y);
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_z", [](Player* sp) {
		return S(sp->getPos().z);
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_direction", [](Player* sp) {
		return S(sp->getDirection());
		});
	
	PlaceholderAPI::registerPlayerPlaceholder("player_exp_to_next", [](Player* sp) {
		return S(sp->getXpNeededForNextLevel());
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_exp_level", [](Player* sp) {
		return S(sp->getPlayerLevel());
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_speed", [](Player* sp) {
		return S(sp->getSpeed());
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_flying", [](Player* sp) {
		bool flying = sp->getNbt()->getCompound("abilities")->getBoolean("flying");
		return S(flying);
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_can_fly", [](Player* sp) {
		return S(sp->canFly());
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_displayname", [](Player* sp) {
		return sp->getNameTag();
		});
	
	PlaceholderAPI::registerPlayerPlaceholder("player_is_op", [](Player* sp) {
		return S(sp->isOP());
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_item_in_hand", [](Player* sp) {
		auto item = sp->getHandSlot();
		string str = "";
		if (!item->isNull())
			return item->getName();
		else
			return str;
		});	
	
	PlaceholderAPI::registerPlayerPlaceholder("player_ip", [](Player* sp) {
		return sp->getIP();
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_device", [](Player* sp) {
		return sp->getDeviceName();
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_language", [](Player* sp) {
		return sp->getLanguageCode();
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_xuid", [](Player* sp) {
		return sp->getXuid();
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_bed_x", [](Player* sp) {
		return S(sp->getSpawnPosition().x);
		});
	
	PlaceholderAPI::registerPlayerPlaceholder("player_bed_y", [](Player* sp) {
		return S(sp->getSpawnPosition().y);
		});
	
	PlaceholderAPI::registerPlayerPlaceholder("player_bed_z", [](Player* sp) {
		return S(sp->getSpawnPosition().z);
		});

	PlaceholderAPI::registerPlayerPlaceholder("player_hunger", [](Player* sp) {
		return S((int)sp->getAttribute(Player::HUNGER).getCurrentValue());
		});
	PlaceholderAPI::registerPlayerPlaceholder("player_max_hunger", [](Player* sp) {
		try{
			string maxHunger = "";
			auto plnbt = sp->getNbt();
			nlohmann::json plnJ = nlohmann::json::parse(plnbt.get()->toJson(0));
			for (auto& nbt : plnJ["Attributes"]) {
				if (nbt["Name"] == "minecraft:player.hunger") {
					maxHunger = std::to_string((double)nbt["Max"]);
					maxHunger = maxHunger.substr(0, maxHunger.find("."));
				}
			}
			return maxHunger;
		}
		catch (...) {
			return (std::string)"20";
		}
		});

	
}

void regServerInit() {

	PlaceholderAPI::registerServerPlaceholder("server_time_<format>_s", [](std::unordered_map<string, string> map) {
			if (map.find("<format>") != map.end()) {
				if ("<format>" != map["<format>"])
					return Helper::getTime(map["<format>"]);
			}
		
		return Helper::getTime("H:M:S");
		});
	PlaceholderAPI::registerServerPlaceholder("server_time_<format>", [](std::unordered_map<string, string> map) {
		if (map.find("<format>") != map.end()) {
			if ("<format>" != map["<format>"])
				return Helper::getTime(map["<format>"]);
		}

		return Helper::getTime("H:M:S");
		});
	PlaceholderAPI::registerServerPlaceholder("server_online", []() {
		return S(Global<ServerNetworkHandler>->getActiveAndInProgressPlayerCount(mce::UUID::EMPTY));
		});
	
	PlaceholderAPI::registerServerPlaceholder("server_max_players", []() {
		return  S(*((int*)Global<ServerNetworkHandler> + 192));
		});
	
	PlaceholderAPI::registerServerPlaceholder("server_version", []() {
		return ll::getBdsVersion();
		});
	PlaceholderAPI::registerServerPlaceholder("server_protocol_version", []() {
		return S(ll::getServerProtocolVersion());
		});
	PlaceholderAPI::registerServerPlaceholder("server_total_entities", []() {
		return S(Level::getAllEntities().size());
		});
	PlaceholderAPI::registerServerPlaceholder("server_world_name", []() {
		return Global<Level>->getLevelData().getLevelName();
		});
	PlaceholderAPI::registerServerPlaceholder("server_difficulty", []() {
		return S((int)Global<PropertiesSettings>->getDifficulty());
		});
	PlaceholderAPI::registerServerPlaceholder("server_on_allowlist", []() {
		return S(Global<PropertiesSettings>->useAllowList());
		});
	PlaceholderAPI::registerServerPlaceholder("server_port", []() {
		return S(Global<PropertiesSettings>->getServerPort());
		});
	PlaceholderAPI::registerServerPlaceholder("server_port_v6", []() {
		return S(Global<PropertiesSettings>->getServerPortv6());
		});
	PlaceholderAPI::registerServerPlaceholder("server_uptime", []() {
		return S(std::time(0) - startTime);
		});
	PlaceholderAPI::registerServerPlaceholder("server_start_time_<format>_s", [](std::unordered_map<string, string> map) {
		if (map.find("<format>") != map.end()) {
			if ("<format>" != map["<format>"])
				return Helper::getTime(map["<format>"], startTime);
		}

		return Helper::getTime("H:M:S",startTime);
		});
	PlaceholderAPI::registerServerPlaceholder("server_start_time_<format>", [](std::unordered_map<string, string> map) {
		if (map.find("<format>") != map.end()) {
			if ("<format>" != map["<format>"])
				return Helper::getTime(map["<format>"], startTime);
		}

		return Helper::getTime("H:M:S", startTime);
		});

	PlaceholderAPI::registerServerPlaceholder("server_name", []() {
		return Global<PropertiesSettings>->getMotd();
		});
	PlaceholderAPI::registerServerPlaceholder("server_has_whitelist", []() {
		return S(Global<PropertiesSettings>->useAllowList());
		});
	PlaceholderAPI::registerServerPlaceholder("server_total_chunks", []() {
		return "";
		});
	
	PlaceholderAPI::registerServerPlaceholder("server_ram_bds_used", []() {
		auto ram = Helper::getRam();
		return ram["bdsused"];
		});
	
	PlaceholderAPI::registerServerPlaceholder("server_ram_free", []() {
		auto ram = Helper::getRam();
		return ram["canuse"];
		});
	
	PlaceholderAPI::registerServerPlaceholder("server_ram_used", []() {
		auto ram = Helper::getRam();
		return ram["used"];
		});
	
	PlaceholderAPI::registerServerPlaceholder("server_ram_max", []() {
		auto ram = Helper::getRam();
		return ram["all"];
		});
	PlaceholderAPI::registerServerPlaceholder("server_tps", []() {
		return S(TPS::tps);
		});
	PlaceholderAPI::registerServerPlaceholder("server_mspt", []() {
		return S(TPS::mspt);
		});
}

LARGE_INTEGER freq_;
auto INITPERFORMANCE = QueryPerformanceFrequency(&freq_);

LARGE_INTEGER begin_time;
LARGE_INTEGER end_time;
inline double ns_time()
{
	return (end_time.QuadPart - begin_time.QuadPart) * 1000000.0 / freq_.QuadPart;
}

#define TestLogTime(func, ...)            \
    QueryPerformanceCounter(&begin_time); \
    func(__VA_ARGS__);                    \
    QueryPerformanceCounter(&end_time);   \
    logger.warn("  {}\t time: {}ns", #func, ns_time());
constexpr int TEST_COUNT = 1000000;


void getValue()
{
		PlaceholderAPI::getValue("%server_tps%");
}

void translateString()
{
	string str = "hi%server_tps%";
	PlaceholderAPI::translateString(str);
}

void translateString2()
{
	string str = "hi%server_test3%%server_test%%server_test_21231%%server_test_21231%%server_test_21231%%server_test_21231%%server_test_21231%%server_test_21231%%server_test_21231%";
	PlaceholderAPI::translateString(str);
}

void translateString3()
{
	string str = "hi%server_time_y%%server_tps%";
	PlaceholderAPI::translateString(str);
}



void checkUpdate();
void ListenEvent() {
	Event::ServerStartedEvent::subscribe_ref([](Event::ServerStartedEvent& ev) {
		checkUpdate();
		startTime = std::time(0);
		return true;
		});
}

typedef std::chrono::high_resolution_clock timer_clock;
THook(void, "?tick@Level@@UEAAXXZ", Level* a1) {
	TIMER_START
	original(a1);
	TIMER_END
		if (TPS::isMSPTing) {
			TPS::mspt = (double)timeReslut / 1000;
			TPS::tps = TPS::mspt <= 50 ? 20 : (int)(1000.0 / TPS::mspt);
			TPS::isMSPTing = false;
		}
}
#include <ScheduleAPI.h>
	

void RegPAPInit() {
	Schedule::repeat([] {
		TPS::isMSPTing = true;		
		},20);
	regPlayerInit();
	regServerInit();
	ListenEvent();
}

/*
//系统
string cpu_ = m_replace(cmd, "{cpu}", getCPUUsed());
*/

/*
%server_tps_1% 服务器当前TPS
%server_tps_5% 服务器 5 分钟前TPS
%server_tps_15% 服务器 15 分钟前TPS
%server_tps_1_colored%
%server_tps_5_colored%
%server_tps_15_colored%
%server_online_<world>%
%server_total_chunks% 服务器总区块数
%server_total_living_entities% 服务器总活跃实体
*/
