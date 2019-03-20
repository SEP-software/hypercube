#ifndef DEBUG_IO_H
#define DEBUG_IO_H 1
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>  // std::stringstream
#include <string>
#include <vector>
namespace SEP {
class debug {
 public:
  void addLine(std::stringstream &x);
  virtual void flush()=0;
  std::vector<std::string> returnLines() { return _lines; }
  void setFlush(int nf) { _nflush = nf; }
  virtual void close() { ; }
  std::vector<std::string> _lines;

 private:
  int _nflush;
};
class errDebug : public debug {
 public:
  errDebug(int nflush = 1000000) { setFlush(nflush); }
  virtual void flush() override;
};
class fileDebug : public debug {
 public:
  fileDebug(std::string &name, int nflush = 1000000);
  virtual void close() override;
  virtual void flush() override;

 private:
  std::ofstream _file;
};
class debugging {
 public:
  static debugging &instance() {
    static debugging instance;
    return instance;
  }
  void addDebug(std::string name, std::shared_ptr<debug> d) {
    _debugs[name] = d;
  }
  std::shared_ptr<debug> getDebug(const std::string &name);

 private:
  debugging() { ; }
  ~debugging() { ; }
  std::map<std::string, std::shared_ptr<debug>> _debugs;
};

}  // namespace SEP
std::vector<std::string> getDebug(std::string buffer);
#endif
