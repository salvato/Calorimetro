//////////////////////////////////////////////////////////////////////
// FileInfo.cpp: implementation of the CFileInfo class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "FileInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileInfo::CFileInfo() {
	TGer          = -1;
	SampleMass    = -1;
	ApiezonMass   = -1;
	PulseDuration = -1;
	Current       = -1;
	RHeater       = -1;
	Delay         = -1;
  BolTFile      = "?";
  BolCFile      = "?";
}


CFileInfo::~CFileInfo() {

}


void
CFileInfo::SetUndef() {
	TGer          = -1;
	SampleMass    = -1;
	ApiezonMass   = -1;
	PulseDuration = -1;
	Current       = -1;
	RHeater       = -1;
	Delay         = -1;
  BolTFile      = "?";
  BolCFile      = "?";
}


bool
CFileInfo::GetUndef() {
  if((TGer < 0.0) || 
     (PulseDuration < 0.0) || 
     (Current < 0.0) || 
     (RHeater < 0.0) || 
     (Delay < 0.0) || 
     (SampleMass  < 0.0)|| 
     (ApiezonMass < 0.0)
    ) return true;
  if(BolTFile == "?") return true;
  if(BolCFile == "?") return true;
  return false;
}
