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
			SignBlockActorMap.emplace(Vec4{ _this->getPosition().toVec3(),a2->getDimensionId() });
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
			auto back = SignBlockActorNbt->getCompound("BackText");
			string backText = signblock->getMessage(SignTextSide::Back);
			auto front = SignBlockActorNbt->getCompound("FrontText");
			string frontText = signblock->getMessage(SignTextSide::Front);

			for (Player* pl : Level::getAllPlayers()) {
				string backplaceHolder = backText;
				string frontplaceHolder = frontText;
				if (!backplaceHolder.empty()) PlaceholderAPI::translateString(backplaceHolder, pl);
				if (!frontplaceHolder.empty()) PlaceholderAPI::translateString(frontplaceHolder, pl);
				if (backText != backplaceHolder || frontText != frontplaceHolder) {
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

unordered_map<SignBlockActor*, pair<string, string>> SignTextCache;

THook(bool, "?_canChangeSign@SignBlock@@CA_NAEAVSignBlockActor@@AEAVPlayer@@@Z",
	SignBlockActor* _this, Player* pl) {
	auto res = original(_this, pl);
	if (Settings::Sign::Enabled && res) {
		string frontplaceHolder = _this->getMessage(SignTextSide::Front);
		string backplaceHolder = _this->getMessage(SignTextSide::Back);
		if (!frontplaceHolder.empty()) PlaceholderAPI::translateString(frontplaceHolder, pl);
		if (!backplaceHolder.empty()) PlaceholderAPI::translateString(backplaceHolder, pl);
		SignTextCache.emplace(_this, pair<string, string>{ frontplaceHolder, backplaceHolder });
	}
	return res;
}

TInstanceHook(void, "?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@V?$shared_ptr@VBlockActorDataPacket@@@std@@@Z",
	ServerNetworkHandler, NetworkIdentifier* a2, UINT64* a3) {

	auto bs = this->getServerPlayer(*a2, 0)->getBlockSource();
	auto pos = (BlockPos*)(*a3 + 48i64);
	auto signblock = (SignBlockActor*)bs->getBlockEntity(*pos);
	if (signblock) {
		auto it = SignTextCache.find(signblock);
		if (it != SignTextCache.end()) {
			auto SignBlockActorNbt = (CompoundTag*)(*a3 + 64i64);
			auto front = SignBlockActorNbt->getCompound("FrontText");
			if (!it->second.first.empty() && front->getString("Text") == it->second.first) {
				front->putString("Text", signblock->getMessage(SignTextSide::Front));
			}
			auto back = SignBlockActorNbt->getCompound("BackText");
			if (!it->second.second.empty() && back->getString("Text") == it->second.second) {
				back->putString("Text", signblock->getMessage(SignTextSide::Back));
			}
			SignTextCache.erase(it);
		}
	}

	return original(this, a2, a3);
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

