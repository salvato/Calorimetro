#if !defined(AFX_WARNINGOVERWRITEDLG_H__6F024B2F_C39E_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_WARNINGOVERWRITEDLG_H__6F024B2F_C39E_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WarningOverwriteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWarningOverwriteDlg dialog

class CWarningOverwriteDlg : public CDialog
{
// Construction
public:
	CWarningOverwriteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWarningOverwriteDlg)
	enum { IDD = IDD_READBOLCALFILE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarningOverwriteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWarningOverwriteDlg)
	afx_msg void OnMerge();
	afx_msg void OnOverwrite();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNINGOVERWRITEDLG_H__6F024B2F_C39E_11D8_9B27_00801E0328BA__INCLUDED_)
