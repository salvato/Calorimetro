// EditWnd.h : header file
//
//
// Written by Kelly Marie Ward
// of Microsoft Developer Support.
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
///////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITWND_H__1F986763_FFEB_11D1_8540_00C04FAD7DBE__INCLUDED_)
#define AFX_EDITWND_H__1F986763_FFEB_11D1_8540_00C04FAD7DBE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////////////////////////////
// CEditWnd window

class CEditWnd : public CEdit
{
// Construction
public:
	CEditWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetParent(CWnd* p_Parent);
	virtual ~CEditWnd();

private:
  CWnd* pParent;

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditWnd)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITWND_H__1F986763_FFEB_11D1_8540_00C04FAD7DBE__INCLUDED_)
