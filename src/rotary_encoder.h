// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file rotary_encoder.h
/// @brief Class to handle encoder rotation actions.

#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

#include <Arduino.h>

namespace mt {

/// @brief The Rotary Encoder class.
class RotaryEncoder {
 public:

  /// @brief Enum of GPIO pin states.
  enum class PinState {
    kLow = 0,
    kHigh,
  };

  /// @brief Enum of angular units.
  enum class AngleUnits {
    kDetents = 0,
    kDegrees,
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
  /// @param no_of_detents The number of detents within the maximum rotation angle.
  /// @param max_rotation_angle_degrees The maximum rotation angle (degrees).
  RotaryEncoder(uint16_t gpio_a_pin, uint16_t gpio_b_pin, uint16_t no_of_detents = 24,
                uint16_t max_rotation_angle_degrees = 360);

  /// @brief Destroy the Rotary Encoder object.
  ~RotaryEncoder();

  /// @brief Check if the encoder has been rotated, and in what direction.
  /// @return The rotation state/direction at the time of checking.
  RotationDirection DetectRotation(); ///< This must be called periodically.

  /// @brief Get the current angular position (degrees).
  /// @param angle_units The units required for the angle.
  /// @return The current angular position.
  float GetAngularPosition(AngleUnits angle_units) const;

 private:

  // Pre-calculated unit conversion constants.
  float kMaxRotationAngleDegreesDividedByNoOfDetents_; ///< max rotation angle in degrees / no. of detents.

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
  /// @brief The default pin state when there is no rotation.
  PinState default_pin_state_; 
  /// @brief Contact A pin state during rotation detection.
  PinState gpio_a_pin_state_;
  /// @brief Contact B pin state during rotation detection.
  PinState gpio_b_pin_state_;
  /// @brief Flag to determine when the first iteration for rotation detection has occurred.
  bool first_iteration_ = true;
  /// @brief The current step in the rotation cycle.
  uint8_t current_step_ = 0;
  /// @brief The previous step in the rotation cycle.
  uint8_t previous_step_ = 0;
  /// @brief Flag to determine when a rotation cycle has finished (1 cycle = 1 detent).
  bool cycle_finished_ = true;
  /// @brief The direction of rotation.
  int8_t direction_ = 0;
};

} // namespace mt

#endif // ROTARY_ENCODER_H_