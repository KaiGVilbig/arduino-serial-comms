#pragma once

#include "SerialDevice.h"
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

const std::string QUIT = "QUIT";

class SerialManager {
    public:
        SerialManager(ISerialDevice& device);
        SerialManager();
        ~SerialManager();

        bool init();
        void start();

        void writer();
        void reader();

    private:
        ISerialDevice* _device;
        bool _deviceOwner = true;
        std::queue<std::string> _writeQueue;
        std::mutex writeLock;
        std::atomic<bool> stopThreads = false;
        
        std::condition_variable _cv;
        std::mutex mtx;
        bool _dataSent;
};