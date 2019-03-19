#ifndef HEADER_IO_H
#define HEADER_IO_H 1
#include <map>
#include <memory>
#include <vector>
#include "SEPException.h"
#include "ioTypes.h"

namespace SEP {
class key {
 public:
  key(const std::string name, const dataType typ) {
    _name = name;
    _type = typ;
  }
  dataType type() const { return _type; }
  std::string name() const { return _name; }

 private:
  std::string _name;
  dataType _type;
};
class header {
 public:
  header(const std::vector<key> keys, const int nh);

  void addKey(const std::string name, const dataType typ);
  void setFloatKey(const std::string name, const std::vector<float> vals);
  void setIntKey(const std::string name, const std::vector<int> vals);
  void setDoubleKey(const std::string name, const std::vector<double> vals);
  void setShortKey(const std::string name, const std::vector<short> vals);
  void addHeaders(const int nh);
  void setHeaders(std::vector<std::vector<unsigned char>>& head);
  std::vector<float> getFloatKey(const std::string name) const;
  std::vector<double> getDoubleKey(const std::string name) const;
  std::vector<int> getIntKey(const std::string name) const;
  std::vector<short> getShortKey(const std::string name) const;
  float getFloatKeyVal(const std::string name, const int index) const;
  double getDoubleKeyVal(const std::string name, const int index) const;
  int getIntKeyVal(const std::string name, const int index) const;
  short getShortKeyVal(const std::string name, const int index) const;
  void setFloatKeyVal(const std::string name, const int index, const float val);
  void setShortKeyVal(const std::string name, const int index, const short val);
  void setDoubleKeyVal(const std::string name, const int index,
                       const double val);
  void setIntKeyVal(const std::string name, const int index, const int val);

  std::shared_ptr<header> clone();

 private:
  size_t getIndex(const std::string name) const { return _key_index.at(name); }
  inline size_t getOffset(const std::string name) const {
    if (_key_offset.count(name) == 0)
      throw SEPException(std::string("Unknown key name") + name);

    return _key_offset.at(name);
  }

  std::vector<key> _keys;
  std::map<std::string, size_t> _key_index;
  std::map<std::string, size_t> _key_offset;
  std::vector<std::vector<unsigned char>> _head;

  int _nsz;
};

}  // namespace SEP
#endif
