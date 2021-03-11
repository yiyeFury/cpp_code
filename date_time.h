#pragma once

typedef struct {
	int year, month;
}YearMonth;

typedef struct { int year, yDays; }YearDays;

class Date
{
private:
	

public:
	// 构造函数
	Date();
	Date(int, int, int);
	// 运算符重载
	Date operator+ (Date);

	int year, month, day;

	// 成员函数
	void GetYear(int);  // 给数据成员赋值
	void GetMonth(int);
	void GetDay(int);

	int GetYear();  // 得到数据成员的值
	int GetMonth();
	int GetDay();

	int (*days_in_month())[12];

	void show_date();
	bool is_leap_year();
	int days_of_year();
	void add_month(int);
	void add_day(int);

	int YearDays();
	void DateFromYearDays(int, int);
	void DateAddDays(int);
};

// 用于计算日期的其它函数（非类成员函数）

YearMonth YearMonthAddMonth(YearMonth, int);
YearDays YearDaysAddDays(YearDays, int);

class Time
{
private:
	
public:
	Time(int, int, int);

	int hour, minute, second;

	void show_time();
	void add_hour(int);
	void add_minute(int);
	void add_second(int);
};

class DateTime : public Date, public Time
{
private:
public:
	DateTime(int, int, int, int, int, int);

	void show_date_time();
	void add_hour(int);
	void add_minute(int);
	void add_second(int);
};