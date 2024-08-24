#pragma once

namespace HomeworkTest {

    /// @brief A simple structure which is used to test how the custom container and the custom allocator work with objects.
    struct Foo {
        int value = 0;

        Foo() = default;
        Foo(int _value) : value(_value) { };
        Foo(const Foo& other) : value(other.value) { };
        Foo(Foo&& other) : value(other.value) { };
        ~Foo() = default;

        Foo& operator=(const Foo& other) {
            value = other.value;
            return *this;
        }

        Foo& operator=(Foo&& other) {
            value = other.value;
            return *this;
        }
    };

    /// @brief A comparator for std::map.
    struct FooLess {
        constexpr bool operator()(const Foo &a, const Foo &b) const
        {
            return a.value < b.value;
        }
    };
};