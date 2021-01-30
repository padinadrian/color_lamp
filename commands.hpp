/**
 * commands.hpp
 */

namespace lamp {

    /** Commands that can be sent to the lamp. */
    enum Command {
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
    void SendCommand(Command c);
}
