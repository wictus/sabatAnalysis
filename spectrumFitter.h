#ifndef SPECTRUM_FITTER
#define SPECTRUM_FITTER

#include "elementSpectrum.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

enum typeOfFit{ chi2, WL };

class spectrumFitter
{
public:
  spectrumFitter(const elementSpectrum& primarySpectrum);
  void fit(std::string out);
  void addNextSpectrum(const elementSpectrum& simSpectrum);
  void setRangeOfFit(const double start, const double stop);
  void fitType(typeOfFit type);
  ~spectrumFitter();
private:
  TLegend buildLegend();
  elementSpectrum fPrimarySpectrum;
  std::vector<elementSpectrum> fSpectraToFit;
  float fStart = 0.0000E+00, fStop = 1.1E+01;
  double fStartOfRange = 0;
  double fEndOfRange = 11;
  int fBins = 1101;
  TF1* fFnc;
  typeOfFit fTypeOfFit = chi2;
};

#endif // SPECTRUM_FITTER