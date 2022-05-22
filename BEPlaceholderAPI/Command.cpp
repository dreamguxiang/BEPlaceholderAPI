#include "Global.h"
#include <DynamicCommandAPI.h>
#include "PlaceholderAPI.h"

void RegCommand()
{
    using ParamType = DynamicCommand::ParameterType;
    auto command = DynamicCommand::createCommand("papi", "papi command", CommandPermissionLevel::GameMasters);

    auto& PAPIEnumList = command->setEnum("PAPIList", { "list" });
    auto& PAPIEnumInfo = command->setEnum("PAPIInfo", { "info","unregister" });
    command->mandatory("PAPIEnum", ParamType::Enum, PAPIEnumList, CommandParameterOption::EnumAutocompleteExpansion);
    command->mandatory("PAPIEnum", ParamType::Enum, PAPIEnumInfo, CommandParameterOption::EnumAutocompleteExpansion);
    command->mandatory("PAPIName", ParamType::String);


    command->addOverload({ PAPIEnumList });
    command->addOverload({ PAPIEnumInfo,"PAPIName"});
    command->setCallback([](DynamicCommand const& command, CommandOrigin const& origin, CommandOutput& output, std::unordered_map<std::string, DynamicCommand::Result>& results) {
        auto action = results["PAPIEnum"].get<std::string>();
        string str = "";
        auto sp = origin.getPlayer();
        switch (do_hash(action.c_str()))
        {
        case do_hash("list"): {
            auto PAPIList = PlaceholderAPI::getPAPIList();
            str += u8"§gPAPI Expanded List§r\n";
			int i = 0;
            for (auto& papi : PAPIList) 
            {
                str += std::to_string(++i) +".§a" + papi + "§r\n";
            }
            output.success(str);
            break;
        }
        
        case do_hash("info"): {
            auto PAPIName = results["PAPIName"].get<std::string>();
            auto list = PlaceholderAPI::getPAPIInfoList();
            str += u8"§gPAPI " + PAPIName + " Info§r\n";
            int i = 0;
            for (auto& papi : list) {
                if (papi.getPluginName() == PAPIName) {
                    str += std::to_string(++i) + ".§a%" + papi.mName + "%§r\n";
                }
            }
            output.success(str);
            break;
        }

        case do_hash("unregister"): {
            auto PAPIName = results["PAPIName"].get<std::string>();
            auto out = PlaceholderAPI::unRegisterPlaceholder(PAPIName);
            if (out) {
                output.success("Success");
            }
            else {
                output.success("Fail");
            }
            break;
        }
        default:
            break;
        }
        });
    DynamicCommand::setup(std::move(command));
}
