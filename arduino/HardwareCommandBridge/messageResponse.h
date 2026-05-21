#pragma once

#include "messages.h"

int D_PINS[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void sendMessage(struct Message msg);

void DevIdentify(struct Message *msg);
void Read(struct Message *msg);
void Set(struct Message *msg);
void Status(struct Message *msg);
void Run(struct Message *msg);