#ifndef PWM_H
#define PWM_H

class Pwm {
public:
	Pwm();
	void changePosition(register16_t);
	register16_t dutyCycle;
protected:
private:
};

#endif