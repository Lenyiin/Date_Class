#pragma once

#include <iostream>

namespace Lenyiin
{
	class Date
	{
	private:
		friend std::ostream& operator<<(std::ostream& _cout, const Date& d);
		friend std::istream& operator>>(std::istream& _cin, Date& d);

		// �ж��Ƿ�Ϊ����
		bool isLeapYear(int year) const
		{
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		// ��ȡ�����·ݵ�����
		int GetMonthDay(int year, int month)
		{
			static int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			int day = monthArray[month];

			// �ж��Ƿ�����������
			if (month == 2 && isLeapYear(year))
			{
				day = 29;
			}

			return day;
		}

		// ��֤���ڵ���Ч��
		bool isValidDate(int year, int month, int day)
		{
			// �·ݱ����� 1 �� 12 ֮��
			if (month < 1 || month > 12)
			{
				return false;
			}

			// ���ڱ����� 1 �� ����������� ֮��
			return day >= 1 && day <= GetMonthDay(year, month);
		}

	public:
		// ���캯��
		Date(int year = 2024, int month = 1, int day = 1)
		{
			if (!isValidDate(year, month, day))
			{
				std::cerr << "Invalid date!" << std::endl;
				exit(1);	// ��ֹ����, ������Ч
			}

			_year = year;
			_month = month;
			_day = day;
		}

		// ��������
		Date(const Date& d)
			: _year(d._year), _month(d._month), _day(d._day)
		{

		}

		void Print()
		{
			std::cout << _year << "-" << _month << "-" << _day << std::endl;
		}

		// ��ֵ���������
		// ��������أ���Ϊ�����Զ������Ϳ�������������һ��ȥʹ�������
		// �Զ������ʹ������ͷ���ֵʱ���ڿ��Ե�����£�����ʹ�����ã����ٿ����Ŀ���
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
			return (*this < d) || (*this == d); // ���븴��
		}

		// d1.operator>(d2);
		bool operator>(const Date& d) const	// bool operator>(Date* this, const Date& d) const
		{
			return d < *this;	// ���븴��
		}

		// d1 >= d2
		// d1.operator>=(&d2);
		bool operator>=(const Date& d) const // bool operator>=(Date* this, const Date& d) const
		{
			return !(*this < d); // ���븴��
		}

		// d1 != d2
		// d1.operator!=(&d2);
		bool operator!=(const Date& d) const // bool operator!=(Date* this, const Date& d) const
		{
			return !(*this == d); // ���븴��
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
				// ������ڲ��Ϸ�����Ҫ���½�λ
				_day -= GetMonthDay(_year, _month);
				_month++;

				// ����²��Ϸ�����Ҫ�����λ
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
				// ������ڲ��Ϸ�, ��Ҫ������λ, �²��Ϸ���Ҫ������λ
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

		// d1.operator++();	// ǰ��++
		Date& operator++()	// Date& operator++(Date* this)
		{
			*this += 1;
			return *this;	// ���ؼ�֮��Ľ��
		}

		// d1.operator++(int);	// ����++
		Date operator++(int) 	// Date operator++(Date* this, int)
		{
			Date ret(*this);
			*this += 1;
			return ret;			// ���ؼ�֮ǰ�Ľ��
		}

		// d1.operator--();	// ǰ��--
		Date& operator--() 	// Date& operator--(Date* this)
		{
			*this -= 1;
			return *this;
		}

		// d1.operator--(int);	// ����--
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

		// ��������
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