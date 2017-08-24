#include "spectrumFitter.h"

TH1F* globalHisto;

Double_t simulateFunction(Double_t* x, Double_t* par)
{
  Double_t xx = x[0];
  Int_t bin = globalHisto->GetXaxis()->FindBin(xx);
  Double_t br = par[0]*globalHisto->GetBinContent(bin);
  return br;
}



spectrumFitter::spectrumFitter(const elementSpectrum& firstSpectrum, const elementSpectrum& secondSpectrum)
:fFirstSpectrum(firstSpectrum), fSecondSpectrum(secondSpectrum)
{
  
}

void spectrumFitter::fit(std::string out)
{
  globalHisto = fFirstSpectrum.getHisto();
  fFnc = new TF1("fFnc", simulateFunction, 0, 11, 1);
  fFnc->SetParameters(0, globalHisto->GetMaximum() );
  fFnc->SetParLimits(0,0, 10000);
  fFnc->SetNumberFitPoints(100000);
  
  TCanvas* c = new TCanvas();
  fSecondSpectrum.getHisto()->Draw();
  fSecondSpectrum.getHisto()->Fit("fFnc", "M");
  std::cout << "Chi square: " << fFnc->GetChisquare() << std::endl;
  c->SetLogy(1);
  TString outName = out;
  outName+=".png";
  c->SaveAs(outName);
  delete globalHisto;
}


