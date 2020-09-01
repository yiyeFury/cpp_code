#pragma once

typedef struct {
	int year, month;
}YearMonth;

typedef struct { int year, yDays; }YearDays;

class Date
{
private:
	int year, month, day;

public:
	// 构造函数
	Date();
	Date(int, int, int);
	// 运算符重载
	Date operator+ (Date);

	// 成员函数
	void GetYear(int);  // 给数据成员赋值
	void GetMonth(int);
	void GetDay(int);

	int GetYear();  // 得到数据成员的值
	int GetMonth();
	int GetDay();

	int (*days_in_month(int))[12];

	void ShowDate();
	bool is_leap_year();
	int YearDays();
	void DateFromYearDays(int, int);
	void DateAddDays(int);
};

// 用于计算日期的其它函数（非类成员函数）

YearMonth YearMonthAddMonth(YearMonth, int);
YearDays YearDaysAddDays(YearDays, int);
