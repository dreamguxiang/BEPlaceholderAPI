# 📮 LUA插件开发

## 准备工作
#### 引入库
```Lua
local PAPI = require("plugins.lib.BEPlaceholderAPI-LUA")
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
 `test(player[,metatable])`
 - 参数
   - player : `Player`   
    玩家对象
   - metatable : `Metatable<String-String>`   
   （可选参数）变量参数内容元表   
    元表中的每个键 - 值对应参数名 - 返回值

- 返回值
  - 变量对应的字符串
  - 类型: `String`


#### 示例
```Lua
local PAPI = require("plugins.lib.BEPlaceholderAPI-LUA")

--不带变量
function PlayerRealName(player)
    return player.realName
end


--带变量
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
 `test(player[,metatable])`
 - 参数
   - metatable : `Metatable<String-String>`   
   （可选参数）变量参数内容元表   
    元表中的每个键 - 值对应参数名 - 返回值

- 返回值
  - 变量对应的字符串
  - 类型: `String`


#### 示例
```Lua
local PAPI = require("plugins.lib.BEPlaceholderAPI-LUA")
--不带变量
function ServerVersion()
    return mc.getBDSVersion()
end
--带变量
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
```Lua
mc.listen('onServerStarted',function() 
    PAPI.unRegisterPlaceholder("server_tps")
end)
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
```Lua
PAPI.getValue("server_tps")
```

<br>

### 获得需要玩家对象的变量值

`PAPI.getValueByPlayer(PAPIName,player)`

- 参数：
  - PAPIName : `String`   
      变量名
  - player : `Player`   
      玩家对象
- 返回值
  - 变量值
  - 类型: `String`

#### 示例
```Lua
mc.listen('onPreJoin',function(player) 
   PAPI.getValueByPlayer("player_uuid",player)
end)
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

```Lua
mc.listen('onPreJoin',function(player) 
   log(PAPI.translateString("HI %player_realname% \nServerTPS:%server_tps%",player))
end)
```

