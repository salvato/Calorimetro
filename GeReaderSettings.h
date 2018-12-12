/////////////////////////////////////////////////////////////////////////////
// GeReaderSettings.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEREADERSETTINGS_H__841EE022_BA22_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_GEREADERSETTINGS_H__841EE022_BA22_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGeReaderSettings dialog
/////////////////////////////////////////////////////////////////////////////

class
CGeReaderSettings : public CPropertyPage {
	DECLARE_DYNCREATE(CGeReaderSettings)

// Construction
public:
	CGeReaderSettings();
	~CGeReaderSettings();

// Dialog Data
	//{{AFX_DATA(CGeReaderSettings)
	enum { IDD = IDD_GEREADER_SETTING };
	CEdit	eAddress;
	CComboBox	cModelNumber;
	int		iAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGeReaderSettings)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	bool bSettingChanged;
  int	GetModelNumber();
  int	GetAddress();

protected:
	// Generated message map functions
	//{{AFX_MSG(CGeReaderSettings)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAddress();
	afx_msg void OnSelchangeModel();
	//}}AFX_MSG

private:
	int iOldModelNumber;
	int iOldAddress;
	bool bAddressModified;
	bool bModelModified;
  int	iModelNumber;

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEREADERSETTINGS_H__841EE022_BA22_11D8_9B27_00801E0328BA__INCLUDED_)
