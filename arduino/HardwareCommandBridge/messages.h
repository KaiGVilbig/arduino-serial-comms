#pragma once
// Message Structure: action,what,param1,param2...

const char CMD_IDENTIFY[] = "IDENTIFY";
const char CMD_READ[] = "READ";
const char CMD_SET[] = "SET";
const char CMD_STATUS[] = "STATUS";
const char CMD_RUN_PROGRAM[] = "RUN";

const char STATUS_GOOD[] = "OK";
const char STATUS_FAIL[] = "FAIL";

struct Message {
  char type[10] = {'\0'};
  char action[10] = {'\0'};
  int params[5] = {-1};
  char status[5] = {'\0'};
  char response[20] = {'\0'};
};

// IDENTIFY
// READ
// SET,LED,0
// SET,LED,1
// STATUS,PIN,13
// RUN,BLINK,14