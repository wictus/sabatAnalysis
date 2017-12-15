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
    histo.SetBinError( histo.FindBin(event.first), event.second.second*event.second.first );
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

void elementSpectrum::produceDataFile(const std::string& output)
{

  std::ofstream file;
  file.open(output.c_str());
  
  if(!file.good())
  {
    std::cout << "Error when creating file: " << output << std::endl;
    std::exit(5);
  }
  
  for(unsigned int i = 0; i < fData.size(); i++)
  {
    file << fData[i].first<< " " << fData[i].second.first<< " " << fData[i].second.second<< std::endl;
  }
  file.close();
}

void elementSpectrum::addAnotherSpectrum(const elementSpectrum& spectrum, const double weightForOriginal, const double weightForSecondSpectrum)
{
  for(unsigned int i = 0; i < fData.size(); i++)
  {
      fData[i].second.first*=weightForOriginal;
      fData[i].second.first+=weightForSecondSpectrum*spectrum.getData()[i].second.first;
      fData[i].second.second = sqrt( pow((weightForOriginal*fData[i].second.second),2) + pow(spectrum.getData()[i].second.second *weightForSecondSpectrum,2) );
  }

}
