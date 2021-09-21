#pragma once

#include "ControllerScheme.h"

class KeyboardControllerScheme : public ControllerScheme {
  public:
    ControllerSchemeState GetInput(const EventWithMouse &) const;
};
