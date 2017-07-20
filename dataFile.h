#ifndef DATAFILE

#define DATAFILE

#include <string>
#include <sys/stat.h>
#include <unistd.h>


class dataFile
{
public:
  dataFile();
  dataFile(std::string path);
  ~dataFile();
  dataFile(const dataFile& );
  dataFile& operator= (dataFile&);
protected:
  inline bool checkPath(){ struct stat buffer; return (stat ( fPath.c_str(), &buffer) == 0); };
  std::string fPath;
};

#endif //DATAFILE