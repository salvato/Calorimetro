/////////////////////////////////////////////////////////////////////////////
// TControlSettings.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "TControlSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTControlSettings property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CTControlSettings, CPropertyPage)

CTControlSettings::CTControlSettings()
  : CPropertyPage(CTControlSettings::IDD) {
	//{{AFX_DATA_INIT(CTControlSettings)
	iAddress = 12;
	bUseAsGeReader = FALSE;
	//}}AFX_DATA_INIT
  iModelNumber = 0;
	
  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Temperature Control";
  strStringItem = "Settings";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    iAddress       = atoi(strtok(buf, ","));
    iModelNumber   = atoi(strtok(0, ","));
    bUseAsGeReader = atoi(strtok(0, "\0"));
    delete[] buf;
  }
  strValue.Format("%d,%d,%d", iAddress, iModelNumber, bUseAsGeReader);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CTControlSettings::~CTControlSettings() {
}


void
CTControlSettings::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTControlSettings)
	DDX_Control(pDX, IDC_GEREADER, buttonUseAsGeReader);
	DDX_Control(pDX, IDC_ADDRESS, eAddress);
	DDX_Control(pDX, IDC_MODEL, cModelNumber);
	DDX_Text(pDX, IDC_ADDRESS, iAddress);
	DDV_MinMaxInt(pDX, iAddress, 0, 30);
	DDX_Check(pDX, IDC_GEREADER, bUseAsGeReader);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTControlSettings, CPropertyPage)
	//{{AFX_MSG_MAP(CTControlSettings)
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_ADDRESS, OnChangeAddress)
	ON_CBN_SELCHANGE(IDC_MODEL, OnSelchangeModel)
	ON_BN_CLICKED(IDC_GEREADER, OnGeReaderClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int
CTControlSettings::GetModelNumber() {
  return iModelNumber;
}


int
CTControlSettings::GetAddress() {
  return iAddress;
}


/////////////////////////////////////////////////////////////////////////////
// CTControlSettings message handlers
/////////////////////////////////////////////////////////////////////////////

int 
CTControlSettings::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}


BOOL 
CTControlSettings::OnInitDialog() {
	CPropertyPage::OnInitDialog();
	
  cModelNumber.SetCurSel(iModelNumber);
  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  bSettingChanged  = false;

  if(bUseAsGeReader)
    buttonUseAsGeReader.SetCheck(BST_CHECKED);
  else
    buttonUseAsGeReader.SetCheck(BST_UNCHECKED);

  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CTControlSettings::OnChangeAddress() {
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
CTControlSettings::OnSelchangeModel() {
  if(cModelNumber.GetCurSel() == iOldModelNumber) {
    bModelModified = false;
  } else {
    bModelModified = true;
  }
  SetModified(bAddressModified || bModelModified);	
}


void
CTControlSettings::OnGeReaderClicked() {
	bUseAsGeReader = (buttonUseAsGeReader.GetCheck() == BST_CHECKED);
  bGeReaderModifyed = TRUE;
}


BOOL
CTControlSettings::OnApply() {
  if(!(bAddressModified || bModelModified || bGeReaderModifyed)) return true;
	if(!UpdateData(true)) return false;

  iModelNumber = cModelNumber.GetCurSel();
  bSettingChanged = true;

  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Temperature Control";
  strStringItem = "Settings";
  strValue.Format("%d,%d,%d", iAddress, iModelNumber, bUseAsGeReader);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  bAddressModified = false;
  bModelModified   = false;
  bGeReaderModifyed = FALSE;

  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  SetModified(bAddressModified || bModelModified || bGeReaderModifyed);	
	return CPropertyPage::OnApply();
}


BOOL
CTControlSettings::GetUseAsGeReader() {
  return bUseAsGeReader;
}
