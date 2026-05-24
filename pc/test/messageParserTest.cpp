#include <gtest/gtest.h>
#include "messageParser.h"

TEST(MessageParser, ConstructMessageAllFields) {
    Message message;
    ParseError p = MessageParser::constructMessage(&message, "SET,PIN,9,10");
    EXPECT_EQ(p,ParseError::NO_ERROR);
    EXPECT_STREQ(message.type,"SET");
    EXPECT_STREQ(message.action,"PIN");
    EXPECT_EQ(message.params[0], 9);
    EXPECT_EQ(message.params[1], 10);
}

TEST(MessageParser, ConstructMessageOnlyType) {
    Message message;
    ParseError p = MessageParser::constructMessage(&message, "IDENTIFY");
    EXPECT_EQ(p,ParseError::NO_ERROR);
    EXPECT_STREQ(message.type,"IDENTIFY");
    EXPECT_STREQ(message.action,"");
    EXPECT_EQ(message.params[0], INT_MIN);
}

TEST(MessageParser, ConstructMessageTypeTooLong) {
    Message message;
    ParseError p = MessageParser::constructMessage(&message, "AAAAAAAAAAAAAAAAAAAAAAAA");
    EXPECT_EQ(p,ParseError::TYPE_LEN);
    EXPECT_STREQ(message.type,"");
}

TEST(MessageParser, ConstructMessageBadParam) {
    Message message;
    ParseError p = MessageParser::constructMessage(&message, "STATUS,PIN,NINE");
    EXPECT_EQ(p,ParseError::INVALID_PARAM);
    EXPECT_STREQ(message.type,"STATUS");
}

TEST(MessageParser, ParserWrongMessage) {
    Message message;
    MessageParser::constructMessage(&message, "IDENTIFY");
    ResponseError r = MessageParser::parseMessage(&message, "STATUS,PIN,0");
    EXPECT_EQ(r,ResponseError::WRONG_MESSAGE);
}

TEST(MessageParser, ParserSuccess) {
    Message message;
    MessageParser::constructMessage(&message, "IDENTIFY");
    ResponseError r = MessageParser::parseMessage(&message, "IDENTIFY,OK,Nano");
    EXPECT_EQ(r,ResponseError::NO_ERROR);
    EXPECT_STREQ(message.status,STATUS_GOOD);
    EXPECT_STREQ(message.response, "Nano");
}