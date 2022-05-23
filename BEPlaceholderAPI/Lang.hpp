#include "Global.h"
#define TRJ(key,val)                                         \
if (json.find(key) != json.end()) {                          \
    const nlohmann::json& out = json.at(key);                \
    out.get_to(val);}                                         \

namespace TRZH {

    string papi_command_help = "§g-------BEPlaceholderAPI帮助-------\n§a/placeholder list   §b列出注册PAPI的插件列表\n§a/placeholder info [可选/插件名称]   §b获取详细变量名称\n§a/placeholder unregister <变量名/插件名>   §b取消注册某个变量名或者插件";
    string papi_command = "§6PlaceholderApi 命令系统";
    string papi_command_list = "§g已加载的PAPI拓展插件列表§r\n";
    string papi_command_infoall = "§g所有变量列表§r\n";
	string papi_command_info = "§g<{0}>变量列表§r\n";
	string papi_command_unregister_success = "§a成功取消注册<{0}>";
	string papi_command_unregister_fail = "§c无法取消注册<{0}>,可能没有被注册或者已经被取消";
	string papi_command_reload = "§a成功重载§r";
	
	
    nlohmann::json globaljson() {
        nlohmann::json json;
        json["papi.command.help"] = papi_command_help;
        json["papi.command"] = papi_command;
        json["papi.command.list"] = papi_command_list;
        json["papi.command.infoall"] = papi_command_infoall;
        json["papi.command.info"] = papi_command_info;
        json["papi.command.unregister.success"] = papi_command_unregister_success;
        json["papi.command.unregister.fail"] = papi_command_unregister_fail;
        json["papi.command.reload"] = papi_command_reload;
        return json;
    }
    void initjson(nlohmann::json json) {
        TRJ("papi.command.help", papi_command_help);
        TRJ("papi.command", papi_command);
        TRJ("papi.command.list", papi_command_list);
        TRJ("papi.command.infoall", papi_command_infoall);
        TRJ("papi.command.info", papi_command_info);
        TRJ("papi.command.unregister.success", papi_command_unregister_success);
        TRJ("papi.command.unregister.fail", papi_command_unregister_fail);
        TRJ("papi.command.reload", papi_command_reload);
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
}


namespace TRUS {

    string papi_command_help = "§g-------BEPlaceholderAPI help -------\n§a/placeholder list   §bList of registered PAPI plugins\n§a/placeholder info [optional/plugin name]   §bGet detailed variable names\n§a/placeholder unregister <variable name/plugin name>   §bUnregister a variable name or plugin";
    string papi_command = "§6PlaceholderApi command system";
    string papi_command_list = "§g List of loaded PAPI extension plugins §r\n";
    string papi_command_infoall = "§gList of all placeholder§r\n";
    string papi_command_info = "§g<{0}>placeholder list§r\n";
    string papi_command_unregister_success = "§aSuccessfully unregister <{0}>";
    string papi_command_unregister_fail = "§cUnable to unregister<{0}>,May not be registered or may have been cancelled";
    string papi_command_reload = "§aReload successfully!";


    nlohmann::json globaljson() {
        nlohmann::json json;
        json["papi.command.help"] = papi_command_help;
        json["papi.command"] = papi_command;
        json["papi.command.list"] = papi_command_list;
        json["papi.command.infoall"] = papi_command_infoall;
        json["papi.command.info"] = papi_command_info;
        json["papi.command.unregister.success"] = papi_command_unregister_success;
        json["papi.command.unregister.fail"] = papi_command_unregister_fail;
        json["papi.command.reload"] = papi_command_reload;
        return json;
    }
    void initjson(nlohmann::json json) {
        TRJ("papi.command.help", papi_command_help);
        TRJ("papi.command", papi_command);
        TRJ("papi.command.list", papi_command_list);
        TRJ("papi.command.infoall", papi_command_infoall);
        TRJ("papi.command.info", papi_command_info);
        TRJ("papi.command.unregister.success", papi_command_unregister_success);
        TRJ("papi.command.unregister.fail", papi_command_unregister_fail);
        TRJ("papi.command.reload", papi_command_reload);
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
}