/**
 * Filename:    color_lamp.ino
 * Author:      padin.adrian@gmail.com
 * Date:        2021/01/29
 * Description: Main file for Arduino sketch
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
