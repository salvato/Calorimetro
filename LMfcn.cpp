/////////////////////////////////////////////////////////////////////////////
// FUnzioni per il Fit dei dati
/////////////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include <math.h>
#include <float.h>

extern int nprob, nfev, njev;
extern double *germy, *datay;
extern double *germx, *datax;
extern double pw;

void ssqfcn(int m, int n, double *x, double *fvec);

/////////////////////////////////////////////////////////////////////////////
// Le Funzioni da Minimizzare:
//
// se: nprob == 0 Fitta i dati del Germanio Con una Retta
//     nprob == 1 Fitta i dati del Bolometro Con un Singolo Esponenziale
//     nprob == 2 Fitta i dati del Bolometro Con un Singolo Esponenziale
/////////////////////////////////////////////////////////////////////////////

void __cdecl
LMfcn(int *m, int *n, double *x, double *fvec, int *iflag) {
  ssqfcn(*m, *n, x, fvec);
  for(int i=0; i<*m; i++) {
    if(_finite(fvec[i]) == 0) {
      *iflag = -1;
      return;
    }
    if(nprob == 0) {
      fvec[i] = fvec[i] - germy[i];
    } else {
      fvec[i] = (fvec[i] - datay[i])/fabs(datay[i]);
    }
  }
  nfev++;
}

/////////////////////////////////////////////////////////////////////////////
// Fit Senza Derivate
/////////////////////////////////////////////////////////////////////////////
void 
ssqfcn(int m, int n, double *x, double *fvec) {

  double tx, y;
  double espmax, tstart, tend;
  double esp, espa, espb, esp1, esp2;

  espmax = 30.0;

  tstart = x[3];
  tend   = tstart + pw;
  y      = x[2];

/////////////////////////////////////////////////////////////////////////////
// Fit Lineare
//
//   x[0] = Offset
//   x[1] = Coefficiente Angolare
/////////////////////////////////////////////////////////////////////////////
  if(nprob == 0) {
    for(int i=0; i<m; i++) {
      fvec[i] = x[0] + x[1]*germx[i];
    }
    return;
  }

/////////////////////////////////////////////////////////////////////////////
// Fit a Singolo Esponenziale
//
//   x[0] = Variazione resistiva dovuta all'impulso di corrente
//   x[1] = Inverso della Costante di tempo del sistema
//   x[2] = Baseline di Resistenza
//   x[3] = Istante di inizio dell'impulso di corrente
/////////////////////////////////////////////////////////////////////////////
  if(nprob == 1) {
    for(int i=0; i<m; i++) {
      tx = datax[i];
      if(tx <= tstart) {
        fvec[i] = y;
      } else if(tx <=tend) {
        esp = (tstart - tx) / x[1];
        if(fabs(esp) > espmax) esp = _copysign(espmax, esp);
        fvec [i] = y - x[0]*(1.0 - exp(esp));
      } else {
        esp1 = -pw / x[1];
        if(fabs(esp1) > espmax ) esp1 = _copysign(espmax, esp1);
        esp = (tend - tx) / x[1];
        if(fabs(esp) > espmax ) esp = _copysign(espmax, esp);
        fvec[i] = y - x[0]*(1.0 - exp(esp1)) * exp(esp);
      }
    }
    return;
  }

/////////////////////////////////////////////////////////////////////////////
// Fit a Doppio Esponenziale
//
//   x[0]= Prefattore primo esponenziale
//   x[1]= Primo Esponente
//   x[2]= Baseline di Temperatura
//   x[3]= Istante di inizio dell'impulso
//   x[4]= Prefattore secondo esponenziale
//   x[5]= Secondo Esponente
/////////////////////////////////////////////////////////////////////////////
  if(nprob == 2) {
    for(int i=0; i<m; i++) {
      tx = datax[i];
      if(tx <= tstart) {
        fvec[i] = y;
      } else if(tx <= tend) {
        espa = (tstart-tx) / x[1];
        if(fabs(espa) > espmax) {
          espa = _copysign(espmax, espa);
        }
        espb = (tstart-tx) / x[5];
        if(fabs(espb) > espmax) {
          espb = _copysign(espmax, espb);
        }
        fvec[i] = y - x[0]*(1.0-exp(espa)) - x[4]*(1.0-exp(espb));
      } else {
        esp1 = -pw / x[1];
        if(fabs(esp1) > espmax) {
          esp1 = _copysign(espmax, esp1);
        }
        esp2 = -pw / x[5];
        if(fabs(esp2) > espmax) {
          esp2 = _copysign (espmax, esp2);
        }
        espa = (tend-tx) / x[1];
        if(fabs(espa) > espmax) {
          espa = _copysign(espmax, espa);
        }
        espb = (tend-tx) / x[5];
        if(fabs(espb) > espmax) {
          espb = _copysign(espmax, espb);
        }
        fvec[i] = y       - x[0]*(1.0 - exp(esp1))*exp(espa);
        fvec[i] = fvec[i] - x[4]*(1.0 - exp(esp2))*exp(espb);
      }
    }// for(int i=0; i<m; i++)
    return;
  }// (nprob == 2)
}
