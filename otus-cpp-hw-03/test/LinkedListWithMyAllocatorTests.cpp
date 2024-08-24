#include "LinkedList.h"
#include "MyAllocator.h"
#include "DynamicPoolStrategy.h"
#include "FixedPoolStrategy.h"
#include "Foo.h"
#include <gtest/gtest.h>

TEST(IntegrationTests, linkedListObjectTypeWithFixedPoolAllocator) {
    //given
    const std::size_t numberOfElements = 10;

    using Allocator = Homework::MyAllocator<HomeworkTest::Foo, numberOfElements, Homework::FixedPoolStrategy>;
    Homework::LinkedList<HomeworkTest::Foo, Allocator> list;
    
    //when
    for (int i = 0; i < numberOfElements; ++i) {
        list.add(HomeworkTest::Foo(i));
    }

    //then
    int i = 0;
    for (auto& element : list) {
        ASSERT_EQ(i, element.value);
        ++i;
    }
    ASSERT_EQ(i, numberOfElements);
}

TEST(IntegrationTests, linkedListObjectTypeWithDynamicPoolAllocator) {
    //given
    const std::size_t initialPoolSize = 10;
    const std::size_t numberOfElements = initialPoolSize * 5; //a total number of elements is bigger than the initial pool size => the pool will grow;

    using Allocator = Homework::MyAllocator<HomeworkTest::Foo, numberOfElements, Homework::DynamicPoolStrategy>;
    Homework::LinkedList<HomeworkTest::Foo, Allocator> list;
    
    //when
    for (int i = 0; i < numberOfElements; ++i) {
        list.add(HomeworkTest::Foo(i));
    }

    //then
    int i = 0;
    for (auto& element : list) {
        ASSERT_EQ(i, element.value);
        ++i;
    }
    ASSERT_EQ(i, numberOfElements);
}