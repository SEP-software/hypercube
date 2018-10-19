#pragma once
#include <string>
namespace SEP {
enum dataType {
  DATA_BYTE,
  DATA_INT,
  DATA_FLOAT,
  DATA_COMPLEX,
  DATA_DOUBLE,
  DATA_SHORT,
  DATA_UNKNOWN
};

size_t getDataTypeSize(const dataType typ);
dataType toElementType(const std::string &name);
std::string getTypeString(const dataType typ);

}  // namespace SEP
