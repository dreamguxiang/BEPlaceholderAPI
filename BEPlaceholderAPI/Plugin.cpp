#include "Global.h"
#include <ServerAPI.h>
#include "Lang.hpp"
#include <windows.h>
Logger logger(PLUGIN_NAME);

inline void CheckProtocolVersion() {
    auto currentProtocol = ll::getServerProtocolVersion();
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
}

void PAPIinit();
void RegCommand();
void PluginInit()
{
    loadCfg();
    CheckProtocolVersion();
    PAPIinit();
    RegCommand();
    Logger().info(" _____          _____  _____");
    Logger().info("|  __ \\  /\\    |  __ \\|_   _|");
    Logger().info("| |__) |/  \\   | |__) | | |    \033[38;5;221mVersion:{}", PLUGIN_VERSION_STRING);
    Logger().info("|  ___// /\\ \\  |  ___/  | |    \033[38;5;218mGithub:{}", "https://github.com/LiteLDev/BEPlaceholderAPI" );
    Logger().info("| |   / ____ \\ | |     _| |_");
    Logger().info("|_|  /_/    \\_\\|_|    |_____|");
    Logger().info("");
	
}


