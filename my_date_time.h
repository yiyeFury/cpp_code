#pragma once

typedef struct {
	int year, month;
}YearMonth;

typedef struct { int year, yDays; }YearDays;

bool IsLeapYear(int);

class Date
{
private:
	

public:
	// 构造函数
	Date();
	Date(int, int, int);
	// 运算符重载
	Date operator+ (Date);

	int year_, month_, day_;

	// 成员函数
    void ShowDate();
	void SetYear(int);  // 给数据成员赋值
	void SetMonth(int);
	void SetDay(int);

	int GetYear();  // 得到数据成员的值
	int GetMonth();
	int GetDay();

	int (*DaysOfEachMonth())[12];
	int DaysOfYear();
	void AddMonth(int);
	void AddDay(int);

	void DateFromYearDays(int, int);
};

// 用于计算日期的其它函数（非类成员函数）
//YearMonth YearMonthAddMonth(YearMonth, int);
//YearDays YearDaysAddDays(YearDays, int);

class Time
{
private:
	
public:
	Time(int=0, int=0, int=0);

	int hour_, minute_, second_;

	void ShowTime();
    void SetHour(int);
    void SetMinute(int);
    void SetSecond(int);

	int GetHour();
	int GetMinute();
	int GetSecond();

	void AddHour(int);
	void AddMinute(int);
	void AddSecond(int);
};

class DateTime : public Date, public Time
{
private:
public:
	DateTime(int=2000, int=1, int=1, int=0, int=0, int=0);

	void ShowDateTime();
	void AddHour(int);
	void AddMinute(int);
	void AddSecond(int);

};