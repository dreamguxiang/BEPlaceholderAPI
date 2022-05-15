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
#include <MC/LevelChunk.hpp>

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
	
}

void ListenEvent() {
	Event::ServerStartedEvent::subscribe_ref([](Event::ServerStartedEvent& ev) {
		startTime = std::time(0);
		return true;
		});
}


/*
*%server_uptime% 服务器运行时间
%server_ram_used% 服务器内存使用
%server_ram_free% 服务器内存空闲
%server_ram_total% 服务器内存总计
%server_ram_max% 服务器最大内存
*%server_name% 服务器名
%server_tps% 服务器TPS
%server_tps_1% 服务器当前TPS
%server_tps_5% 服务器 5 分钟前TPS
%server_tps_15% 服务器 15 分钟前TPS
%server_tps_1_colored%
%server_tps_5_colored%
%server_tps_15_colored%
%server_online_<world>%
*%server_has_whitelist% 服务器是否启用了白名单
%server_total_chunks% 服务器总区块数
%server_total_living_entities% 服务器总活跃实体
*%server_total_entities% 服务器总实体数
*/