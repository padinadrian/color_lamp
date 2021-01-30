/**
 * color_lamp.ino
 */

/* ===== Includes ===== */
#include "commands.hpp"

/* ===== Setup ===== */
void setup() {
    pinMode(8, INPUT);
    digitalWrite(8, LOW);
}

/* ===== Loop ===== */
void loop() {
    lamp::SendCommand(lamp::LAMP_CMD_OFF);
    delay(1000);
    lamp::SendCommand(lamp::LAMP_CMD_ON);
    delay(1000);
}
