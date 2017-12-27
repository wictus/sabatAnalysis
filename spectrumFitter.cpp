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


spectrumFitter::spectrumFitter(const elementSpectrum& primarySpectrum)
:fPrimarySpectrum(primarySpectrum)
{
  gStyle->SetOptFit(1111);
}

void spectrumFitter::addNextSpectrum(const elementSpectrum& simSpectrum)
{
  fSpectraToFit.push_back(simSpectrum);
}


void spectrumFitter::fit(std::string out)
{
  for( unsigned int i = 0; i < fSpectraToFit.size(); i++)
    globalHisto.push_back( &fSpectraToFit[i].getHisto() );
  
  fFnc = new TF1("fFnc", simulateFunction, fStartOfRange, fEndOfRange, fSpectraToFit.size());
  for( unsigned int i = 0; i < fSpectraToFit.size(); i++)
  {
    fFnc->SetParameter(i, 0);
    std::string name = fSpectraToFit[i].getPath();
    int length = name.find_last_of("/") - (name.substr(0, name.find_last_of("/"))).find_last_of("/");
    name= name.substr( (name.substr(0, name.find_last_of("/"))).find_last_of("/")+1 , length-1);
    fFnc->SetParName(i,name.c_str());
    fFnc->SetParLimits(i,0, 20 );
  }
 
  fFnc->SetNumberFitPoints(100000);
  
  TH1F* finalHisto = new TH1F("final", "final", fBins, fStart, fStop);
  TCanvas* c = new TCanvas();
  fPrimarySpectrum.getHisto().Draw("hist");
  fPrimarySpectrum.getHisto().Fit("fFnc", "0EMR");
  std::cout << "Chi square: " << fFnc->GetChisquare()/fFnc->GetNDF() << std::endl;
    
  for( unsigned int i = 0; i < fSpectraToFit.size(); i++)
  {
    fSpectraToFit[i].getHisto().Scale( fFnc->GetParameter(i));
    fSpectraToFit[i].getHisto().SetLineColor(2+i);
    fSpectraToFit[i].getHisto().Draw("histsame");
    finalHisto->Add( &fSpectraToFit[i].getHisto());
  }
   
  TLegend legend = buildLegend();
  legend.Draw();
  c->SetLogy();

  TString outName = out;
  outName+=".png";
  c->SaveAs(outName);
  finalHisto->SetLineColor(1);
  finalHisto->SetLineWidth(2);
  finalHisto->Draw("hist");
  finalHisto->SetMinimum(1e-8);
  fPrimarySpectrum.getHisto().Draw("histsame");
  c->SaveAs("test.png");
  
  fPrimarySpectrum.getHisto().Add(finalHisto, -1);
  fPrimarySpectrum.getHisto().Draw("hist");
  fPrimarySpectrum.getHisto().SetTitle("Experimental - fit");
  c->SaveAs("difference.png");
  
  delete c;
  delete finalHisto;
}

TLegend spectrumFitter::buildLegend()
{
  TLegend leg(0.1,0.65,0.38,0.85);
  leg.AddEntry(&fPrimarySpectrum.getHisto(), "Experimental spectrum", "l");
  for(unsigned int i = 0; i < fSpectraToFit.size(); i++)
  {
    std::string name = fSpectraToFit[i].getPath();
    int length = name.find_last_of("/") - (name.substr(0, name.find_last_of("/"))).find_last_of("/");
    name= name.substr( (name.substr(0, name.find_last_of("/"))).find_last_of("/")+1 , length-1);    
    leg.AddEntry(&fSpectraToFit[i].getHisto(), name.c_str(), "l");
  }
  return leg;
}


spectrumFitter::~spectrumFitter()
{

  for(unsigned int i = 0; i < globalHisto.size(); i++)
  {
    globalHisto.pop_back();
  } 
  
  delete fFnc;  
}

void spectrumFitter::setRangeOfFit(const double start, const double stop)
{
  fStartOfRange = start;
  fEndOfRange = stop;
}
