#include "radish/vm.hpp"
#include "radish/logging.hpp"

#include "quickjs/quickjs.h"

namespace radish {

// 1GB
constexpr size_t DEFAULT_MEMORY_LIMIT = 1073741824;

virtual_machine::create_error virtual_machine::create() {

    auto runtime = JS_NewRuntime();
    if (!runtime) {
        return {"Failed to allocate runtime memory"};
    }

    auto vm = std::unique_ptr<virtual_machine>(new virtual_machine());
    vm->_runtime = runtime;

    return create_error{std::move(vm)};
}

virtual_machine::~virtual_machine() {
    if (_runtime != nullptr) {
        JS_FreeRuntime(_runtime);
        _runtime = nullptr; 
    }
}

} // namespace radish