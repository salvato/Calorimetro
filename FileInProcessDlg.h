#if !defined(AFX_FILEINPROCESSDLG_H__F9F29121_C50D_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_FILEINPROCESSDLG_H__F9F29121_C50D_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileInProcessDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileInProcessDlg dialog

class CFileInProcessDlg : public CDialog
{
// Construction
public:
	CFileInProcessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileInProcessDlg)
	enum { IDD = IDD_PROCESSING };
	CString	sFilename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileInProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileInProcessDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEINPROCESSDLG_H__F9F29121_C50D_11D8_9B27_00801E0328BA__INCLUDED_)
