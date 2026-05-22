#include "SerialDevice.h"

int main() {
    SerialDevice device("/dev/ttyUSB0", 9600);
    if (!device.openComm()) {
        std::cout << "Comms open failed\n";
    } else {
        std::cout << "Serial port opened\n";
    }

    device.sendCommand("IDENTIFY\n");
    std::string response = device.readResponse();
    std::cout << response << std::endl;
    device.closeComm();

    return 0;
}