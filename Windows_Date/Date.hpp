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