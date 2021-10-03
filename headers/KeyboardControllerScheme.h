#pragma once

#include "ControllerScheme.h"

class KeyboardControllerScheme final : public ControllerScheme {
  public:
    ControllerSchemeState GetInput(const EventWithMouse &) const;
};
