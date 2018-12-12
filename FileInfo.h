// FileInfo.h: interface for the CFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINFO_H__0F2C1901_CAB1_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_FILEINFO_H__0F2C1901_CAB1_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class
CFileInfo {
public:
	bool GetUndef();
	void SetUndef();
	double TGer;
	double SampleMass;
	double ApiezonMass;
	double PulseDuration;
	double Current;
	double RHeater;
	double Delay;
  CString BolTFile;
  CString BolCFile;
	CFileInfo();
	virtual ~CFileInfo();

};

#endif // !defined(AFX_FILEINFO_H__0F2C1901_CAB1_11D8_9B27_00801E0328BA__INCLUDED_)
