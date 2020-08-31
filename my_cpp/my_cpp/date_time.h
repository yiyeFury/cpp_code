#pragma once

typedef struct {
	int year, month;
}YearMonth;

typedef struct { int year, yDays; }YearDays;

class Date
{
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

	void ShowDate();
	int IsLeapYear();
	int YearDays();
	void DateFromYearDays(int, int);
	void DateAddDays(int);

private:
	int year, month, day;
};

// 用于计算日期的其它函数（非类成员函数）

YearMonth YearMonthAddMonth(YearMonth, int);
YearDays YearDaysAddDays(YearDays, int);
