/**
 * Calliope Hearts.
 *
 * Show a heart if two Calliope mini come into close proximity.
 *
 * @copyright (c) Calliope gGmbH.
 *
 * Licensed under the Apache Software License 2.0 (ASL 2.0)
 * Portions (c) Copyright British Broadcasting Corporation under MIT License.
 *
 * @author Matthias L. Jugel <leo@calliope.cc>
 * @author Stephan Noller <stephan@calliope.cc>
 */

#include "MicroBit.h"

const uint8_t dot[25] = {0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0,
                         0, 0, 1, 0, 0,
                         0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0
};
const uint8_t heart[25] = {0, 1, 0, 1, 0,
                           1, 1, 1, 1, 1,
                           1, 1, 1, 1, 1,
                           0, 1, 1, 1, 0,
                           0, 0, 1, 0, 0
};

const MicroBitImage Dot(5, 5, dot);
const MicroBitImage Heart(5, 5, heart);

MicroBit uBit;

bool specialAttachmentActive = false;
bool foundPartner = false;
int specialAttachmentTransmitPower = 1;

void onData(MicroBitEvent event) {
    PacketBuffer packet = uBit.radio.datagram.recv();
    const int signalStrength = packet.getRSSI();
    foundPartner = packet.getByte(0) == '!' && signalStrength < 75;
}

int main() {
    // Initialise the micro:bit runtime.
    uBit.init();
    uBit.serial.baud(115200);
    uBit.serial.send("Calliope Hearts v1.0\r\n");

    // init take over
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
    uBit.radio.enable();
    uBit.radio.setGroup(227);

    while (true) {
        if (uBit.systemTime() % 1500 < 750) uBit.display.clear();
        else if (foundPartner) uBit.display.print(Heart);
        else uBit.display.image.setPixelValue(2, 2, 255);
        uBit.radio.setTransmitPower(specialAttachmentTransmitPower);
        uBit.radio.datagram.send("!");
        uBit.sleep(100);
    }
}
