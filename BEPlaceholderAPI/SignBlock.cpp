#include "Global.h"
#include "Helper.h"
#include "PlaceholderAPI.h"
#include <ScheduleAPI.h>
#include "SignBlock.h"

std::unordered_map<BlockActor*, BlockSource*> SignBlockActorMap;

THook(void*, "?tick@BlockActor@@UEAAXAEAVBlockSource@@@Z",
	BlockActor* _this, BlockSource* a2) {
	auto type = _this->getType();
	if (type == BlockActorType::Sign) {		
		SignBlockActorMap.clear();
		std::pair<BlockActor*, BlockSource*> signBlockData(_this,a2);
		SignBlockActorMap.insert(signBlockData);
	}
	return original(_this, a2);
}

void UpdateAllSignBlock() {
	for (auto i : SignBlockActorMap) {
		BlockActor* _this = i.first;
		BlockSource* a2 = i.second;
		SignBlockActor* BlockEntity = (SignBlockActor*)_this;

		auto SignBlockActorNbt = BlockEntity->getNbt();
		//获取Text
		string text = SignBlockActorNbt->getString("Text");
		string placedText;
		PlaceholderAPI::translateString(placedText);

		//更新告示牌
		BlockEntity->setMessage(placedText, "");
		BlockEntity->setChanged();
		
		auto pkt = BlockEntity->_getUpdatePacket(*a2);
		Level::sendPacketForAllPlayer(*pkt);
	}
}

void initSchedule() {
	//20Tick自动更新
	Schedule::repeat(UpdateAllSignBlock, 20);
}

