#pragma once
#include <string.h>
#include <vector>
#include <sstream>

const char CMD_IDENTIFY[] = "IDENTIFY";
const char CMD_READ[] = "READ";
const char CMD_SET[] = "SET";
const char CMD_STATUS[] = "STATUS";
const char CMD_RUN_PROGRAM[] = "RUN";

const char STATUS_GOOD[] = "OK";
const char STATUS_FAIL[] = "FAIL";

const char BAD_REQUEST[] = "UNKNOWN_COMMAND";

enum class ParseError {
    NO_ERROR,
    TYPE_LEN,
    ACTION_LEN,
    PARAM_LEN,
    INVALID_PARAM
};

enum class ResponseError {
    NO_ERROR,
    WRONG_MESSAGE
};

const int TYPE = 0;
const int ACTION = 1;
const int PARAMS = 2;

const int RESPONSE_STATUS = 2;
const int RESPONSE_VALUE = 3;

struct Message {
    char type[10] = {'\0'};
    char action[10] = {'\0'};
    int params[5] = {-1};
    char status[5] = {'\0'};
    char response[50] = {'\0'};
};

namespace MessageParser {
    ParseError constructMessage(Message* message, const std::string& input);
    ResponseError parseMessage(Message* message, const std::string& raw);
};