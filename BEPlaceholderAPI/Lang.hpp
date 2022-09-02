#include "Global.h"
#include <I18nAPI.h>

#pragma once
#include <I18nAPI.h>

static const SingleFileI18N::LangData defaultLangData = {
    {"en_US", {
         {"papi.command.help", "§g-------BEPlaceholderAPI help -------\n§a/placeholder list   §bList of registered PAPI plugins\n§a/placeholder info [optional/plugin name]   §bGet detailed variable names\n§a/placeholder unregister <variable name/plugin name>   §bUnregister a variable name or plugin"},
         {"papi.command", "§6PlaceholderApi command system"},
         {"papi.command.info", "§g<{0}>placeholder list§r\n"},
         {"papi.command.infoall", "§gList of all placeholder§r\n"},
         {"papi.command.list", "§g List of loaded PAPI extension plugins §r\n"},
         {"papi.command.reload", "§aReload successfully!"},
         {"papi.command.unregister.fail", "§cUnable to unregister<{0}>,May not be registered or may have been cancelled"},
         {"papi.command.unregister.success", "§aSuccessfully unregister <{0}>"},
    }},
    {"zh_CN", {
         {"papi.command.help", "§g------ - BEPlaceholderAPI帮助------ - \n§a / placeholder list   §b列出注册PAPI的插件列表\n§a / placeholder info[可选 / 插件名称]   §b获取详细变量名称\n§a / placeholder unregister <变量名 / 插件名>   §b取消注册某个变量名或者插件"},
         {"papi.command", "§6PlaceholderApi 命令系统"},
         {"papi.command.info", "§g<{0}>变量列表§r\n"},
         {"papi.command.infoall", "§g所有变量列表§r\n"},
         {"papi.command.list", "§g已加载的PAPI拓展插件列表§r\n"},
         {"papi.command.reload", "§a成功重载§r"},
         {"papi.command.unregister.fail", "§c无法取消注册<{0}>,可能没有被注册或者已经被取消"},
         {"papi.command.unregister.success", "§a成功取消注册<{0}>"},
    }}
};