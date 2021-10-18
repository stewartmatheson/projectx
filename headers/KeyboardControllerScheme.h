#pragma once

#include <optional>

#include "ControllerScheme.h"

class KeyboardControllerScheme final : public ControllerScheme {
  public:
    std::optional<ControllerSchemeState> GetInput(const EventWithMouse &) const;
};
