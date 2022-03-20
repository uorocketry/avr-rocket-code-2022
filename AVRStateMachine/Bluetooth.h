#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "usart.h"

class Bluetooth : public Usart {
public:
	Bluetooth() : Usart(1) {this->setBaud();};
	void setBaud(void);
	void isConnected(void);
protected:
private:
	bool connected;
};

#endif