/**
 * Bluefruit Controller Arduino Sketch
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
#include <bluefruit.h>
#include "commands.hpp"


/* ===== Definitions ===== */

// Button Mapping
enum {
    BLF_BUTTON_1     = 1,
    BLF_BUTTON_2     = 2,
    BLF_BUTTON_3     = 3,
    BLF_BUTTON_4     = 4,
    BLF_BUTTON_UP    = 5,
    BLF_BUTTON_DOWN  = 6,
    BLF_BUTTON_LEFT  = 7,
    BLF_BUTTON_RIGHT = 8,
};

// Uart over BLE service
BLEUart bleuart;

// Function prototypes for packetparser.cpp
uint8_t readPacket (BLEUart *ble_uart, uint16_t timeout);

// Packet buffer
extern uint8_t packetbuffer[];


/* ===== Functions ===== */

/** Initialize BLE and start advertising as a peripherial. */
void startAdvertising(void)
{
    // Advertising packet
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();

    // Include the BLE UART (AKA 'NUS') 128-bit UUID
    Bluefruit.Advertising.addService(bleuart);

    // Secondary Scan Response packet (optional)
    // Since there is no room for 'Name' in Advertising packet
    Bluefruit.ScanResponse.addName();

    /* Start Advertising
     * - Enable auto advertising if disconnected
     * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
     * - Timeout for fast mode is 30 seconds
     * - Start(timeout) with timeout = 0 will advertise forever (until connected)
     *
     * For recommended advertising interval
     * https://developer.apple.com/library/content/qa/qa1931/_index.html
     */
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
    Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}


/**************************************************************************/

/* ===== SETUP ===== */

void setup(void)
{
    Bluefruit.begin();
    Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
    Bluefruit.setName("Adrian Color Lamp");

    // Configure and start the BLE Uart service
    bleuart.begin();

    // Set up and start advertising
    startAdvertising();

    // Configured lamp control pin
    pinMode(13, INPUT);
    digitalWrite(13, LOW);
}


/* ===== LOOP ===== */

/** Constantly poll for new command or response data */
void loop(void)
{
    // Wait for new data to arrive
    uint8_t len = readPacket(&bleuart, 500);
    if (len == 0) return;

    // Buttons
    if (packetbuffer[1] == 'B') {
        uint8_t button = packetbuffer[2] - '0';
        boolean pressed = packetbuffer[3] - '0';
        if (pressed) {
            switch (button) {
                case BLF_BUTTON_UP: {
                    lamp::SendCommand(lamp::LAMP_CMD_ON);
                    bleuart.write("On\n");
                    break;
                }
                case BLF_BUTTON_DOWN: {
                    lamp::SendCommand(lamp::LAMP_CMD_OFF);
                    bleuart.write("Off\n");
                    break;
                }
                case BLF_BUTTON_LEFT: {
                    lamp::SendCommand(lamp::LAMP_CMD_DIM);
                    bleuart.write("Dimmer\n");
                    break;
                }
                case BLF_BUTTON_RIGHT: {
                    lamp::SendCommand(lamp::LAMP_CMD_BRIGHT);
                    bleuart.write("Brighter\n");
                    break;
                }
                case BLF_BUTTON_1: {
                    lamp::SendCommand(lamp::LAMP_CMD_RED);
                    bleuart.write("Red\n");
                    break;
                }
                case BLF_BUTTON_2: {
                    lamp::SendCommand(lamp::LAMP_CMD_GREEN);
                    bleuart.write("Green\n");
                    break;
                }
                case BLF_BUTTON_3: {
                    lamp::SendCommand(lamp::LAMP_CMD_YELLOW);
                    bleuart.write("Yellow\n");
                    break;
                }
                case BLF_BUTTON_4: {
                    lamp::SendCommand(lamp::LAMP_CMD_WHITE);
                    bleuart.write("White\n");
                    break;
                }
            }
        }
    }
}
