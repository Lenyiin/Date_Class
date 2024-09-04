#include "Date.hpp"
using namespace Lenyiin;

// 测试构造析构函数
void TestDate_1()
{
    // 默认无参构造
    Date d1;
    // 默认有参构造
    Date d2(2024, 9, 1);
    // 拷贝构造
    Date d3(d2);

    // 测试输出功能
    std::cout << "d1 为 " << d1 << std::endl;
    std::cout << "d2 为 " << d2 << std::endl;
    std::cout << "d3 为 " << d3 << std::endl;

    // 赋值拷贝
    d1 = d3;
    std::cout << "d1 为" << d1 << std::endl;

    // 测试闰年闰月
    Date d4(2008, 2, 29);
    std::cout << "d4 为" << d4 << std::endl;

    // 测试日期有效性
    Date d5(2007, 2, 29);
    std::cout << "d5 为" << d5 << std::endl;
}

// 测试日期比较
void TestDate_2()
{
    Date d1(2018, 3, 5);
    Date d2(2019, 6, 20);
    Date d3(d1);

    // 测试 <
    if (d1 < d2)
    {
        std::cout << d1 << " < " << d2 << std::endl;
    }
    if (d2 < d1)
    {
        std::cout << d2 << " < " << d1 << std::endl;
    }

    // 测试 ==    !=
    if (d1 == d3)
    {
        std::cout << d1 << " == " << d3 << std::endl;
    }
    else
    {
        std::cout << d1 << " != " << d3 << std::endl;
    }
    if (d1 == d2)
    {
        std::cout << d1 << " == " << d2 << std::endl;
    }
    else
    {
        std::cout << d1 << " != " << d2 << std::endl;
    }

    // 测试 <=
    if (d1 <= d2)
    {
        std::cout << d1 << " <= " << d2 << std::endl;
    }
    if (d2 <= d1)
    {
        std::cout << d2 << " <= " << d1 << std::endl;
    }

    // 测试 >
    if (d1 > d2)
    {
        std::cout << d1 << " > " << d2 << std::endl;
    }
    if (d2 > d1)
    {
        std::cout << d2 << " > " << d1 << std::endl;
    }

    // 测试 >=
    if (d1 >= d2)
    {
        std::cout << d1 << " >= " << d2 << std::endl;
    }
    if (d2 >= d1)
    {
        std::cout << d2 << " >= " << d1 << std::endl;
    }
}

// 测试日期增减
void TestDate_3()
{
    Date d1(2024, 9, 2);

    // 测试打印函数
    d1.Print();

    // +
    Date d2 = d1 + 100;
    // +=
    d1 += 100;
    d1.Print();
    d2.Print();

    // -
    d2 = d1 - 100;
    // -=
    d1 -= 100;
    d1.Print();
    d2.Print();

    // += 负数
    d2 = d1 + (-100);
    d1 += -100;
    d1.Print();
    d2.Print();

    // -= 负数
    d2 = d1 - (-100);
    d1 -= -100;
    d1.Print();
    d2.Print();
}

// 计算日期差
void TestDate_4()
{
    Date d1(2024, 9, 2);

    // 前置 ++    后置 ++
    Date d2 = ++d1;
    Date d3 = d1++;
    d1.Print();
    d2.Print();
    d3.Print();

    // 前置 --    后置 --
    d2 = --d1;
    d3 = d1--;
    d1.Print();
    d2.Print();
    d3.Print();

    // 日期差值
    Date d4 = d1 + 100;
    std::cout << d4 << " - " << d1 << " = " << d4 - d1 << std::endl;

    // 日期修改
    Date d5(2024, 9, 2);
    std::cout << "修改前的 d5 为" << d5 << std::endl;
    d5[0] = 2066, d5[1] = 6, d5[2] = 6;
    std::cout << "修改后的 d5 为" << d5 << std::endl;

    // 测试输入
    Date d6;
    std::cin >> d6;
    std::cout << "d6 为" << d6 << std::endl;
}

int main()
{
    // TestDate_1();

    // TestDate_2();

    // TestDate_3();

    TestDate_4();

    return 0;
}