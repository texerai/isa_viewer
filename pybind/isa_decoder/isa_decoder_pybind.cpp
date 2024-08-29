#include <pybind11/pybind11.h>
#include <string>

#include "amdisa/isa_decoder.h"

namespace py = pybind11;

// Wrapper class to expose only needed functionality
// to python and respect the python function interfaces.
struct instruction
{
    std::string name;
    std::string description;

    instruction(const std::string& name, const std::string& description) : name(name),
        description(description) {}
};

class decoder
{
public:
    void init(const std::string& path_to_xml)
    {
        std::string err_message;
        bool is_init = decoder_.Initialize(path_to_xml, err_message);
        if (!is_init)
        {
            throw std::runtime_error(err_message);
        }
    }

    instruction decode(const uint64_t inst)
    {
        std::string err_message;
        amdisa::InstructionInfoBundle bundle;
        bool is_decoded = decoder_.DecodeInstruction(inst, bundle, err_message);
        if (bundle.bundle.size() > 1)
        {
            throw std::runtime_error("Error: Bundle has more than one instructions, not implemented.");
        }
        else if (!is_decoded)
        {
            throw std::runtime_error(err_message); 
        }

        std::string name = bundle.bundle[0].instruction_name;
        std::string description = bundle.bundle[0].instruction_description;
        return instruction(name, description);
    }

private:
    amdisa::IsaDecoder decoder_;
};

PYBIND11_MODULE(amdisa, m) {
    py::class_<instruction>(m, "instruction")
        .def(py::init<const std::string&, const std::string&>())
        .def_readwrite("name", &instruction::name)
        .def_readwrite("description", &instruction::description);

    // Expose IsaDecoder.
    py::class_<decoder>(m, "decoder")
        .def(py::init<>())  // Constructor
        .def("init", &decoder::init, "Initialize AMD ISA Decdoer.")
        .def("decode", &decoder::decode, "Decode instruction");
}
