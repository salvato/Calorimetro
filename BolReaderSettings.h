/////////////////////////////////////////////////////////////////////////////
// BolReaderSettings.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOLREADERSETTINGS_H__841EE023_BA22_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_BOLREADERSETTINGS_H__841EE023_BA22_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBolReaderSettings dialog
/////////////////////////////////////////////////////////////////////////////

class
CBolReaderSettings : public CPropertyPage {
	DECLARE_DYNCREATE(CBolReaderSettings)

// Construction
public:
	CBolReaderSettings();
	~CBolReaderSettings();

// Dialog Data
	//{{AFX_DATA(CBolReaderSettings)
	enum { IDD = IDD_BOLREADER_SETTINGS };
	CEdit	eAddress;
	CComboBox	cModelNumber;
	int		iAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBolReaderSettings)
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
	//{{AFX_MSG(CBolReaderSettings)
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

#endif // !defined(AFX_BOLREADERSETTINGS_H__841EE023_BA22_11D8_9B27_00801E0328BA__INCLUDED_)
