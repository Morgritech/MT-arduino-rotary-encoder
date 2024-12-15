// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file rotary_encoder.h
/// @brief Class to handle encoder rotation actions.

#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

#include <Arduino.h>

#include <pin_debouncer.h>

namespace mt {

/// @brief The Rotary Encoder class.
class RotaryEncoder {
 public:

  /// @brief Enum of GPIO pin states.
  enum class PinState {
    kLow = 0,
    kHigh,
  };

  /// @brief Enum of detent states/rotation directions.
  enum class RotationDirection {
    kNegative = -1,
    kNeutral = 0,
    kPositive = 1,
  };

  /// @brief Construct a Rotary Encoder object.
  /// @param gpio_a_pin The GPIO input pin assigned to the encoder contact A.
  /// @param gpio_b_pin The GPIO input pin assigned to the encoder contact B.
  /// @param debounce_period_ms The period of time (ms) allowed for pin debouncing.
  /// @param no_of_detents The number of detents within the maximum rotation angle.
  /// @param max_rotation_angle_degrees The maximum rotation angle (degrees).
  RotaryEncoder(uint16_t gpio_a_pin, uint16_t gpio_b_pin, uint16_t debounce_period_ms = 70,
                uint16_t no_of_detents = 24, uint16_t max_rotation_angle_degrees = 360);

  /// @brief Destroy the Rotary Encoder object.
  ~RotaryEncoder();

  /// @brief Check if the encoder has been rotated, and in what direction.
  /// @return The rotation state/direction at the time of checking.
  RotationDirection DetectRotation(); ///< This must be called periodically.

  /// @brief Get the current (absolute) angular position (degrees).
  /// @return The current angular position (degrees).
  float GetAngularPosition() const;

 private:

  /// @brief The GPIO input pin assigned to the encoder contact A.
  uint16_t gpio_a_pin_;
  /// @brief The GPIO input pin assigned to the encoder contact B.
  uint16_t gpio_b_pin_;
  /// @brief The number of detents within the maximum rotation angle.
  uint16_t no_of_detents_;
  /// @brief The maximum rotation angle (degrees).
  uint16_t max_rotation_angle_degrees_;
  /// @brief The current angular position (detents (steps)).
  uint32_t angular_position_detents_ = 0;
  PinDebouncer pin_debouncer_;
  /// @brief The status of the debounce operation during rotation detection.
  PinDebouncer::Status debounce_status_ = PinDebouncer::Status::kNotStarted;
};

} // namespace mt

#endif // ROTARY_ENCODER_H_