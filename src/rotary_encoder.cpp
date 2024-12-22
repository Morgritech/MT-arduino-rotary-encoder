// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file rotary_encoder.cpp
/// @brief Class to handle encoder rotation actions.

#include "rotary_encoder.h"

#include <Arduino.h>

namespace mt {

RotaryEncoder::RotaryEncoder(uint16_t gpio_a_pin, uint16_t gpio_b_pin, uint16_t no_of_detents,
                             uint16_t max_rotation_angle_degrees) {
  gpio_a_pin_ = gpio_a_pin;
  gpio_b_pin_ = gpio_b_pin;
  no_of_detents_ = no_of_detents;
  max_rotation_angle_degrees_ = max_rotation_angle_degrees;

  kMaxRotationAngleDegreesDividedByNoOfDetents_ = max_rotation_angle_degrees_ / no_of_detents_;
}

RotaryEncoder::~RotaryEncoder() {}

RotaryEncoder::RotationDirection RotaryEncoder::DetectRotation() {
  RotationDirection rotation_direction = RotationDirection::kNeutral;

  gpio_a_pin_state_ = static_cast<PinState>(digitalRead(gpio_a_pin_));
  gpio_b_pin_state_ = static_cast<PinState>(digitalRead(gpio_b_pin_));

  if (first_iteration_ == true){
    default_pin_state_ = gpio_a_pin_state_;
    first_iteration_ = false;
  }

  if (gpio_a_pin_state_ != default_pin_state_ && gpio_b_pin_state_ == default_pin_state_) {
    current_step_ = 1;
  }
  else if (gpio_a_pin_state_ != default_pin_state_ && gpio_b_pin_state_ != default_pin_state_) {
    current_step_ = 2;
  }
  else if (gpio_a_pin_state_ == default_pin_state_ && gpio_b_pin_state_ != default_pin_state_) {
    current_step_ = 3;
  }
  else {
    current_step_ = 0;
  }

  if (cycle_finished_ == true && current_step_ != 0) {
    // A new rotation has started.
    cycle_finished_ = false;
  }
  else if (cycle_finished_ == false && current_step_ != 0) {
    // Rotation is ongoing.
    switch (current_step_) {
      case 1: {
        if (previous_step_ == 0) {
          direction_++;
        }
        else if (previous_step_ == 2) {
          direction_--;
        }
        break;
      }
      case 2: {
        if (previous_step_ == 1) {
          direction_++;
        }
        else if (previous_step_ == 3) {
          direction_--;
        }
        break;
      }
      case 3: {
        if (previous_step_ == 2) {
          direction_++;
        }
        else if (previous_step_ == 0) {
          direction_--;
        }
        break;
      }
    }
  }
  else if (cycle_finished_ == false && current_step_ == 0) {
    // Rotation has ended.
    cycle_finished_ = true;

    if (direction_ > 0) {
      rotation_direction = RotationDirection::kPositive;
      angular_position_detents_ ++;
    }
    else if (direction_ < 0) {
      rotation_direction = RotationDirection::kNegative;
      angular_position_detents_ --;    
    }

    direction_ = 0;
  }

  previous_step_ = current_step_;
  return rotation_direction;
}

float RotaryEncoder::GetAngularPosition(AngleUnits angle_units) const {
  float angular_position = 0.0;

  switch (angle_units) {
    case AngleUnits::kDetents: {
      angular_position = angular_position_detents_;
      break;
    }
    case AngleUnits::kDegrees: {
      angular_position = angular_position_detents_ * kMaxRotationAngleDegreesDividedByNoOfDetents_;
      break;
    }
  }

  return angular_position;
}

} // namespace mt