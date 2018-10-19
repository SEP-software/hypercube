#include "header.h"
#include <cstring>
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
  assert(vals.size() == _nh);
  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(_head->data() + ih * _nsz + off, vals.data() + sizeof(float) * ih,
           sizeof(float));
}
void header::setIntKey(const std::string name, const std::vector<int> vals) {
  size_t off = getOffset(name);
  assert(vals.size() == _nh);
  assert(_keys[getIndex(name)].type() == DATA_INT);

  for (size_t ih = 0; ih < _nsz; ih++)
    memcpy(_head->data() + ih * _nsz + off, vals.data() + sizeof(int) * ih,
           sizeof(int));
}
void header::setDoubleKey(const std::string name,
                          const std::vector<double> vals) {
  size_t off = getOffset(name);
  assert(vals.size() == _nh);
  assert(_keys[getIndex(name)].type() == DATA_DOUBLE);

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(_head->data() + ih * _nsz + off, vals.data() + sizeof(double) * ih,
           sizeof(double));
}
void header::setShortKey(const std::string name,
                         const std::vector<short> vals) {
  size_t off = getOffset(name);
  assert(vals.size() == _nh);
  assert(_keys[getIndex(name)].type() == DATA_SHORT);

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(_head->data() + ih * _nsz + off, vals.data() + sizeof(short) * ih,
           sizeof(short));
}

void header::setHeaders(const int nh,
                        std::shared_ptr<std::vector<unsigned char>> head) {
  assert(head->size() == _nsz * _nh);
  _head = head;
  _nh = nh;
}
std::vector<float> header::getFloatKey(const std::string name) const {
  size_t off = getOffset(name);
  std::vector<float> vals(_nh);
  assert(_keys[getIndex(name)].type() == DATA_FLOAT);

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(vals.data() + sizeof(float) * ih, _head->data() + ih * _nsz + off,
           sizeof(float));
  return vals;
}
std::vector<double> header::getDoubleKey(const std::string name) const {
  size_t off = getOffset(name);
  std::vector<double> vals(_nh);
  assert(_keys[getIndex(name)].type() == DATA_DOUBLE);

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(vals.data() + sizeof(double) * ih, _head->data() + ih * _nsz + off,
           sizeof(double));
  return vals;
}
std::vector<int> header::getIntKey(const std::string name) const {
  size_t off = getOffset(name);
  std::vector<int> vals(_nh);
  assert(_keys[getIndex(name)].type() == DATA_INT);

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(vals.data() + sizeof(int) * ih, _head->data() + ih * _nsz + off,
           sizeof(int));
  return vals;
}
std::vector<short> header::getShortKey(const std::string name) const {
  size_t off = getOffset(name);
  std::vector<short> vals(_nh);
  assert(_keys[getIndex(name)].type() == DATA_SHORT);

  for (size_t ih = 0; ih < _nh; ih++)
    memcpy(vals.data() + sizeof(short) * ih, _head->data() + ih * _nsz + off,
           sizeof(short));
  return vals;
}
float header::getFloatKeyVal(const std::string name, const int index) const {
  size_t off = getOffset(name);
  float val;
  assert(_keys[getIndex(name)].type() == DATA_FLOAT);

  memcpy(&val, _head->data() + index * _nsz + off, sizeof(float));
  return val;
}
double header::getDoubleKeyVal(const std::string name, const int index) const {
  size_t off = getOffset(name);
  double val;
  assert(_keys[getIndex(name)].type() == DATA_DOUBLE);

  memcpy(&val, _head->data() + index * _nsz + off, sizeof(double));
  return val;
}
int header::getIntKeyVal(const std::string name, const int index) const {
  size_t off = getOffset(name);
  int val;
  assert(_keys[getIndex(name)].type() == DATA_INT);

  memcpy(&val, _head->data() + index * _nsz + off, sizeof(int));
  return val;
}
short header::getShortKeyVal(const std::string name, const int index) const {
  size_t off = getOffset(name);
  short val;
  assert(_keys[getIndex(name)].type() == DATA_SHORT);

  memcpy(&val, _head->data() + index * _nsz + off, sizeof(short));
  return val;
}
void header::setFloatKeyVal(const std::string name, const int index,
                            const float val) {
  size_t off = getOffset(name);
  assert(_keys[getIndex(name)].type() == DATA_FLOAT);

  memcpy(_head->data() + index * _nsz + off, &val, sizeof(float));
}
void header::setShortKeyVal(const std::string name, const int index,
                            const short val) {
  size_t off = getOffset(name);
  assert(_keys[getIndex(name)].type() == DATA_SHORT);

  memcpy(_head->data() + index * _nsz + off, &val, sizeof(short));
}
void header::setDoubleKeyVal(const std::string name, const int index,
                             const double val) {
  size_t off = getOffset(name);
  assert(_keys[getIndex(name)].type() == DATA_DOUBLE);

  memcpy(_head->data() + index * _nsz + off, &val, sizeof(double));
}

void header::setIntKeyVal(const std::string name, const int index,
                          const int val) {
  size_t off = getOffset(name);
  assert(_keys[getIndex(name)].type() == DATA_INT);

  memcpy(_head->data() + index * _nsz + off, &val, sizeof(int));
}
