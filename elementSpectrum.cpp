#include "elementSpectrum.h"

elementSpectrum::elementSpectrum(const std::string& path): dataFile(path)
{
  histo = new TH1F(fPath.c_str(), fPath.c_str(), 1101, 0.0000E+00, 1.1E+01);
//   std::cout << "filling: " << fPath.c_str() << std::endl;
  for(auto event: fData)
  {
//     std::cout << "filling: " << event.first << " " << event.second << std::endl;
    histo->Fill(event.first, event.second);
  }  
}

elementSpectrum::elementSpectrum(const elementSpectrum& copy): dataFile(copy.fPath)
{
  this->fData = copy.fData;
  histo = new TH1F(fPath.c_str(), fPath.c_str(), 1101, 0.0000E+00, 1.1E+01);
//   std::cout << "filling: " << fPath.c_str() << std::endl;
  for(auto event: fData)
  {
//     std::cout << "filling: " << event.first << " " << event.second << std::endl;
    histo->Fill(event.first, event.second);
  }
}


void elementSpectrum::plot(const std::string& output)
{
  
  TCanvas* c= new TCanvas();
//   histo->Scale( 1.0/histo->Integral() );
  histo->Draw();
  c->SetLogy();
  c->SaveAs(output.c_str());
  delete histo;
  delete c;
  
}

elementSpectrum::~elementSpectrum()
{
  
}

TH1F* elementSpectrum::getHisto()
{
  return histo;
}
