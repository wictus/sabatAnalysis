#include "dataFile.h"

dataFile::dataFile(const dataFile& file)
: fPath(file.fPath)
{
      
}

dataFile::dataFile(std::string path)
:fPath(path)
{
  
}

dataFile::dataFile()
{
  fPath = "";
}

dataFile& dataFile::operator=(dataFile& file)
{
  this->fPath = file.fPath;
  return *this;
}

dataFile::~dataFile()
{

}


