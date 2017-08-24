#include <iostream>
#include "dataFile.h"
#include "elementSpectrum.h"
#include "spectrumFitter.h"

int main(int argc, char **argv) {
  
  std::string filePath = "";
  std::string outPath = "";
  if(3 == argc)
  {
    filePath = argv[1];
    outPath = argv[2];
  }
  
  elementSpectrum file(argv[1]);
  file.readData();
  
  elementSpectrum file2(argv[2]);
  file2.readData();
  
  spectrumFitter test(file, file2);
  test.fit(argv[2]);
  
  return 0;
}

void exampleOfElementSpectrumUsage(const std::string& filePath, const std::string& outPath)
{
  elementSpectrum file(filePath);
   file.readData();
   file.plot(outPath);
    
}