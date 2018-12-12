//////////////////////////////////////////////////////////////////////
// FileHeader.h: interface for the CFileHeader class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEHEADER_H__A7367991_B935_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_FILEHEADER_H__A7367991_B935_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class 
CFileHeader {
public:
	CFileHeader();
	virtual ~CFileHeader();

  double Current; 
  double ApiezonMass; 
  double SampleMass;
  double TestCurrent; 
  double PulseWidth; 
  double Delay; 
  double WireResistance; 
  double HeaterResistance;
  CString BolTFile;
  CString BolCFile;
};

#endif // !defined(AFX_FILEHEADER_H__A7367991_B935_11D8_9B27_00801E0328BA__INCLUDED_)
