#pragma once
#include <Global.h>
#include <MC/Player.hpp>
#include <MC/Level.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Block.hpp>
#include <MC/VanillaBlocks.hpp>
#include <MC/BinaryStream.hpp>
#include <MC/MinecraftPackets.hpp>
#include <MC/Dimension.hpp>
#include <MC/Packet.hpp>
#include <mc/ExtendedStreamReadResult.hpp>

using namespace std;

namespace signBlock {
	inline void UpdateBlockPacket(Dimension* dim, BlockPos bp, const unsigned int runtimeId, unsigned int layer = 1) {
		if (!dim)
			return;
		BinaryStream wp;
		wp.writeVarInt(bp.x);
		wp.writeUnsignedVarInt(bp.y);
		wp.writeVarInt(bp.z);
		wp.writeUnsignedVarInt(runtimeId);
		wp.writeUnsignedVarInt(3);  // flag
		wp.writeUnsignedVarInt(layer);  // layer
		shared_ptr<Packet> pkt = MinecraftPackets::createPacket(MinecraftPacketIds::UpdateBlock);
		pkt->read(wp);
		dim->sendPacketForPosition({ bp.x, bp.y, bp.z }, *pkt, nullptr);
	};

	inline void UpdateBlockPacket(int dimId, BlockPos bp, const unsigned int runtimeId, unsigned int layer = 1) {
		auto dim = (Dimension*)Global<Level>->getDimension(dimId).mHandle.lock().get();
		UpdateBlockPacket(dim, bp, runtimeId);
	};
}