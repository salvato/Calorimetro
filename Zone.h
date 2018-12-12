//////////////////////////////////////////////////////////////////////
// Zone.h: interface for the CZone class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZONE_H__A7367998_B935_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_ZONE_H__A7367998_B935_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXCOEF 30

class 
CZone {
public:
	CZone();
	virtual ~CZone();
public:
  double rMin;
  double rMax;
  double Zl;
  double Zu;
  int nCoef;
  double A[MAXCOEF];

};

#endif // !defined(AFX_ZONE_H__A7367998_B935_11D8_9B27_00801E0328BA__INCLUDED_)
