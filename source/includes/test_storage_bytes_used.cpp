// Copyright Steinwurf ApS 2011.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

/// @file test_storage_bytes_used.cpp Unit tests for the
///       storage_bytes_used class

#include <kodo_core/storage_bytes_used.hpp>

#include <cstdint>

#include <gtest/gtest.h>
#include <stub/function.hpp>

namespace kodo_core
{
// Put dummy layers and tests classes in an anonymous namespace
// to avoid violations of ODF (one-definition-rule) in other
// translation units
namespace
{
/// Helper layer
class dummy_layer
{
public:

    template<class Factory>
    void initialize(Factory& the_factory)
    {
        (void) the_factory;
        m_initialize();
    }

    uint32_t block_size() const
    {
        return m_block_size();
    }

    stub::function<void()> m_initialize;
    stub::function<uint32_t()> m_block_size;
};

// Helper stack
class dummy_stack : public storage_bytes_used<dummy_layer>
{ };

// Helper factory
class dummy_factory
{ };
}
}

TEST(test_storage_bytes_used, api)
{
    kodo_core::dummy_factory factory;
    kodo_core::dummy_stack stack;

    stack.m_block_size.set_return(10U);

    stack.initialize(factory);
    stack.set_bytes_used(9U);

    EXPECT_EQ(stack.m_initialize.calls(), 1U);
    EXPECT_TRUE(stack.m_block_size.expect_calls().with().to_bool());
    EXPECT_EQ(stack.bytes_used(), 9U);

    // Initialize again and check that the state is reset
    stack.initialize(factory);
    EXPECT_EQ(stack.m_initialize.calls(), 2U);
    EXPECT_TRUE(stack.m_block_size.expect_calls().with().to_bool());
    EXPECT_EQ(stack.bytes_used(), 0U);
}
