#ifndef SPECTRUM_FITTER
#define SPECTRUM_FITTER

#include "elementSpectrum.h"
#include "TF1.h"

class spectrumFitter
{
public:
  spectrumFitter(const elementSpectrum& firstSpectrum, const elementSpectrum& secondSpectrum);
  void fit(std::string out);
  
private:
  elementSpectrum fFirstSpectrum, fSecondSpectrum;
  TF1* fFnc;
};

#endif // SPECTRUM_FITTER