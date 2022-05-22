local  PAPIgetValueAPI = ll.import("BEPlaceholderAPI","GetValue")
local  PAPIgetValueByPlayerAPI = ll.import("BEPlaceholderAPI","GetValueWithPlayer")
local  PAPIregisterPlayerPlaceholderAPI = ll.import("BEPlaceholderAPI","registerPlayerPlaceholder")
local  PAPIregisterServerPlaceholderAPI = ll.import("BEPlaceholderAPI","registerServerPlaceholder")
local  PAPIregisterStaticPlaceholderAPI = ll.import("BEPlaceholderAPI","registerStaticPlaceholder")
local PAPItranslateStringAPI = ll.import("BEPlaceholderAPI","translateString")

module = {}

function module.registerPlayerPlaceholder(func,PluginName,PAPIName)
    ll.export(func,PluginName,tostring(func))
    PAPIregisterPlayerPlaceholderAPI(PluginName,tostring(func),PAPIName)
end

function module.registerServerPlaceholder(func,PluginName,PAPIName)
    ll.export(func,PluginName,tostring(func))
    PAPIregisterServerPlaceholderAPI(PluginName,tostring(func),PAPIName)
end

function module.registerStaticPlaceholder(func,PluginName,PAPIName,UpdateInterval)
    ll.export(func,PluginName,tostring(func))
    PAPIregisterStaticPlaceholderAPI(PluginName,tostring(func),PAPIName,UpdateInterval)
end

function module.getValue(key)
    return PAPIgetValueAPI(key)
end

function module.getValueByPlayer(key,xuid)
    return PAPIgetValueByPlayerAPI(key,xuid)
end

function module.translateString(str,xuid)
    return PAPItranslateStringAPI(str,xuid)
end

return module