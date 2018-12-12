/////////////////////////////////////////////////////////////////////////////
// EditWnd.cpp : implementation file
//
//
// Written by Kelly Marie Ward
// of Microsoft Developer Support.
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "EditWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditWnd
/////////////////////////////////////////////////////////////////////////////


CEditWnd::CEditWnd() {
  pParent = NULL;
}


CEditWnd::~CEditWnd() {
}


BEGIN_MESSAGE_MAP(CEditWnd, CEdit)
	//{{AFX_MSG_MAP(CEditWnd)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditWnd message handlers
/////////////////////////////////////////////////////////////////////////////

void
CEditWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)  {
  if(nChar != 13) {
		CEdit::OnChar(nChar, nRepCnt, nFlags);
  }
}


void
CEditWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  if(nChar == 27) { // Esc means "Cancel".
    SetWindowText("");
    ShowWindow(SW_HIDE);
    GetParent()->SetFocus();
  } else if (nChar == 13) {  // Enter means "OK".
    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
    pParent->SendMessage(WM_SETFOCUS, WPARAM(0), LPARAM(this));
    ShowWindow(SW_HIDE);
  } else {
    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
  }
}


void
CEditWnd::SetParent(CWnd *p_Parent) {
  pParent = p_Parent;
}
