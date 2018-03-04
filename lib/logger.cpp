#include <assert.h>
#include <logger.h>

using namespace SEP;
void buffer::add(const std::string &line) {
  _buf.push_back(line);
  if (_buf.size() == _flush) flush();
  _buf.resize(0);
}
fileBuffer::fileBuffer(const std::string fle, const int flushsz) {
  _flush = flushsz;
  _myf.open(fle);
}

void logger::addMessage(const std::string &buf, const std::string &msg) {
  getBuffer(buf)->add(msg);
}
std::shared_ptr<buffer> logger::getBuffer(const std::string &buf) {
  if (_bufs.count(buf) == 0) _bufs[buf].reset(new errBuffer(100));
  return _bufs[buf];
}
void logger::createFileBuffer(const std::string &buf, const std::string &fle,
                              const int nflush) {
  _bufs[buf].reset(new fileBuffer(fle, nflush));
}
void logger::createErrBuffer(const std::string &buf, const int nflush) {
  _bufs[buf].reset(new errBuffer(nflush));
}
/*
void logMessage(std::&msg) { logger::get()->addMessage("default", msg); }
void logBuffer(std::string &buf, std::string &msg) {
  logger::get()->addMessage(buf, msg);
}
std::string getBuffer(std::string buf) {
  std::stringstream x;
  logger::get()->getBuffer(buf)->printAll(x);
  return x.str();
}
*/