#pragma once

#include "SerialDevice.h"
#include <queue>
#include <mutex>
#include <atomic>

const std::string QUIT = "QUIT";

class SerialManager {
    public:
        SerialManager();
        ~SerialManager();

        bool init();
        void start();

        void writer();
        void reader();

    private:
        SerialDevice _device;
        std::queue<std::string> _writeQueue;

        std::mutex writeLock;

        std::atomic<bool> stopThreads = false;

        int readTimeout = 100;
};