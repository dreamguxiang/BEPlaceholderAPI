#include "Global.h"
#include "Helper.h"
#include "PlaceholderAPI.h"
#include <ScheduleAPI.h>
#include "SignBlock.h"

std::set<Vec4> SignBlockActorMap;


THook(void*, "?tick@BlockActor@@UEAAXAEAVBlockSource@@@Z",
	BlockActor* _this, BlockSource* a2) {
	auto type = _this->getType();
	if (type == BlockActorType::Sign) {		
		auto dim = SymCall("?getDimension@BlockSource@@UEAAAEAVDimension@@XZ", Dimension*, BlockSource*)(a2);
		SignBlockActorMap.emplace(Vec4{ _this->getPosition().toVec3(),dim->getDimensionId()});
	}
	return original(_this, a2);
}


#include <MC/BinaryStream.hpp>
#include <SendPacketAPI.h>
void UpdateAllSignBlock() {
	for (auto& i : SignBlockActorMap) {
		auto bs = Level::getBlockSource(i.dimid);
		auto pos = i.vc.toBlockPos();
		auto ba = bs->getBlockEntity(pos);
		if (ba) {
			SignBlockActor* BlockEntity = (SignBlockActor*)ba;
			auto SignBlockActorNbt = ba->getNbt().get()->clone();
			string old = SignBlockActorNbt->getString("Text");
			string text = SignBlockActorNbt->getString("Text");
			//给指定玩家发包
			auto playerList = Level::getAllPlayers();
			for (Player* pl : playerList) {
				//获取指定玩家的包
				string placeHolder = text;
				PlaceholderAPI::translateString(placeHolder,pl);
				if (old != placeHolder) {
					SignBlockActorNbt->putString("Text", placeHolder);
					BinaryStream bs;
					bs.writeVarInt(pos.x); bs.writeUnsignedVarInt(pos.y); bs.writeVarInt(pos.z);
					bs.writeCompoundTag(*SignBlockActorNbt);
					NetworkPacket<56> pkt(bs.getAndReleaseData());
					//Level::sendPacketForAllPlayer(pkt);
					pl->sendNetworkPacket(pkt);
				}
			}
		}
	}
}

void initSchedule() {
	//20Tick自动更新
	Schedule::repeat([] {
		UpdateAllSignBlock();
	}, 20);
}

