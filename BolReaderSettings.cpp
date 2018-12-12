/////////////////////////////////////////////////////////////////////////////
// BolReaderSettings.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "BolReaderSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBolReaderSettings property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CBolReaderSettings, CPropertyPage)

CBolReaderSettings::CBolReaderSettings()
  : CPropertyPage(CBolReaderSettings::IDD) {
	//{{AFX_DATA_INIT(CBolReaderSettings)
	iAddress = 16;
	//}}AFX_DATA_INIT
  iModelNumber = 1;
	
  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Bol Reader";
  strStringItem = "Settings";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    iAddress     = atoi(strtok(buf, ","));
    iModelNumber = atoi(strtok(0, "\0"));
    delete[] buf;
  }
  strValue.Format("%d,%d", iAddress, iModelNumber);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  bSettingChanged  = false;
}


CBolReaderSettings::~CBolReaderSettings() {
}


void
CBolReaderSettings::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBolReaderSettings)
	DDX_Control(pDX, IDC_ADDRESS, eAddress);
	DDX_Control(pDX, IDC_MODEL, cModelNumber);
	DDX_Text(pDX, IDC_ADDRESS, iAddress);
	DDV_MinMaxInt(pDX, iAddress, 1, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBolReaderSettings, CPropertyPage)
	//{{AFX_MSG_MAP(CBolReaderSettings)
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_ADDRESS, OnChangeAddress)
	ON_CBN_SELCHANGE(IDC_MODEL, OnSelchangeModel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int
CBolReaderSettings::GetModelNumber() {
  return iModelNumber;
}


int
CBolReaderSettings::GetAddress() {
  return iAddress;
}

/////////////////////////////////////////////////////////////////////////////
// CBolReaderSettings message handlers
/////////////////////////////////////////////////////////////////////////////

int 
CBolReaderSettings::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}


BOOL 
CBolReaderSettings::OnInitDialog() {
	CPropertyPage::OnInitDialog();
	
  cModelNumber.SetCurSel(iModelNumber);
  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  bSettingChanged  = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CBolReaderSettings::OnChangeAddress() {
  CString sText;
  eAddress.GetWindowText(sText);
  if(atoi(sText) == iOldAddress) {
    bAddressModified = false;
  } else {
    bAddressModified = true;
  }
  SetModified(bAddressModified || bModelModified);	
}


void
CBolReaderSettings::OnSelchangeModel() {
  if(cModelNumber.GetCurSel() == iOldModelNumber) {
    bModelModified = false;
  } else {
    bModelModified = true;
  }
  SetModified(bAddressModified || bModelModified);	
}


BOOL
CBolReaderSettings::OnApply() {
  if(!(bAddressModified || bModelModified)) return true;
	if(!UpdateData(true)) return false;

  iModelNumber = cModelNumber.GetCurSel();
  bSettingChanged = true;

  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Bol Reader";
  strStringItem = "Settings";
  strValue.Format("%d,%d", iAddress, iModelNumber);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  SetModified(bAddressModified || bModelModified);	
	return CPropertyPage::OnApply();
}

