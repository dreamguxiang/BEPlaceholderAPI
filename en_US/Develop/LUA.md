# 📮 JS plugin development

## Preparation
# # # # import library
```Lua
local PAPI = require("plugins.lib.BEPlaceholderAPI-LUA")
```

## API documentation

### Register player variables

`PAPI.registerPlayerPlaceholder(Func,PluginName,PAPIName)`

- parameters:
  - Func : `Function`
		Bind a function to a variable
	- PluginName : `String`
		The plugin name
	- PAPIName : `String`
		The variable name
- Returned value: None

#### Func function definition
`test(player[,object])`
- parameters
	- player : `Player`
		The player object
	- object : `Object<string-string>`
		(Optional) Variable parameter content object
		Each key-value in the object corresponds to the parameter name-return value

- the return value
	- String corresponding to the variable
	- Type: `String`


#### sample
```Lua
local PAPI = require("plugins.lib.BEPlaceholderAPI-LUA")

--No variables
function PlayerRealName(player)
    return player.realName
end


--with a variable
function PlayerTest2(player,table)
    for k, v in pairs(table) do
        if k ==  "<0>" then
           return v + player.uuid
        end
    end
    return "Fail"
end

mc.listen('onServerStarted',function() 
    PAPI.registerPlayerPlaceholder(PlayerRealName,"BEPlaceholderAPI_LUA","player_test_realname")
    PAPI.registerPlayerPlaceholder(PlayerTest2,"BEPlaceholderAPI_LUA","player_test_<1>")
end)
```

<br>


### Register server variables

`PAPI.registerServerPlaceholder(Func,PluginName,PAPIName)`

- parameters:
	- Func : `Function`
		Bind a function to a variable
	- PluginName : `String`
		The plugin name
	- PAPIName : `String`
		The variable name
- Returned value: None

#### Func function definition
`test([,object])`
- parameters
	- object : `Object<string-string>`</string-string>
		(Optional) Variable parameter content object
		Each key-value in the object corresponds to the parameter name-return value

- the return value
	- String corresponding to the variable
	- Type: `String`


#### sample
```Lua
local PAPI = require("plugins.lib.BEPlaceholderAPI-LUA")
--No variables
function ServerVersion()
    return mc.getBDSVersion()
end
--with a variable
function ServerTest2(table)
    for k, v in pairs(table) do
        if k ==  "<1>" then
           return v + mc.getBDSVersion()
       end
    end
    return "Fail"
end

mc.listen('onServerStarted',function() 
    PAPI.registerServerPlaceholder(ServerVersion,"BEPlaceholderAPI_LUA","server_version_test")
    PAPI.registerServerPlaceholder(ServerTest2,"BEPlaceholderAPI_LUA","server_test_<1>")
end)
```




### Register static variables

`registerStaticPlaceholder(Func,PluginName,PAPIName,UpdateInterval)`

- parameters:
	- Func : `Function`
		Bind a function to a variable
	- PluginName : `String`
		The plugin name
	- PAPIName : `String`
		The variable name
	- UpdateInterval : `Number`
		Update interval (set '-1' to no update)
- Returned value: None

#### Func function definition
`test()`
- the return value
	- String corresponding to the variable
	- Type: `String`

#### sample
```Lua
local PAPI = require("plugins.lib.BEPlaceholderAPI-LUA")

local num = 0
function Test4()
     num++
    return tostring(num)
end

mc.listen('onServerStarted',function() 
    PAPI.registerStaticPlaceholder(Test4,"BEPlaceholderAPI_JS","server_test4",50)
end)
```





### Unregister variables

`PAPI.unRegisterPlaceholder(PAPIName)`
- parameters:
	- PAPIName : `String`
		The variable name
- the return value
	- Success or not
	- type; `Boolean`

#### sample
```Lua
mc.listen('onServerStarted',function() 
    PAPI.unRegisterPlaceholder("server_tps")
end)
```

<br>


### Get the variable value

`PAPI.getValue(PAPIName)`

- parameters:
- PAPIName : `String`
The variable name
- the return value
- a variable's value
- Type: `String`

#### sample
```Lua
PAPI.getValue("server_tps")
```




### Get the value of the variable required for the player object

`PAPI.getValueByPlayer(PAPIName,player)`

- parameters:
	- PAPIName : `String`
		The variable name
	- player : `Player`
		The player object
- the return value
	- a variable's value
	- Type: `String`

#### sample
```Lua
mc.listen('onPreJoin',function(player) 
   PAPI.getValueByPlayer("player_uuid",player)
end)
```




### Translate text (get strings containing multiple variables)

`PAPI.translateString(str,player)`
- parameters:
	- str : `String`
		Text to be translated
	- player : `Player`
		The player object
- the return value
	- Translated text
	- Type: `String`

```Lua
mc.listen('onPreJoin',function(player) 
   log(PAPI.translateString("HI %player_realname% \nServerTPS:%server_tps%",player))
end)
```