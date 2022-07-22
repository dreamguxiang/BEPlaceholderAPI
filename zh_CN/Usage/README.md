# 如何安装BEPlaceholderAPI

## 💻 安装

### 安装LiteLoader
1.可以前往[LiteLoader Docs](https://docs.litebds.com/#/zh_CN/Usage/)查看如何安装LiteLoader

### 安装BEPlaceholderAPI
1.前往[Minebbs]()或[Github release](https://github.com/dreamguxiang/BEPlaceholderAPI/releases)下载最新的`BEPlaceholderAPI-版本号.zip`压缩包

2.将压缩文件内的所有内容解压到`plugin`文件夹中。如果解压过程中出现文件冲突，选择覆盖即可。
>请不要解压文件夹到`plugins`文件夹

3.享受BEPlaceholderAPI

## 🎯 BEPlaceholderAPI指令
- `placeholder list`
**列出** 当前注册的BEPlaceholderAPI变量

- `placeholder help`
**输出** BEPlaceholderAPI指令的帮助列表

- `placeholder reload`
**热重载** 所有的BEPlaceholderAPI变量

- `placeholder info [可选/插件名称]`
**获取** 详细变量名称

- `placeholder unregister <变量名/插件名>`
**取消** 注册某个变量名或者插件

## 自带变量

### 变量须使用百分号%包裹使用
<br>

### 玩家变量
|  变量名   | 介绍  |
|  ----  | ----  |
| player_realname  | 玩家名 |
| player_uuid  | 玩家UUID |
| player_ping    | 玩家延迟 |
| player_health   | 玩家生命值 |
| player_max_health   | 玩家最大生命值 |
| player_gamemode   | 玩家游戏模式 |
| player_x   | 玩家X坐标 |
| player_y   | 玩家Y坐标 |
| player_z   | 玩家Z坐标 |
| player_direction   | 玩家朝向 |
| player_exp_level   | 玩家经验 |
| player_speed   |  玩家速度 |
| player_flying   | 玩家是否正在飞行 |
| player_can_fly   |玩家能否飞行 |
| player_displayname   | 玩家名称下方显示内容 |
| player_is_op   |玩家是否为OP |
| player_item_in_hand   | 玩家手中物品 |
| player_ip    | 玩家IP |
| player_device    | 玩家设备 |
| player_language    |  玩家语言 |
| player_xuid    |  玩家XUID |
| player_bed_x    | 玩家床的X坐标 |
| player_bed_y     | 玩家床的Y坐标 |
| player_bed_z     | 玩家床的Z坐标 |
| player_hunger     |  玩家饥饿值 |
| player_max_hunger     | 玩家最大饥饿值 |

### 服务器变量

|  变量名   | 介绍  |
|  ----  | ----  |
| server_time_`<format>`  | 现实时间 |
| server_online  | 服务器在线人数 |
| server_max_players     | 服务器最大在线数 |
| server_version    | 服务器版本 |
| server_protocol_version    | 服务器协议版本 |
| server_total_entities    | 服务器实体总数 |
| server_world_name    | 世界名称 |
| server_seed    |世界种子 |
| server_on_allowlist    | 服务器是否开启白名单 |
| server_difficulty    | 世界难度 |
| server_port    | 服务器端口 |
| server_port_v6    |  服务器ipv6端口 |
| server_uptime   | 服务器运行时间 |
| server_start_time_`<format>`   |服务器启动时间 |
| server_name   | 服务器名 |
| server_has_whitelist    |服务器有无白名单|
| server_ram_bds_used    | BDS核心使用内存|
| server_ram_free    | 服务器空闲内存 |
| server_ram_used     | 服务器使用总内存 |
| server_ram_max     |  服务器最大内存 |
| server_tps     |  服务器TPS |
| server_mspt     | 服务器MSPT |