#pragma once

#include "SerialDevice.h"
#include "messageParser.h"
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
        std::queue<Message> _writeQueue;
        std::queue<Message> _commandHistory;
        std::mutex writeLock;
        std::mutex historyLock;
        std::atomic<bool> stopThreads = false;

        std::condition_variable _cv;
        std::mutex mtx;
        bool _dataSent;
};