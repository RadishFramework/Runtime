#include "radish/vm.hpp"

namespace radish {

virtual_machine::create_error virtual_machine::create() {

    wasmtime::Config cfg{};
    cfg.debug_info(true);

    virtual_machine* vm = new virtual_machine();
    vm->_engine = new wasmtime::Engine(std::move(cfg));

    return create_error{vm};
}

}