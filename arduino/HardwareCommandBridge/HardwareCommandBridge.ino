#include "messageResponse.h";

char data[50];

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    int bytesRead = Serial.readBytesUntil('\n', data, sizeof(data) -1);
    data[bytesRead] = '\0';

    messageHandler(data);
    Serial.flush();
  }
}

void messageHandler(char* message) {
  struct Message msg = messageParser(message);

  if (strcmp(msg.type, CMD_IDENTIFY) == 0) {
    DevIdentify(&msg);
  } else if (strcmp(msg.type, CMD_SET) == 0) {
    Set(&msg);
  } else if (strcmp(msg.type, CMD_STATUS) == 0) {
    Status(&msg);
  } else if (strcmp(msg.type, CMD_READ) == 0) {
    Read(&msg);
  } else if (strcmp(msg.type, CMD_RUN_PROGRAM) == 0) {
    Run(&msg);
  } else {
    strcat(msg.status, STATUS_FAIL);
    strcat(msg.response, BAD_REQUEST);
  }

  sendMessage(msg);
}

struct Message messageParser(char* message) {
  struct Message m;

  char* saveptr;
  char* token = strtok_r(message, ",", &saveptr);

  // Set message type
  strcpy(m.type, token);

  // Set message action
  token = strtok_r(NULL, ",", &saveptr);
  strcpy(m.action, token);

  // Set message params
  int paramNo = 0;
  while ((token = strtok_r(NULL, ",", &saveptr))) {
    bool isNum = true;
    for (int i = 0; i < (int)strlen(token); i++) {
      if (!isdigit(token[i])) {
        isNum = false;
        break;
      }
    }

    if (isNum) {
      m.params[paramNo] = atoi(token);
      paramNo++;
    } else {
      strcpy(m.charParams, token);
    }
  }
  return m;
}