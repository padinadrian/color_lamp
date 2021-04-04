/**
 * Bluefruit Controller Packet Parser
 *
 * Author:  Adrian Padin (padin.adrian@gmail.com)
 * Date:    2021-04-03
 *
 * This sketch is based on an example sketch by Adafruit.
 * The original example's license statement is preserved below.
 */

/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/* ===== Includes ===== */
#include <string.h>
#include <Arduino.h>
#include <bluefruit.h>


/* ===== Definitions ===== */

// Expected length for a button packet.
#define PACKET_BUTTON_LEN   (5)

// Size of the read buffer for incoming packets
#define READ_BUFSIZE        (20)

/* Buffer to hold incoming characters */
uint8_t packetbuffer[READ_BUFSIZE + 1];

/**************************************************************************/
/*!
    @brief  Waits for incoming data and parses it
*/
/**************************************************************************/
uint8_t readPacket(BLEUart *ble_uart, uint16_t timeout)
{
    uint16_t origtimeout = timeout, replyidx = 0;

    memset(packetbuffer, 0, READ_BUFSIZE);

    while (timeout--) {
        if (replyidx >= 20) {
            break;
        }

        if ((packetbuffer[1] == 'B') && (replyidx == PACKET_BUTTON_LEN)) {
            break;
        }

        while (ble_uart->available()) {
            char c =  ble_uart->read();
            if (c == '!') {
                replyidx = 0;
            }
            packetbuffer[replyidx] = c;
            replyidx++;
            timeout = origtimeout;
        }

        if (timeout == 0) {
            break;
        }

        delay(1);
    }

    packetbuffer[replyidx] = 0;  // null term

    // no data or timeout
    if (!replyidx) {
        return 0;
    }

    // doesn't start with '!' packet beginning
    if (packetbuffer[0] != '!') {
        return 0;
    }

    // check checksum!
    uint8_t xsum = 0;
    uint8_t checksum = packetbuffer[replyidx - 1];

    for (uint8_t i = 0; i < replyidx - 1; i++) {
        xsum += packetbuffer[i];
    }
    xsum = ~xsum;

    // Throw an error message if the checksum's don't match
    if (xsum != checksum) {
        return 0;
    }

    // checksum passed!
    return replyidx;
}
