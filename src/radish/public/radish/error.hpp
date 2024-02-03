#pragma once

#include "radish.hpp"

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
    constexpr error(TSuccess success) : _value(success), _success(true) {
    }

    /// @brief Creates a failed error object.
    /// @param failure The failure object.
    constexpr error(TFailure failure) : _value(failure), _success(false) {
        _value.failure = failure;
    }

    /// @brief Gets the successful value. Asserts if this error was a failure case.
    /// @return The success value.
    [[nodiscard]]
    constexpr TSuccess value() const { 
        if (failed())
            return TSuccess{};

        return _value.success;
    }

    /// @brief Gets the failure value. Asserts of this error was not a failure.
    /// @return The failure value.
    [[nodiscard]]
    constexpr TFailure failure() const {
        if (!failed())
            return TFailure{};

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

        value(TSuccess success) : success(success) {}
        value(TFailure failure) : failure(failure) {}
        ~value() {}
    } _value;

    bool _success;
};

}