#include <gtest/gtest.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>

int main(int argc, char **argv) {
    auto layout = std::make_shared<log4cxx::PatternLayout>("[%p] (%d{yyyy-MM-dd HH:mm:ss}) %m%n");
    auto appender = std::make_shared<log4cxx::ConsoleAppender>(layout);
    log4cxx::BasicConfigurator::configure(appender);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}