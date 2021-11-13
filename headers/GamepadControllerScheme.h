#pragma once

#include <optional>

#include "ControllerScheme.h"
#include "EventWithMouse.h"

class GamepadControllerScheme final : public ControllerScheme {
  public:
    std::optional<ControllerSchemeState> GetInput(const EventWithMouse &) const;
};
