//LiteLoaderScript Dev Helper
/// <reference path="c:\Users\Admin\Desktop\LiteLoader\plugins/Library/JS/Api.js" /> 

const GetValue = ll.import("BEPlaceholderAPI","GetValue")
const GetValueByPlayer = ll.import("BEPlaceholderAPI","GetValueWithPlayer")
const PAPIregisterInit = ll.import("BEPlaceholderAPI","registerInit")

mc.listen("onUseItem", (player,item) => {
    player.sendText("JsTest\NName:"+GetValueByPlayer("PlayerRealName",player.xuid)+ " Health:"+GetValueByPlayer("PlayerHealth",player.xuid))
})


function RegisterPAPI(func,PluginName,FuncName,PAPIName){
    ll.export(func,PluginName,FuncName)//导出函数
    PAPIregisterInit(PluginName,FuncName,PAPIName)
}

function PlayerHealth(xuid){
    var pl = mc.getPlayer(xuid)
    return pl.health.toString()   
}

mc.listen("onServerStarted", () => {
    RegisterPAPI(PlayerHealth,"BEPlaceholderAPI_JS","PlayerHealth","PlayerHealth")
})