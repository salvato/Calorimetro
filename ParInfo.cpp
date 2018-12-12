// ParInfo.cpp: implementation of the CParInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ParInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParInfo::CParInfo(int num, CString name, double val, double err, double min, double max, bool fixed):
  Num(num),
  Name(name),
  Val(val),
  Err(err),
  Min(min),
  Max(max),
  Fixed(fixed) {
}

CParInfo::~CParInfo()
{

}

CParInfo::CParInfo():
  Num(0),
  Name("Unknown"),
  Val(0.0),
  Err(0.0),
  Min(0.0),
  Max(0.0),
  Fixed(false){

}
