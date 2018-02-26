#ifndef EXAMPLES

#define EXAMPLES

#include <iostream>
#include <sstream>
#include <vector>
#include "dataFile.h"
#include "elementSpectrum.h"
#include "spectrumFitter.h"

void exampleOfMultipleFit(const std::string& expFile, const std::vector<std::string>& simFiles);
void exampleOfSingleFit(const std::string& file1, const std::string& file2);
TH1F generateGaussian(const std::string& name ,const  double mean, const double sigma, const double N);
TH1F generateThreeGaussians(const std::string& name ,const std::vector<double>  mean, const std::vector<double>  sigma, const std::vector<double> N);
void testOfSinglePeak(const double expPeakHeight, const double simPeakHeight, const std::string out);
void testOfFewGaussians();
void testOfFewSinglePeaks();
elementSpectrum addTwoElements(elementSpectrum firstElement, elementSpectrum secondElement, double firstElementWeight = 1, double secondElementWeight = 1);
void checkAdditionForTwoElements();

#endif //EXAMPLES