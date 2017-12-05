#include "elementSpectrum.h"

elementSpectrum::elementSpectrum(const TH1F& histo)
:histo(histo)
{
  
}


elementSpectrum::elementSpectrum(const std::string& path): dataFile(path)
{
  histo =TH1F(fPath.c_str(), fPath.c_str(), fBins, fStart, fStop);
  for(auto event: fData)
  {
    histo.Fill(event.first, event.second.first);
  }  
}

elementSpectrum::elementSpectrum(const elementSpectrum& copy): dataFile(copy.fPath)
{
  this->fData = copy.fData;
  histo = *(new TH1F(fPath.c_str(), fPath.c_str(), fBins, fStart, fStop));
  for(auto event: fData)
  {
    histo.Fill(event.first, event.second.first);
    histo.SetBinError( histo.FindBin(event.first), event.second.second*event.second.first*10 );
  }
  if( fData.size() == 0)
    this->histo = copy.histo;
}


void elementSpectrum::plot(const std::string& output)
{
  if( histo.GetEntries() == 0 )
  {
    for(auto event: fData)
    {
      histo.Fill(event.first, event.second.first);
    } 
  }
  TCanvas* c= new TCanvas();
  histo.Draw();
  c->SetLogy();
  c->SaveAs(output.c_str());
  delete c;
  
}

elementSpectrum::~elementSpectrum()
{
  
}

TH1F& elementSpectrum::getHisto()
{
  return histo;
}
