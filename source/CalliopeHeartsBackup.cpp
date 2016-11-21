/**
 * Calliope Hearts.
 *
 * Simply show the scrolling ticker.
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
#include "CalliopeHeartsConfig.h"

#if BACKUP

const uint8_t heart[25] = {0, 1, 0, 1, 0,
                           1, 0, 1, 0, 1,
                           1, 0, 0, 0, 1,
                           0, 1, 0, 1, 0,
                           0, 0, 1, 0, 0
};

const MicroBitImage Heart(5, 5, heart);

MicroBit uBit;

int main() {
    // Initialise the micro:bit runtime.
    uBit.init();
    uBit.serial.baud(115200);
    uBit.serial.send("Calliope Hearts v1.0 (backup)\r\n");

    int counter = 0;
    while (true) {
        if (uBit.systemTime() % 1500 < 750) {
            if(counter++ % 120 == 0) {
                uBit.display.scroll("Ich", 180);
                uBit.display.scroll(Heart, 180);
                uBit.display.scroll("IT!", 180);
            }
            uBit.display.clear();
        } else uBit.display.print(Heart);

        uBit.sleep(100);
    }
}

#endif