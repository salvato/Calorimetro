#ifndef __PULSER_H       /* prevent multiple includes */
#define __PULSER_H

class
CPulser{
public:
	CPulser(CString BoardName);
	~CPulser();
	void Configure(double width, int current);
	void SetPulseWidth(double);
	void SetPulseCurrent(int);
	bool TriggerOn();
	bool TriggerOff();
	double PW;
private:
	HANDLE myHandle;
	void ProgramDtoA(unsigned DtoA);
};
#endif