/////////////////////////////////////////////////////////////////////////////
// TControlSettings.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCONTROLSETTINGS_H__841EE021_BA22_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_TCONTROLSETTINGS_H__841EE021_BA22_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTControlSettings dialog
/////////////////////////////////////////////////////////////////////////////

class
CTControlSettings : public CPropertyPage {
	DECLARE_DYNCREATE(CTControlSettings)

// Construction
public:
	CTControlSettings();
	~CTControlSettings();

// Dialog Data
	//{{AFX_DATA(CTControlSettings)
	enum { IDD = IDD_TCONTROL_SETTINGS };
	CButton	buttonUseAsGeReader;
	CEdit	eAddress;
	CComboBox	cModelNumber;
	int		iAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTControlSettings)
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
  BOOL GetUseAsGeReader();

protected:
	// Generated message map functions
	//{{AFX_MSG(CTControlSettings)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAddress();
	afx_msg void OnSelchangeModel();
	afx_msg void OnGeReaderClicked();
	//}}AFX_MSG

private:
	int iOldModelNumber;
	int iOldAddress;
	bool bAddressModified;
	bool bModelModified;
  int	iModelNumber;
	BOOL	bUseAsGeReader;
  BOOL bGeReaderModifyed;
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCONTROLSETTINGS_H__841EE021_BA22_11D8_9B27_00801E0328BA__INCLUDED_)
