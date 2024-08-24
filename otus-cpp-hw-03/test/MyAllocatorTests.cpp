#include "MyAllocator.h"
#include "DynamicPoolStrategy.h"
#include "FixedPoolStrategy.h"
#include "Foo.h"
#include <map>
#include <functional>
#include <gtest/gtest.h>

TEST(MyAllocatorTest, mapPrimitiveTypeAndFixedPoolStrategy) {
    //given
    const std::size_t numberOfElements = 10;

    using Allocator = Homework::MyAllocator<std::pair<const int, int>, numberOfElements, Homework::FixedPoolStrategy>;
    std::map<int, int, std::less<int>, Allocator> map;
    
    //when
    for (int i = 0; i < numberOfElements; ++i) {
        map[i] = i;
    }

    //then
    ASSERT_EQ(numberOfElements, map.size());
    for (int i = 0; i < numberOfElements; ++i) {
        ASSERT_EQ(i, map[i]);
    }
}

TEST(MyAllocatorTest, mapPrimitiveTypeAndDynamicPoolStrategy) {
    //given
    const std::size_t initialPoolSize = 10;
    const std::size_t numberOfElements = initialPoolSize * 5; //a total number of elements is bigger than the initial pool size => the pool will grow

    using Allocator = Homework::MyAllocator<std::pair<const int, int>, initialPoolSize, Homework::DynamicPoolStrategy>;
    std::map<int, int, std::less<int>, Allocator> map;
    
    //when
    for (int i = 0; i < numberOfElements; ++i) {
        map[i] = i;
    }

    //then
    ASSERT_EQ(numberOfElements, map.size());
    for (int i = 0; i < numberOfElements; ++i) {
        ASSERT_EQ(i, map[i]);
    }
}

TEST(MyAllocatorTest, mapObjectTypeAndDynamicPoolStrategy) {
    //given
    const std::size_t initialPoolSize = 10;
    const std::size_t numberOfElements = initialPoolSize * 5; //a total number of elements is bigger than the initial pool size => the pool will grow

    using Allocator = Homework::MyAllocator<std::pair<const int, HomeworkTest::Foo>, initialPoolSize, Homework::DynamicPoolStrategy>;
    std::map<int, HomeworkTest::Foo, HomeworkTest::FooLess, Allocator> map;
    
    //when
    for (int i = 0; i < numberOfElements; ++i) {
        map[i] = HomeworkTest::Foo(i);
    }

    //then
    ASSERT_EQ(numberOfElements, map.size());
    for (int i = 0; i < numberOfElements; ++i) {
        ASSERT_EQ(i, map[i].value);
    }
}