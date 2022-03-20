#include "Bluetooth.h"
#include "stdafx.h"
#include <string.h>

void Bluetooth::setBaud() {
	char* cmd = "AT+BAUD4";
	for (size_t i = 0; i < strlen(cmd); i++) {
		this->sendChar(cmd[i]);
	}
	this->sendChar('\n');
}