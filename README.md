# 实现一个功能完备的 C++ Date 类详细指南，带你一次性搞定所有关于日期类编程题

​																	--- All rights by auther Lenyiin



在这个项目中，我们将详细探讨如何实现一个功能完备的 `C++ Date` 类，用一个类解决 `nowcoder` 上所有关于日期类的程序题。该项目将覆盖从类的基本结构、日期验证、日期比较、日期增减、日期差计算等各个方面。我们将逐步构建一个功能强大的 `Date` 类，并深入解释每个步骤的实现细节。该项目的目标是让初学者能够清晰理解和实现一个实用的日期类，并通过题目需要自定义裁切解题。

如果你是老鸟，想直接看代码，请直接翻看 [第七章](#7、完整示例代码和测试) ，如果你想翻看关于日期类的题解，请直接翻看 [第八章](#8、日期类相关程序题的速刷) 。

# 目录

1. [Date类的基础结构](#1、date类的基础结构)
2. [日期有效性验证](#2、日期有效性验证)
3. [日期比较功能](#3、日期比较功能)
4. [日期增减操作](#4、日期增减操作)
5. [计算日期差](#5、计算日期差)
6. [日期的输入和输出和修改](#6、日期的输入和输出和修改)
7. [完整示例代码和测试](#7、完整示例代码和测试)
8. [日期类相关程序题的速刷](#8、日期类相关程序题的速刷)
9. [总结与心得](#9、总结与心得)





# 1、Date类的基础结构

在 C++  中，类是用来封装数据和相关操作的一种方式。一个 `Date` 类通常包括年、月、日三个基本成员变量。我们首先定义一个最基本的 `Date` 类。

## 1.1、基本类定义

```
#include <iostream>

class Date {
public:
    // 构造函数
    Date(int year = 2024, int month = 1, int day = 1)
    	: _year(year), _month(month), _day(day)
    {
    }
    
    // 拷贝构造
    Date(const Date& d)
        : _year(d._year), _month(d._month), _day(d._day)
    {
    }
    
    // 赋值运算符重载
    // d1.operator=(d2);
    Date& operator=(const Date& d)	// Date& operator=(Date* this, const Date& d)
    {
        if (*this != d)
        {
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }
        return *this;
    }

    // 打印日期
    void Print()
    {
        std::cout << _year << "-" << _month << "-" << _day << std::endl;
    }
    
    // 析构函数
    ~Date()
    {
        std::cout << "~Date()" << std::endl;
    }
    
private:
    int _year;  // 年
    int _month; // 月
    int _day;   // 日
};
```

**解释：**

- **数据成员**：`_year`, `_month`, `_day` 是存储年、月、日的私有数据成员。将这些成员设为 `private` 是为了封装性，防止外部直接修改。
- **构造函数**：`Date(int year = 2024, int month = 1, int day = 1)` 是一个构造函数，并设置了默认初始时间，用于初始化 `Date` 对象。初始化列表 ` : _year(year), _month(month), _day(day)` 直接将传入的参数赋给成员变量。
- **打印函数**：`Print()` 是一个公有成员函数，用于输出日期。这里我们使用 `std::cout` 打印日期，格式为 "YYYY-MM-DD"。

## 1.2、构造函数的参数验证

在构造函数中，我们可以增加对传入参数的验证，以确保创建的日期是有效的。效性检查将会在后续部分中详细讨论。



# 2、日期有效性验证

日期的有效性检查是 `Date` 类的重要功能之一。有效性检查确保日期在合理范围内，比如检查月份是否在 1 到 12 之间，日期是否符合相应的月份和年份。

## 2.1、闰年判断

```
// 判断是否为闰年
bool isLeapYear(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
```

**解释：**

- `isLeapYear()`：这个私有成员函数用于判断一个年份是否为闰年。闰年的规则是：四年一闰，百年不闰，四百年再闰。这个函数帮助我们在处理日期时正确考虑闰年。



## 2.2、任意月份的天数获取

```
int GetMonthDay(int year, int month)
{
	static int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day = monthArray[month];

	// 判断是否是闰年闰月
	if (month == 2 && isLeapYear(year))
	{
		day = 29;
	}

	return day;
}
```

**解释：**

- `GetMonthDay()`：这个私有成员函数用于返回给定的年、月的实际天数。



## 2.3、日期验证

```
// 验证日期的有效性
bool isValidDate(int year, int month, int day)
{
	// 月份必须在 1 到 12 之间
	if (month < 1 || month > 12)
	{
		return false;
	}

	// 日期必须在 1 到 当月最大天数 之间
	return day >= 1 && day <= GetMonthDay(year, month);
}
```

**解释：**

- 函数首先检查月份是否在 1 到 12 之间，然后根据月份和年份的不同天数限制进行检查。若日期无效，返回 `false`，否则返回 `true`。



## 2.4、修改构造函数以包含验证

```
// 构造函数
Date(int year = 2024, int month = 1, int day = 1)
{
	if (!isValidDate(year, month, day))
	{
		std::cerr << "Invalid date!" << std::endl;
		exit(1);	// 终止程序, 日期无效
	}

	_year = year;
	_month = month;
	_day = day;
}
```

**解释：**

- **构造函数**：在构造函数中，我们调用 `isValidDate()` 函数验证日期的有效性。如果日期无效，则输出错误信息并终止程序。这样可以确保 `Date` 对象在创建时总是有效的。



# 3、日期比较功能

为了方便地比较两个日期，我们需要重载比较运算符，如 `==`、`<`、`>` 等。这样可以使我们使用标准运算符进行日期比较。自定义类型传参数和返回值时，在可以的情况下，尽量使用引用，减少拷贝的开销。

## 3.1、重载 == 运算符

```
// d1.operator==(d2);
bool operator==(const Date& d) const	// bool operator==(Date* this, const Date& d) const
{
	if (this->_year == d._year && this->_month == d._month && this->_day == d._day)
	{
		return true;
	}
	return false;
}
```

**解释：**

- **operator==()**：这个成员函数重载了 `==` 运算符，使得我们可以直接比较两个 `Date` 对象是否相等。两个日期相等的条件是年、月、日都相等。



## 3.2、重载 < 运算符

```
// d1.operator<(&d2);
bool operator<(const Date& d) const	// bool operator<(Date* this, const Date& d) const
{
	if (this->_year < d._year)
	{
		return true;
	}
	else if (this->_year == d._year && this->_month < d._month)
	{
		return true;
	}
	else if (this->_year == d._year && this->_month == d._month && this->_day < d._day)
	{
		return true;
	}
	return false;
}
```

**解释：**

- **operator<()**：这个成员函数重载了 `<` 运算符，使得我们可以判断一个 `Date` 对象是否早于另一个 `Date` 对象。比较过程首先按年份比较，如果年份相同则按月份比较，最后按日期比较。



## 3.3、重载 <= 运算符

```
// d1 <= d2
// d1.operator<=(&d2);
bool operator<=(const Date& d) const // bool operator<=(Date* this, const Date& d) const
{
	return (*this < d) || (*this == d); // 代码复用
}
```



## 3.4、重载 > 运算符

```
// d1.operator>(d2);
bool operator>(const Date& d) const	// bool operator>(Date* this, const Date& d) const
{
	return d < *this;	// 代码复用
}
```



## 3.5、重载 >= 运算符

```
// d1 >= d2
// d1.operator>=(&d2);
bool operator>=(const Date& d) const	// bool operator>=(Date* this, const Date& d) const
{
	return !(*this < d); // 代码复用
}
```



## 3.6、重载 != 运算符

```
// d1 != d2
// d1.operator!=(&d2);
bool operator!=(const Date& d) const	// bool operator!=(Date* this, const Date& d) const
{
	return !(*this == d); // 代码复用
}
```



# 4、日期增减操作

日期增减操作是处理日期时非常重要的功能。我们可以通过实现日期的加减功能来支持日期的各种操作。

## 4.1、重载 += 运算符

```
// d1.operator+=(int);
Date& operator+=(int day)	// Date& operator+=(Date* this, int day)
{
	if (day < 0)
	{
		return *this -= -day;
	}

	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		// 如果日期不合法，就要往月进位
		_day -= GetMonthDay(_year, _month);
		_month++;

		// 如果月不合法，就要往年进位
		if (_month > 12)
		{
			_year++;
			_month = 1;
		}
	}

	return *this;
}
```

**解释：**

- `operator+=(int)`：这个运算符重载函数将当前日期增加指定天数。如果增加天数后日期无效（即超出了当前月份的最大天数），则调整日期到下一个月。如果月份超出12，则调整到下一年。



## 4.2、重载 + 运算符

```
// d1.operator+(int);
Date operator+(int day)	// Date operator+(Date* this, int day)
{
	Date ret(*this);	// Date ret(this->_year, this->_month, this->_day);
	return ret += day;
}
```

**解释：**

- 复用 `+=` 重载运算符



## 4.3、重载 -= 运算符

```
// d1.operator-=(int);
Date& operator-=(int day) // Date& operator-=(Date* this, int day)
{
	if (day < 0)
	{
		return *this += -day;
	}

	_day -= day;
	while (_day < 1)
	{
		// 如果日期不合法, 就要往月退位, 月不合法就要往年退位
		_month--;
		if (_month == 0)
		{
			_year--;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}

	return *this;
}
```

**解释：**

- `operator-=(int)`：这个运算符重载函数将当前日期减少指定天数。如果增加天数后日期无效（即小于1），则调整日期到上一个月。如果月份小于1，则调整到上一年。



## 4.4、重载 - 运算符

```
// d1.operator-(int);
Date operator-(int day) // Date operator-(Date* this, int day)
{
	Date ret(*this);
	return ret -= day;
}
```

**解释：**

- 复用 `-=` 重载运算符



# 5、计算日期差

计算两个日期之间的天数差可以帮助我们进行日期间的时间差分析。

## 5.1、重载 ++ 运算符 

```
// d1.operator++();	// 前置++
Date& operator++()	// Date& operator++(Date* this)
{
	*this += 1;
	return *this;	// 返回加之后的结果
}
```



## 5.2、重载 ++(int) 运算符

```
// d1.operator++(int);	// 后置++
Date operator++(int) 	// Date operator++(Date* this, int)
{
	Date ret(*this);
	*this += 1;
	return ret;			// 返回加之前的结果
}
```



## 5.3、重载 -- 运算符

```
// d1.operator--();	// 前置--
Date& operator--() 	// Date& operator--(Date* this)
{
	*this -= 1;
	return *this;
}
```



## 5.4、重载 --(int) 运算符

```
// d1.operator--(int);	// 后置--
Date operator--(int) 	// Date operator--(Date* this, int)
{
	Date ret(*this);
	*this -= 1;
	return ret;
}
```



## 5.5、计算日期差实现

```
// d1.operator-(d2);
int operator-(const Date& d)	// int operator-(Date* this, const Date& d)
{
	Date max = *this;
	Date min = d;
	int flag = 1;

	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}

	int count = 0;
	while (min != max)
	{
		++min;
		count++;
	}

	return count * flag;
}
```



# 6、日期的输入和输出和修改

为了方便用户输入、输出和修改日期，我们需要重载输入流运算符 `>>` 、输出流运算符 `<<` 以及 下标运算符 `[]` 。这将使得 `Date` 类能够与标准输入输出流兼容，并且能自由修改日期。

## 6.1、重载输入流运算符 >>

```
std::istream& operator>>(std::istream& _cin, Date& d)
{
	_cin >> d._year >> d._month >> d._day;
	return _cin;
}
```



## 6.2、重载输出流运算符 <<

```
std::ostream& operator<<(std::ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}
```



## 6.3、重载下标运算符 []

```
// d1.operator[](int);
int& operator[](int index) // int& operator[](Date* this, int index)
{
	if (index == 0)
	{
		return _year;
	}
	else if (index == 1)
	{
		return _month;
	}
	else if (index == 2)
	{
		return _day;
	}
}
```



# 7、完整示例代码和测试

在这个部分，我们将整合所有功能，提供一个完整的 `Date` 类实现，并展示如何进行测试。

## 7.1、完整的 Date 类代码

> 新建头文件 `Date.hpp`

```
#pragma once

#include <iostream>

namespace Lenyiin
{
	class Date
	{
	private:
		friend std::ostream& operator<<(std::ostream& _cout, const Date& d);
		friend std::istream& operator>>(std::istream& _cin, Date& d);

		// 判断是否为闰年
		bool isLeapYear(int year) const
		{
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		// 获取任意月份的天数
		int GetMonthDay(int year, int month)
		{
			static int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			int day = monthArray[month];

			// 判断是否是闰年闰月
			if (month == 2 && isLeapYear(year))
			{
				day = 29;
			}

			return day;
		}

		// 验证日期的有效性
		bool isValidDate(int year, int month, int day)
		{
			// 月份必须在 1 到 12 之间
			if (month < 1 || month > 12)
			{
				return false;
			}

			// 日期必须在 1 到 当月最大天数 之间
			return day >= 1 && day <= GetMonthDay(year, month);
		}

	public:
		// 构造函数
		Date(int year = 2024, int month = 1, int day = 1)
		{
			if (!isValidDate(year, month, day))
			{
				std::cerr << "Invalid date!" << std::endl;
				exit(1);	// 终止程序, 日期无效
			}

			_year = year;
			_month = month;
			_day = day;
		}

		// 拷贝构造
		Date(const Date& d)
			: _year(d._year), _month(d._month), _day(d._day)
		{

		}

		void Print()
		{
			std::cout << _year << "-" << _month << "-" << _day << std::endl;
		}

		// 赋值运算符重载
		// 运算符重载，是为了让自定义类型可以像内置类型一样去使用运算符
		// 自定义类型传参数和返回值时，在可以的情况下，尽量使用引用，减少拷贝的开销
		// d1.operator==(d2);
		bool operator==(const Date& d) const	// bool operator==(Date* this, const Date& d) const
		{
			if (this->_year == d._year && this->_month == d._month && this->_day == d._day)
			{
				return true;
			}
			return false;
		}

		// d1.operator<(&d2);
		bool operator<(const Date& d) const	// bool operator<(Date* this, const Date& d) const
		{
			if (this->_year < d._year)
			{
				return true;
			}
			else if (this->_year == d._year && this->_month < d._month)
			{
				return true;
			}
			else if (this->_year == d._year && this->_month == d._month && this->_day < d._day)
			{
				return true;
			}
			return false;
		}

		// d1 <= d2
		// d1.operator<=(&d2);
		bool operator<=(const Date& d) const // bool operator<=(Date* this, const Date& d) const
		{
			return (*this < d) || (*this == d); // 代码复用
		}

		// d1.operator>(d2);
		bool operator>(const Date& d) const	// bool operator>(Date* this, const Date& d) const
		{
			return d < *this;	// 代码复用
		}

		// d1 >= d2
		// d1.operator>=(&d2);
		bool operator>=(const Date& d) const // bool operator>=(Date* this, const Date& d) const
		{
			return !(*this < d); // 代码复用
		}

		// d1 != d2
		// d1.operator!=(&d2);
		bool operator!=(const Date& d) const // bool operator!=(Date* this, const Date& d) const
		{
			return !(*this == d); // 代码复用
		}

		// d1.operator=(d2);
		Date& operator=(const Date& d) // Date& operator=(Date* this, const Date& d)
		{
			if (*this != d)
			{
				_year = d._year;
				_month = d._month;
				_day = d._day;
			}
			return *this;
		}

		// d1.operator+=(int);
		Date& operator+=(int day)	// Date& operator+=(Date* this, int day)
		{
			if (day < 0)
			{
				return *this -= -day;
			}

			_day += day;
			while (_day > GetMonthDay(_year, _month))
			{
				// 如果日期不合法，就要往月进位
				_day -= GetMonthDay(_year, _month);
				_month++;

				// 如果月不合法，就要往年进位
				if (_month > 12)
				{
					_year++;
					_month = 1;
				}
			}

			return *this;
		}

		// d1.operator+(int);
		Date operator+(int day)	// Date operator+(Date* this, int day)
		{
			Date ret(*this);	// Date ret(this->_year, this->_month, this->_day);
			return ret += day;
		}

		// d1.operator-=(int);
		Date& operator-=(int day) // Date& operator-=(Date* this, int day)
		{
			if (day < 0)
			{
				return *this += -day;
			}

			_day -= day;
			while (_day < 1)
			{
				// 如果日期不合法, 就要往月退位, 月不合法就要往年退位
				_month--;
				if (_month == 0)
				{
					_year--;
					_month = 12;
				}
				_day += GetMonthDay(_year, _month);
			}

			return *this;
		}

		// d1.operator-(int);
		Date operator-(int day) // Date operator-(Date* this, int day)
		{
			Date ret(*this);
			return ret -= day;
		}

		// d1.operator++();	// 前置++
		Date& operator++()	// Date& operator++(Date* this)
		{
			*this += 1;
			return *this;	// 返回加之后的结果
		}

		// d1.operator++(int);	// 后置++
		Date operator++(int) 	// Date operator++(Date* this, int)
		{
			Date ret(*this);
			*this += 1;
			return ret;			// 返回加之前的结果
		}

		// d1.operator--();	// 前置--
		Date& operator--() 	// Date& operator--(Date* this)
		{
			*this -= 1;
			return *this;
		}

		// d1.operator--(int);	// 后置--
		Date operator--(int) 	// Date operator--(Date* this, int)
		{
			Date ret(*this);
			*this -= 1;
			return ret;
		}

		// d1.operator-(d2);
		int operator-(const Date& d)	// int operator-(Date* this, const Date& d)
		{
			Date max = *this;
			Date min = d;
			int flag = 1;

			if (*this < d)
			{
				max = d;
				min = *this;
				flag = -1;
			}

			int count = 0;
			while (min != max)
			{
				++min;
				count++;
			}

			return count * flag;
		}

		// d1.operator[](int);
		int& operator[](int index) // int& operator[](Date* this, int index)
		{
			if (index == 0)
			{
				return _year;
			}
			else if (index == 1)
			{
				return _month;
			}
			else if (index == 2)
			{
				return _day;
			}
		}

		// 析构函数
		~Date()
		{
			std::cout << "~Date()" << std::endl;
		}

	private:
		int _year;
		int _month;
		int _day;
	};

	std::ostream& operator<<(std::ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}

	std::istream& operator>>(std::istream& _cin, Date& d)
	{
		_cin >> d._year >> d._month >> d._day;
		return _cin;
	}
}
```



## 7.2、测试代码

> 新建源文件 Date.cpp

```
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

    //测试 >=
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
    //TestDate_1();

    //TestDate_2();

    //TestDate_3();

    TestDate_4();

    return 0;
}
```



# 8、日期类相关程序题的速刷

## 8.1、计算日期到天数转换

### 8.1.1、[题目描述](https://www.nowcoder.com/practice/769d45d455fe40b385ba32f97e7bcded?tpId=37&tqId=21296&ru=/exam/oj)

```
描述：
	根据输入的日期，计算是这一年的第几天。
    保证年份为4位数且日期合法。
    进阶：时间复杂度：O(n) ，空间复杂度：O(1)
输入描述：
	输入一行，每行空格分割，分别是年，月，日
输出描述
	输出是这一年的第几天
```

### 8.1.2、示例

```
输入：2012 12 31
输出：366
```

### 8.1.3、题解

```
#include <iostream>
using namespace std;

class Date {
private:
    friend std::istream& operator>>(std::istream& _cin, Date& d);

    // 判断是否为闰年
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // 获取任意月份的天数
    int GetMonthDay(int year, int month) {
        static int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int day = monthArray[month];

        // 判断是否是闰年闰月
        if (month == 2 && isLeapYear(year)) {
            day = 29;
        }

        return day;
    }

public:
    // 构造函数
    Date(int year, int month, int day) {
        _year = year;
        _month = month;
        _day = day;
    }

    bool operator!=(const Date& d) const {
        if (this->_year == d._year && this->_month == d._month && this->_day == d._day) {
            return false;
        }
        return true;
    }

    Date& operator+=(int day) { // Date& operator+=(Date* this, int day)
        _day += day;
        while (_day > GetMonthDay(_year, _month)) {
            // 如果日期不合法，就要往月进位
            _day -= GetMonthDay(_year, _month);
            _month++;

            // 如果月不合法，就要往年进位
            if (_month > 12) {
                _year++;
                _month = 1;
            }
        }

        return *this;
    }

    int operator-(const Date& d) {
        Date max = *this;
        Date min = d;
        int flag = 1;

        int count = 0;
        while (min != max) {
            min += 1;
            count++;
        }

        return count * flag;
    }

private:
    int _year;
    int _month;
    int _day;
};

istream& operator>>(istream& _cin, Date& d) {
    _cin >> d._year >> d._month >> d._day;
    return _cin;
}

int main() {
    int year, month, day;

    while (cin >> year >> month >> day) {
        Date d1(year, month, day);
        Date d2(year, 1, 0);
        cout << d1 - d2;
    }

    return 0;
}
```



## 8.2、日期差值

### 8.2.1、[题目描述](https://www.nowcoder.com/practice/ccb7383c76fc48d2bbc27a2a6319631c?tpId=62&&tqId=29468&rp=1&ru=/activity/oj&qru=/ta/sju-kaoyan/question-ranking)

```
描述：
	有两个日期，求两个日期之间的天数，如果两个日期是连续的，我们规定他们之间的天数为两天
输入描述：
	有多组数据，每组数据有两行，分别表示两个日期，形式为YYYYMMDD
输出描述：
	每组数据输出一行，即日期差值
```

### 8.2.2、示例

```
输入：20110412
	 20110422
输出：11
```

### 8.2.3、题解

```
#include <iostream>
#include <cstring>
using namespace std;

class Date {
public:
    // 判断是否为闰年
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // 获取任意月份的天数
    int GetMonthDay(int year, int month) {
        static int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int day = monthArray[month];

        // 判断是否是闰年闰月
        if (month == 2 && isLeapYear(year)) {
            day = 29;
        }

        return day;
    }

    Date(int year, int month, int day)
        : _year(year)
        , _month(month)
        , _day(day)
    {}

    bool operator<(const Date& d) const {
        if (this->_year < d._year) {
            return true;
        } else if (this->_year == d._year && this->_month < d._month) {
            return true;
        } else if (this->_year == d._year && this->_month == d._month &&
                   this->_day < d._day) {
            return true;
        }
        return false;
    }

    bool operator!=(const Date& d) {
        if (this->_year != d._year || this->_month != d._month ||
                this->_day != d._day) return true;
        else return false;
    }

    Date& operator+=(int day) {
        _day += day;
        while (_day > GetMonthDay(_year, _month)) {
            // 如果日期不合法，就要往月进位
            _day -= GetMonthDay(_year, _month);
            ++_month;
            // 如果月不合法，就要往年进位
            if (_month > 12) {
                ++_year;
                _month = 1;
            }
        }
        return *this;
    }

    int operator-(const Date& d) {
        Date max = *this;
        Date min = d;
        if (*this < d) {
            max = d;
            min = *this;
        }
        int count = 1;
        while (min != max) {
            min += 1;
            ++count;
        }
        return count;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main() {
    int year, month, day;

    scanf("%4d%2d%2d", &year, &month, &day);
    Date d1(year, month, day);
    scanf("%4d%2d%2d", &year, &month, &day);
    Date d2(year, month, day);

    cout << d1 - d2 << endl;

    return 0;
}
```



## 8.3、打印日期

### 8.3.1、[题目描述](https://www.nowcoder.com/practice/b1f7a77416194fd3abd63737cdfcf82b?tpId=69&&tqId=29669&rp=1&ru=/activity/oj&qru=/ta/hust-kaoyan/question-ranking)

```
描述：
	给出年份 m 和一年中的第 n 天，算出第 n 天是几月几号
输入描述：
	输入包括两个整数 y(1<=y<=3000) , n(1<=n<=366)
输出描述：
	可能有多组测试数据，对于每组数据， 按 yyyy-mm-dd的格式将输入中对应的日期打印出来
```

### 8.3.2、示例

```
输入：
    2000 3
    2000 31
    2000 40
    2000 60
    2000 61
    2001 60
输出：
    2000-01-03
    2000-01-31
    2000-02-09
    2000-02-29
    2000-03-01
    2001-03-01
```

### 8.3.3、题解

```
#include <iostream>
using namespace std;

class Date {
public:
    // 判断是否为闰年
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

// 获取任意月份的天数
    int GetMonthDay(int year, int month) {
        static int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int day = monthArray[month];

        // 判断是否是闰年闰月
        if (month == 2 && isLeapYear(year)) {
            day = 29;
        }

        return day;
    }

    // 构造函数
    Date(int year, int month = 1, int day = 0)
        : _year(year)
        , _month(month)
        , _day(day)
    {}

    void Print() {
        printf("%04d-%02d-%02d", _year, _month, _day);
    }

    Date& operator+=(int day) {
        _day += day;
        while (_day > GetMonthDay(_year, _month)) {
            // 如果日期不合法，就要往月进位
            _day -= GetMonthDay(_year, _month);
            ++_month;

            // 如果月不合法，就要往年进位
            if (_month > 12) {
                ++_year;
                _month = 1;
            }
        }
        return *this;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main() {
    int year, day;
    while (cin >> year >> day) {
        Date d(year);
        d += day;
        d.Print();
    }

    return 0;
}
```



## 8.4、日期累加

### 8.4.1、[题目描述](https://www.nowcoder.com/practice/eebb2983b7bf40408a1360efb33f9e5d?tpId=40&&tqId=31013&rp=1&ru=/activity/oj&qru=/ta/kaoyan/question-ranking)

```
描述：
	设计一个程序能计算一个日期加上若干天后是什么日期。
输入描述：
	输入第一行表示样例个数 m , 接下来 m 行每行四个整数分别表示年月日和累加的天数。
输出描述：
	输出 m 行, 每行按 yyyy-mm-dd 的个数输出。
```

### 8.4.2、示例

```
输入：
    1
    2008 2 3 100
输出：
	2008-05-13
```

### 8.4.3、题解

```
#include <iostream>
using namespace std;

class Date {
public:
    // 判断是否为闰年
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // 获取任意月份的天数
    int GetMonthDay(int year, int month) {
        static int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int day = monthArray[month];

        // 判断是否是闰年闰月
        if (month == 2 && isLeapYear(year)) {
            day = 29;
        }

        return day;
    }

    // 构造函数
    Date(int year, int month, int day)
        : _year(year), _month(month), _day(day)
    {}

    void Print() {
        printf("%04d-%02d-%02d\n", _year, _month, _day);
    }

    Date& operator+=(int day) {
        _day += day;
        while (_day > GetMonthDay(_year, _month)) {
            // 如果日期不合法，就要往月进位
            _day -= GetMonthDay(_year, _month);
            _month++;
            // 如果月不合法，就要往年进位
            if (_month > 12) {
                _year++;
                _month = 1;
            }
        }
        return *this;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main() {
    int count = 0;
    cin >> count;

    while (count--) {
        int year, month, day;
        int gap;
        cin >> year >> month >> day >> gap;

        Date d(year, month, day);
        d += gap;
        d.Print();
    }

    return 0;
}
```



# 9、总结与心得

通过实现一个功能完备的 `Date` 类，我们掌握了以下技能：

1. **类的设计与封装**：学会了如何将数据和相关操作封装到类中，确保数据的安全和完整性。
2. **日期有效性验证**：了解了如何检查日期的有效性，包括闰年和月份天数的处理。
3. **运算符重载**：学会了如何重载比较运算符，使得日期对象可以使用标准运算符进行比较。
4. **日期操作**：掌握了如何进行日期的增减操作，计算日期差等实用功能。
5. **输入输出流重载**：能够实现自定义的输入输出功能，使得 `Date` 类的使用更加方便。
6. **自定义裁切**：学会了如何在题目要求上进行自定义裁切，以满足题目的需求。



希望这个项目对您有所帮助，也欢迎您在此基础上进行更多的探索和改进。如果您有任何问题或建议，欢迎在评论区留言，我们可以共同探讨和学习。更多知识分享可以访问我的个人博客网站 https://blog.lenyiin.com/