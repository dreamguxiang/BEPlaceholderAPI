#pragma once
#include "Global.h"

namespace Settings {

    namespace Chat {
       extern bool Enabled;
       extern bool CanUseBrackets;
    }


    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void WriteDefaultConfig(const std::string& fileName);
    void LoadConfigFromJson(const std::string& fileName);
    void reloadJson(const std::string& fileName);
}