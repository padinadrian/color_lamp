// /**
//  * commands.cpp
//  * Implementation
//  */

// #include <stdint.h>
// #include "commands.hpp"
// #include <Arduino.h>
// // #include <iostream>

// #define PIN_HIGH  (DDRB &= ~1)  // set to input
// #define PIN_LOW   (DDRB |= 1)   // set to output

// namespace lamp {

//     /** Send a command to the lamp. */
//     void SendCommand(Command c) {
//         static uint8_t buffer[4] = {0x01, 0xFE};
//         register uint8_t byte;

//         buffer[2] = c;
//         buffer[3] = ~c;     // Inverse of command

//         // TODO: Start
//         // std::cout << "\nstart" << std::endl;
//         PIN_LOW;
//         delayMicroseconds(9052);
//         PIN_HIGH;
//         delayMicroseconds(4551);

//         for (int i = 0; i < 4; ++i) {
//             byte = buffer[i];
//             for (int j = 0; j < 8; ++j)
//                 PIN_LOW;
//                 delayMicroseconds(580);
//                 PIN_HIGH;
//                 if (byte & 1) {
//                     // 1
//                     delayMicroseconds(1705);
//                 }
//                 else {
//                     // 0
//                     delayMicroseconds(580);
//                 }
//                 byte >>= 1;     // right shift
//             }
//             // std::cout << "|";
//         }

//         // Stay high 40ms
//         PIN_LOW;
//         delayMicroseconds(580);
//         PIN_HIGH;
//         delayMicroseconds(40300);
//         // TODO: Stop
//         PIN_LOW;
//         delayMicroseconds(9052);
//         PIN_HIGH;
//         delayMicroseconds(4551);
//         PIN_LOW;
//         delayMicroseconds(580);
//         PIN_HIGH;
//         // std::cout << "stop" << std::endl;
//     }
// }
