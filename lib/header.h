#ifndef HEADER_IO_H
#define HEADER_IO_H 1
#include <map>
#include <memory>
#include <vector>
#include "ioTypes.h"

namespace SEP {
class key {
 public:
  key(const std::string name, const dataType typ, const size_t index) {
    _name = name;
    _type = typ;
    _index = index;
  }
  dataType type() const { return _type; }
  std::string name() const { return _name; }
  size_t index() const { return _index; }

 private:
  std::string _name;
  dataType _type;
  size_t _index;
};
class header {
 public:
  header(const std::vector<key> keys);

  void addKey(const std::string name, const dataType typ);
  void setFloatKey(const std::string name, const std::vector<float> vals);
  void setIntKey(const std::string name, const std::vector<int> vals);
  void setDoubleKey(const std::string name, const std::vector<double> vals);
  void setShortKey(const std::string name, const std::vector<short> vals);

  void setHeaders(const int nh,
                  std::shared_ptr<std::vector<unsigned char>> head);
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

 private:
  size_t getIndex(const std::string name) const { return _key_index.at(name); }
  size_t getOffset(const std::string name) const {
    size_t index = getIndex(name);
    return _keys[index].index();
  }
  std::vector<key> _keys;
  std::map<std::string, size_t> _key_index;
  std::shared_ptr<std::vector<unsigned char>> _head = nullptr, _data = nullptr;
  int _nh, _nsz = 0;
};

}  // namespace SEP
#endif
