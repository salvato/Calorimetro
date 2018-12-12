// Readings.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Readings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadings

CReadings::CReadings(CString Title) : CWnd() {

  pMyBitmap = new CBitmap();
  if(pMyBitmap->LoadBitmap(IDB_READINGS) == 0) {
    AfxMessageBox("Non Trovo lo Sfondo!");
  }
  BITMAP Bmp;
  pMyBitmap->GetBitmap(&Bmp);
  myRect.left   = 0;
  myRect.right  = Bmp.bmWidth;
  myRect.top    = 0;
  myRect.bottom = Bmp.bmHeight;
  
  pBkgnd = new CStatic();
  pValue = new CEdit();

  CString ClassName;
  UINT cStyle= CS_DBLCLKS | CS_HREDRAW | CS_NOCLOSE | CS_OWNDC | CS_VREDRAW;
  cStyle |= CS_BYTEALIGNCLIENT;
  DWORD exStyle = WS_EX_DLGMODALFRAME;
  DWORD Style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
  ClassName = AfxRegisterWndClass(cStyle, 0, 0, AfxGetApp()->LoadIcon(IDI_READINGS));
  BOOL result = CreateEx(exStyle, ClassName, Title, Style, 0, 0, 100, 100, NULL, NULL);
  if(!result) {
    AfxMessageBox("Sensor Data CreateEx Failed\r\n");
  }
}

CReadings::~CReadings() {
  if(!IsIconic()) {
    CWinApp* pApp = AfxGetApp();
    CString strValue;
    CString strSection = "Readings";
    CString strStringItem;
    GetWindowText(strStringItem);
    CRect Rect;
    GetWindowRect(&Rect);
    strValue.Format("%d,%d", Rect.left, Rect.top);  
    pApp->WriteProfileString(strSection, strStringItem, strValue);
  }
  if(pMyBitmap != NULL) delete pMyBitmap;
  if(pBkgnd != NULL) delete pBkgnd;
  if(pValue != NULL) delete pValue;
}


BEGIN_MESSAGE_MAP(CReadings, CWnd)
	//{{AFX_MSG_MAP(CReadings)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReadings message handlers

int
CReadings::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

  int xControl  = 0;
  int yControl  = 0;

  CWinApp* pApp = AfxGetApp();
  CString strValue;
  CString strSection = "Readings";
  CString strStringItem;
  strStringItem = lpCreateStruct->lpszName;
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    sscanf(strValue, "%d,%d", &xControl, &yControl);
  }
  CalcWindowRect(&myRect,  adjustBorder);
  myRect.SetRect(xControl, yControl, xControl+myRect.Width(), yControl+myRect.Height());
  MoveWindow(&myRect, true);

  DWORD Style = WS_CHILD | WS_VISIBLE | SS_BITMAP;
  RECT Rect;
  GetClientRect(&Rect);
  if(!pBkgnd->Create(NULL, Style, Rect, this)) {
    return -1;
  }
  pBkgnd->SetBitmap(HBITMAP(*pMyBitmap));

  Style = WS_CHILD|WS_VISIBLE|ES_READONLY;
  Rect.left   = 6;
  Rect.right  = 136;
  Rect.top    = 8;
  Rect.bottom = 37;
  if(!pValue->Create(Style, Rect, this, 1)) {
    return -1;
  }
  pValue->SetWindowText("NoData");
	CMenu* menu= GetSystemMenu(false);
	menu->EnableMenuItem(SC_MAXIMIZE, MF_GRAYED | MF_BYCOMMAND);
	menu->EnableMenuItem(SC_SIZE, MF_GRAYED | MF_BYCOMMAND);
	return 0;
}


HBRUSH
CReadings::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	switch (nCtlColor) {
	  case CTLCOLOR_STATIC:
		  pDC->SetTextColor(RGB(192, 255, 255));
		  pDC->SetBkColor(RGB(0, 0, 0));
		  return (HBRUSH)GetStockObject(BLACK_BRUSH);
	  default:
	    HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
	    return hbr;
  }
}

void
CReadings::NewValue(CString value) {
  pValue->SetWindowText(value);
}


void
CReadings::NewValue(double value) {
  char txt[16];
  _gcvt(value, 8, txt);
  pValue->SetWindowText(txt);
}


void
CReadings::NewValue(float value) {
  char txt[16];
  _gcvt((double)value, 8, txt);
  pValue->SetWindowText(txt);
}


void
CReadings::NewValue(int value) {
  char txt[16];
  _gcvt((double)value, 8, txt);
  pValue->SetWindowText(txt);
}

