#ifndef ELEMENT_SPECTRUM
#define ELEMENT_SPECTRUM

#include "dataFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TAxis.h"

class elementSpectrum: public dataFile
{
public:
  elementSpectrum(const TH1F& histo);
  elementSpectrum(const std::string& path);
  elementSpectrum(const elementSpectrum& copy);
  ~elementSpectrum();
  void plot(const std::string& output);
  TH1F& getHisto();
protected:
  int fBins = 1101;
  float fStart = 0.0000E+00, fStop = 1.1E+01;
  TH1F histo;
  
};

#endif //ELEMENT_SPECTRUM