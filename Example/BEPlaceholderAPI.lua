local PAPI = require("plugins.BEPlaceholderAPI.lib.BEPlaceholderAPI-LUA")

function ServerTest3()
    return "3"
end


mc.listen('onServerStarted',function() 
    PAPI.registerServerPlaceholder(ServerTest3,"BEPlaceholderAPI_LUA","server_test3")
end)