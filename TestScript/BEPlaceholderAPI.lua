GetValue = ll.import("BEPlaceholderAPI","GetValue")
GetValueByPlayer = ll.import("BEPlaceholderAPI","GetValueWithPlayer")
PAPIregisterInit = ll.import("BEPlaceholderAPI","registerInit")

mc.listen("onUseItem", function (player,item)
    player.sendText("LuaTest\nName:"+GetValueByPlayer("PlayerRealName",player.xuid)+ " Health:"+GetValueByPlayer("PlayerHealth",player.xuid),0)
end)

function RegisterPAPI(func,PluginName,FuncName,PAPIName)

    ll.export(func,PluginName,FuncName)
    PAPIregisterInit(PluginName,FuncName,PAPIName)

end


function PlayerHealth(xuid)
    local pl = mc.getPlayer(xuid)
    return pl.health
end

mc.listen('onServerStarted',function() 
    RegisterPAPI(PlayerHealth,"BEPlaceholderAPI_JS","PlayerHealth","PlayerHealth")
end)