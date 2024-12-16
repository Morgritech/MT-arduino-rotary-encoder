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
uint8_t kNoOfDetents = 24; ///< The number of detents within the maximum rotation angle.
uint8_t kMaxRotationAngleDegrees = 360; ///< The maximum rotation angle (degrees).

/// @brief The Period of time in milliseconds (ms) for debouncing the encoder contact pins.
const uint16_t kContactDebouncePeriod_ms = 20;

/// @brief The Rotary Encoder instance for the encoder.
mt::RotaryEncoder rotary_encoder(kContactAPin, kContactBPin, kContactDebouncePeriod_ms, kNoOfDetents, kMaxRotationAngleDegrees);
//mt::RotaryEncoder rotary_encoder(kContactAPin, kContactBPin); // Default values: debounce period = 70 ms, no. of detents = 24, max rotation angle = 360 degrees.

/// @brief The serial communication speed.
const int kBaudRate = 9600;

/// @brief The main application entry point for initialisation tasks.
void setup() {
  // Initialise the Serial Port.
  Serial.begin(kBaudRate);

  // Initialise the input pins.
  pinMode(kContactAPin, INPUT);
  pinMode(kContactBPin, INPUT);

  Serial.println(F("\n...Setup complete...\n"));
}

/// @brief The continuously running function for repetitive tasks.
void loop() {
  // Detect encoder rotation (and direction).
  mt::RotaryEncoder::RotationDirection rotation_direction = rotary_encoder.DetectRotation(); // This must be called periodically.

  if (rotation_direction != mt::RotaryEncoder::RotationDirection::kNeutral) {
    if (rotation_direction == mt::RotaryEncoder::RotationDirection::kNegative) {
      Serial.println(F("Negative direction."));
    }
    else {
      Serial.println(F("Positive direction."));
    }

    // Get the angular position (Detents).
    Serial.print(F("Angular position (Detents): "));
    Serial.println(rotary_encoder.GetAngularPosition(mt::RotaryEncoder::AngleUnits::kDetents));

    // Get the angular position (Degrees).
    Serial.print(F("Angular position (Degrees): "));
    Serial.println(rotary_encoder.GetAngularPosition(mt::RotaryEncoder::AngleUnits::kDegrees));    
  }
}