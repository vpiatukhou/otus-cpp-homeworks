#include "LinkedList.h"
#include "Foo.h"
#include <gtest/gtest.h>

TEST(MyLinkedListTest, addPrimitiveType) {
    //given
    int numberOfElements = 3;

    Homework::LinkedList<int> list;
    
    //when
    for (int i = 0; i < numberOfElements; ++i) {
        list.add(i);
    }

    //then
    int i = 0;
    for (int element : list) {
        ASSERT_EQ(i, element);
        ++i;
    }
    ASSERT_EQ(i, numberOfElements);
}

TEST(MyLinkedListTest, addObjectType) {
    //given
    int numberOfElements = 3;

    Homework::LinkedList<HomeworkTest::Foo> list;
    
    //when
    for (int i = 0; i < numberOfElements; ++i) {
        list.add(HomeworkTest::Foo(i));
    }

    //then
    int i = 0;
    for (HomeworkTest::Foo element : list) {
        ASSERT_EQ(i, element.value);
        ++i;
    }
    ASSERT_EQ(i, numberOfElements);
}