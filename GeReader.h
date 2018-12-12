#ifndef __GEREADER_H
#define __GEREADER_h

#include <sys/timeb.h>
#include "Afxtempl.h"
#include "Zone.h"
#include "GpibInstrument.h"

class CNotify;
class CReadings;

class CGeReader: public CGpibInstrument {
public:
	CGeReader(CWnd* Cal, int Addr);
	~CGeReader();
  virtual void  SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask);
	virtual bool  StartRun();
	virtual bool  StopRun();
	virtual bool  ChangeScale(int iScale);
	bool ReadChebCoef(CString FileName);

protected:
	double Cnv(double r);
	virtual bool  myConfigure(CString sConf);
  virtual bool  myInit();
	virtual bool  myDisconnect();
	virtual bool  myConnect();
	void SendData(char *message);
	void SendRunData(char *message);
  CReadings*    pMyValues;
	struct _timeb timebuffer;
	double x, t;
	bool 	 justStarted;
	bool   inRun;
	double timeStart;
	double time0;
	double rMin, rMax;
	CArray<CZone, CZone&>  rZone;

private:

};

#endif

