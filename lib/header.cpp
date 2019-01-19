#include "header.h"
#include <cstring>
#include "SEPException.h"
using namespace SEP;

header::header(const std::vector<key> keys) { _keys = keys; }

void header::addKey(const std::string name, const dataType typ) {
  size_t nsz = _nsz + getDataTypeSize(_keys[_keys.size() - 1].type());
  _key_index[name] = _keys.size();
  _keys.push_back(key(name, typ, nsz));
  if (_nh == 0) {
    std::shared_ptr<std::vector<unsigned char>> head2 =
        std::make_shared<std::vector<unsigned char>>(nsz * _nh);
    for (size_t ih = 0; ih < _nh; ih++) {
      memcpy(head2->data() + ih * nsz, _head->data() + ih * _nsz, _nsz);
    }
    _head = head2;
  }
  _nsz = nsz;
}
void header::setFloatKey(const std::string name,
                         const std::vector<float> vals) {
  size_t off = getOffset(name);
  if (vals.size() != _nh)
    throw(SEPException(
        std::string("Size of vals not equal to number of headers")));
  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(_head->data() + ih * _nsz + off, vals.data() + sizeof(float) * ih,
           sizeof(float));
}
void header::setIntKey(const std::string name, const std::vector<int> vals) {
  size_t off = getOffset(name);
  if (vals.size() != _nh)
    throw(SEPException(
        std::string("Size of vals not equal to number of headers")));
  if (_keys[getIndex(name)].type() != DATA_INT)
    throw(SEPException(std::string("Key type is not integer")));

  for (size_t ih = 0; ih < _nsz; ih++)
    memcpy(_head->data() + ih * _nsz + off, vals.data() + sizeof(int) * ih,
           sizeof(int));
}
void header::setDoubleKey(const std::string name,
                          const std::vector<double> vals) {
  size_t off = getOffset(name);
  if (vals.size() != _nh)
    throw(SEPException(
        std::string("Size of vals not equal to number of headers")));
  if (_keys[getIndex(name)].type() != DATA_DOUBLE)
    throw(SEPException(std::string("Key type is not double")));
  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(_head->data() + ih * _nsz + off, vals.data() + sizeof(double) * ih,
           sizeof(double));
}
void header::setShortKey(const std::string name,
                         const std::vector<short> vals) {
  size_t off = getOffset(name);
  if (vals.size() != _nh)
    throw(SEPException(
        std::string("Size of vals not equal to number of headers")));
  if (_keys[getIndex(name)].type() != DATA_SHORT)
    throw(SEPException(std::string("Key type is not short")));
  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(_head->data() + ih * _nsz + off, vals.data() + sizeof(short) * ih,
           sizeof(short));
}

void header::setHeaders(const int nh,
                        std::shared_ptr<std::vector<unsigned char>> head) {
  if (head->size() != _nsz * _nh)
    throw(SEPException(
        std::string("Header size not equal to number headers * keys size.")));

  _head = head;
  _nh = nh;
}
std::vector<float> header::getFloatKey(const std::string name) const {
  size_t off = getOffset(name);
  std::vector<float> vals(_nh);
  if (_keys[getIndex(name)].type() != DATA_FLOAT)
    throw(SEPException(std::string("Key type is not float")));
  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(vals.data() + sizeof(float) * ih, _head->data() + ih * _nsz + off,
           sizeof(float));
  return vals;
}
std::vector<double> header::getDoubleKey(const std::string name) const {
  size_t off = getOffset(name);
  std::vector<double> vals(_nh);
  if (_keys[getIndex(name)].type() != DATA_DOUBLE)
    throw(SEPException(std::string("Key type is not double")));

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(vals.data() + sizeof(double) * ih, _head->data() + ih * _nsz + off,
           sizeof(double));
  return vals;
}
std::vector<int> header::getIntKey(const std::string name) const {
  size_t off = getOffset(name);
  std::vector<int> vals(_nh);
  if (_keys[getIndex(name)].type() != DATA_INT)
    throw(SEPException(std::string("Key type is not int")));

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(vals.data() + sizeof(int) * ih, _head->data() + ih * _nsz + off,
           sizeof(int));
  return vals;
}
std::vector<short> header::getShortKey(const std::string name) const {
  size_t off = getOffset(name);
  std::vector<short> vals(_nh);
  if (_keys[getIndex(name)].type() != DATA_SHORT)
    throw(SEPException(std::string("Key type is not short")));

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(vals.data() + sizeof(short) * ih, _head->data() + ih * _nsz + off,
           sizeof(short));
  return vals;
}
float header::getFloatKeyVal(const std::string name, const int index) const {
  size_t off = getOffset(name);
  float val;
  if (_keys[getIndex(name)].type() != DATA_FLOAT)
    throw(SEPException(std::string("Key type is not float")));

  memcpy(&val, _head->data() + index * _nsz + off, sizeof(float));
  return val;
}
double header::getDoubleKeyVal(const std::string name, const int index) const {
  size_t off = getOffset(name);
  double val;
  if (_keys[getIndex(name)].type() != DATA_DOUBLE)
    throw(SEPException(std::string("Key type is not double")));

  memcpy(&val, _head->data() + index * _nsz + off, sizeof(double));
  return val;
}
int header::getIntKeyVal(const std::string name, const int index) const {
  size_t off = getOffset(name);
  int val;
  if (_keys[getIndex(name)].type() != DATA_INT)
    throw(SEPException(std::string("Key type is not int")));

  memcpy(&val, _head->data() + index * _nsz + off, sizeof(int));
  return val;
}
short header::getShortKeyVal(const std::string name, const int index) const {
  size_t off = getOffset(name);
  short val;
  if (_keys[getIndex(name)].type() != DATA_SHORT)
    throw(SEPException(std::string("Key type is not short")));

  memcpy(&val, _head->data() + index * _nsz + off, sizeof(short));
  return val;
}
void header::setFloatKeyVal(const std::string name, const int index,
                            const float val) {
  size_t off = getOffset(name);
  if (_keys[getIndex(name)].type() != DATA_FLOAT)
    throw(SEPException(std::string("Key type is not float")));

  memcpy(_head->data() + index * _nsz + off, &val, sizeof(float));
}
void header::setShortKeyVal(const std::string name, const int index,
                            const short val) {
  size_t off = getOffset(name);
  if (_keys[getIndex(name)].type() != DATA_SHORT)
    throw(SEPException(std::string("Key type is not short")));

  memcpy(_head->data() + index * _nsz + off, &val, sizeof(short));
}
void header::setDoubleKeyVal(const std::string name, const int index,
                             const double val) {
  size_t off = getOffset(name);
  if (_keys[getIndex(name)].type() != DATA_DOUBLE)
    throw(SEPException(std::string("Key type is not double")));

  memcpy(_head->data() + index * _nsz + off, &val, sizeof(double));
}

void header::setIntKeyVal(const std::string name, const int index,
                          const int val) {
  size_t off = getOffset(name);
  if (_keys[getIndex(name)].type() != DATA_INT)
    throw(SEPException(std::string("Key type is not int")));

  memcpy(_head->data() + index * _nsz + off, &val, sizeof(int));
}
