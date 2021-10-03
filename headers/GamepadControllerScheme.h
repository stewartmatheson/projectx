#pragma once

#include "ControllerScheme.h"
#include "EventWithMouse.h"

class GamepadControllerScheme final : public ControllerScheme {
  public:
    ControllerSchemeState GetInput(const EventWithMouse &) const;
};
