//////////////////////////////////////////////////////////////////////
// GpibInstrument.h: interface for the CGpibInstrument class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPIBINSTRUMENT_H__B3F302E1_B5C8_11D2_9F8E_00801E0328BA__INCLUDED_)
#define AFX_GPIBINSTRUMENT_H__B3F302E1_B5C8_11D2_9F8E_00801E0328BA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "GpibNotify.h"

class 
CGpibInstrument {
public:
	int gpibwrite(CString sCmd);
	CGpibInstrument(CWnd* Cal, int Addr);
	virtual ~CGpibInstrument();

	bool Connect();
	bool Init(CGpibNotify* pNotify=NULL);
  bool Configure(CString sConf);
	bool Disconnect();

	bool Connected;
  bool Initialized;
	bool Configured;

	void GpibError(char *message);
	char* GetError();
  virtual void SRQService(long, long, long, long, long FAR*){};

private:

	bool CouldConfigure();

protected:
	virtual bool myConnect();
  virtual bool myDisconnect();
  virtual bool myInit();
  virtual bool myConfigure(CString sConf);
	void errmsg(char*, int, int, long);
	int gpibwrite(char* cmd);
	CWnd* pParent;
	CGpibNotify* pGpibNotify;
	int myUd;
	int myGpibAddress;
  int msk;
	char LastError[256];
	char buf[256];
	char cmd[256];
};

#endif // !defined(AFX_GPIBINSTRUMENT_H__B3F302E1_B5C8_11D2_9F8E_00801E0328BA__INCLUDED_)
