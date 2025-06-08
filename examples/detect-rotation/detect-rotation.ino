// Copyright (C) 2024 Morgritech
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

/// @file detect-rotation.ino
/// @brief Example showing how to detect encoder rotation (and direction), and obtain the absolute angular position using the MT-arduino-rotary-encoder library.

#include <rotary_encoder.h>

// GPIO pins.
const uint8_t kContactAPin = 2; ///< Input pin for the encoder contact A.
const uint8_t kContactBPin = 3; ///< Input pin for the encoder contact B.

// Rotary encoder properties.
uint8_t kNoOfDetents = 20; ///< The number of detents within the maximum rotation angle.
uint16_t kMaxRotationAngle_degrees = 360; ///< The maximum rotation angle (degrees).

/// @brief The Rotary Encoder instance for the encoder.
auto rotary_encoder = mt::RotaryEncoder(kContactAPin, kContactBPin, kNoOfDetents, kMaxRotationAngle_degrees);
//auto rotary_encoder = mt::RotaryEncoder(kContactAPin, kContactBPin); // Default values: no. of detents = 24, max rotation angle = 360 degrees.

/// @brief The serial communication speed.
const int kBaudRate = 9600;

/// @brief The main application entry point for initialisation tasks.
void setup() {
  // Initialise the Serial Port.
  Serial.begin(kBaudRate);

  // Initialise the input pins.
  pinMode(kContactAPin, INPUT_PULLUP);
  pinMode(kContactBPin, INPUT_PULLUP);

  Serial.println(F("\n...Setup complete...\n"));
}

/// @brief The continuously running function for repetitive tasks.
void loop() {
  // Detect encoder rotation (and direction).
  mt::RotaryEncoder::RotationDirection rotation_direction = rotary_encoder.DetectRotation(); // This must be called repeatedly.

  if (rotation_direction != mt::RotaryEncoder::RotationDirection::kNeutral) {
    if (rotation_direction == mt::RotaryEncoder::RotationDirection::kPositive) {
      Serial.println(F("Positive direction."));
    }
    else {
      Serial.println(F("Negative direction."));
    }

    // Get the angular position (Detents).
    Serial.print(F("Angular position (Detents): "));
    Serial.println(rotary_encoder.GetAngularPosition(mt::RotaryEncoder::AngleUnits::kDetents));

    // Get the angular position (Degrees).
    Serial.print(F("Angular position (Degrees): "));
    Serial.println(rotary_encoder.GetAngularPosition(mt::RotaryEncoder::AngleUnits::kDegrees));
  }
}