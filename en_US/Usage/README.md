# How to install the BEPlaceholderAPI

## 💻 installation

### Install LiteLoader
1. You can go to [LiteLoader Docs](https://docs.litebds.com/#/en_US/Usage/) to see how to install LiteLoader

### Install BEPlaceholderAPI
1. Head to [Minebbs]() or [Github](https://github.com/dreamguxiang/BEPlaceholderAPI/releases) to download the latest release `BEPlaceholderAPI-version.zip` compressed package

2. Unpack all contents of the compressed file into the `plugin` folder. If file conflicts occur during decompression, select overwrite.
> Please do not unzip folders into the `plugins` folder

3. Enjoy BEPlaceholderAPI

## 🎯 BEPlaceholderAPI
- `placeholder list`
**Lists** the currently registered BEPlaceholderAPI variables

- `placeholder help`
**Return** the help list for the BEPlaceholderAPI directive

- `placeholder reload`
**Hot overload** All BEPlaceholderAPI variables

- `placeholder info [optional/plugin name]`
**Gets the** detailed variable name

- `placeholder unregister < variable name/plugin name>`
**Unregister** a variable name or plug-in

## Self-contained variables

### Variables must be wrapped with the percent sign % using
<br>

### Player Variables
|  Variable Name   | Introduction  |
|  ----  | ----  |
| player_realname  | Player Name |
| player_uuid  | Player UUID |
| player_ping    | Player Ping |
| player_health   | Player Life Value |
| player_max_health   | Player maximum life value |
| player_gamemode   | Player Game Mode |
| player_x   | Player pos X |
| player_y   | Player pos Y |
| player_z   | Player pos Z |
| player_direction   | Player direction |
| player_exp_level   | Player level |
| player_speed   |  Player speed |
| player_flying   | Whether the player is flying |
| player_can_fly   |Can the player fly |
| player_displayname   | Content displayed below player name |
| player_is_op   | is Player OP |
| player_item_in_hand   | Player item in hand |
| player_ip    | Player IP |
| player_device    | Player device |
| player_language    |  Player Language |
| player_xuid    |  Player XUID |
| player_bed_x    | Player bed X |
| player_bed_y     | Player bed Y |
| player_bed_z     | Player bed Z |
| player_hunger     |  Player Hunger Value |
| player_max_hunger     | Player maximum hunger value |

### Server variables

|  Variable Name   | Introduction  |
|  ----  | ----  |
| server_time_`<format>`  | Real Time  |
| server_online  | Number of servers online |
| server_max_players     |  Maximum number of servers online |
| server_version    | Server Version |
| server_protocol_version    | Server Protocol Versions |
| server_total_entities    | Total number of server entities |
| server_world_name    | World Name |
| server_seed    |World Seeds |
| server_on_allowlist    | Server is whitelisted or not |
| server_difficulty    | World Difficulty |
| server_port    |  Server port |
| server_port_v6    |  Server ipv6 port |
| server_uptime   | Server uptime |
| server_start_time_`<format>`   |Server start-up time |
| server_name   | Server name |
| server_has_whitelist    |Server with or without whitelist|
| server_ram_bds_used    | BDS uses memory|
| server_ram_free    | Server Free Memory  |
| server_ram_used     | Total memory used by the server |
| server_ram_max     |  Maximum server memory |
| server_tps     |  Server TPS |
| server_mspt     | Server MSPT |