#include "spectrumFitter.h"

std::vector<TH1F*> globalHisto;

Double_t simulateFunction(Double_t* x, Double_t par[])
{
  Double_t xx = x[0];
  Int_t bin = globalHisto[0]->GetXaxis()->FindBin(xx);
  double br = 0;
  for( unsigned int i = 0; i < globalHisto.size(); i++)
  {
    br+= par[i]*globalHisto[i]->GetBinContent(bin);
  }
  return br;
}


spectrumFitter::spectrumFitter(const elementSpectrum& firstSpectrum, const elementSpectrum& secondSpectrum)
:fFirstSpectrum(firstSpectrum), fSecondSpectrum(secondSpectrum)
{
    fSpectraToFit.push_back(secondSpectrum);
}

void spectrumFitter::addNextSpectrum(const elementSpectrum& spectrum)
{
  fSpectraToFit.push_back(spectrum);
}


void spectrumFitter::fit(std::string out)
{
  for( unsigned int i = 0; i < fSpectraToFit.size(); i++)
    globalHisto.push_back( &fSpectraToFit[i].getHisto() );
  
  fFnc = new TF1("fFnc", simulateFunction, 0, 11, fSpectraToFit.size());
  for( unsigned int i = 0; i < fSpectraToFit.size(); i++)
  {
    fFnc->SetParameter(i, 1);
    fFnc->SetParLimits(i,0, 10 );
  }
 
  fFnc->SetNumberFitPoints(100000);
  
  TCanvas* c = new TCanvas();
  fFirstSpectrum.getHisto().Draw();
  fFirstSpectrum.getHisto().Fit("fFnc", "0EWM");
  
  for( unsigned int i = 0; i < fSpectraToFit.size(); i++)
  {
    fSpectraToFit[i].getHisto().Scale( fFnc->GetParameter(i));
    fSpectraToFit[i].getHisto().SetLineColor(2+i);
    fSpectraToFit[i].getHisto().Draw("same");
  }
  
  c->BuildLegend();
  c->SetLogy();
  std::cout << "Chi square: " << fFnc->GetChisquare() << std::endl;

  TString outName = out;
  outName+=".png";
  c->SaveAs(outName);
  delete c;
}


spectrumFitter::~spectrumFitter()
{

  for(unsigned int i = 0; i < globalHisto.size(); i++)
  {
    globalHisto.pop_back();
  } 
  
  delete fFnc;  
}
