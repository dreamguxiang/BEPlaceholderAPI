const PAPIgetValueAPI = ll.import("BEPlaceholderAPI","GetValue")
const PAPIgetValueByPlayerAPI = ll.import("BEPlaceholderAPI","GetValueWithPlayer")
const PAPIregisterPlayerPlaceholderAPI = ll.import("BEPlaceholderAPI","registerPlayerPlaceholder")
const PAPIregisterServerPlaceholderAPI = ll.import("BEPlaceholderAPI","registerServerPlaceholder")

class PAPI{
    constructor() {}

    static registerPlayerPlaceholder(func,PluginName,FuncName,PAPIName){
        ll.export(func,PluginName,FuncName)
        PAPIregisterPlayerPlaceholderAPI(PluginName,FuncName,PAPIName)
    }

    static registerServerPlaceholder(func,PluginName,FuncName,PAPIName){
        ll.export(func,PluginName,FuncName)
        PAPIregisterServerPlaceholderAPI(PluginName,FuncName,PAPIName)
    }
    
    static getValue(key){
        PAPIgetValueAPI(key)
    }

    static getValueByPlayer(key,xuid){
        PAPIgetValueByPlayerAPI(key,xuid)
    }
}

module.exports = {
    PAPI
};