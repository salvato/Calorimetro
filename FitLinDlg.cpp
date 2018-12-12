/////////////////////////////////////////////////////////////////////////////
// FitLinDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Includes/LMheader.h"
#include "Includes/LMfcn.h"
#include "resource.h"
#include "DoFitDlg.h"
#include "FitLinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern double *datax;
extern double *datay;
extern double *germx;
extern double *germy;
extern double pw;
extern int    nprob;
extern int    njev;
extern int    nfev;


/////////////////////////////////////////////////////////////////////////////
// CFitLinDlg dialog
/////////////////////////////////////////////////////////////////////////////


CFitLinDlg::CFitLinDlg(CDoFitDlg* pParent /*=NULL*/)
	: CDialog(CFitLinDlg::IDD, (CDialog*)pParent) {
	//{{AFX_DATA_INIT(CFitLinDlg)
	m_a = 0.0;
	m_b = 0.0;
	m_Chi2 = 0.0;
	//}}AFX_DATA_INIT
  myParent = pParent;
  fitDone = false;
}


void CFitLinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFitLinDlg)
	DDX_Control(pDX, IDOK, m_b_ok);
	DDX_Control(pDX, IDC_B, m_e_b);
	DDX_Control(pDX, IDC_A, m_e_a);
	DDX_Control(pDX, IDC_CHI2, m_eChi2);
	DDX_Control(pDX, IDC_OVERFLOW, m_bOverflow);
	DDX_Control(pDX, IDC_CONVERGED, m_bConverged);
	DDX_Text(pDX, IDC_A, m_a);
	DDX_Text(pDX, IDC_B, m_b);
	DDX_Text(pDX, IDC_CHI2, m_Chi2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFitLinDlg, CDialog)
	//{{AFX_MSG_MAP(CFitLinDlg)
	ON_BN_CLICKED(IDOK, OnDoFitClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFitLinDlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL CFitLinDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CFitLinDlg::OnDoFitClicked() {
  UpdateData(TRUE);
  m_b_ok.EnableWindow(FALSE);
  m_e_b.EnableWindow(FALSE);
  m_e_a.EnableWindow(FALSE);
  FitData();
  UpdateData(FALSE);
  m_b_ok.EnableWindow(TRUE);
  m_e_b.EnableWindow(TRUE);
  m_e_a.EnableWindow(TRUE);
}


BOOL
CFitLinDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
  if(wParam == 2 && lParam == 0)
    return TRUE;
	return CDialog::OnCommand(wParam, lParam);
}


BOOL
CFitLinDlg::DestroyWindow() {
  UpdateData(TRUE);
  return CDialog::DestroyWindow();
}


BOOL
CFitLinDlg::Create(UINT nID, CDoFitDlg* pParent) {
  myParent = pParent;	
	return CDialog::Create(IDD, pParent);
}


void
CFitLinDlg::FitData() {
  int info, n, m;
  double tol = 1.0e-6;
  double* par;

  fitDone = false;
  myParent->m_b_OK.EnableWindow(FALSE);
  n = 2;
  par = new double[n];
  par[0] = m_b;
  par[1] = m_a;
  nprob = 0;
  
  m      = myParent->m_Ger; 

  double* fvec = new double[m];

  lm_dif(LMfcn, m, n, par, fvec, tol, &info);
  
  m_b = par[0];
  m_a = par[1];
  if(info < 0 || (info/16) !=0) {
    m_eChi2.EnableWindow(FALSE);
    m_bOverflow.EnableWindow(TRUE);
    m_bOverflow.SetCheck(1);
    m_bConverged.EnableWindow(FALSE);
    m_bConverged.SetCheck(0);
  } else {
    m_bOverflow.EnableWindow(FALSE);
    m_bOverflow.SetCheck(0);
    info &= 0xF;
    m_eChi2.EnableWindow(TRUE);
    m_Chi2 = eunorm(m, fvec);
    if(info>0 && info<5) {
      m_bConverged.EnableWindow(TRUE);
      m_bConverged.SetCheck(1);
      fitDone = true;
      if(myParent->FitExp1Dlg.fitDone || myParent->FitExp2Dlg.fitDone)
        myParent->m_b_OK.EnableWindow(TRUE);
    }
  }

  delete[] par;
  delete[] fvec;
}
