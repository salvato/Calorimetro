//////////////////////////////////////////////////////////////////////
// ParInfo.h: interface for the CParInfo class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARINFO_H__D8B1CF47_F169_11D6_9B26_00801E0328BA__INCLUDED_)
#define AFX_PARINFO_H__D8B1CF47_F169_11D6_9B26_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class
CParInfo {
public:
	CParInfo();
	bool Fixed;
	CParInfo(int num, CString name, double val, double err, double min, double max, bool fixed);
	virtual ~CParInfo();
  int Num;
  CString Name;
  double Val, Err, Min, Max;
};

#endif // !defined(AFX_PARINFO_H__D8B1CF47_F169_11D6_9B26_00801E0328BA__INCLUDED_)
