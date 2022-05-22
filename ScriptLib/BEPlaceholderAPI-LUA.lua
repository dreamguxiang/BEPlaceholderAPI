local  PAPIgetValueAPI = ll.import("BEPlaceholderAPI","GetValue")
local  PAPIgetValueByPlayerAPI = ll.import("BEPlaceholderAPI","GetValueWithPlayer")
local  PAPIregisterPlayerPlaceholderAPI = ll.import("BEPlaceholderAPI","registerPlayerPlaceholder")
local  PAPIregisterServerPlaceholderAPI = ll.import("BEPlaceholderAPI","registerServerPlaceholder")

module = {}

function module.registerPlayerPlaceholder(func,PluginName,FuncName,PAPIName)
    ll.export(func,PluginName,FuncName)
    PAPIregisterPlayerPlaceholderAPI(PluginName,FuncName,PAPIName)
end

function module.registerServerPlaceholder(func,PluginName,FuncName,PAPIName)
    ll.export(func,PluginName,FuncName)
    PAPIregisterServerPlaceholderAPI(PluginName,FuncName,PAPIName)
end

function module.getValue(key)
    PAPIgetValueAPI(key)
end

function module.getValueByPlayer(key,xuid)
    PAPIgetValueByPlayerAPI(key,xuid)
end

return module