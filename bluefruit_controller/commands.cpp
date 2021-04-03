/**
 * Filename:    commands.cpp
 * Author:      padin.adrian@gmail.com
 * Date:        2021/01/29
 * Description: Implementation of LED lamp commands
 */

#include <stdint.h>
#include <Arduino.h>
#include "commands.hpp"

// #define PIN_HIGH  (DDRB &= 0xFE)  // set to input
// #define PIN_LOW   (DDRB |= 0x01)  // set to output
#define PIN_HIGH pinMode(13, INPUT)
#define PIN_LOW pinMode(13, OUTPUT)

namespace lamp {

    /** Send a command to the lamp. */
    void SendCommand(LampCommand c) {

        // First two bytes are always the same.
        // Second byte is inverse of first.
        static uint8_t buffer[4] = {0x01, 0xFE};
        register uint8_t byteToSend;

        // Third byte is the command.
        // Fourth byte is inverse of the command.
        buffer[2] = c;
        buffer[3] = ~c;     // Inverse of command

        // Start bit
        PIN_LOW;
        delayMicroseconds(9052);
        PIN_HIGH;
        delayMicroseconds(4551);

        // Send 4 bytes of data
        for (int i = 0; i < 4; ++i) {
            byteToSend = buffer[i];
            for (int j = 0; j < 8; ++j) {
                PIN_LOW;
                delayMicroseconds(580);
                PIN_HIGH;
                if (byteToSend & 1) {
                    // Send a 1
                    delayMicroseconds(1705);
                }
                else {
                    // Send a 0
                    delayMicroseconds(580);
                }
                byteToSend >>= 1;     // right shift
            }
        }

        // Stay high 40ms
        PIN_LOW;
        delayMicroseconds(580);
        PIN_HIGH;
        delayMicroseconds(40300);

        // Stop bit
        PIN_LOW;
        delayMicroseconds(9052);
        PIN_HIGH;
        delayMicroseconds(4551);
        PIN_LOW;
        delayMicroseconds(580);
        PIN_HIGH;
    }
}