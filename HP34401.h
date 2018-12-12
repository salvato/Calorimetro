#ifndef __HP34401_H
#define __HP34401_h

#include <sys/timeb.h>
#include <sys/types.h>
#include "Afxtempl.h"
#include "GeReader.h"

#define HP34401RUN_DATA (GPIB_MSG+4)
#define HP34401_DATA    (GPIB_MSG+5)

class CNotify;
class CReadings;

class CHP34401: public CGeReader {
public:
	virtual bool ChangeScale(int iScale);
	CHP34401(CWnd* Cal, int Addr);
	~CHP34401();
	virtual bool  StartRun();
	virtual bool  StopRun();
  void SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask);

private:
	virtual bool  myConfigure(CString sConf);
  virtual bool  myInit();
	virtual bool  myDisconnect();
	virtual bool  myConnect();
	void SendData(char *message);
	void SendRunData(char *message);
};

#endif

