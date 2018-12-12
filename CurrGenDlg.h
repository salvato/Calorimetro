/////////////////////////////////////////////////////////////////////////////
// CurrGenDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRGENDLG_H__68B43542_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_CURRGENDLG_H__68B43542_B95C_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCurrGen;

/////////////////////////////////////////////////////////////////////////////
// CCurrGenDlg dialog
/////////////////////////////////////////////////////////////////////////////

class 
CCurrGenDlg : public CPropertyPage {
	DECLARE_DYNCREATE(CCurrGenDlg)

// Construction
public:
	CCurrGenDlg();
	~CCurrGenDlg();

// Dialog Data
	//{{AFX_DATA(CCurrGenDlg)
	enum { IDD = IDD_CURRENT_GENERATOR };
	double	Current;
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurrGenDlg)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
  void SetDevice(CCurrGen* Device);

protected:
	// Generated message map functions
	//{{AFX_MSG(CCurrGenDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChangeCurrent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool SetCurrent(double Current);
  CCurrGen* pCurrGen;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURRGENDLG_H__68B43542_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
