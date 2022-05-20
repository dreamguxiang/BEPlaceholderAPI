#include <MC/SignBlockActor.hpp>
#include <MC/BlockActorDataPacket.hpp>
#include "Global.h"
#include "PlaceholderAPI.h"

THook(void, "??0SignBlockActor@@QEAA@AEBVBlockPos@@@Z", 
	SignBlockActor* _this, BlockPos* a2) {
	logger.debug("SignPos:{}", a2->toString());
	string text = _this->getNbt()->getString("Text");
	//auto pkt = _this->_getUpdatePacket(*player->getBlockSource());
	//Level::sendPacketForAllPlayer(*pkt);

	return original(_this, a2);
}