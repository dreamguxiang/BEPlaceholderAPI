#pragma once

#include <ll/api/plugin/NativePlugin.h>

namespace papi {

[[nodiscard]] auto getSelfPluginInstance() -> ll::plugin::NativePlugin&;

} // namespace change_this
