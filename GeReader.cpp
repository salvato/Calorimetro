#include "stdafx.h"

#include "ni488.h"
#include <fstream>
#include "math.h"
#include "Readings.h"
#include "GeReader.h"


CGeReader::CGeReader(CWnd* Cal, int Addr)
  :CGpibInstrument(Cal, Addr),	inRun(false) {
	justStarted	= false;
  _ftime(&timebuffer);
  time0 = timebuffer.time + timebuffer.millitm/1000.0;
}


CGeReader::~CGeReader() {
}


bool
CGeReader::ReadChebCoef(CString FileName) {
  char Line[255];
  std::ifstream ChebFile;
  ChebFile.open(FileName, std::ios::in);
  if(ChebFile.fail()) {
    ChebFile.clear();
    return false;
  }
  ChebFile.getline(Line, sizeof(Line)-1);
  strtok(Line, "=");// Zone Totali
  int nZone = atoi(strtok(0, "\0"));

	ChebFile.getline(Line, sizeof(Line)-1);// Copertura totale
  strtok(Line, "=");
  rMin = atof(strtok(0, ":"));
  rMax = atof(strtok(0, "\0"));
  
  for(int i=0; i<nZone; i++) {
    CZone Zone;
  	ChebFile.getline(Line, sizeof(Line)-1);//i-esima zona
    strtok(Line, "=");
    Zone.rMin = atof(strtok(0, ":"));
    Zone.rMax = atof(strtok(0, "\0"));

   	ChebFile.getline(Line, sizeof(Line)-1);//Zl
    strtok(Line, "=");
    Zone.Zl = atof(strtok(0, "\0"));

   	ChebFile.getline(Line, sizeof(Line)-1);//Zu
    strtok(Line, "=");
    Zone.Zu = atof(strtok(0, "\0"));

  	ChebFile.getline(Line, sizeof(Line)-1);//Numero Coefficienti della zona
    strtok(Line, "=");
    int nCoef = atoi(strtok(0, "\0"));

    if(nCoef > MAXCOEF) {
  		AfxMessageBox("Too Many Chebichev Coefficient", MB_OK | MB_ICONSTOP);
	  	PostQuitMessage(1);
    }

    Zone.nCoef = nCoef;
    for(int j=0; j<nCoef; j++) {
    	ChebFile.getline(Line, sizeof(Line)-1);//j-esimo coefficiente
      Zone.A[j] = atof(Line);
    }
    rZone.Add(Zone);
	}
  double a0, a1;
  a0 = rZone[0].A[0];
  a1 = rZone[1].A[0];
	ChebFile.close();
  return true;
}


double
CGeReader::Cnv(double r) {
	double Z, x, T;

	T = 0.0;
	if (r <= rMin || r >= rMax) return -1.0;
  int i, j;
  for(i=0; i<rZone.GetSize(); i++) {
    if(r >= rZone[i].rMin && r <= rZone[i].rMax) {
      break;
    }
  }
	Z = log10(r);
	x=((Z-rZone[i].Zl)-(rZone[i].Zu-Z))/(rZone[i].Zu-rZone[i].Zl);
	for (j=0; j<rZone[i].nCoef; j++)
		T = T + rZone[i].A[j]*cos(double(j)*acos(x));
	return T;
}


bool  
CGeReader::ChangeScale(int iScale) {
  return false;
}


bool
CGeReader::StartRun() {
	return false;
}


bool
CGeReader::StopRun() {
	return false;
}


void 
CGeReader::SendData(char *message) {
  pParent->SendMessage(GE_READER_DATA, WPARAM(strlen(message)), LPARAM(message));
}


void 
CGeReader::SendRunData(char *message) {
  pParent->SendMessage(GE_READER_RUN_DATA, WPARAM(strlen(message)), LPARAM(message));
}


bool
CGeReader::myConfigure(CString sConf) {
  return false;
}


bool
CGeReader::myInit() {
  return false;
}


bool
CGeReader::myDisconnect() {
  return false;
}


bool
CGeReader::myConnect() {
  return false;
}


void
CGeReader::SRQService(long, long, long, long, long FAR*) {
}

