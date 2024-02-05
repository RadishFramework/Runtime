#include "radish/vm.hpp"

using namespace hermes;

namespace radish {

virtual_machine::create_error virtual_machine::create() {

    auto cfg = vm::RuntimeConfig::Builder()
        .withEnableEval(false)
        .build();

    auto runtime = fbhm::makeHermesRuntime(cfg);

    auto vm = std::unique_ptr<virtual_machine>(new virtual_machine());
    vm->_runtime = std::move(runtime);

    return create_error{std::move(vm)};
}

}