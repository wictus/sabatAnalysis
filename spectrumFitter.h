#ifndef SPECTRUM_FITTER
#define SPECTRUM_FITTER

#include "elementSpectrum.h"
#include "TF1.h"

class spectrumFitter
{
public:
  spectrumFitter(const elementSpectrum& firstSpectrum, const elementSpectrum& secondSpectrum);
  void fit(std::string out);
  void addNextSpectrum(const elementSpectrum& spectrum);
  
private:
  elementSpectrum fFirstSpectrum, fSecondSpectrum;
  std::vector<elementSpectrum> fSpectraToFit;
  TF1* fFnc;
};

#endif // SPECTRUM_FITTER