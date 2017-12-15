#include "dataFile.h"


dataFile::dataFile(const dataFile& file)
: fPath(file.fPath)
{
      
}

dataFile::dataFile(const std::string& path)
:fPath(path)
{ 
  if( path.compare("") != 0 && !checkPath() )
  {
    std::cout<< "Bad path to file: " << path << std::endl;
    std::exit(2);
  }
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

void dataFile::readData()
{
  std::ifstream file;
  file.open(fPath.c_str());
  std::string line;
  while( std::getline(file, line) )
  {
    std::istringstream iss(line);
    double bin, height, error;
    if (! ( iss >> bin >> height >> error) )
      break;
    fData.push_back(std::make_pair<>(bin, std::make_pair<>(height,error) ) );
  }
  std::cout << "Read file with: " << fData.size() << " lines\n";
  if(fData.size() == 0)
  {
    std::cout << "Problem with file: " << fPath << std::endl;
    std::exit(2);
  }
}

std::string dataFile::getPath()
{
  return fPath;
}

std::vector< std::pair< double, std::pair< double, double > > > dataFile::getData() const
{
  return fData;
}
