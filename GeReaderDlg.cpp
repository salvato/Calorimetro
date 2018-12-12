/////////////////////////////////////////////////////////////////////////////
// GeReaderDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <fstream>
#include "resource.h"
#include "GeReader.h"
#include "GeReaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeReaderDlg property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CGeReaderDlg, CPropertyPage)


CGeReaderDlg::CGeReaderDlg() 
  : CPropertyPage(CGeReaderDlg::IDD) {
	//{{AFX_DATA_INIT(CGeReaderDlg)
	m_Range = 6;
	m_FilePar = _T("Germanio1.chb");
	//}}AFX_DATA_INIT

  pGeReader = NULL;
  bRangeChanged = false;
  bFileChanged = false;

  int iArg1;
  CWinApp* pApp = AfxGetApp();
  strSection = "Configuration";
  strStringItem = "GeReader";
  strValue = pApp->GetProfileString(strSection, strStringItem);

  iArg1 = m_Range;         // Range
  if(strValue != "") {
    sscanf(strValue, "%d", &iArg1);
    m_Range = iArg1;
  }
  strValue.Format("%1d", iArg1);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strStringItem = "GERMANIO";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  CString FileGe = m_FilePar;// File dei coefficienti di Chebichev
  if(strValue != "") {
    FileGe = strValue;
    m_FilePar = FileGe;
  }
  char szFilter[] = "Chebichev Coef. (*.chb)|*.chb|All Files (*.*)|*.*||";
  char szDefExt[] = "chb";
  std::ifstream ChebFile;
  ChebFile.open(FileGe, std::ios::in);
  while (ChebFile.fail()){
    ChebFile.clear();
    CFileDialog FileDialog(TRUE, szDefExt, FileGe,
                           OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
    if(FileDialog.DoModal() == IDOK) {
      FileGe = FileDialog.GetPathName();
      m_FilePar = FileGe;
    } else {
		  AfxMessageBox("Germanium file not Found", MB_OK | MB_ICONSTOP);
      PostQuitMessage(-3001);
      return;
    }
    ChebFile.open(FileGe, std::ios::in);
  }
	ChebFile.close();
  strValue = FileGe;
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CGeReaderDlg::~CGeReaderDlg() {

}


void
CGeReaderDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeReaderDlg)
	DDX_Control(pDX, IDC_RANGE, cRange);
	DDX_CBIndex(pDX, IDC_RANGE, m_Range);
	DDX_Text(pDX, IDC_FILEPAR, m_FilePar);
	DDV_MaxChars(pDX, m_FilePar, 128);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeReaderDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CGeReaderDlg)
	ON_BN_CLICKED(IDCHANGE, OnChangeFile)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_RANGE, OnSelchangeRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void
CGeReaderDlg::SetDevice(CGeReader* Device) {
  pGeReader = Device;
}


/////////////////////////////////////////////////////////////////////////////
// CGeReaderDlg message handlers
/////////////////////////////////////////////////////////////////////////////

void
CGeReaderDlg::OnChangeFile() {
  char szFilter[] = "Chebichev Coef. (*.chb)|*.chb|All Files (*.*)|*.*||";
  char szDefExt[] = "chb";
  CFileDialog FileDialog(TRUE, szDefExt, m_FilePar,
                         OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
  if(FileDialog.DoModal() == IDOK) {
    m_FilePar = FileDialog.GetFileTitle()+".chb";
    UpdateData(FALSE);
    CWinApp* pApp = AfxGetApp();
    strSection = "Configuration";
    strStringItem = "GERMANIO";
    strValue = m_FilePar;
    pApp->WriteProfileString(strSection, strStringItem, strValue);
    if(FileOld != m_FilePar) {
      bFileChanged = true;
    } else {
      bFileChanged = true;
    }
    SetModified(bFileChanged || bRangeChanged);		
  }
}


BOOL
CGeReaderDlg::OnInitDialog() {
  
  CDialog::OnInitDialog();
  bRangeChanged = false;
  bFileChanged  = false;
  RangeOld      = m_Range;
  FileOld       = m_FilePar;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


int 
CGeReaderDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void 
CGeReaderDlg::OnSelchangeRange() {
  if(cRange.GetCurSel() == RangeOld) {
    bRangeChanged = false;
  } else {
    bRangeChanged = true;
  }
  SetModified(bFileChanged || bRangeChanged);		
}


BOOL 
CGeReaderDlg::OnApply() {
  if(!(bFileChanged || bRangeChanged)) return true;		
  if(!UpdateData(true)) return FALSE;

  int iArg1 = m_Range;

  CWinApp* pApp = AfxGetApp();
  strSection    = "Configuration";
  if(bRangeChanged) {
    if(!pGeReader->ChangeScale(m_Range+1)) {
      return false;
    }
    strStringItem = "GeReader";
    strValue.Format("%1d", iArg1);
    pApp->WriteProfileString(strSection, strStringItem, strValue);
    bRangeChanged = false;
    RangeOld = m_Range;
  }

  if(bFileChanged) {
    if(!pGeReader->ReadChebCoef(m_FilePar)) {
      return false;
    }
    strStringItem = "GERMANIO";
    strValue = m_FilePar;
    pApp->WriteProfileString(strSection, strStringItem, strValue);
    bFileChanged = false;
    FileOld = m_FilePar;
  }
  SetModified(bFileChanged || bRangeChanged);		
	return CPropertyPage::OnApply();
}

