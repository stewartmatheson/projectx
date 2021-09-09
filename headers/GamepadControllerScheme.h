#pragma once
#include "ControllerScheme.h"
#include "EventWithMouse.h"

class GamepadControllerScheme : public ControllerScheme {
  public:
	 ControllerSchemeState GetInput(const EventWithMouse&) const;
};
