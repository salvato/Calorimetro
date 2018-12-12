#if !defined(AFX_LOWLEVELSETTINGS_H__841EE024_BA22_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_LOWLEVELSETTINGS_H__841EE024_BA22_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LowLevelSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLowLevelSettings

class CLowLevelSettings : public CPropertySheet
{
	DECLARE_DYNAMIC(CLowLevelSettings)

// Construction
public:
	CLowLevelSettings(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CLowLevelSettings(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLowLevelSettings)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLowLevelSettings();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLowLevelSettings)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOWLEVELSETTINGS_H__841EE024_BA22_11D8_9B27_00801E0328BA__INCLUDED_)
