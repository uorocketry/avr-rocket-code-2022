#ifndef USART_H
#define USART_H
class Usart
{
public:
	Usart(int id);
	void sendChar(char c);
	void sendString(char *str);
	int getID(void);	
	void readChar();
protected:
private:
	int id;
};

#endif