#include <log4cxx/logmanager.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>

#include "SerialManager.h"

static auto logger = log4cxx::LogManager::getLogger("ardiono-serial-comms");

int main() {

    auto layout = std::make_shared<log4cxx::PatternLayout>("[%p] (%d{yyyy-MM-dd HH:mm:ss}) %m%n");
    auto appender = std::make_shared<log4cxx::ConsoleAppender>(layout);
    log4cxx::BasicConfigurator::configure(appender);

    LOG4CXX_INFO(logger, "Arduino Serial Comms started.");
    SerialManager manager;
    if (manager.init()) {
        manager.start();
    }

    // shut down logger
    log4cxx::LogManager::shutdown();
    return 0;
}