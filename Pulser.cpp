#include <stdafx.h>
#include "dii.h"
#include "pulser.h"

///////////////////////////////////////////////////////////////////////////////
// Schema del Generatore di Impulso Scheda PCI-8255:                         //
//                                                                           //
// Clock/2 --> CLK0(CN1-7)                                                   //
//                                                                           //
//                +--> GATE0(CN1-9)                                          //
// P1C0(CN1-26) ->|                                                          //
//                +--> GATE1(CN1-16)                                         //
//                                                                           //
// OUT0(CN1-10) -> CLK1(CN1-13)                                              //
//                                                                           //
// OUT1(CN115) --> Inverter --> Connettore DB25 (1)                          //
///////////////////////////////////////////////////////////////////////////////

#define PORT_MODE0		      0x80
#define PORT1               0
#define PORT1A		          0		  // Used by the Pulser !!
#define PORT1B		          1
#define PORT1C		          2 
#define COUNTER0            0		  // Used by the Pulser !!
#define COUNTER1            1		  // Used by the Pulser !!
#define CLOCKFREQUENCY      2.5E6 // Scheda Modificata con doppio prescaler
#define COUNTER_MODE0       0x00  // Interrupt on Terminal Count
#define COUNTER_MODE1       0x02  // Programmable One-Shoot
#define COUNTER_MODE2       0x04  // Rate Generator
#define COUNTER_MODE3       0x06  // Square Wave Generator
#define COUNTER_MODE4       0x08  // Software Triggered Strobe
#define COUNTER_MODE5       0x0A  // Hardware Triggered Strobe
#define BINARY              0x00
#define BCD                 0x01
#define	LSB_MSB		   	  	  0x30

CPulser::CPulser(CString BoardName) {
  char szBoardName[201];
  //DiiSelectDevice (NULL, szBoardName, sizeof(szBoardName)-1);
 	strcpy(szBoardName, BoardName);
  // Set Device Handle
  myHandle = DiiOpenNamedDevice(szBoardName, TRUE);
  if(myHandle==INVALID_HANDLE_VALUE) {
    DiiSelectDevice (NULL, szBoardName, sizeof(szBoardName)-1);
    myHandle = DiiOpenNamedDevice(szBoardName, TRUE);
    if(myHandle==INVALID_HANDLE_VALUE) {
      AfxMessageBox("Error PCI 8255 Not Responding");
      PostQuitMessage(-321);
      return;
    }
  }//verifica se l'accesso alla scheda 

  if(!DiiSet8255Config(myHandle, PORT1, PORT_MODE0)) {//#1:Mode0,PortA-Out,PortB-Out,PortC-Out
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiSet8255Config PORT1: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }
	if(!DiiSetDigitalByte(myHandle, PORT1A, LOBYTE(0))) {	//Current Generator at Minimum Value
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiSetDigitalByte PORT1A: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }
	if(!DiiSetDigitalByte(myHandle, PORT1C, 0)) {		      //No Trigger to the Counter yet;
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiSetDigitalByte PORT1C: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }
	if(!DiiSetDigitalByte(myHandle, PORT1B, LOBYTE(0))) {	//	"					"						"		 	"
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiSetDigitalByte PORT1B: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }

  if(!DiiSetTimerConfig(myHandle, COUNTER0, LSB_MSB | COUNTER_MODE3 | BINARY)) {
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiSetTimerConfig 0: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }

  if(!DiiSetTimerConfig(myHandle, COUNTER1, LSB_MSB | COUNTER_MODE1 | BINARY)) {
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiSetTimerConfig 1: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }

}


CPulser::~CPulser() {
  if(!DiiCloseDevice(myHandle)) {
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiCloseDevice: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }
}


void
CPulser::SetPulseWidth(double PulseWidth) {
	DWORD PulseNumber;
	DWORD Prescaler;
	double ScaledPulsesPerSecond;
	PW = PulseWidth;
	Prescaler = (PulseWidth < 100.0) ? 10000 : 64000;
  if(!DiiLoadTimer(myHandle, COUNTER0, Prescaler)) {
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiLoadTimer COUNTER0: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }
  ScaledPulsesPerSecond= double(CLOCKFREQUENCY) / double(Prescaler);

	double tmp = ScaledPulsesPerSecond * PulseWidth;
	PulseNumber= UINT(tmp);
  if(!DiiLoadTimer(myHandle, COUNTER1, PulseNumber)) {
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiLoadTimer COUNTER1: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }
}


void
CPulser::SetPulseCurrent(int CurrentNumber) {
	DiiSetDigitalByte(myHandle, PORT1A, LOBYTE(CurrentNumber));
	DiiSetDigitalByte(myHandle, PORT1B, HIBYTE(CurrentNumber));
}


bool
CPulser::TriggerOn() {
  if(!DiiSetDigitalByte(myHandle, PORT1C, BYTE(1))) {
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in TriggerOn: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }
	return TRUE;
}


bool
CPulser::TriggerOff() {
	DiiSetDigitalByte(myHandle, PORT1C, BYTE(0));

  if(!DiiSetTimerConfig(myHandle, COUNTER0, LSB_MSB | COUNTER_MODE3 | BINARY)) {
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiSetTimerConfig 0: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }

  if(!DiiSetTimerConfig(myHandle, COUNTER1, LSB_MSB | COUNTER_MODE1 | BINARY)) {
    DWORD Error = GetLastError();
    CString sError;
    sError.Format(" Errore in DiiSetTimerConfig 1: GetLastError Returned %d", Error);
    AfxMessageBox(sError);
  }
	return TRUE;
}


void 
CPulser::Configure(double width, int current) {
  SetPulseCurrent(current);
  SetPulseWidth(width);
}

