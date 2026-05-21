#pragma once

#include "messages.h"

void sendMessage(struct Message msg);

void DevIdentify(struct Message *msg);
void Read(struct Message *msg);
void Set(struct Message *msg);
void Status(struct Message *msg);
void Run(struct Message *msg);