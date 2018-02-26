#include "examples.h"

void exampleOfMultipleFit(const std::string& expFile, const std::vector< std::string >& simFiles)
{
  elementSpectrum exp(expFile);
  exp.readData();
  std::vector<elementSpectrum> sims;
  for(auto file: simFiles)
  {
    elementSpectrum sim(file);
    sim.readData();
    sims.push_back(sim);
  }
  spectrumFitter fit(exp);
  fit.addNextSpectrum(sims[0]);
  if( sims.size() > 1 )
    for(int i = 1; i < sims.size(); i++)
      fit.addNextSpectrum(sims[i]);
  
//   fit.setRangeOfFit(0,4.5);
  fit.fitType(chi2);
  fit.fit("coctail");
}

void checkAdditionForTwoElements()
{
  elementSpectrum first("../data/baseSpectra/Prompt\ -\ submarine\ 10\ cm/Cl35/7.9_1E8_LaBr3_3x3_FWHM_Cl_t_lt_50ns_out__sorted_cell__13_CUT.txt");
  first.readData();
  first.plot("Chlorine35.png");
  elementSpectrum second("../data/baseSpectra/Prompt\ -\ submarine\ 10\ cm/Cl37/7.9_1E8_LaBr3_3x3_FWHM_Cl37_t_lt_50ns_out__sorted_cell__13_CUT.txt");
  second.readData();
  second.plot("Chlorine37.png");
  
  first.addAnotherSpectrum(second,0.76,0.24);
  first.plot("SumOfChlorines.png");
  
  first.produceDataFile("../data/baseSpectra/Prompt\ -\ submarine\ 10\ cm/Cl/joinedClorines.txt");
}

elementSpectrum addTwoElements(elementSpectrum firstElement, elementSpectrum secondElement, double firstElementWeight, double secondElementWeight)
{  
  TH1F firstHisto = firstElement.getHisto();
  TH1F secondHisto= secondElement.getHisto();
    
  firstHisto.Scale(firstElementWeight);
  secondHisto.Scale(secondElementWeight);
  firstHisto.Add(&secondHisto);
  
  elementSpectrum sumOfTwo(firstHisto);
  return sumOfTwo;
}

void exampleOfSingleFit(const std::string& file1, const std::string& file2)
{
  elementSpectrum spec(file1);
  spec.readData();
  spec.plot("firstSpec.png");
  
  elementSpectrum spec2(file2);
  spec2.readData();
  spec2.plot("secondSpec.png");
  
  spectrumFitter test(spec);
  test.addNextSpectrum(spec2);
  test.fit(file2);
  
}

void exampleOfElementSpectrumUsage(const std::string& filePath, const std::string& outPath)
{
  elementSpectrum file(filePath);
   file.readData();
   file.plot(outPath);
    
}

TH1F generateGaussian(const std::string& name ,const  double mean, const double sigma, const double N)
{
  TH1F histo (name.c_str(), name.c_str(), 1101, 0.0000E+00, 1.1E+01);
   TF1 f2("f2","gaus",0,1.1E+01);
   f2.SetParameters(1,mean,sigma);
   histo.FillRandom("f2",1E6);
   histo.Scale(N);
   histo.SetName(name.c_str());
   
  return histo;
}

TH1F generateThreeGaussians(const std::string& name ,const std::vector<double>  mean, const std::vector<double>  sigma, const std::vector<double> N)
{
  if(N.size() != 3)
  {
    std::cout << "Wrong size of vector with heigts\n";
    std::exit(2);
  }
    TH1F histoMain = generateGaussian(name+"1", mean[0], sigma[0], N[0]);
    TH1F histoToAdd = generateGaussian(name+"2", mean[1], sigma[1], N[1]);
    histoMain.Add(&histoToAdd);
    histoToAdd =generateGaussian(name+"3", mean[2], sigma[2], N[2]);
    histoMain.Add(&histoToAdd);
    return histoMain;
}

void testOfSinglePeak(const double expPeakHeight, const double simPeakHeight, const std::string out)
{
  TH1F histoOne = generateGaussian("main", 5, 1, expPeakHeight);
  TH1F histoTwo = generateGaussian("fitted", 5, 1, simPeakHeight);
  
  elementSpectrum mainSpectrum(histoOne);
  elementSpectrum signalSpectrum(histoTwo);
  
  
  spectrumFitter test(mainSpectrum);
  test.addNextSpectrum(signalSpectrum);
  test.fit(out);
}

void testOfFewGaussians()
{
  std::vector<double> heights;
  heights.push_back(1);
  heights.push_back(3);
  heights.push_back(2);
  std::vector<double> positions;
  positions.push_back(2);
  positions.push_back(5);
  positions.push_back(7);
  std::vector<double> smears;
  smears.push_back(0.5);
  smears.push_back(0.5);
  smears.push_back(0.5);
  
  TH1F expHisto = generateThreeGaussians("exp", positions, smears,heights );
  TH1F simulatedHisto = generateGaussian("sim", 5,0.5,1);
  TH1F simulatedHisto2 = generateGaussian("sim2", 2,0.5,1);
  TH1F simulatedHisto3 = generateGaussian("sim3", 7,0.5,1);
  TH1F simulatedHisto4 = generateGaussian("sim4", 3,0.5,1);
  elementSpectrum expSpec(expHisto);
  elementSpectrum simSpec(simulatedHisto);
  elementSpectrum simSpec2(simulatedHisto2);
  elementSpectrum simSpec3(simulatedHisto3);
  elementSpectrum simSpec4(simulatedHisto4);
  spectrumFitter fitter( expSpec);
  fitter.addNextSpectrum( simSpec);
  fitter.addNextSpectrum( simSpec2);
  fitter.addNextSpectrum( simSpec3);
  fitter.addNextSpectrum( simSpec4);
  fitter.fit("tescik");
}

void testOfFewSinglePeaks()
{
 
  for(double height = 1; height < 15; height++)
  {
    
    std::string out= "test";
    std::ostringstream s;
    s << height;
    out+=s.str();
    s.str(std::string());
    testOfSinglePeak(1, height,out);
  } 
}