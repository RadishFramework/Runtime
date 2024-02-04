#pragma once

#include "radish.hpp"
#include <cassert>

namespace radish {

/// @brief Radish uses typed error objects to signal errors rather than exceptions.
/// This system makes error handling both explicit and non-bubbling.
/// @tparam TSuccess The type returned when the function was successful.
/// @tparam TFailure The type returned when the function was unsuccessful.
template<typename TSuccess, typename TFailure>
struct error final {
    static_assert(!std::is_same_v<TSuccess, TFailure>, "TSuccess and TFailure cannot be the same type");

    /// @brief Creates a successful error object.
    /// @param success The success object.
    constexpr error(TSuccess success) : _value(std::move(success)), _success(true) {
    }

    // error(TSuccess&& success) : _value(std::move(success)), _success(true) {
    // }

    /// @brief Creates a failed error object.
    /// @param failure The failure object.
    constexpr error(TFailure failure) : _value(std::move(failure)), _success(false) {
    }

    // constexpr error(TFailure&& failure) : _value(std::move(failure)), _success(false) {
    // }

    /// @brief Gets the successful value. Asserts if this error was a failure case.
    /// @return The success value.
    [[nodiscard]]
    constexpr TSuccess& value() { 
        assert(!failed());
        return _value.success;
    }

    [[nodiscard]]
    constexpr const TSuccess& value() const { 
        assert(!failed());
        return _value.success;
    }

    /// @brief Gets the failure value. Asserts of this error was not a failure.
    /// @return The failure value.
    [[nodiscard]]
    constexpr TFailure& failure() {
        assert(failed());
        return _value.failure;
    }

    constexpr const TFailure& failure() const {
        assert(failed());
        return _value.failure;
    }

    /// @brief Returns whether this error has a failed value.
    /// @return True if this is a failure value, otherwise false.
    [[nodiscard]]
    constexpr bool failed() const { return !_success; }

private:
    union value {
        TSuccess success;
        TFailure failure;

        value(TSuccess&& success) : success(std::move(success)) {}
        value(TFailure&& failure) : failure(std::move(failure)) {}

        ~value() {}
    } _value;

    bool _success;
};

}