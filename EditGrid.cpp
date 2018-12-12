/////////////////////////////////////////////////////////////////////////////
// EditGrid.cpp : implementation file
//
//
// Written by Kelly Marie Ward
// of Microsoft Developer Support.
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
// Modified by Gabriele Salvato - 2004
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "EditGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditGrid
/////////////////////////////////////////////////////////////////////////////

CEditGrid::CEditGrid() {
  pParent = NULL;
}


CEditGrid::~CEditGrid() {
}


BEGIN_MESSAGE_MAP(CEditGrid, CMSFlexGrid)
	//{{AFX_MSG_MAP(CEditGrid)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CEditGrid, CMSFlexGrid)
  //{{AFX_EVENTSINK_MAP(CEditGrid)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_REFLECT(CEditGrid, -603 /* KeyPress */, OnKeyPressGrid, VTS_PI2)
	ON_EVENT_REFLECT(CEditGrid, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CEditGrid, 72 /* LeaveCell */, OnUpdateGrid, VTS_NONE)
END_EVENTSINK_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditGrid message handlers
/////////////////////////////////////////////////////////////////////////////

void
CEditGrid::PreSubclassWindow() {
	//Calculate border size
	SetRow(0);
	SetCol(0);
	m_lBorderWidth = GetCellLeft();
	m_lBorderHeight = GetCellTop();

	// To convert grid rect from twips to DC units
	// We need pixels per inch
	CDC* pDC = GetDC();
	m_nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
	m_nLogY = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
	
	//Create invisible edit control
	m_edit.Create(WS_CHILD|ES_MULTILINE|ES_WANTRETURN, 
		CRect(0,0,0,0), this, GetDlgCtrlID());
  m_edit.SetParent(this);
}


void
CEditGrid::OnDblClickGrid() {
  if(GetCol() == GetCols()-1) {
    bool Fixed;
    CString String = GetText();
    if(String == "True") {
      SetText("False");
      Fixed = false;
    } else {
      SetText("True");
      Fixed = true;
    }
    if(pParent != NULL) {
      pParent->SendMessage(MSG_FIXUNFIX, WPARAM(GetRow()), LPARAM(Fixed));
    }
    return;
  } else if(GetCol() == 3) {
    return;
  } else {
    m_edit.SetWindowText(GetText());
    m_edit.SetSel(0,-1);

    // Adjust for border height and convert from twips to screen units.
    //
    // TWIP:
    // "Twip" is a unit of measurement equal to 1/20th of a printers point.
    // There are 1440 twips to and inch, 567 twips to a centimeter.
    m_edit.MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440,
                      ((GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
                      (GetCellWidth()* m_nLogX)/1440,
                      (GetCellHeight()* m_nLogY)/1440, FALSE);

    m_edit.ShowWindow(SW_SHOW);
    m_edit.SetFocus();
  }
}


void
CEditGrid::OnKeyPressGrid(short FAR* KeyAscii) {	
  ASSERT (KeyAscii != NULL);

  if(GetCol() == GetCols()-1) {
    return;
  }

  m_edit.SetWindowText(GetText());

  if(*KeyAscii == 13) {
    m_edit.SetSel(0,-1);
  } else {
    char buf[] = " ";
    buf[0] = (char)*KeyAscii;
    m_edit.SetSel(-1,-1);
    m_edit.ReplaceSel(buf);
  }

  // Adjust for border height and convert from twips to screen units.
  //
  // TWIP:
  // "Twip" is a unit of measurement equal to 1/20th of a printers point.
  // There are 1440 twips to and inch, 567 twips to a centimeter.
  m_edit.MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440,
            ((GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
            (GetCellWidth()* m_nLogX)/1440,
            (GetCellHeight()* m_nLogY)/1440, FALSE);

  m_edit.ShowWindow(SW_SHOW);
  m_edit.SetFocus();
}


void
CEditGrid::OnUpdateGrid() {
  // Check to see if edit is visible.
  BOOL bVisible = ::GetWindowLong(m_edit.GetSafeHwnd(), GWL_STYLE)
  & WS_VISIBLE;
  if(bVisible) {
    CString cStr;
    m_edit.GetWindowText(cStr);
    SetText(cStr);
    m_edit.SetWindowText("");
    m_edit.ShowWindow(SW_HIDE);
    if(pParent != NULL) {
      pParent->SendMessage(MSG_PARUPDATE, WPARAM(GetRow()), LPARAM(0));
    }
  }
}


UINT
CEditGrid::OnGetDlgCode() {	
	return DLGC_WANTALLKEYS;
}


void
CEditGrid::OnSetFocus(CWnd* pOldWnd) {
	CMSFlexGrid::OnSetFocus(pOldWnd);
	
	OnUpdateGrid();	
}


void 
CEditGrid::SetParent(CWnd *myParent) {
  pParent = myParent;
}
