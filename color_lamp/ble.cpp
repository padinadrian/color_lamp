/**
 * Filename:    ble.cpp
 * Author:      padin.adrian@gmail.com
 * Date:        2021/01/29
 * Description: Setup and handling of ble capabilities
 */

/* ===== Includes ===== */
#include <BLE_API.h>

/* ===== Definitions ===== */
#define DEVICE_NAME     "Color Lamp"
#define UART_BUF_LEN    20

/* ===== Globals ===== */
static BLE ble;

// UUID of service and characteristic
// TODO: Change later!
static const uint8_t service_uuid[]         = {0x71, 0x3D, 0, 0, 0x50, 0x3E, 0x4C, 0x75, 0xBA, 0x94, 0x31, 0x48, 0xF1, 0x8D, 0x94, 0x1E};
static const uint8_t service_chars_uuid[]   = {0x71, 0x3D, 0, 2, 0x50, 0x3E, 0x4C, 0x75, 0xBA, 0x94, 0x31, 0x48, 0xF1, 0x8D, 0x94, 0x1E};

// Used in advertisement
static const uint8_t uart_base_uuid_rev[]    = {0x1E, 0x94, 0x8D, 0xF1, 0x48, 0x31, 0x94, 0xBA, 0x75, 0x4C, 0x3E, 0x50, 0, 0, 0x3D, 0x71};

// UART read/write buffer
uint8_t uart_chars_buf[UART_BUF_LEN] = {0};

GattCharacteristic  characteristic1(
    service_chars_uuid,
    uart_chars_buf,
    1,
    TXRX_BUF_LEN, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE_WITHOUT_RESPONSE );
