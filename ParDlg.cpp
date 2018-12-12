/////////////////////////////////////////////////////////////////////////////
// ParDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ParInfo.h"
#include "ParDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define TITLES {"Number", "Name", "Value", "Error", "Minimum", "Maximum", "Fixed"}


/////////////////////////////////////////////////////////////////////////////
// CParDlg dialog
/////////////////////////////////////////////////////////////////////////////


CParDlg::CParDlg(CWnd* p_Parent /*=NULL*/)
	: CDialog(CParDlg::IDD, p_Parent) {
	//{{AFX_DATA_INIT(CParDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  pParent = p_Parent;
}


CParDlg::~CParDlg() {
  if(!::IsWindow(m_hWnd)) return;
  if(!IsIconic()) {
    CWinApp* pApp = AfxGetApp();
    CString strSection = "Parameters";
    CString strStringItem;
    GetWindowText(strStringItem);
    CRect Rect;
    GetWindowRect(&Rect);
    CString strValue;
    strValue.Format("%d,%d", Rect.left, Rect.top);  
    pApp->WriteProfileString(strSection, strStringItem, strValue);
  }
}


void
CParDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParDlg)
	DDX_Control(pDX, IDC_MSFLEXGRID, myGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParDlg, CDialog)
	//{{AFX_MSG_MAP(CParDlg)
  ON_MESSAGE(MSG_FIXUNFIX, OnFixUnfix)
  ON_MESSAGE(MSG_PARUPDATE, OnParUpdate)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


bool 
CParDlg::AddPar(CParInfo Parinfo) {
  CString String;
  long lastRow = myGrid.GetRows();
  if(Parinfo.Num > 1) 
    myGrid.SetRows(++lastRow);
  myGrid.SetRow(lastRow-1);
  myGrid.SetCol(0);
  String.Format("%d", Parinfo.Num);
  myGrid.SetText(String);
  myGrid.SetCol(1);
  myGrid.SetText(Parinfo.Name);
  myGrid.SetCol(2);
  String.Format("%.4g", Parinfo.Val);
  myGrid.SetText(String);
  myGrid.SetCol(3);
  String.Format("%.4g", Parinfo.Err);
  myGrid.SetText(String);
  myGrid.SetCol(4);
  String.Format("%.4g", Parinfo.Min);
  myGrid.SetText(String);
  myGrid.SetCol(5);
  String.Format("%.4g", Parinfo.Max);
  myGrid.SetText(String);
  myGrid.SetCol(6);
  if(Parinfo.Fixed)
    String.Format("True", Parinfo.Fixed);
  else
    String.Format("False", Parinfo.Fixed);
  myGrid.SetText(String);

  return true;
}


bool 
CParDlg::AddPar(int i, CString name, double val, double err, double min, double max, bool fixed) {
  return AddPar(CParInfo(i, name, val, err, min, max, fixed));
}


CParInfo 
CParDlg::GetParInfo(int num) {
  if(num < 1) 
    return CParInfo();
  if(myGrid.GetRows() <= num)
    return CParInfo();
  myGrid.SetRow(num);
  CParInfo ParInfo;
  ParInfo.Num = num;
  myGrid.SetCol(1);
  ParInfo.Name = myGrid.GetText();
  myGrid.SetCol(2);
  ParInfo.Val = atof(myGrid.GetText());
  myGrid.SetCol(3);
  ParInfo.Err = atof(myGrid.GetText());
  myGrid.SetCol(4);
  ParInfo.Min = atof(myGrid.GetText());
  myGrid.SetCol(5);
  ParInfo.Max = atof(myGrid.GetText());
  myGrid.SetCol(6);
  ParInfo.Fixed = (myGrid.GetText() == "True");
  return ParInfo;
}


void 
CParDlg::UpdateWindow() {
  int ShowStatus = ShowWindow(SW_HIDE);
  CRect myRect;
  GetWindowRect(myRect);
  myRect.SetRect(myRect.left, myRect.top, 1000, 1000);
  MoveWindow(&myRect, true);
  myRect.SetRect(0, 0, 900, 900);
  myGrid.MoveWindow(myRect, TRUE);
  GetWindowRect(myRect);
  int x0 = myRect.left;
  int y0 = myRect.top;
  int i = myGrid.GetRows()-1;
  int j = myGrid.GetCols()-1;
  if(i<15) {
    myGrid.SetRow(i);
    myGrid.SetCol(j);
    int xr = myGrid.GetCellLeft() + myGrid.GetCellWidth() + 2*myGrid.m_lBorderWidth;
    int yb = myGrid.GetCellTop() + myGrid.GetCellHeight() + 2*myGrid.m_lBorderHeight;
    myRect.SetRect(0, 0, (xr * myGrid.m_nLogX)/1440, (yb* myGrid.m_nLogY)/1440);
    myGrid.MoveWindow(myRect, TRUE);
    CalcWindowRect(&myRect, CWnd::adjustOutside);
    myRect.SetRect(x0, y0, x0+myRect.Width(), y0+myRect.Height());
    MoveWindow(&myRect, true);
    ShowWindow(ShowStatus);
  } else {
    myGrid.SetRow(15);
    myGrid.SetCol(j);
    int xr = myGrid.GetCellLeft() + myGrid.GetCellWidth() + 2*myGrid.m_lBorderWidth + 225;
    int yb = myGrid.GetCellTop() + myGrid.GetCellHeight() + 2*myGrid.m_lBorderHeight;
    myRect.SetRect(0, 0, (xr * myGrid.m_nLogX)/1440, (yb* myGrid.m_nLogY)/1440);
    myGrid.MoveWindow(myRect, TRUE);
    CalcWindowRect(&myRect, CWnd::adjustOutside);
    myRect.SetRect(x0, y0, x0+myRect.Width(), y0+myRect.Height());
    MoveWindow(&myRect, true);
    ShowWindow(ShowStatus);
  }
}


void 
CParDlg::ClearAll() {
  CString Titles[] = TITLES;
  myGrid.Clear();
  myGrid.SetRows(2);
  myGrid.SetCols(sizeof(Titles)/sizeof(Titles[0]));
  for(int i=0; i<sizeof(Titles)/sizeof(Titles[0]); i++){
    myGrid.SetRow(0);
    myGrid.SetCol(i);
    myGrid.SetText(Titles[i]);
  }
  UpdateWindow();
}


bool 
CParDlg::UpdatePar(CParInfo ParInfo) {
  CString String;
  long lastRow = myGrid.GetRows();
  if((ParInfo.Num < 1) || (ParInfo.Num > lastRow))
    return false;
  myGrid.SetRow(ParInfo.Num);
  myGrid.SetCol(2);
  String.Format("%.4g", ParInfo.Val);
  myGrid.SetText(String);
  myGrid.SetCol(3);
  String.Format("%.4g", ParInfo.Err);
  myGrid.SetText(String);
  myGrid.SetCol(4);
  String.Format("%.4g", ParInfo.Min);
  myGrid.SetText(String);
  myGrid.SetCol(5);
  String.Format("%.4g", ParInfo.Max);
  myGrid.SetText(String);
  myGrid.SetCol(6);
  if(ParInfo.Fixed)
    String.Format("True", ParInfo.Fixed);
  else
    String.Format("False", ParInfo.Fixed);
  myGrid.SetText(String);

  return true;
}


/////////////////////////////////////////////////////////////////////////////
// CParDlg message handlers
/////////////////////////////////////////////////////////////////////////////

LRESULT
CParDlg::OnFixUnfix(WPARAM wParam, LPARAM lParam) {
  if(pParent != NULL) {
    pParent->SendMessage(MSG_FIXUNFIX, wParam, lParam);
  }
  return LRESULT(0);
}


LRESULT 
CParDlg::OnParUpdate(WPARAM wParam, LPARAM lParam) {
  if(pParent != NULL) {
    pParent->SendMessage(MSG_PARUPDATE, wParam, lParam);
  }
  return LRESULT(0);
}


int
CParDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

  CWinApp* pApp = AfxGetApp();
  CString strSection = "Parameters";
  CString strStringItem;
  GetWindowText(strStringItem);
  CString strValue;
  strValue = pApp->GetProfileString(strSection, strStringItem);
  x0 = 0;
  y0 = 0;
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    x0   = atoi(strtok(buf, ","));
    y0   = atoi(strtok(0, "\0"));
    delete[] buf;
  }

	return 0;
}


BOOL
CParDlg::OnInitDialog() {
	CDialog::OnInitDialog();

  myGrid.SetParent(this);
	
  CString Titles[] = TITLES;
  myGrid.SetRows(2);
  myGrid.SetCols(sizeof(Titles)/sizeof(Titles[0]));
  myGrid.SetFixedRows(1);
  myGrid.SetFixedCols(2);
  myGrid.SetFillStyle(1);
  myGrid.SetFocusRect(2);
  myGrid.SetAllowBigSelection(0);

  CDC* pDC = myGrid.GetDC();
  CSize Size = pDC->GetTextExtent(Titles[0]);
  myGrid.SetColWidth(0, (1440/myGrid.m_nLogX)*Size.cx);
  Size = pDC->GetTextExtent(Titles[myGrid.GetCols()-1]);
  myGrid.SetColWidth(myGrid.GetCols()-1, (1440/myGrid.m_nLogX)*Size.cx);
  ReleaseDC(pDC);

  CRect myRect;
  myGrid.SetRow(myGrid.GetRows()-1);
  myGrid.SetCol(myGrid.GetCols()-1);
  int xr = myGrid.GetCellLeft() + myGrid.GetCellWidth() + 2*myGrid.m_lBorderWidth;
  int yb = myGrid.GetCellTop() + myGrid.GetCellHeight() + 2*myGrid.m_lBorderHeight;
  myRect.SetRect(0, 0, (xr * myGrid.m_nLogX)/1440, (yb* myGrid.m_nLogY)/1440);
  myGrid.MoveWindow(myRect, TRUE);
  CalcWindowRect(&myRect, CWnd::adjustOutside);
  myRect.SetRect(x0, y0, x0+myRect.Width(), y0+myRect.Height());
  MoveWindow(&myRect, true);

  for(int i=0; i<sizeof(Titles)/sizeof(Titles[0]); i++){
    myGrid.SetRow(0);
    myGrid.SetCol(i);
    myGrid.SetText(Titles[i]);
  }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL
CParDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
	return CDialog::OnCommand(wParam, lParam);
}


void
CParDlg::OnDestroy() {
	CDialog::OnDestroy();
	
  if(!IsIconic()) {
    CWinApp* pApp = AfxGetApp();
    CString strSection = "Parameters";
    CString strStringItem;
    GetWindowText(strStringItem);
    CRect Rect;
    GetWindowRect(&Rect);
    CString strValue;
    strValue.Format("%d,%d", Rect.left, Rect.top);  
    pApp->WriteProfileString(strSection, strStringItem, strValue);
  }
}
