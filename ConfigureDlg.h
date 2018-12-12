/////////////////////////////////////////////////////////////////////////////
// ConfigureDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGUREDLG_H__31917CC2_E687_11D6_9B26_00801E0328BA__INCLUDED_)
#define AFX_CONFIGUREDLG_H__31917CC2_E687_11D6_9B26_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CConfigureDlg
/////////////////////////////////////////////////////////////////////////////

class 
CConfigureDlg : public CPropertySheet {
	DECLARE_DYNAMIC(CConfigureDlg)

// Construction
public:
	CConfigureDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CConfigureDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigureDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConfigureDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConfigureDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGUREDLG_H__31917CC2_E687_11D6_9B26_00801E0328BA__INCLUDED_)
