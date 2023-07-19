# 📮 JS插件开发

## 准备工作
#### 引入库
```JavaScript
const PAPI = require('./lib/BEPlaceholderAPI-JS').PAPI;
```

## API文档

### 注册玩家变量

`PAPI.registerPlayerPlaceholder(Func,PluginName,PAPIName)`

- 参数：
  - Func : `Function`   
      与变量绑定函数
  - PluginName : `String`   
      插件名
  - PAPIName : `String`   
      变量名
- 返回值：无

#### Func函数定义
 `test(player[,object])`
 - 参数
   - player : `Player`   
    玩家对象
   - object : `Object<String-String>`   
   （可选参数）变量参数内容对象   
    对象中的每个键 - 值对应参数名 - 返回值

- 返回值
  - 变量对应的字符串
  - 类型: `String`


#### 示例
```JavaScript
const PAPI = require('./lib/BEPlaceholderAPI-JS').PAPI;

//不带变量
function PlayerRealName(player){
    return player.realName
}

//带变量
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

### 注册服务器变量

`PAPI.registerServerPlaceholder(Func,PluginName,PAPIName)`

- 参数：
  - Func : `Function`   
      与变量绑定函数
  - PluginName : `String`   
      插件名
  - PAPIName : `String`   
      变量名
- 返回值：无

#### Func函数定义
 `test([,object])`
 - 参数
   - object : `Object<String-String>`   
   （可选参数）变量参数内容对象   
    对象中的每个键 - 值对应参数名 - 返回值

- 返回值
  - 变量对应的字符串
  - 类型: `String`


#### 示例
```JavaScript
const PAPI = require('./lib/BEPlaceholderAPI-JS').PAPI;
//不带变量
function ServerVersion(){
    return mc.getBDSVersion()
}
//带变量
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

<br>

### 注册静态变量

`registerStaticPlaceholder(Func,PluginName,PAPIName,UpdateInterval)`

- 参数：
  - Func : `Function`   
      与变量绑定函数
  - PluginName : `String`   
      插件名
  - PAPIName : `String`   
      变量名
  - UpdateInterval : `Number`   
      更新间隔(设置`-1`为不更新)
- 返回值：无

#### Func函数定义
 `test()`
- 返回值
  - 变量对应的字符串
  - 类型: `String`

#### 示例
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

<br>

### 取消注册变量

`PAPI.unRegisterPlaceholder(PAPIName)`
- 参数：
  - PAPIName : `String`   
      变量名
- 返回值
  - 是否成功
  - 类型；`Boolean`

#### 示例
```JavaScript
mc.listen("onServerStarted", () => {
    PAPI.unRegisterPlaceholder("server_tps")
})
```

<br>

### 获得变量值

`PAPI.getValue(PAPIName)`

- 参数：
  - PAPIName : `String`   
      变量名
- 返回值
  - 变量值
  - 类型: `String`

#### 示例
```JavaScript
PAPI.getValue("server_tps")
```

<br>

### 获得需要玩家对象的变量值

`PAPI.getValueByPlayer(PAPIName,xuid)`

- 参数：
  - PAPIName : `String`   
      变量名
  - xuid : `String`   
      玩家xuid
- 返回值
  - 变量值
  - 类型: `String`

#### 示例
```JavaScript
mc.listen("onPreJoin", (player) => {
   log(PAPI.getValueByPlayer("player_uuid",player))
})
```

<br>

### 翻译文本(获取包含多个变量的字符串)

`PAPI.translateString(str,player)`
- 参数：
  - str : `String`   
      需要翻译的文本
  - player : `Player`   
      玩家对象
- 返回值
  - 翻译后文本
  - 类型: `String`

```JavaScript
mc.listen("onPreJoin", (player) => {
   log(PAPI.translateString("HI %player_realname% \nServerTPS:%server_tps%",player))
})
```

