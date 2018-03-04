#ifndef LOGGER_H
#define LOGGER_H 1
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
namespace SEP {

class buffer {
 public:
  buffer() { ; }
  void add(const std::string &line);
  std::vector<std::string> get() { return _buf; }
  // void printAll(std::stringstream &x);
  virtual void flush() { ; }
  int _flush;

  std::vector<std::string> _buf;
};

class fileBuffer : public buffer {
 public:
  fileBuffer(const std::string fle, const int flushsz);
  virtual void flush() {
    for (auto i = 0; i < _buf.size(); i++) _myf << _buf[i] << std::endl;
    _myf << std::flush;
  }

 private:
  std::ofstream _myf;
};

class errBuffer : public buffer {
 public:
  errBuffer(const int flushsz) { _flush = flushsz; }  // namespace SEP
  virtual void flush() {
    for (auto i = 0; i < _buf.size(); i++) std::cerr << _buf[i] << std::endl;
    std::cerr << std::flush;
  }
};

class logger {
 private:
  // Private constructor
  logger();
  // Stop the compiler generating methods of copy the object
  logger(logger const &copy);             // Not Implemented
  logger &operator=(logger const &copy);  // Not Implemented
  std::map<std::string, std::shared_ptr<buffer>> _bufs;

 public:
  void addMessage(const std::string &buf, const std::string &msg);
  std::shared_ptr<buffer> getBuffer(const std::string &buf);
  void createFileBuffer(const std::string &buf, const std::string &fle,
                        const int nflush);
  void createErrBuffer(const std::string &buf, const int nflush);
  void flush() {
    for (auto x = _bufs.begin(); x != _bufs.end(); x++) {
      x->second->flush();
    }
  }
  static logger &get() {
    static logger instance;
    return instance;
  }
};
}  // namespace SEP
#endif