#include "Global.h"
#include "Helper.h"
#include "PlaceholderAPI.h"
#include <ScheduleAPI.h>
#include "SignBlock.h"

std::set<Vec4> SignBlockActorMap;


THook(void*, "?tick@BlockActor@@UEAAXAEAVBlockSource@@@Z",
	BlockActor* _this, BlockSource* a2) {
	if (Settings::Sign::Enabled) {
		auto type = _this->getType();
		if (type == BlockActorType::Sign || type == BlockActorType::HangingSign) {
			auto dim = SymCall("?getDimension@BlockSource@@UEAAAEAVDimension@@XZ", Dimension*, BlockSource*)(a2);
			SignBlockActorMap.emplace(Vec4{_this->getPosition().toVec3(),a2->getDimensionId()});
		}
	}
	return original(_this, a2);
}

enum class SignTextSide : __int32
{
	Front = 0x0,
	Back = 0x1,
};

#include <MC/BinaryStream.hpp>
#include <SendPacketAPI.h>
void UpdateAllSignBlock() {
	for (auto& i : SignBlockActorMap) {
		auto bs = Level::getBlockSource(i.dimid);
		auto pos = i.vc.toBlockPos();
		auto ba = bs->getBlockEntity(pos);
		if (ba) {
			auto SignBlockActorNbt = ba->getNbt().get()->clone();
			auto signblock = (SignBlockActor*)ba;
			auto back= SignBlockActorNbt->getCompound("BackText");
			string backText = signblock->getMessage(SignTextSide::Back);
			auto front = SignBlockActorNbt->getCompound("FrontText");
			string frontText = signblock->getMessage(SignTextSide::Front);

			for (Player* pl : Level::getAllPlayers()) {
				string backplaceHolder = backText;
				string frontplaceHolder = frontText;
				if (!backplaceHolder.empty()) PlaceholderAPI::translateString(backplaceHolder, pl);
				if (!frontplaceHolder.empty()) PlaceholderAPI::translateString(frontplaceHolder, pl);
				if (backText != backText || frontText != frontplaceHolder) {
					back->putString("Text", backplaceHolder);
					front->putString("Text", frontplaceHolder);
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
		SignBlockActorMap.clear();
	}, 20);
}

