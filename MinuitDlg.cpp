/////////////////////////////////////////////////////////////////////////////
// MinuitDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <fstream>
#include "resource.h"
#include "ParInfo.h"
#include "ParDlg.h"
#include "Plot3.h"
#include "MsgWindow.h"
#include "MinuitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMinuitDlg dialog
/////////////////////////////////////////////////////////////////////////////

CMinuitDlg::CMinuitDlg(CWnd* pParent /*=NULL*/, CMsgWindow* pMsg/*=NULL*/)
	: myParent(pParent), pMsgWindow(pMsg), CDialog(CMinuitDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CMinuitDlg)
	Command = _T("");
	Filename = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

  xControl = 0;
  yControl = 0;
  nPar     = 0;

  pPlotA     = NULL;
  pParDlg    = NULL;
  
}


CMinuitDlg::~CMinuitDlg() {
  if(pPlotA != NULL)
    delete pPlotA;
  if(pParDlg != NULL)
    delete pParDlg;
}


void 
CMinuitDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMinuitDlg)
	DDX_Control(pDX, IDC_COMMAND, cCommand);
	DDX_Text(pDX, IDC_COMMAND, Command);
	DDV_MaxChars(pDX, Command, 80);
	DDX_Text(pDX, IDC_FILENAME, Filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMinuitDlg, CDialog)
	//{{AFX_MSG_MAP(CMinuitDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_GOCOM, OnGoCom)
	ON_WM_CREATE()
  ON_MESSAGE(MSG_NEWTEXT,   OnNewText)
  ON_MESSAGE(MSG_FIXUNFIX,  OnFixUnfix)
  ON_MESSAGE(MSG_PARUPDATE, OnParUpdate)
	ON_BN_CLICKED(IDC_DONE, OnDone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void 
CMinuitDlg::GetUpdatedPar() {
  int ivarbl;
  char name[33];
  name[32] = 0;
  double val, err, min, max;
  for(int i=0; i<nPar; i++) {
    _strnset(name, ' ', sizeof(name)-1);
    MNPOUT(i+1, name, sizeof(name)-1, &val, &err, &min, &max, &ivarbl);
    pParDlg->UpdatePar(CParInfo(i+1, name, val, err, min, max, ivarbl==0));
  }
}


void 
CMinuitDlg::SendUpdatedPar() {
  CParInfo ParInfo;
  for(int i=0; i<nPar; i++) {
    ParInfo = pParDlg->GetParInfo(i+3);
    line = "SET LIM";
    narg = 3;
    arglis[0] = ParInfo.Num;
    arglis[1] = ParInfo.Min;
    arglis[2] = ParInfo.Max;
    MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
    line = "SET PAR";
    narg = 2;
    arglis[0] = ParInfo.Num;
    arglis[1] = ParInfo.Val;
    MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  }
}


/////////////////////////////////////////////////////////////////////////////////
// Fit a Singolo Esponenziale                                                  //
//                                                                             //
//   par[0] = Variazione della Temperatura Dovuta all'Impulso di Corrente      //
//   par[1] = Inverso della Costante di Tempo del Sistema                      //
//   par[2] = Baseline di Temperatura                                          //
//   par[3] = Istante di Inizio dell'Impulso di Corrente                       //
//   par[4] = Pendenza Fondo Lineare                                           //
//   par[5] = Temperatura Minima  da Cosiderare nel Fit -- Fissata dall'Utente //
//   par[6] = Temperatura Massima da Cosiderare nel Fit -- Fissata dall'Utente //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

bool
CMinuitDlg::SetPars(double *Pars, int iPars) {
  int i;
  nPar = iPars;

  pParDlg->ShowWindow(SW_HIDE);
  pParDlg->EnableWindow(false);

  MNINIT(5, 6, 7, MSG_NEWTEXT, this);
  line = "SET PRI";
  narg = 1;
  arglis[0] = -1;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "SET NOW";
  narg = 0;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);

  char Name[20];
  double val, err, min, max;
  int iPar;

  iPar = 1;
  strcpy(Name, "Delta_T");
  val = Pars[iPar-1];
  err = fabs(val * 0.1);
  min = 0.0;
  max = 100.0*val;

  MNPARM(&iPar, Name, int(strlen(Name)), &val, &err, &min, &max, &iErr);
  if(iErr != 0) {
    AfxMessageBox("Errore nella definizione del parametro 1");
    return false;
  }

  iPar = 2;
  strcpy(Name, "Tau");
  val = Pars[iPar-1];
  err = fabs(val * 0.1);
  min = 0.0;
  max = 10.0*fabs(val);

  MNPARM(&iPar, Name, int(strlen(Name)), &val, &err, &min, &max, &iErr);
  if(iErr != 0) {
    AfxMessageBox("Errore nella definizione del parametro 2");
    return false;
  }

  iPar = 3;
  strcpy(Name, "T_Base");
  val = Pars[iPar-1];
  if(val == 0.0) {
    err = 0.01;
    min =-1.0;
    max = 1;
  } else {
    err = fabs(val * 0.1);
    min = __min(-10.0*val, 10.0*val);
    max = __max(-10.0*val, 10.0*val);
  }

  MNPARM(&iPar, Name, int(strlen(Name)), &val, &err, &min, &max, &iErr);
  if(iErr != 0) {
    AfxMessageBox("Errore nella definizione del parametro 3");
    return false;
  }

  iPar = 4;
  strcpy(Name, "Pulse_ST");
  val = Pars[iPar-1];
  err = fabs(val * 1.0e-2);
  min = val*0.5;
  max = 2.0*val;

  MNPARM(&iPar, Name, int(strlen(Name)), &val, &err, &min, &max, &iErr);
  if(iErr != 0) {
    AfxMessageBox("Errore nella definizione del parametro 4");
    return false;
  }

  iPar = 5;
  strcpy(Name, "Slope");
  val = Pars[iPar-1];
  err = 0.0001;
  min =-0.1;
  max = 0.1;

  MNPARM(&iPar, Name, int(strlen(Name)), &val, &err, &min, &max, &iErr);
  if(iErr != 0) {
    AfxMessageBox("Errore nella definizione del parametro 5");
    return false;
  }

  iPar = 6;
  strcpy(Name, "From");
  val = Pars[iPar-1];
  err = 0.0;
  min = 0.0;
  max = 0.0;

  MNPARM(&iPar, Name, int(strlen(Name)), &val, &err, &min, &max, &iErr);
  if(iErr != 0) {
    AfxMessageBox("Errore nella definizione del parametro 6");
    return false;
  }

  iPar = 7;
  strcpy(Name, "To");
  val = Pars[iPar-1];
  err = 0.0;
  min = 0.0;
  max = 0.0;

  MNPARM(&iPar, Name, int(strlen(Name)), &val, &err, &min, &max, &iErr);
  if(iErr != 0) {
    AfxMessageBox("Errore nella definizione del parametro 7");
    return false;
  }

  char buf[25];
  int ivarbl;
  for(i=1; i<=nPar; i++) {  
    _strnset(buf, ' ', sizeof(buf));
    MNPOUT(i, buf, sizeof(buf)-1, &val, &err, &min, &max, &ivarbl);
    buf[24] = 0;
    line = buf;
    line.TrimRight();
    pParDlg->AddPar(CParInfo(i, line, val, err, min, max, (err==0.0)));
  }

  pParDlg->UpdateWindow();
  pParDlg->ShowWindow(SW_SHOW);
  pParDlg->EnableWindow(false);

  line = "CALL FCN";
  narg = 1;
  arglis[0] = 1;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "FIX";
  narg = 1;
  arglis[0] = 5;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "MINI";
  narg = 0;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "REL";
  narg = 1;
  arglis[0] = 5;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "MINI";
  narg = 0;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "SET STR 2";
  narg = 0;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "MINI 5000 1.D-10";
  narg = 0;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "MINI 10000 1.D-11";
  narg = 0;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "CALL FCN";
  narg = 1;
  arglis[0] = 3;
  MNEXCM(fcn, line, int(strlen(line)), arglis, &narg, &iErr, NULL);
  GetUpdatedPar();

  pParDlg->EnableWindow(true);
  cCommand.EnableWindow(true);

  return true;
}


/////////////////////////////////////////////////////////////////////////////
// CMinuitDlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL 
CMinuitDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
  CRect Rect;
  GetWindowRect(&Rect);
  Rect.SetRect(xControl, yControl, xControl+Rect.Width(), yControl+Rect.Height());
  MoveWindow(&Rect, true);

  if(pParDlg == NULL) {
    pParDlg = new CParDlg(this);
    if(pParDlg->Create(IDD_PARDLG, this) == 0) {
      AfxMessageBox("Impossibile Creare la Finestra dei Parametri");
      PostQuitMessage(-313);
    }
    pParDlg->ShowWindow(SW_SHOW);
  }
  pParDlg->ClearAll();
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void 
CMinuitDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	CDialog::OnSysCommand(nID, lParam);
}


void 
CMinuitDlg::OnPaint() {
	if (IsIconic())	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
  } else {
		CDialog::OnPaint();
	}
}


HCURSOR 
CMinuitDlg::OnQueryDragIcon() {
	return (HCURSOR) m_hIcon;
}


void 
CMinuitDlg::OnGoCom() {
  pParDlg->EnableWindow(false);
  UpdateData(true);
  Command.MakeUpper();
  if(Command.Find("EXI") != -1) {
    Command ="";
    UpdateData(false);
    pParDlg->EnableWindow(true);
    return;
  }
  if(Command.Find("STO") != -1) {
    Command ="";
    UpdateData(false);
    pParDlg->EnableWindow(true);
    return;
  }
  if(Command.Find("CLE") != -1) {
    Command ="";
    UpdateData(false);
    pParDlg->EnableWindow(true);
    return;
  }
  int ires = cCommand.AddString(Command);
  if(ires == CB_ERR || ires == CB_ERRSPACE) {
    cCommand.Clear();
    cCommand.AddString(Command);
  }
  CWaitCursor wait;   // display wait cursor
  line = Command;
  MNCOMD (fcn, line, int(strlen(line)), &iErr, NULL);
  if(iErr == 11) {
    PostQuitMessage(0);
    return;
  }
  line = "CALL FCN";
  narg = 1;
  arglis[0] = 3;
  MNEXCM(fcn, line, int(strlen(line)), arglis, &narg, &iErr, NULL);
  GetUpdatedPar();

  Command ="";
  UpdateData(false);
  pParDlg->EnableWindow(true);
}


BOOL 
CMinuitDlg::OnCommand(WPARAM wParam, LPARAM lParam) { 
  if(wParam == 1 && lParam == 0) {
    UpdateData(true);
    return TRUE;
  }

  if(wParam == 2 && lParam == 0) {
    if(AfxMessageBox("Terminate Fit:\nAre you Sure?", 
                     MB_APPLMODAL|MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)== IDYES) {
      myParent->PostMessage(FIT_DONE, 0, 0);
      CString strValue;
      CString strSection;
      CString strStringItem;
      CWinApp* pApp = AfxGetApp();
      GetWindowText(strStringItem);
      if(!IsIconic()) {
        strSection = "Dialog";
        GetWindowText(strStringItem);
        CRect Rect;
        GetWindowRect(&Rect);
        strValue.Format("%d,%d", Rect.left, Rect.top);  
        pApp->WriteProfileString(strSection, strStringItem, strValue);
      }
      return CDialog::OnCommand(wParam, lParam);
    }
    return TRUE;
  }
  return CDialog::OnCommand(wParam, lParam);
}


int 
CMinuitDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Dialog";
  strStringItem = lpCreateStruct->lpszName;
  strValue = AfxGetApp()->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    xControl = atoi(strtok(buf, ","));
    yControl = atoi(strtok(0, "\0"));
    delete[] buf;
  }

  szFilter = "Command File. (*.cmd)|*.cmd|All Files (*.*)|*.*||";
  szDefExt = "cmd";

  strStringItem = "Directories";
  strSection = "Commands";
  strValue = AfxGetApp()->GetProfileString(strSection, strStringItem);

  pPlotA = new CPlotWindow("Fitting");
  pPlotA->SetLimits(0.0, 0.1, 0.0, 1.0, true, true, false, false);
  pPlotA->UpdatePlot();

  return 0;
}


LRESULT
CMinuitDlg::OnNewText(WPARAM wParam, LPARAM lParam) {
  if(pMsgWindow != NULL) {
    CString sString; 
    sString = (char *)lParam;
    sString.TrimRight(" ");
    pMsgWindow->AddText(sString);
  }
  return LRESULT(0);
}


LRESULT
CMinuitDlg::OnFixUnfix(WPARAM wParam, LPARAM lParam) {
  if(lParam != 0) {
    line = "FIX";
  } else {
    line = "REL";
  }
  narg = 1;
  arglis[0] = int(wParam);
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  return LRESULT(0);
}


LRESULT 
CMinuitDlg::OnParUpdate(WPARAM wParam, LPARAM lParam) {
  int i = int(wParam);
  CParInfo ParInfo = pParDlg->GetParInfo(i);
  line = "SET LIM";
  narg = 3;
  arglis[0] = ParInfo.Num;
  arglis[1] = ParInfo.Min;
  arglis[2] = ParInfo.Max;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "SET PAR";
  narg = 2;
  arglis[0] = ParInfo.Num;
  arglis[1] = ParInfo.Val;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  line = "CALL FCN";
  narg = 1;
  arglis[0] = 3;
  MNEXCM(fcn, LPCTSTR(line), line.GetLength(), arglis, &narg, &iErr, NULL);
  GetUpdatedPar();
  return LRESULT(0);
}


void
CMinuitDlg::GetPars(double *par, int nPar) {
  char buf[25];
  double val, err, min, max;
  int ivarbl;
  for(int i=1; i<=nPar; i++) {  
    _strnset(buf, ' ', sizeof(buf));
    MNPOUT(i, buf, sizeof(buf)-1, &val, &err, &min, &max, &ivarbl);
    par[i-1] = val;
  }
}


void
CMinuitDlg::OnDone() {
  CString strValue;
  CString strSection;
  CString strStringItem;
  CWinApp* pApp = AfxGetApp();
  GetWindowText(strStringItem);
  if(!IsIconic()) {
    strSection = "Dialog";
    GetWindowText(strStringItem);
    CRect Rect;
    GetWindowRect(&Rect);
    strValue.Format("%d,%d", Rect.left, Rect.top);  
    pApp->WriteProfileString(strSection, strStringItem, strValue);
  }
  myParent->PostMessage(FIT_DONE, IDOK, 0);
}

void
CMinuitDlg::SetFilename(CString File) {
  Filename = File;
  UpdateData(false);
}


void
CMinuitDlg::OnCancel() {
  CString strValue;
  CString strSection;
  CString strStringItem;
  CWinApp* pApp = AfxGetApp();
  GetWindowText(strStringItem);
  if(!IsIconic()) {
    strSection = "Dialog";
    GetWindowText(strStringItem);
    CRect Rect;
    GetWindowRect(&Rect);
    strValue.Format("%d,%d", Rect.left, Rect.top);  
    pApp->WriteProfileString(strSection, strStringItem, strValue);
  }
  myParent->PostMessage(FIT_DONE, IDCANCEL, 0);
}
