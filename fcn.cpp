#include "stdafx.h"
#include <fstream>
#include "math.h"
#include "float.h"
#include "Plot3.h"
#include "Includes/fcn.h"

extern double *xFit;
extern double *yFit;
extern double *yTheo;
extern int    nDati;
extern double pulW;

static int    nCall = 0;

CPlotWindow*  pPlotA;

/////////////////////////////////////////////////////////////////////////////
// La Funzione da minimizzare
/////////////////////////////////////////////////////////////////////////////
void __stdcall
fcn(int* npar, double* g, double* f, double* par, int* iflag, void ( __stdcall* util)(void)) {

/////////////////////////////////////////////////////////////////////////////
// Inizializzazione
/////////////////////////////////////////////////////////////////////////////
  if(*iflag == 1) {
    nCall = 0;
  } //if(*iflag == 1)
/////////////////////////////////////////////////////////////////////////////
// Fine Inizializzazione
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
// Fit a Singolo Esponenziale                                                  //
//                                                                             //
//   par[0] = Variazione della Temperatura Dovuta all'Impulso di Corrente      //
//   par[1] = Costante di Tempo del Sistema                                    //
//   par[2] = Baseline di Temperatura                                          //
//   par[3] = Istante di Inizio dell'Impulso di Corrente                       //
//   par[4] = Pendenza Fondo Lineare                                           //
//   par[5] = Temperatura Minima  da Cosiderare nel Fit -- Fissata dall'Utente //
//   par[6] = Temperatura Massima da Cosiderare nel Fit -- Fissata dall'Utente //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
  double esp, esp1;

  double tStart = par[3];       // Il Timer che fa partire l'impulso NON e' preciso
  double tEnd   = tStart + pulW;// Quello che determina la durata dell'impulso.....
                                // E' MOLTO preciso !
  double y0     = par[2];
  double TMin   = par[5];
  double TMax   = par[6];

  double tx, espmax=30.0;

  *f = 0.0;
  for(int i=0; i<nDati; i++) {
    tx = xFit[i];
    if(tx <= tStart) {
      yTheo[i] = y0;
    } else if(tx <= tEnd) {
      esp = (tStart - tx) / par[1];
      if(fabs(esp) > espmax) esp = _copysign(espmax, esp);
      yTheo[i] = y0 + par[0]*(1.0 - exp(esp));
    } else {
      esp1 = -pulW / par[1];
      if(fabs(esp1) > espmax ) esp1 = _copysign(espmax, esp1);
      esp = (tEnd - tx) / par[1];
      if(fabs(esp) > espmax ) esp = _copysign(espmax, esp);
      yTheo[i] = y0 + par[0]*(1.0 - exp(esp1)) * exp(esp);
    }
    yTheo[i] += par[4] * (tx-xFit[0]);
    if((tx >= TMin) && (tx <= TMax)) {
      *f += pow((yTheo[i]-yFit[i])/fabs(yFit[i]), 2);
    }
  }

  if(!div(nCall,100).rem || *iflag == 3) {
    if(pPlotA != NULL) {
      pPlotA->DelDataSet(1);
      pPlotA->DelDataSet(2);
      pPlotA->DelDataSet(3);
      pPlotA->NewDataSet(1, 1, RGB(255,255,255), CPlotWindow::iline, "Risposta Teorica");
      pPlotA->NewDataSet(2, 1, RGB(255,255,  0), CPlotWindow::ipoint, "Dati Sperimentali");
      pPlotA->NewDataSet(3, 1, RGB(  0,  0,255), CPlotWindow::ipoint, "Dati Non Fittati");
      for(int i=0; i<nDati; i++) {
        tx = xFit[i];
        pPlotA->NewPoint(2, tx, yFit[i]);
        if((tx >= TMin) && (tx <= TMax)) {
          pPlotA->NewPoint(1, tx, yTheo[i]);
        } else {
          pPlotA->NewPoint(3, tx, yTheo[i]);
        }
      }
      pPlotA->SetShowDataSet(1, true);
      pPlotA->SetShowDataSet(2, true);
      pPlotA->SetShowDataSet(3, true);
      pPlotA->UpdatePlot();
    }
  }

  nCall++;
}

