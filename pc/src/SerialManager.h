#pragma once

#include "SerialDevice.h"

const std::string QUIT = "QUIT";

class SerialManager {
    public:
        SerialManager();
        ~SerialManager();

        bool init();
        void start();

    private:
        SerialDevice _device;
};