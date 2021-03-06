#ifndef DATAFILE

#define DATAFILE

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>


class dataFile
{
public:
  dataFile();
  dataFile(const std::string& path);
  ~dataFile();
  dataFile(const dataFile& );
  dataFile& operator= (dataFile&);
  void readData();
  std::string getPath();
  std::vector<std::pair<double,std::pair<double,double> > > getData() const;
protected:
  bool testLine(const std::string& line);
  std::vector<std::pair<double,std::pair<double,double> > > fData;
  inline bool checkPath(){ struct stat buffer; return (stat ( fPath.c_str(), &buffer) == 0); };
  std::string fPath;
};

#endif //DATAFILE