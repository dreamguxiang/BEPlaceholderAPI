#include "Entry.h"

#include <fmt/format.h>
#include <functional>
#include <ll/api/Config.h>
#include <ll/api/io/FileUtils.h>
#include <ll/api/plugin/NativePlugin.h>
#include <ll/api/plugin/PluginManagerRegistry.h>
#include "Global.h"
#include <memory>
#include <stdexcept>
#include <papi/Config.h>
#include <papi/Lang.h>

void PAPIinit();

namespace bet::command {
void registercommand();
}


namespace papi {

namespace {

std::unique_ptr<std::reference_wrapper<ll::plugin::NativePlugin>> selfPluginInstance; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

auto disable(ll::plugin::NativePlugin& /*self*/) -> bool {
    auto& logger = getSelfPluginInstance().getLogger();
    return true;
}


auto enable(ll::plugin::NativePlugin& /*self*/) -> bool {
    auto& logger = getSelfPluginInstance().getLogger();
    bet::command::registercommand();
    return true;
}

auto load(ll::plugin::NativePlugin& self) -> bool {
    auto& logger = self.getLogger();
    selfPluginInstance = std::make_unique<std::reference_wrapper<ll::plugin::NativePlugin>>(self);

    PAPIinit();
    logger.info(" _____          _____  _____");
    logger.info("|  __ \\  /\\    |  __ \\|_   _|");
    logger.info("| |__) |/  \\   | |__) | | |    ");
    logger.info("|  ___// /\\ \\  |  ___/  | |    \033[38;5;218mGithub:{}", "https://github.com/dreamguxiang/BEPlaceholderAPI" );
    logger.info("| |   / ____ \\ | |     _| |_");
    logger.info("|_|  /_/    \\_\\|_|    |_____|");
    logger.info("");

    const auto& configFilePath = self.getConfigDir() / "config.json";
    if (!ll::config::loadConfig(config, configFilePath)) {
        logger.warn("Cannot load configurations from {}", configFilePath);
        logger.info("Saving default configurations");

        if (!ll::config::saveConfig(config, configFilePath)) {
            logger.error("Cannot save default configurations to {}", configFilePath);
        }
    }

    ll::i18n::getInstance() = std::make_unique<ll::i18n::SingleFileI18N>(
        ll::i18n::SingleFileI18N("plugins/BEPlaceholderAPI/language.json", config.LangCode,defaultLangData)
    );
    return true;
}

auto unload(ll::plugin::NativePlugin& self) -> bool {
    auto& logger = self.getLogger();
    selfPluginInstance.reset();
    return true;
}
}
auto getSelfPluginInstance() -> ll::plugin::NativePlugin& {
    if (!selfPluginInstance) {
        throw std::runtime_error("selfPluginInstance is null");
    }
    return *selfPluginInstance;
}
}

extern "C" {
_declspec(dllexport) auto ll_plugin_disable(ll::plugin::NativePlugin& self) -> bool { return papi::disable(self); }
_declspec(dllexport) auto ll_plugin_enable(ll::plugin::NativePlugin& self) -> bool { return papi::enable(self); }
_declspec(dllexport) auto ll_plugin_load(ll::plugin::NativePlugin& self) -> bool { return papi::load(self); }
_declspec(dllexport) auto ll_plugin_unload(ll::plugin::NativePlugin& self) -> bool { return papi::unload(self); }
}
