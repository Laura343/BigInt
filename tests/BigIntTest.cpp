#include <BigInt/BigInt.h>
#include <gtest/gtest.h>

#include <vector>

using namespace ACA;
using namespace std;

TEST(BigInt,isBigger)
{
    const vector<tuple<BigInt,BigInt,bool>> ExpectedActualList=
    {
        { BigInt("0"), BigInt("1"), false },
        { BigInt("1001999"), BigInt("1000999"), true },
        { BigInt("1002523734"), BigInt("1002523733"), true },
        { BigInt("100000"), BigInt("99999"), true }
    };

    for (auto [num1,num2, isBigger] : ExpectedActualList) {
        EXPECT_EQ(num1>num2, isBigger);
    }
}

TEST(BigInt, Increment) 
{
    const vector<pair<BigInt, BigInt>> ExpectedActualList = {
        { BigInt("0"), BigInt("1") },
        { BigInt("8"), BigInt("9") },
        { BigInt("9"), BigInt("10") },
        { BigInt("99999"), BigInt("100000") }
    };

    for (auto [num, num_plus_one] : ExpectedActualList) {
        EXPECT_EQ(++num, num_plus_one);
    }
}

TEST(BigInt, Decrement)
 {
    const vector<pair<BigInt, BigInt>> ExpectedActualList = {
        { BigInt("1"), BigInt("0") },
        { BigInt("11110"), BigInt("11109") },
        { BigInt("17762"), BigInt("17761") },
        { BigInt("100000"), BigInt("99999") }
    };

    for (auto [num, num_minus_one] : ExpectedActualList) {
        EXPECT_EQ(--num, num_minus_one);
    }
}

TEST(BigInt,Sum)
{
    const vector<tuple<BigInt,BigInt,BigInt>> ExpectedActualList=
    {
        {BigInt(10000),BigInt(10000),BigInt(20000)},
        {BigInt(0),BigInt(19872),BigInt(19872)},
        {BigInt(99923),BigInt(10999),BigInt(110922)},
        {BigInt(97432),BigInt(4000),BigInt(101432)}
    };
    for(auto [num1,num2,sum]:ExpectedActualList)
    {
        EXPECT_EQ(num1+num2,sum);
    }
}

TEST(BigInt,Subtract)
{
    const vector<tuple<BigInt,BigInt,BigInt>> ExpectedActualList=
    {
        {BigInt("10000"),BigInt("10000"),BigInt("0")},
        {BigInt("19872"),BigInt("0"),BigInt("19872")},
        {BigInt("1000000000"),BigInt("999999999"),BigInt("1")},
        {BigInt("97432"),BigInt("4000"),BigInt("93432")},
        {BigInt("777777"),BigInt("80000"),BigInt("697777")},
        {BigInt("1200000"),BigInt("400012"),BigInt("799988")},
    };
    for(auto [num1,num2,sub]:ExpectedActualList)
    {
        EXPECT_EQ(num1-num2,sub);
    }
}

TEST(BigInt,Multiple)
{
    const vector<tuple<BigInt,BigInt,BigInt>> ExpectedActualList=
    {
        {BigInt("10000"),BigInt("10000"),BigInt("100000000")},
        {BigInt("19872"),BigInt("0"),BigInt("0")},
        {BigInt("1"),BigInt("999999999"),BigInt("999999999")},
        {BigInt("97432"),BigInt("4000"),BigInt("389728000")},
        {BigInt("777"),BigInt("80000"),BigInt("62160000")},
        {BigInt("1267"),BigInt("8234"),BigInt("10432478")},
        {BigInt("126722"),BigInt("8237"),BigInt("1043809114")},
    };
    for(auto [num1,num2,mul]:ExpectedActualList)
    {
        EXPECT_EQ(num1*num2,mul);
    }
}

TEST(BigInt,Divide)
{
    const vector<tuple<BigInt,BigInt,BigInt>> ExpectedActualList=
    {
        {BigInt("10001"),BigInt("10000"),BigInt("1")},
        {BigInt("0"),BigInt("19872"),BigInt("0")},
        {BigInt("788888"),BigInt("999999999"),BigInt("0")},
        {BigInt("97432"),BigInt("4000"),BigInt("24")},
        {BigInt("981524"),BigInt("38"),BigInt("25829")},
    };
    for(auto [num1,num2,div]:ExpectedActualList)
    {
        EXPECT_EQ(num1/num2,div);
    }
}

TEST(BigInt,Remainder)
{
    const vector<tuple<BigInt,BigInt,BigInt>> ExpectedActualList=
    {
        {BigInt("10001"),BigInt("10000"),BigInt("1")},
        {BigInt("0"),BigInt("19872"),BigInt("0")},
        {BigInt("788888"),BigInt("999999999"),BigInt("788888")},
        {BigInt("97432"),BigInt("4000"),BigInt("1432")},
        {BigInt("981524"),BigInt("38"),BigInt("22")},
    };
    for(auto [num1,num2,rem]:ExpectedActualList)
    {
        EXPECT_EQ(num1%num2,rem);
    }
}

TEST(BigInt,Pow)
{
    const vector<tuple<BigInt,BigInt,BigInt>> ExpectedActualList=
    {
        {BigInt("976"),BigInt("4"),BigInt("907401035776")},
        {BigInt("0"),BigInt("19872"),BigInt("0")},
        {BigInt("1"),BigInt("999999999"),BigInt("1")},
        {BigInt("97432"),BigInt("3"),BigInt("924921452205568")},
        {BigInt("2"),BigInt("24"),BigInt("16777216")},
    };
    for(auto [num1,num2,pow]:ExpectedActualList)
    {
        EXPECT_EQ(num1^num2,pow);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

