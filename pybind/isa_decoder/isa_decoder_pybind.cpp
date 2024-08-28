#include <pybind11/pybind11.h>
#include "amdisa/isa_decoder.h"  // Replace with your actual API header file

namespace py = pybind11;

PYBIND11_MODULE(isa_decoder_py, m) {
    // Expose IsaDecoder.
    py::class_<amdisa::IsaDecoder>(m, "IsaDecoder")
        .def(py::init<>())  // Constructor
        .def("Initialize", &amdisa::IsaDecoder::Initialize, "Initialize IsaDecdoer");
}
