# 📮 JS plugin development

## Preparation
#### import library
```JavaScript
const PAPI = require('./lib/BEPlaceholderAPI-JS').PAPI;
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
```JavaScript
const PAPI = require('./lib/BEPlaceholderAPI-JS').PAPI;

// No variables
function PlayerRealName(player){
	return player.realName
}

/ / with a variable
function PlayerTest2(player,object){
		for (let key in object){
				if(key == "<1>"){
						return obj[key] + player.name
				}
		}
		return "Fail";
}

mc.listen("onServerStarted", () => {
    PAPI.registerPlayerPlaceholder(PlayerRealName,"BEPlaceholderAPI_JS","player_test_realname")
		PAPI.registerPlayerPlaceholder(PlayerTest2,"BEPlaceholderAPI_JS","player_test_<1>")
})
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
```JavaScript
const PAPI = require('./lib/BEPlaceholderAPI-JS').PAPI;
//No variable
function ServerVersion(){
    return mc.getBDSVersion()
}
//With variable
function ServerTest2(object){
    for (let key in object){
        if(key == "<1>"){
        return obj[key] + mc.getBDSVersion()
        }
    }
    return "Fail";
}
mc.listen("onServerStarted", () => {
    PAPI.registerServerPlaceholder(ServerVersion,"BEPlaceholderAPI_JS","server_version_test")
    PAPI.registerServerPlaceholder(ServerTest2,"BEPlaceholderAPI_JS","server_test_<1>")
})
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
```JavaScript
const PAPI = require('./lib/BEPlaceholderAPI-JS').PAPI;
let num = 0
function Test4(){
     num++
    return num.toString()
}
mc.listen("onServerStarted", () => {
    PAPI.registerStaticPlaceholder(Test4,"BEPlaceholderAPI_JS","server_test4",50)
})
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
```JavaScript
mc.listen("onServerStarted", () => {
    PAPI.unRegisterPlaceholder("server_tps")
})
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
```JavaScript
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
```JavaScript
mc.listen("onPreJoin", (player) => {
		log(PAPI.getValueByPlayer("player_uuid",player))
})
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

```JavaScript
mc.listen("onPreJoin", (player) => {
   log(PAPI.translateString("HI %player_realname% \nServerTPS:%server_tps%",player))
})
` ` `