#include "messageResponse.h"
#include "deviceInfo.h"
#include "programs.h"

void sendMessage(struct Message msg) {
  char response[47] = {'\0'};
  strcat(response, msg.type);
  strcat(response, ",");
  
  if (msg.action[0] != '\0') {
    strcat(response, msg.action);
    strcat(response, ",");
  }

  strcat(response, msg.status);
  strcat(response, ",");

  strcat(response, msg.response);

  Serial.write(response);
}

void DevIdentify(struct Message *msg) {
  strcpy(msg->status, STATUS_GOOD);
  strcpy(msg->response, BOARD);
}

void Read(struct Message *msg) {
  int pinN = pinNo(msg->params[0]);
  if (pinN <= LED_BUILTIN || pinN >= A7) {
    strcpy(msg->status, STATUS_FAIL);
    strcpy(msg->response, "BAD_PARAM");
    return;
  }

  int pinout = 0;
  char pinReading[6];

  if (strcmp(msg->action, "A") == 0) {
    pinout = analogRead(pinN);
  } else if (strcmp(msg->action, "D") == 0) {
    pinout = digitalRead(pinN);
  } else {
    strcpy(msg->status, STATUS_FAIL);
    strcpy(msg->response, "BAD_PARAM");
    return;
  }
  itoa(pinout, pinReading, sizeof(pinReading));
  strcpy(msg->status, STATUS_GOOD);
  strcpy(msg->response, pinReading);
}

void Set(struct Message *msg) {
  if (strcmp(msg->action, "LED") == 0 && (msg->params[0] == 0 || msg->params[0] == 1)) {
    digitalWrite(LED_BUILTIN, msg->params[0]);
    strcpy(msg->status, STATUS_GOOD);
  } else if (strcmp(msg->action, "PIN") == 0 && msg->params[0] < LED_BUILTIN && msg->params[0] > 1) {
    pinMode(msg->params[0], OUTPUT);

    int outValue = msg->params[1];
    if (msg->params[1] < 0 && pinNo(msg->params[2]) > LED_BUILTIN && pinNo(msg->params[2]) <= A7) {
      outValue = analogRead(pinNo(msg->params[2]));
    }
    analogWrite(msg->params[0], outValue);

    char res[6];
    itoa(outValue, res, sizeof(res));
    strcpy(msg->response, res);
    strcpy(msg->status, STATUS_GOOD);
  } else {
    strcpy(msg->status, STATUS_FAIL);
    strcpy(msg->response, "BAD_PARAM");
  }
}

void Status(struct Message *msg) {
  if (strcmp(msg->action, "PIN") == 0 && msg->params[0] >= LED_BUILTIN && msg->params[0] <= A7) {
    char stat = digitalRead(msg->params[0]) + '0';
    strcpy(msg->status, STATUS_GOOD);
    msg->response[0] = stat;
  } else {
    strcpy(msg->status, STATUS_FAIL);
    strcpy(msg->response, "BAD_PARAM");
  }
}

void Run(struct Message *msg) {
  if (strcmp(msg->action, PROGRAM_BLINK) == 0) {
    char blinkNo[10];
    int rate = 500;
    if (msg->params[1]) {
      rate = msg->params[1];
    }

    itoa(Blink(msg->params[0], rate), blinkNo, 10);
    strcpy(msg->status, STATUS_GOOD);
    strcpy(msg->response, blinkNo);
  } else {
    strcpy(msg->status, STATUS_FAIL);
    strcpy(msg->response, "UNKNOWN_PROGRAM");
  }
}

int pinNo(int n) {
  return n + LED_BUILTIN + 1;
}