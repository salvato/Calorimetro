/////////////////////////////////////////////////////////////////////////////
// PlotsDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Plot3.h"
#include "resource.h"
#include "PlotsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlotsDlg property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CPlotsDlg, CPropertyPage)

CPlotsDlg::CPlotsDlg() : CPropertyPage(CPlotsDlg::IDD) {

  nPlots   = 0;
  axLimits = NULL;
  pPlot    = NULL;
	//{{AFX_DATA_INIT(CPlotsDlg)
  m_Xmin = _T("0.0");
  m_Xmax = _T("1.0");
  m_Ymax = _T("1.0");
  m_Ymin = _T("0.0");
  m_AutorangeX = TRUE;
  m_AutorangeY = TRUE;
	m_LogX   = FALSE;
	m_LogY   = FALSE;
	m_Active = FALSE;
	//}}AFX_DATA_INIT
}


CPlotsDlg::~CPlotsDlg() {
  CString strStringItem;
  CString strValue;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  for(int i=0; i<nPlots; i++) {
    strStringItem = "Plot: " + axLimits[i].name;
    strValue.Format("%g,%g,%g,%g,%c,%c,%c,%c,%c", 
                    axLimits[i].xmin,
                    axLimits[i].xmax,
                    axLimits[i].ymin,
                    axLimits[i].ymax,
                    axLimits[i].autorangeX ? '1': '0',
                    axLimits[i].autorangeY ? '1': '0',
                    axLimits[i].logX ? '1': '0',
                    axLimits[i].logY ? '1': '0',
                    axLimits[i].active ? '1': '0'
                  );
    pApp->WriteProfileString(strSection, strStringItem, strValue);
  }
  if(axLimits != NULL) delete[] axLimits;
}


void 
CPlotsDlg::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlotsDlg)
	DDX_Control(pDX, IDC_LOGY, m_ckLogY);
	DDX_Control(pDX, IDC_LOGX, m_ckLogX);
	DDX_Control(pDX, IDC_AUTORANGEX, m_ckAutoX);
	DDX_Control(pDX, IDC_AUTORANGEY, m_ckAutoY);
	DDX_Control(pDX, IDC_YMIN, m_edYmin);
	DDX_Control(pDX, IDC_YMAX, m_edYmax);
	DDX_Control(pDX, IDC_XMIN, m_edXmin);
	DDX_Control(pDX, IDC_XMAX, m_edXmax);
	DDX_Control(pDX, IDC_PLOTS, m_Plots);
	DDX_Text(pDX, IDC_XMIN, m_Xmin);
	DDX_Text(pDX, IDC_XMAX, m_Xmax);
	DDX_Text(pDX, IDC_YMAX, m_Ymax);
	DDX_Text(pDX, IDC_YMIN, m_Ymin);
	DDX_Check(pDX, IDC_AUTORANGEX, m_AutorangeX);
	DDX_Check(pDX, IDC_AUTORANGEY, m_AutorangeY);
	DDX_Check(pDX, IDC_LOGX, m_LogX);
	DDX_Check(pDX, IDC_LOGY, m_LogY);
	DDX_Check(pDX, IDC_PLOTACTIVE, m_Active);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlotsDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CPlotsDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_PLOTS, OnSelchangePlots)
	ON_BN_CLICKED(IDC_AUTORANGEX, OnAutorangeX)
	ON_BN_CLICKED(IDC_AUTORANGEY, OnAutorangeY)
	ON_BN_CLICKED(IDC_PLOTACTIVE, OnPlotactive)
	ON_BN_CLICKED(IDC_LOGX, OnLogx)
	ON_BN_CLICKED(IDC_LOGY, OnLogy)
	ON_EN_CHANGE(IDC_XMIN, OnChangeXmin)
	ON_EN_CHANGE(IDC_YMIN, OnChangeYmin)
	ON_EN_CHANGE(IDC_XMAX, OnChangeXmax)
	ON_EN_CHANGE(IDC_YMAX, OnChangeYmax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlotsDlg message handlers
/////////////////////////////////////////////////////////////////////////////

void 
CPlotsDlg::OnSelchangePlots(NMHDR* pNMHDR, LRESULT* pResult) {

  UpdateData(TRUE);
  double Xmin, Xmax, Ymin, Ymax;
  Xmin = atof(m_Xmin);
  Xmax = atof(m_Xmax);
  Ymin = atof(m_Ymin);
  Ymax = atof(m_Ymax);

  if(Xmin < Xmax && Ymin < Ymax) {

    axLimits[previousSel].xmin       = Xmin;
    axLimits[previousSel].xmax       = Xmax;
    axLimits[previousSel].ymin       = Ymin;
    axLimits[previousSel].ymax       = Ymax;
    axLimits[previousSel].autorangeX = m_AutorangeX;
    axLimits[previousSel].autorangeY = m_AutorangeY;
    axLimits[previousSel].logX       = m_LogX;
    axLimits[previousSel].logY       = m_LogY;
    axLimits[previousSel].active     = m_Active;

    previousSel = m_Plots.GetCurSel();
    char temp[15];
    m_Xmin = _gcvt(axLimits[previousSel].xmin, 9, temp);
    m_Xmax = _gcvt(axLimits[previousSel].xmax, 9, temp);
    m_Ymin = _gcvt(axLimits[previousSel].ymin, 9, temp);
    m_Ymax = _gcvt(axLimits[previousSel].ymax, 9, temp);

    m_AutorangeX = axLimits[previousSel].autorangeX;
    m_AutorangeY = axLimits[previousSel].autorangeY;
    m_LogX       = axLimits[previousSel].logX;
    m_LogY       = axLimits[previousSel].logY;
    m_Active     = axLimits[previousSel].active;

    m_edXmin.EnableWindow(m_Active && !m_AutorangeX);
    m_edXmax.EnableWindow(m_Active && !m_AutorangeX);
    m_edYmin.EnableWindow(m_Active && !m_AutorangeY);
    m_edYmax.EnableWindow(m_Active && !m_AutorangeY);
    m_ckAutoX.EnableWindow(m_Active);
    m_ckAutoY.EnableWindow(m_Active);
    m_ckLogX.EnableWindow(m_Active);
    m_ckLogY.EnableWindow(m_Active);

    UpdateData(FALSE);
  } else {
    AfxMessageBox("Check Axes Limits");
    m_Plots.SetCurSel(previousSel);
    m_edXmin.EnableWindow(m_AutorangeX);
    m_edXmax.EnableWindow(m_AutorangeX);
    m_edYmin.EnableWindow(m_AutorangeY);
    m_edYmax.EnableWindow(m_AutorangeY);
    m_ckAutoX.EnableWindow(TRUE);
    m_ckAutoY.EnableWindow(TRUE);
    m_ckLogX.EnableWindow(TRUE);
    m_ckLogY.EnableWindow(TRUE);
  }
  *pResult = 0;
}


void 
CPlotsDlg::OnAutorangeX() {
  UpdateData(TRUE);
  m_edXmin.EnableWindow(m_Active && !m_AutorangeX);
  m_edXmax.EnableWindow(m_Active && !m_AutorangeX);
  SetModified(TRUE);
}


void 
CPlotsDlg::OnAutorangeY() {
  UpdateData(TRUE);
  m_edYmin.EnableWindow(m_Active && !m_AutorangeY);
  m_edYmax.EnableWindow(m_Active && !m_AutorangeY);
  SetModified(TRUE);
}


BOOL 
CPlotsDlg::OnInitDialog() {
  	
	TC_ITEM TabCtrlItem;
	CDialog::OnInitDialog();
  TabCtrlItem.mask = TCIF_TEXT;

  for(int i=0; i<nPlots; i++) {
    TabCtrlItem.pszText = new char[strlen(axLimits[i].name)+1];
    strcpy(TabCtrlItem.pszText, axLimits[i].name);
    m_Plots.InsertItem(i, &TabCtrlItem);
    delete[] TabCtrlItem.pszText;
  }

  char temp[15];
  m_Xmin = _gcvt(axLimits[0].xmin, 9, temp);
  m_Xmax = _gcvt(axLimits[0].xmax, 9, temp);
  m_Ymin = _gcvt(axLimits[0].ymin, 9, temp);
  m_Ymax = _gcvt(axLimits[0].ymax, 9, temp);

  m_AutorangeX = axLimits[0].autorangeX;
  m_AutorangeY = axLimits[0].autorangeY;
  m_LogX       = axLimits[0].logX;
  m_LogY       = axLimits[0].logY;
  m_Active     = axLimits[0].active;

  m_edXmin.EnableWindow(m_Active && !m_AutorangeX);
  m_edXmax.EnableWindow(m_Active && !m_AutorangeX);
  m_edYmin.EnableWindow(m_Active && !m_AutorangeY);
  m_edYmax.EnableWindow(m_Active && !m_AutorangeY);
  m_ckAutoX.EnableWindow(m_Active);
  m_ckAutoY.EnableWindow(m_Active);
  m_ckLogX.EnableWindow(m_Active);
  m_ckLogY.EnableWindow(m_Active);

  previousSel = 0;
  UpdateData(FALSE);

  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void 
CPlotsDlg::OnPlotactive() {
  UpdateData(TRUE);
  m_edXmin.EnableWindow(m_Active && !m_AutorangeX);
  m_edXmax.EnableWindow(m_Active && !m_AutorangeX);
  m_edYmin.EnableWindow(m_Active && !m_AutorangeY);
  m_edYmax.EnableWindow(m_Active && !m_AutorangeY);
  m_ckAutoX.EnableWindow(m_Active);
  m_ckAutoY.EnableWindow(m_Active);
  m_ckLogX.EnableWindow(m_Active);
  m_ckLogY.EnableWindow(m_Active);
  SetModified(TRUE);
}


void 
CPlotsDlg::OnLogx() {
	SetModified(TRUE);
}


void 
CPlotsDlg::OnLogy() {
  SetModified(TRUE);	
}


void
CPlotsDlg::OnChangeXmin() {
	SetModified(TRUE);
}


void
CPlotsDlg::OnChangeYmin() {
	SetModified(TRUE);
}


void
CPlotsDlg::OnChangeXmax() {
	SetModified(TRUE);
}


void 
CPlotsDlg::OnChangeYmax() {
	SetModified(TRUE);
}


void 
CPlotsDlg::SetPlots(CPlotWindow** pPlots, CDataSetProperties** pProp, int nP) {
  pPlot = pPlots;
  pProperties = pProp;
  if(nPlots != 0) {
    delete[] axLimits;
  }
  nPlots = nP;
  axLimits = new pLimits[nPlots];
  CString strStringItem;
  CString strValue;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  for(int i=0; i<nPlots; i++) {
    strStringItem = "Plot: " + pProperties[i]->Title;
    strValue = pApp->GetProfileString(strSection, strStringItem);
    if(strValue != "") {
      char *buf = new char[strlen(strValue)+1];
      strcpy(buf, strValue);
      axLimits[i].xmin = atof(strtok(buf, ","));
      axLimits[i].xmax = atof(strtok(0, ","));
      axLimits[i].ymin = atof(strtok(0, ","));
      axLimits[i].ymax = atof(strtok(0, ","));
      axLimits[i].autorangeX = (*strtok(0, ",") == '1') ? true : false;
      axLimits[i].autorangeY = (*strtok(0, ",") == '1') ? true : false;
      axLimits[i].logX = (*strtok(0, ",") == '1') ? true : false;
      axLimits[i].logY = (*strtok(0, ",") == '1') ? true : false;
      axLimits[i].active = (*strtok(0, "\0") == '1') ? true : false;
      axLimits[i].name = _T(pProperties[i]->Title);
      if(axLimits[i].active) {
        pPlot[i] = new CPlotWindow(axLimits[i].name);
        pPlot[i]->SetLimits(axLimits[i].xmin,
                            axLimits[i].xmax,
                            axLimits[i].ymin,
                            axLimits[i].ymax,
                            axLimits[i].autorangeX,
                            axLimits[i].autorangeY,
                            axLimits[i].logX,
                            axLimits[i].logY
                           );
        pPlot[i]->NewDataSet(*pProperties[i]);
        pPlot[i]->SetShowDataSet(pProperties[i]->GetId(), true);
        pPlot[i]->UpdatePlot();
      }
      delete[] buf;
    } else {
      axLimits[i].xmin       = 0.0;
      axLimits[i].xmax       = 1.0;
      axLimits[i].ymin       = 0.0;
      axLimits[i].ymax       = 1.0;
      axLimits[i].autorangeX = FALSE;
      axLimits[i].autorangeY = FALSE;
      axLimits[i].logX       = FALSE;
      axLimits[i].logY       = FALSE;
      axLimits[i].active     = FALSE;
      axLimits[i].name = _T(pProperties[i]->Title);
    }
    strValue.Format("%g,%g,%g,%g,%c,%c,%c,%c,%c", 
                    axLimits[i].xmin,
                    axLimits[i].xmax,
                    axLimits[i].ymin,
                    axLimits[i].ymax,
                    axLimits[i].autorangeX ? '1': '0',
                    axLimits[i].autorangeY ? '1': '0',
                    axLimits[i].logX ? '1': '0',
                    axLimits[i].logY ? '1': '0',
                    axLimits[i].active ? '1': '0'
                  );
    pApp->WriteProfileString(strSection, strStringItem, strValue);
  }
}


BOOL 
CPlotsDlg::OnApply() {
  if(!UpdateData(true)) return false;

  axLimits[previousSel].xmin       = atof(m_Xmin);
  axLimits[previousSel].xmax       = atof(m_Xmax);
  axLimits[previousSel].ymin       = atof(m_Ymin);
  axLimits[previousSel].ymax       = atof(m_Ymax);
  axLimits[previousSel].autorangeX = m_AutorangeX;
  axLimits[previousSel].autorangeY = m_AutorangeY;
  axLimits[previousSel].logX       = m_LogX;
  axLimits[previousSel].logY       = m_LogY;
  axLimits[previousSel].active     = m_Active;

  for(int i=0; i<nPlots; i++) {
    if(axLimits[i].active) {
      if(pPlot[i] == NULL) {
        pPlot[i] = new CPlotWindow(axLimits[i].name);
        pPlot[i]->NewDataSet(*pProperties[i]);
        pPlot[i]->SetShowDataSet(0, true);
    
        pPlot[i]->SetLimits(axLimits[i].xmin,
                            axLimits[i].xmax,
                            axLimits[i].ymin,
                            axLimits[i].ymax,
                            axLimits[i].autorangeX,
                            axLimits[i].autorangeY,
                            axLimits[i].logX,
                            axLimits[i].logY
                           );
        pPlot[i]->UpdatePlot();
      }
    } else {
      delete pPlot[i];
      pPlot[i] = NULL;
    }
  }
	return CPropertyPage::OnApply();
}
