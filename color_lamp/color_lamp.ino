/**
 * color_lamp.ino
 */

/* ===== Includes ===== */
#include <stdint.h>
// #include "commands.hpp"
// #include <iostream>

// #define PIN_HIGH  (DDRB &= 0xFE)  // set to input
// #define PIN_LOW   (DDRB |= 0x01)  // set to output
#define PIN_HIGH NULL
#define PIN_LOW NULL

namespace lamp {

    enum LampCommand {
        LAMP_CMD_BRIGHT = 0x80,
        LAMP_CMD_DIM    = 0x81,
        LAMP_CMD_OFF    = 0x82,
        LAMP_CMD_ON     = 0x83,
        LAMP_CMD_RED    = 0x84,
        LAMP_CMD_GREEN  = 0x85,
        LAMP_CMD_BLUE   = 0x86,
        LAMP_CMD_WHITE  = 0x87,
        LAMP_CMD_YELLOW = 0x94,
    };

    /** Send a command to the lamp. */
    void SendCommand(LampCommand c) {
        static uint8_t buffer[4] = {0x01, 0xFE};
        register uint8_t byte;

        buffer[2] = c;
        buffer[3] = ~c;     // Inverse of command

        // TODO: Start
        // std::cout << "\nstart" << std::endl;
        PIN_LOW;
        delayMicroseconds(9052);
        PIN_HIGH;
        delayMicroseconds(4551);

        for (int i = 0; i < 4; ++i) {
            byte = buffer[i];
            for (int j = 0; j < 8; ++j) {
                PIN_LOW;
                delayMicroseconds(580);
                PIN_HIGH;
                if (byte & 1) {
                    // 1
                    delayMicroseconds(1705);
                }
                else {
                    // 0
                    delayMicroseconds(580);
                }
                byte >>= 1;     // right shift
            }
            // std::cout << "|";
        }

        // Stay high 40ms
        PIN_LOW;
        delayMicroseconds(580);
        PIN_HIGH;
        delayMicroseconds(40300);
        // TODO: Stop
        PIN_LOW;
        delayMicroseconds(9052);
        PIN_HIGH;
        delayMicroseconds(4551);
        PIN_LOW;
        delayMicroseconds(580);
        PIN_HIGH;
        // std::cout << "stop" << std::endl;
    }
}

/* ===== Setup ===== */
void setup() {
  pinMode(8, INPUT);
  digitalWrite(8, LOW);
  // PORTD &= ~(1);    // Set pin 8 to low
  // DDRB &= ~(1);     // Set pin 8 to input
}

/* ===== Loop ===== */
void loop() {
  // put your main code here, to run repeatedly:
    lamp::SendCommand(lamp::LAMP_CMD_OFF);
    delay(1000);
    lamp::SendCommand(lamp::LAMP_CMD_ON);
    delay(1000);
}
