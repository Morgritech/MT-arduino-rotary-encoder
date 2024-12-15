// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file rotary_encoder.cpp
/// @brief Class to handle encoder rotation actions.

#include "rotary_encoder.h"

#include <Arduino.h>

#include <pin_debouncer.h>

namespace mt {

RotaryEncoder::RotaryEncoder(uint16_t gpio_a_pin, uint16_t gpio_b_pin, uint16_t debounce_period_ms,
                             uint16_t no_of_detents, uint16_t max_rotation_angle_degrees)
    : button_debouncer_(gpio_a_pin, debounce_period_ms) {
  gpio_a_pin_ = gpio_a_pin_;
  gpio_b_pin_ = gpio_b_pin_;
  no_of_detents = no_of_detents_;
  max_rotation_angle_degrees = max_rotation_angle_degrees_;
}

RotaryEncoder::~RotaryEncoder() {}

float RotaryEncoder::GetAngularPosition() const { return 0.0f; }

}  // namespace mt