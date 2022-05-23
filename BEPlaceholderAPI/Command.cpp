#include "Global.h"
#include <DynamicCommandAPI.h>
#include "PlaceholderAPI.h"
#include "Helper.h"
#include <ScheduleAPI.h>
#include <I18nAPI.h>

void RegCommand()
{
    using ParamType = DynamicCommand::ParameterType;
    auto command = DynamicCommand::createCommand("placeholder", tr("papi.command"), CommandPermissionLevel::GameMasters);
    command->setAlias("papi");
    auto& PAPIEnumList = command->setEnum("PAPIList", { "list","help","reload"});
    auto& PAPIEnumInfo = command->setEnum("PAPIInfo", { "info"});
    auto& PAPIEnumReg = command->setEnum("PAPIReg", { "unregister"});
	
    command->optional("PAPIPluginsNameEnum", ParamType::SoftEnum,command->setSoftEnum("PAPIPluginsNameList", {}));
    command->mandatory("PAPINameEnum", ParamType::SoftEnum, command->setSoftEnum("PAPINameList", {}));
	
	
    command->mandatory("PAPIEnum", ParamType::Enum, PAPIEnumList);
    command->mandatory("PAPIEnum", ParamType::Enum, PAPIEnumInfo);
    command->mandatory("PAPIEnum", ParamType::Enum, PAPIEnumReg);
    command->mandatory("PAPIName", ParamType::String); 
	

    command->addOverload({ PAPIEnumList });
    command->addOverload({ PAPIEnumInfo, "PAPIPluginsNameEnum" });
    command->addOverload({ PAPIEnumReg, "PAPINameEnum" });
	
    command->setCallback([](DynamicCommand const& command, CommandOrigin const& origin, CommandOutput& output, std::unordered_map<std::string, DynamicCommand::Result>& results) {
        auto action = results["PAPIEnum"].get<std::string>();
        string str = "";
        auto sp = origin.getPlayer();
        switch (do_hash(action.c_str()))
        {
        case do_hash("list"): {
            auto PAPIList = PlaceholderAPI::getPAPIPluginsList();
            str += tr("papi.command.list");
			int i = 0;
            for (auto& papi : PAPIList) 
            {
                str += std::to_string(++i) +".§a" + papi + "§r\n";
            }
            output.success(str);
            break;
        }
        
        case do_hash("info"): {
            auto list = PlaceholderAPI::getPAPIInfoList();
            if (results["PAPIPluginsNameEnum"].isSet) {
                auto PAPIName = results["PAPIPluginsNameEnum"].getEnumValue();
                str += tr("papi.command.info", PAPIName);
                int i = 0;
                for (auto& papi : list) {
                    if (papi.getPluginName() == PAPIName) {
                        str += std::to_string(++i) + ".§a%" + papi.mName + "%§r\n";
                    }
                }
                output.success(str);
            }
            else {
                str += tr("papi.command.infoall");
                int i = 0;
                for (auto& papi : list) {
                    str += std::to_string(++i) + ".§a%" + papi.mName + "%§r\n";
                }
                output.success(str);
            }
            break;
        }

        case do_hash("unregister"): {
            auto PAPIName = results["PAPINameEnum"].getEnumValue();
            auto out = PlaceholderAPI::unRegisterPlaceholder(PAPIName);
            if (out) {
                output.success(BEPAPI + tr("papi.command.unregister.success", PAPIName));
            }
            else {
                output.error(BEPAPI + tr("papi.command.unregister.fail", PAPIName));
            }
            break;
        }
        case do_hash("help"): {
            output.success(tr("papi.command.help")+"\n\n§l§c@By §6DreamGuXiang&QingYu");
            break;
        }
        case do_hash("reload"): {
            Settings::LoadConfigFromJson(JsonFile);
            Translation::load("plugins/BEPlaceholderAPI/lang/" + Settings::LangCode + ".json");
            output.success(BEPAPI + tr("papi.command.reload"));
            break;
        }
        default:
            break;
        }
        });
    auto cmd = DynamicCommand::setup(std::move(command));
    Schedule::repeat([cmd] {
        cmd->addSoftEnumValues("PAPIPluginsNameList", Helper::getPAPIPlugins());
        cmd->addSoftEnumValues("PAPINameList", Helper::getPAPIInfoList());
        }, 200);
}
