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
    : pin_debouncer_(gpio_a_pin, debounce_period_ms) {
  gpio_a_pin_ = gpio_a_pin_;
  gpio_b_pin_ = gpio_b_pin_;
  no_of_detents = no_of_detents_;
  max_rotation_angle_degrees = max_rotation_angle_degrees_;
}

RotaryEncoder::~RotaryEncoder() {}

RotaryEncoder::RotationDirection RotaryEncoder::DetectRotation() {
  RotationDirection rotation_direction = RotationDirection::kNeutral;

  if (first_iteration_ == true){
    previous_b_pin_state_ = static_cast<PinState>(digitalRead(gpio_b_pin_));
    first_iteration_ = false;
  }
  else if (debounce_status_ == PinDebouncer::Status::kNotStarted && debouncing_rotation_ == false) {
    // No encoder rotation has occurred yet.
    current_b_pin_state_ = static_cast<PinState>(digitalRead(gpio_b_pin_));
    if (current_b_pin_state_ != previous_b_pin_state_) {
      // Rotation has occurred.
      debounce_status_ = PinDebouncer::Status::kOngoing;
    }
  }
  else if (debounce_status_ == PinDebouncer::Status::kNotStarted && debouncing_rotation_ == true) {
    // Finished debouncing rotation.
    //current_b_pin_state_ = static_cast<PinState>(digitalRead(gpio_b_pin_)); // Read it again after it has settled?
    PinState current_a_pin_state = static_cast<PinState>(digitalRead(gpio_a_pin_));
    
    if (current_a_pin_state != current_b_pin_state_) {
      rotation_direction = RotationDirection::kPositive;
    }
    else {
      rotation_direction = RotationDirection::kNegative;
    }

    previous_b_pin_state_ = current_b_pin_state_;
  }

  if (debounce_status_ == PinDebouncer::Status::kOngoing) {
    debounce_status_ = pin_debouncer_.DebouncePin();
  }

  return RotationDirection();
}

float RotaryEncoder::GetAngularPosition(AngleUnits angle_units) const { return 0.0f; }

}  // namespace mt