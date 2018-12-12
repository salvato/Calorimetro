/////////////////////////////////////////////////////////////////////////////
// PulserDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <fstream>
#include "resource.h"
#include "Pulser.h"
#include "PulserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPulserDlg property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CPulserDlg, CPropertyPage)

CPulserDlg::CPulserDlg() : CPropertyPage(CPulserDlg::IDD) {
	//{{AFX_DATA_INIT(CPulserDlg)
	m_Delay  = 10.0;
	m_Width  = 0.1;
	m_CurSel = 0;
	//}}AFX_DATA_INIT
  double Arg1, Arg2;
  int iArg3;
  
  std::ifstream Currents;
	int index;
	double temp;
  tValues.SetSize(0, 256);

  CString strValue;
  CString strSection = "Configuration";
  CString strStringItem;
  CWinApp* pApp = AfxGetApp();

  strStringItem = "CURRFILE";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  CString FileCur;
  FileCur = strValue;
  
  Currents.open(FileCur, std::ios::in);
  if(Currents.fail()) {
    char szFilter[] = "Current Values (Curval)|*.*||";
    char szDefExt[] = "";
    FileCur = "curval";
	  while (Currents.fail()) {
      Currents.clear();
      CFileDialog FileDialog(TRUE, szDefExt, FileCur,
                             OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
      if(FileDialog.DoModal() == IDOK) {
        FileCur = FileDialog.GetPathName();
      } else {
		    AfxMessageBox("Current file not Found", MB_OK | MB_ICONSTOP);
		    PostQuitMessage(-4001);
        return;
      }
      Currents.open(FileCur, std::ios::in);
    }
  }
	Currents >> index >> temp;
  while(!(Currents.fail() || Currents.eof())) {
    tValues.Add(temp);
   Currents >> index >> temp;
  }
	Currents.close();
  strValue = FileCur;
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strStringItem = "PULSER";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  Arg1  = m_Width;
  Arg2  = m_Delay;
  iArg3 = m_CurSel+1;
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    Arg1 = atof(strtok(buf, ","));
    Arg2 = atof(strtok(0, ","));
    iArg3 = atoi(strtok(0, ","));
    m_Width  = Arg1;
    m_Delay  = Arg2;
    m_CurSel = iArg3-1;
    delete[] buf;
  }
  strValue.Format("%g,%g,%d", Arg1, Arg2, iArg3);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CPulserDlg::~CPulserDlg() {
}


void 
CPulserDlg::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPulserDlg)
	DDX_Control(pDX, IDC_CURRENTS, m_CurrVals);
	DDX_Text(pDX, IDC_DELAY, m_Delay);
	DDV_MinMaxDouble(pDX, m_Delay, 0., 600.);
	DDX_Text(pDX, IDC_WIDTH, m_Width);
	DDV_MinMaxDouble(pDX, m_Width, 0., 3000.);
	DDX_CBIndex(pDX, IDC_CURRENTS, m_CurSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPulserDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CPulserDlg)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_CURRENTS, OnSelchangeCurrents)
	ON_WM_CANCELMODE()
	ON_EN_CHANGE(IDC_DELAY, OnChangeDelay)
	ON_EN_CHANGE(IDC_WIDTH, OnChangeWidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPulserDlg message handlers
/////////////////////////////////////////////////////////////////////////////

int
CPulserDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


BOOL
CPulserDlg::OnInitDialog() {
  char TempBuf[20];
  CDialog::OnInitDialog();
  int nElem = int(tValues.GetSize());
  for(int i=0; i < nElem; i++) {
 	  _gcvt(tValues[i], 7, TempBuf);
    m_CurrVals.AddString(TempBuf);
  }
  m_CurrVals.SetCurSel(m_CurSel);

  return TRUE;
}


BOOL 
CPulserDlg::OnApply() {
  pPulser->Configure(m_Width, m_CurSel + 1);
  int iArg3;
  double dArg1, dArg2;
  CString strValue;
  CString strStringItem;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  strStringItem = "PULSER";

  dArg1 = m_Width;
  dArg2 = m_Delay;
  iArg3 = m_CurSel + 1;
  strValue.Format("%g,%g,%d", dArg1, dArg2, iArg3);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
	
	return CPropertyPage::OnApply();
}


void 
CPulserDlg::OnSelchangeCurrents() {
  SetModified(TRUE);
}


void 
CPulserDlg::SetDevice(CPulser* pmyPulser) {
  pPulser = pmyPulser;
}


void 
CPulserDlg::OnChangeDelay() {
  SetModified(TRUE);
}


void 
CPulserDlg::OnChangeWidth() {
  SetModified(TRUE);
}


double 
CPulserDlg::GetCurrent() {
  return tValues[m_CurSel];
}
