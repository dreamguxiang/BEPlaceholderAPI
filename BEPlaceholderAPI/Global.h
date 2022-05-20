#pragma once


#include <iostream>
#include <Global.h>
#include <MC/Level.hpp>
#include <MC/Player.hpp>
#include <EventAPI.h>
#include <LoggerAPI.h>
#include <MC/BlockInstance.hpp>
#include <MC/Block.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Actor.hpp>
#include <MC/ItemStack.hpp>
#include "Version.h"
#include "Setting.h"
#include <LLAPI.h>
#include <Utils/StringHelper.h>
#include <RemoteCallAPI.h>
#include <ServerAPI.h>
#include <MC/LevelData.hpp>
#include <MC/SignBlockActor.hpp>
#include <MC/BlockActorDataPacket.hpp>
#include <MC/SignItem.hpp>
#include <MC/ServerPlayer.hpp>
#include <MC/ItemStack.hpp>
#include <MC/AttributeInstance.hpp>
#include <MC/ServerNetworkHandler.hpp>
#include <mc/RakPeerHelper.hpp>
#include <MC/Attribute.hpp>
#include <EventAPI.h>
#include <I18nAPI.h>
#include <MC/LevelChunk.hpp>


extern Logger logger;
#define S(x) std::to_string(x)
#define JsonFile "plugins/BEPlaceholderAPI/config.json"
#define VERSION LL::Version{PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION, PLUGIN_LLVERSION_STATUS}