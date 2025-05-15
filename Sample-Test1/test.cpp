#include "gtest/gtest.h"
#include "unique_ptr.h"

TEST(uniquePtrTest, TestName) 
{
	unique_ptr<int, decltype(std::default_delete<int>())> number(new int(12), std::default_delete<int>());
	EXPECT_EQ(*number, 12);
}

TEST(uniquePtrTest, constructor)
{
	unique_ptr<int> number;
	EXPECT_EQ(number.Get(), nullptr);
}

TEST(uniquePtrTest, releaseTest)
{
	unique_ptr<int> number(new int(12));
	int* num = number.Release();
	EXPECT_EQ(*num, 12);
	EXPECT_EQ(number.Get(), nullptr);
	delete num;
}

TEST(uniquePtrTest, swapTest)
{
	unique_ptr<int> number(new int(12));
	unique_ptr<int> number2(new int(14));
	int* num1 = number.Get();
	int* num2 = number2.Get();
	number.Swap(number2);
	EXPECT_EQ(*number2, 12);
	EXPECT_EQ(*number, 14);
	EXPECT_EQ(num1, number2.Get());
	EXPECT_EQ(num2, number.Get());
}

TEST(uniquePtrTest, resetTest)
{
	unique_ptr<int> number(new int(12));
	number.Reset(new int(18));
	EXPECT_EQ(*number, 18);
	number.Reset();
	EXPECT_EQ(number.Get(), nullptr);
}

TEST(uniquePtrTest, moveTest)
{
	unique_ptr<int> number(new int(12));
	unique_ptr<int> num = std::move(number);
	EXPECT_EQ(*num, 12);
	EXPECT_EQ(number.Get(), nullptr);
}

TEST(uniquePtrTest, moveTest1)
{
	unique_ptr<int> number;
	unique_ptr<int> num = std::move(number);
	EXPECT_EQ(num.Get(), nullptr);
	EXPECT_EQ(number.Get(), nullptr);
}

TEST(uniquePtrTest, moveTest2)
{
	unique_ptr<int> number(new int(11643));
	unique_ptr<int> num;
	num = std::move(number);
	EXPECT_EQ(*num, 11643);
	EXPECT_EQ(number.Get(), nullptr);
}

TEST(uniquePtrTest, moveTest3)
{
	int* num = static_cast<int*>(malloc(sizeof(int)));
	unique_ptr<int, decltype(&free)> number(num, &free);
}

TEST(uniquePtrTest, moveTest4)
{
	unique_ptr<int> number1(new int(12));
	int* num = static_cast<int*>(malloc(sizeof(int)));
	unique_ptr<int, decltype(&free)> number2(num, &free);
	number1.Swap(number2);
}