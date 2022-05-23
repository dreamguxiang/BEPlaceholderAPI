#include "Setting.h"
#define JSON2(key1,key2,val)                                \
if (json.find(key1) != json.end()) {                      \
    if (json.at(key1).find(key2) != json.at(key1).end()) {\
    const nlohmann::json& out2 = json.at(key1).at(key2);  \
         out2.get_to(val);}}                              \

#define JSON1(key,val)                                         \
if (json.find(key) != json.end()) {                          \
    const nlohmann::json& out = json.at(key);                \
    out.get_to(val);}                                         \

namespace Settings {

    string LangCode = "zh_CN";
    namespace Chat {
        bool Enabled = true;
        bool CanUseBrackets = true;
    }
    namespace Sign {
        bool Enabled = true;
    }
	

    nlohmann::json globaljson() {
        nlohmann::json json;
        json["LangCode"] = LangCode;
        json["Chat"]["Enabled"] = Chat::Enabled;
		json["Sign"]["Enabled"] = Sign::Enabled;
        return json;
    }

    void initjson(nlohmann::json json) {
        JSON1("LangCode", LangCode);
        JSON2("Chat", "Enabled", Chat::Enabled);
        JSON2("Sign", "Enabled", Sign::Enabled);
    }

    void WriteDefaultConfig(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Can't open file " << fileName << std::endl;
            return;
        }
        auto json = globaljson();
        file << json.dump(4);
        file.close();
    }

    void LoadConfigFromJson(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Can't open file " << fileName << std::endl;
            return;
        }
        nlohmann::json json;
        file >> json;
        file.close();
        initjson(json);
        WriteDefaultConfig(fileName);
    }
	
    void reloadJson(const std::string& fileName) {
        std::ofstream file(fileName);
        if (file)
        {
            file << globaljson().dump(4);
        }
        else
        {
            Logger("BEPlaceholderAPI").error("Configuration File Creation failed!");
        }
        file.close();
    }
} // namespace Settings


