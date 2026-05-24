#include "messageParser.h"

static void delimSeparator(std::vector<std::string>* msgVector, const std::string& msg) {
    std::stringstream ss(msg);
    char delim = ',';
    std::string temp;

    while(getline(ss, temp, delim)) {
        msgVector->push_back(temp);
    }
}

namespace MessageParser {
    std::string messageSerializer(Message* message) {
        std::string msg = std::string(message->type);
        if (message->action[0] != '\0') {
            msg += ',' + std::string(message->action);
        }
        // if message->status[0] != '\0', it is an incoming message,
        // add status and response, skip params
        // else, outgoing message, skip status and response, add params
        if (message->status[0] != '\0') {
            msg += ',' + std::string(message->status);
            msg += ',' + std::string(message->response);
        } else if (message->params[0] != INT_MIN) {
            for (int p : message->params) {
                if (p == INT_MIN) break;
                msg += ',' + std::to_string(p);
            }
        }

        return msg;
    }

    ParseError constructMessage(Message* message, const std::string& input) {
        std::vector<std::string> separatedMessage;
        delimSeparator(&separatedMessage, input);

        int idx = 0;
        for (std::string s : separatedMessage) {
            if (idx == TYPE) {
                if (s.size() >= sizeof(message->type)) return ParseError::TYPE_LEN;
                strncpy(message->type, s.c_str(), sizeof(message->type) - 1);
            } else if (idx == ACTION) {
                if (s.size() >= sizeof(message->action)) return ParseError::ACTION_LEN;
                strncpy(message->action, s.c_str(), sizeof(message->action) - 1);
            } else if (idx - PARAMS < sizeof(message->params)/sizeof(int)) {
                try{
                    message->params[idx - PARAMS] = std::stoi(s);
                } catch(const std::exception& e) {
                    return ParseError::INVALID_PARAM;
                }
            } else {
                return ParseError::PARAM_LEN;
            }
            idx++;
        }
        return ParseError::NO_ERROR;
    }

    ResponseError parseMessage(Message* message, const std::string& raw) {
        std::vector<std::string> separatedResponse;
        delimSeparator(&separatedResponse, raw);

        int idx = 0;
        for (std::string s : separatedResponse) {
            if (idx == TYPE && strcmp(message->type, s.c_str()) != 0) return ResponseError::WRONG_MESSAGE;

            // if message has no action, like IDENTIFY, response will also no have action,
            // increment idx for comparison to const
            if (idx == ACTION && message->action[0] == '\0') idx++;

            if (idx == RESPONSE_STATUS) {
                strncpy(message->status, s.c_str(), sizeof(message->status) - 1);
            } else if (idx == RESPONSE_VALUE) {
                strncpy(message->response, s.c_str(), sizeof(message->response) - 1);
            }
            idx++;
        }
        return ResponseError::NO_ERROR;
    }

    std::string errorMessage(ResponseError err) {
        std::string resp = "";
        switch(err) {
            case ResponseError::WRONG_MESSAGE:
                resp = "Wrong message for given response.";
                break;
            default:
                resp = "No error.";
                break;
        }
        return resp;
    }

    std::string errorMessage(ParseError err) {
        std::string resp = "Command Parse Error: ";
        switch(err) {
            case ParseError::TYPE_LEN:
                resp += "Type field too long.";
                break;
            case ParseError::ACTION_LEN:
                resp += "Action field too long.";
                break;
            case ParseError::PARAM_LEN:
                resp += "Too many parameters.";
                break;
            case ParseError::INVALID_PARAM:
                resp += "Invalid parameter.";
                break;
            default:
                resp = "No error.";
                break;
        }
        return resp;
    }
}