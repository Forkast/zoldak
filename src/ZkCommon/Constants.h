#pragma once

namespace Zk {
namespace Common {

namespace Constants {

static const double PIXELS_PER_METER = 64.0;
static const double METERS_PER_PIXEL = 1.0 / PIXELS_PER_METER;

}

enum class LayerType : int
{
	MEDKIT_SPAWN = 0,
	GRENADES_SPAWN,
	PLAYER_A_SPAWN,
	PLAYER_B_SPAWN,
	PLAYER_A_FLAG,
	PLAYER_B_FLAG,
	FOREGROUND,
	MIDGROUND,
	BACKGROUND,
	MAX_LAYER
};

}}
