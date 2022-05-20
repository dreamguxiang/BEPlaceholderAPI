#include "Global.h"
#include "PlaceholderAPI.h"
#include "Helper.h"
#include <MC/ServerPlayer.hpp>
#include <MC/ItemStack.hpp>
#include <MC/AttributeInstance.hpp>
#include <MC/ServerNetworkHandler.hpp>
#include <mc/RakPeerHelper.hpp>
#include <MC/Attribute.hpp>
#include <ctime>
#include <EventAPI.h>
#include <I18nAPI.h>
#include <MC/LevelChunk.hpp>

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
		return S(sp->getPlayerGameType());
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
		return S(sp->canFly());
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

	PlaceholderAPI::registerPlayerPlaceholder("player_is_op", [](Player* sp) {
		return S(sp->isOP());
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
		return S(sp->getAttribute(Player::HUNGER).getCurrentValue());
		});

	
}

void regServerInit() {

	PlaceholderAPI::registerServerPlaceholder("server_time_<format>", [](std::map<string, string> map) {	
		if(map.find("<format>") != map.end()) {
			if("<format>" != map["<format>"])
				return Helper::getTime(map["<format>"]);
		}
		return Helper::getTime("%H:%M:%S");
		});
	PlaceholderAPI::registerServerPlaceholder("server_online", []() {
		return S(Helper::getActiveAndInProgressPlayerCount(mce::UUID::EMPTY));
		});
	
	PlaceholderAPI::registerServerPlaceholder("server_max_players", []() {
		return  S(*((int*)Global<ServerNetworkHandler> + 188));
		});
	
	PlaceholderAPI::registerServerPlaceholder("server_version", []() {
		return LL::getBdsVersion();
		});
	PlaceholderAPI::registerServerPlaceholder("server_rotocol_version", []() {
		return S(LL::getServerProtocolVersion());
		});
	PlaceholderAPI::registerServerPlaceholder("server_total_entities", []() {
		return S(Level::getAllEntities().size());
		});
	PlaceholderAPI::registerServerPlaceholder("server_world_name", []() {
		return Helper::getLevelData().getLevelName();
		});
	PlaceholderAPI::registerServerPlaceholder("server_seed", []() {
		return Global<PropertiesSettings>->getLevelSeed();
		});
	PlaceholderAPI::registerServerPlaceholder("server_difficulty", []() {
		return S(Global<PropertiesSettings>->getDifficulty());
		});
	PlaceholderAPI::registerServerPlaceholder("server_difficulty", []() {
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
	PlaceholderAPI::registerServerPlaceholder("server_name", []() {
		return Global<PropertiesSettings>->getMotd();
		});
	PlaceholderAPI::registerServerPlaceholder("server_has_whitelist", []() {
		return S(Global<PropertiesSettings>->useAllowList());
		});
	PlaceholderAPI::registerServerPlaceholder("server_total_entities", []() {
		return S(Level::getAllEntities().size());
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

void ListenEvent() {
	Event::ServerStartedEvent::subscribe_ref([](Event::ServerStartedEvent& ev) {
		startTime = std::time(0);
		return true;
		});
}

typedef std::chrono::high_resolution_clock timer_clock;
THook(void, "?tick@ServerLevel@@UEAAXXZ", Level* a1) {
	TIMER_START
	original(a1);
	TIMER_END
		if (TPS::isMSPTing) {
			TPS::mspt = (double)timeReslut / 1000;
			TPS::tps = TPS::mspt <= 50 ? 20 : (int)(1000.0 / TPS::mspt);
			TPS::isMSPTing = false;
		}
}
//#include <MC/SignBlockActor.hpp>
//THook(void*, "?_getUpdatePacket@SignBlockActor@@MEAA?AV?$unique_ptr@VBlockActorDataPacket@@U?$default_delete@VBlockActorDataPacket@@@std@@@std@@AEAVBlockSource@@@Z", SignBlockActor* a1,BlockSource* a2) {
//	std::cout << "update" << std::endl;
//	return original(a1, a2);
//}

#include <ScheduleAPI.h>
	

void RegPAPInit() {
	Schedule::repeat([] {
		TPS::isMSPTing = true;		
		},20);
	regPlayerInit();
	regServerInit();
}
/*
//系统
string cpu_ = m_replace(cmd, "{cpu}", getCPUUsed());
string ramAll_ = m_replace(cpu_, "{ramAll}", ram["all"]);
string ramUse_ = m_replace(ramAll_, "{ramUse}", ram["used"]);
string ramPercent_ = m_replace(ramUse_, "{ranPercent}", ram["percent"]);
string ramCan_ = m_replace(ramPercent_, "{ramCan}", ram["canuse"]);
*/

/*
%server_tps% 服务器TPS
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