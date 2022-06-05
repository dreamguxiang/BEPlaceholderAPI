#include "Global.h"
#include "Helper.h"
#include "PlaceholderAPI.h"
#include <ScheduleAPI.h>
#include "SignBlock.h"

std::unordered_map<string,Vec4> SignBlockActorMap;


THook(void*, "?tick@BlockActor@@UEAAXAEAVBlockSource@@@Z",
	BlockActor* _this, BlockSource* a2) {
	if (Settings::Sign::Enabled) {
		auto type = _this->getType();
		if (type == BlockActorType::Sign) {
			auto dim = SymCall("?getDimension@BlockSource@@UEAAAEAVDimension@@XZ", Dimension*, BlockSource*)(a2);
			SignBlockActorMap.emplace(Vec4{ _this->getPosition().toVec3(),dim->getDimensionId() }.toStr(), Vec4{_this->getPosition().toVec3(),dim->getDimensionId()});
		}
	}
	return original(_this, a2);
}


#include <MC/BinaryStream.hpp>
#include <SendPacketAPI.h>
void UpdateAllSignBlock() {
	for (auto& i : SignBlockActorMap) {
		auto bs = Level::getBlockSource(i.second.dimid);
		auto pos = i.second.vc.toBlockPos();
		auto ba = bs->getBlockEntity(pos);
		if (ba) {
			SignBlockActor* BlockEntity = (SignBlockActor*)ba;
			auto SignBlockActorNbt = ba->getNbt().get()->clone();
			string text = SignBlockActorNbt->getString("Text");
			for (Player* pl : Level::getAllPlayers()) {
				string placeHolder = text;
				PlaceholderAPI::translateString(placeHolder, pl);
				if (text != placeHolder) {
					SignBlockActorNbt->putString("Text", placeHolder);
					BinaryStream bs;
					bs.writeVarInt(pos.x); bs.writeUnsignedVarInt(pos.y); bs.writeVarInt(pos.z);
					bs.writeCompoundTag(*SignBlockActorNbt);
					NetworkPacket<56> pkt(bs.getAndReleaseData());
					pl->sendNetworkPacket(pkt);
				}
			}
		}
	}
}

typedef std::chrono::high_resolution_clock timer_clock;
#define TIMER_START1 auto start = timer_clock::now();
#define TIMER_END1                                                      \
    auto elapsed = timer_clock::now() - start;                         \
    long long timeReslut =                                             \
        std::chrono::duration_cast<std::chrono::microseconds>(elapsed) \
            .count();


void initSchedule() {
	//20Tick自动更新
	Schedule::repeat([] {
		UpdateAllSignBlock();
	}, 20);
}

