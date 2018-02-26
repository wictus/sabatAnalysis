#include <iostream>
#include <sstream>
#include <vector>
#include "dataFile.h"
#include "elementSpectrum.h"
#include "spectrumFitter.h"
#include "examples.h"

int main(int argc, char **argv) {   
  if(argc > 2)
  {
    std::vector<std::string> simPaths;
    for(int i = 2; i < argc; i++)
      simPaths.push_back(argv[i]);
    exampleOfMultipleFit(argv[1], simPaths);
  }
  

  return 0;
}
