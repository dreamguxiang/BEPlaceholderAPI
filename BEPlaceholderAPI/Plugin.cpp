#include "Global.h"
#include <ServerAPI.h>
#include "Lang.hpp"
Logger logger(PLUGIN_NAME);

inline void CheckProtocolVersion() {
    auto currentProtocol = LL::getServerProtocolVersion();
    if (TARGET_BDS_PROTOCOL_VERSION != currentProtocol)
    {
        logger.warn("Protocol version not match, target version: {}, current version: {}.",
            TARGET_BDS_PROTOCOL_VERSION, currentProtocol);
        logger.warn("This will most likely crash the server, please use the Plugin that matches the BDS version!");
    }
}


void loadCfg() {
    //config
    if (!std::filesystem::exists("plugins/BEPlaceholderAPI"))
        std::filesystem::create_directories("plugins/BEPlaceholderAPI");	
    if (std::filesystem::exists(JsonFile)) {
        try {
            Settings::LoadConfigFromJson(JsonFile);
        }
        catch (std::exception& e) {
            logger.error("Config File isInvalid, Err {}", e.what());
            Sleep(1000 * 100);
            exit(1);
        }
        catch (...) {
            logger.error("Config File isInvalid");
            Sleep(1000 * 100);
            exit(1);
        }
    }
    else {
        logger.info("Config with default values created");
        Settings::WriteDefaultConfig(JsonFile);
    }

    //-----CN------
    if (!std::filesystem::exists(LangParh))
        std::filesystem::create_directories(LangParh);
    if (std::filesystem::exists("plugins/BEPlaceholderAPI/lang/zh_CN.json")) {
        try {
            TRZH::LoadConfigFromJson("plugins/BEPlaceholderAPI/lang/zh_CN.json");
        }
        catch (std::exception& e) {
            logger.error("Config File isInvalid, Err {}", e.what());
            Sleep(1000 * 100);
            exit(1);
        }
        catch (...) {
            logger.error("Config File isInvalid");
            Sleep(1000 * 100);
            exit(1);
        }
    }
    else {
        logger.info("Config with default values created");
        TRZH::WriteDefaultConfig("plugins/BEPlaceholderAPI/lang/zh_CN.json");
    }
	
    //--------US----------
    if (!std::filesystem::exists(LangParh))
        std::filesystem::create_directories(LangParh);
    if (std::filesystem::exists("plugins/BEPlaceholderAPI/lang/en_US.json")) {
        try {
            TRUS::LoadConfigFromJson("plugins/BEPlaceholderAPI/lang/en_US.json");
        }
        catch (std::exception& e) {
            logger.error("Config File isInvalid, Err {}", e.what());
            Sleep(1000 * 100);
            exit(1);
        }
        catch (...) {
            logger.error("Config File isInvalid");
            Sleep(1000 * 100);
            exit(1);
        }
    }
    else {
        logger.info("Config with default values created");
        TRUS::WriteDefaultConfig("plugins/BEPlaceholderAPI/lang/en_US.json");
    }
}

void PAPIinit();
void RegCommand();
void PluginInit()
{
    loadCfg();
    CheckProtocolVersion();
    PAPIinit();
    RegCommand();
    CheckProtocolVersion();
    Logger().info(" _____          _____  _____");
    Logger().info("|  __ \\  /\\    |  __ \\|_   _|");
    Logger().info("| |__) |/  \\   | |__) | | |    \033[38;5;221mVersion:{}", PLUGIN_VERSION_MAJOR + '.' + PLUGIN_VERSION_MINOR + '.' + PLUGIN_VERSION_REVISION);
    Logger().info("|  ___// /\\ \\  |  ___/  | |    \033[38;5;218mGithub:{}", "https://github.com/LiteLDev/BEPlaceholderAPI" );
    Logger().info("| |   / ____ \\ | |     _| |_");
    Logger().info("|_|  /_/    \\_\\|_|    |_____|");
    Logger().info("");
	
}


