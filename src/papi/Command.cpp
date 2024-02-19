#include "Global.h"

#include "PlaceholderAPI.h"
#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"
#include "ll/api/command/SoftEnum.h"

#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>
#include <ll/api/Config.h>
#include <papi/Entry.h>
#include <papi/Config.h>

using namespace ll::command;

namespace bet::command {

using namespace ll::i18n_literals;

struct PAPI {

    enum class PAPI_List {
        list, help, reload
    } PAPIList;

    enum class PAPI_Info {
        info
    } PAPIInfo;

    enum class PAPI_Reg {
        unregister
    } PAPIReg;

    enum class PAPI_Name{

    } PAPIName;
    enum class PAPI_Plugins_Name{

    } PAPIPluginsName;

    SoftEnum<PAPI_Plugins_Name> PAPIPluginsNameList;
    SoftEnum<PAPI_Name> PAPINameList;

};



void registercommand() {

    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        "placeholder",
        "papi.command"_tr(),
        CommandPermissionLevel::GameDirectors,
        CommandFlagValue::None
    );
    cmd.overload<PAPI>()
        .required("PAPIList")
        .execute<[&](CommandOrigin const& origin, CommandOutput& output, PAPI const& param, ::Command const& cmd) {
            switch(param.PAPIList) {
            case PAPI::PAPI_List::list: {
                std::string str       = "";
                auto        PAPIList  = PlaceholderAPI::getPAPIPluginsList();
                str                  += "papi.command.list"_tr();
                int i                 = 0;
                for (auto& papi : PAPIList) {
                    str += std::to_string(++i) + ".§a" + papi + "§r\n";
                }
                output.success(str);

                break;
            }
            case PAPI::PAPI_List::help:
                output.success("papi.command.help"_tr()+"\n\n§l§c@By §6DreamGuXiang&QingYu");
                break;
            case PAPI::PAPI_List::reload:
                const auto& configFilePath =  papi::getSelfPluginInstance().getConfigDir() / "config.json";
                ll::config::loadConfig(config, configFilePath);

                ll::i18n::getInstance() = std::make_unique<ll::i18n::SingleFileI18N>(
                    ll::i18n::SingleFileI18N("plugins/BEPlaceholderAPI/language.json", config.LangCode)
                );
                break;
            }
    }>();

    cmd.overload<PAPI>()
        .required("PAPIInfo")
        .execute<[&](CommandOrigin const& origin, CommandOutput& output, PAPI const& param, ::Command const& cmd) {
              switch(param.PAPIInfo) {
              case PAPI::PAPI_Info::info:
                  auto list = PlaceholderAPI::getPAPIInfoList();
                  if (results["PAPIPluginsNameEnum"].isSet) {
                      auto PAPIName = param.PAPIPluginsNameList;
                      str += "papi.command.info", PAPIName);
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
        }>();
}

}