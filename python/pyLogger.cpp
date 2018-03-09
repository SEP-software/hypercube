#include <pybind11/pybind11.h>
#include "logger.h"
namespace py = pybind11;
namespace SEP {

PYBIND11_MODULE(pyLogger, clsLog) {
  py::class_<buffer, std::shared_ptr<buffer>>(clsLog, "buffer")
      .def("get", (std::vector<std::string>(buffer::*)()) & buffer::get,
           "Get the buffer contents");
  py::class_<logger>(clsLog, "logger")  //
      .def("get", &logger::get)
      .def("addMessage",
           (void (logger::*)(const std::string &, const std::string &)) &
               logger::addMessage,
           "Add message")
      .def("getBuffer",
           (std::shared_ptr<buffer>(logger::*)(const std::string &)) &
               logger::getBuffer,
           "Get buffer")
      .def("createFileBuffer",
           (void (logger::*)(const std::string &, const std::string &,
                             const int)) &
               logger::createFileBuffer,
           "Create a file buffer ovject")
      .def("createErrBuffer",
           (void (logger::*)(const std::string &, const int)) &
               logger::createErrBuffer,
           "Create an error buffer ovject")
      .def("flush", (void (logger::*)()) & logger::flush, "Flush all buffers");
}
}  // namespace SEP
