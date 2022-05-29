#include "Global.h"
#include <ServerAPI.h>
#include "Lang.hpp"
Logger logger(PLUGIN_NAME);

//×Ö·û»­
string pic = \
"               _____          _____  _____\n"\
"              |  __ \\  /\\    |  __ \\|_   _|\n" \
"              | |__) |/  \\   | |__) | | |\n" \
"              |  ___// /\\ \\  |  ___/  | |\n" \
"              | |   / ____ \\ | |     _| |_\n" \
"              |_|  /_/    \\_\\|_|    |_____|\n\n"\
"   --------  \033[38;5;221mBEPlaceholderAPI \033[38;5;218mVersion\033[38;5;75m:\033[38;5;196m";

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

void fixUpLibDir() {
    WCHAR* buffer = new (std::nothrow) WCHAR[1024];
    if (!buffer)
        return;

    DWORD length = GetEnvironmentVariableW(TEXT("PATH"), buffer, 1024);
    std::wstring PATH(buffer, length);
    length = GetCurrentDirectoryW(1024, buffer);
    std::wstring CWD(buffer, length);

    SetEnvironmentVariableW(TEXT("PATH"), (CWD + L"\\plugins\\BEPlaceholderAPI\\lib;" + PATH).c_str());
    delete[] buffer;
}

void PAPIinit();
void RegCommand();
void checkVersion();
void PluginInit()
{
    fixUpLibDir();
    loadCfg();
    CheckProtocolVersion();
    PAPIinit();
    RegCommand();
    CheckProtocolVersion();
    checkVersion();
    std::cout << pic << PLUGIN_VERSION_MAJOR << '.' << PLUGIN_VERSION_MINOR << '.' << PLUGIN_VERSION_REVISION << "\033[0m  --------\n\n";
    logger.info("Loaded.");
}


