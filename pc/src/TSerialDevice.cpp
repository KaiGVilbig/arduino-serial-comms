#include "SerialDevice.h"

TSerialDevice::TSerialDevice() {
    _failState = false;
}

TSerialDevice::~TSerialDevice() {

}

void TSerialDevice::setFailState(bool fail) {
    _failState = fail;
}

bool TSerialDevice::openComm() {
    return !_failState;
}

void TSerialDevice::closeComm() {

}

void TSerialDevice::sendCommand(const std::string& command) {

}

std::string TSerialDevice::readResponse() {
    if (_failState) return "";
    return "";
}