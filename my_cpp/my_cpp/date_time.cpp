#include<iostream>

#include"date_time.h"

using namespace std;


// 构造函数
Date::Date() :year(0), month(0), day(0) {}
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

int (*(Date::days_in_month(int y)))[12]
{
	static int tmp_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  // 一年中每个月的天数
	int(*days)[12] = &tmp_days;
	if (is_leap_year()) 
		(*days)[1] = 29;
	return days;
}

// 运算符重载
Date Date::operator+ (Date date)
{
	Date sumDate;
	int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  // 一年中每个月的天数

	sumDate.year = year + date.year;
	sumDate.month = month + date.month;

	for (; sumDate.month > 12; sumDate.year++) sumDate.month -= 12;
	if (sumDate.is_leap_year()) monthDays[1] = 29;
	for (sumDate.day = day + date.day; sumDate.day > monthDays[sumDate.month - 1];)
	{
		for (sumDate.day -= monthDays[sumDate.month - 1], sumDate.month++; sumDate.month > 12;)
		{
			sumDate.month -= 12;
			sumDate.year++;
			if (sumDate.is_leap_year()) monthDays[1] = 29;
			else monthDays[1] = 28;
		}

	}
	return sumDate;
}

// 给对象的数据成员的赋值
void Date::GetYear(int y)
{
	year = y;
}
void Date::GetMonth(int m)
{
	month = m;
}
void Date::GetDay(int d)
{
	day = d;
}

// 获取对象的数据成员的值
int Date::GetYear() { return year; }
int Date::GetMonth() { return month; }
int Date::GetDay() { return day; }


bool Date::is_leap_year()
{
	// 计算是否为闰年
	bool cond1, cond2;
	cond1 = (year % 4 == 0) && (year % 100 != 0);
	cond2 = year % 400 == 0;

	if (cond1 || cond2) 
		return true;
	else 
		return false;
}


void Date::ShowDate()  // 输出日期
{
	cout << year << " 年 " << month << " 月 " << day << "日" << endl;
}

int Date::YearDays()  // 计算年积日
{
	int yearDays = 0;
	int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  // 一年中每个月的天数
	if (is_leap_year()) monthDays[1] = 29;  //若是闰年，2月有29天
	for (int i = 0; i < month - 1; i++) {
		yearDays += monthDays[i];
	}

	yearDays += day;
	return(yearDays);
}

void Date::DateAddDays(int days)  // 当前日期加上天数，计算出新的日期
{
	int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  // 一年中每个月的天数
	if (is_leap_year()) monthDays[1] = 29;  //若是闰年，2月有29天

	for (day = day + days; day > monthDays[month - 1];)
	{
		day -= monthDays[month - 1];
		month++;
		if (month > 12)
		{
			month -= 12, year++;
			if (is_leap_year()) monthDays[1] = 29;
			else monthDays[1] = 28;
		}
	}
}

YearMonth AddMonth(YearMonth yearMonth, int m)
{
	yearMonth.month += m;
	if (yearMonth.month > 12) {
		yearMonth.month -= 12;
		yearMonth.year++;
	}
	return(yearMonth);
}

void Date::DateFromYearDays(int baseYear, int yearDays)  // 根据年和年积日，计算日期
{
	year = baseYear;
	day = yearDays;

	int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  // 一年中每个月的天数
	if (is_leap_year()) monthDays[1] = 29;  //若是闰年，2月有29天

	for (month = 1; day > monthDays[month - 1]; )
	{
		day -= monthDays[month - 1];
		month++;
		if (month>12)
		{
			month -= 12, year++;
			if (is_leap_year()) monthDays[1] = 29;
			else monthDays[1] = 28;
		}
	}
}

YearMonth YearMonthAddMonth(YearMonth yearMonth, int numMonth)
{
	yearMonth.month += numMonth;
	if (yearMonth.month > 12)
	{
		yearMonth.month -= 12; yearMonth.year++;
	}
	return yearMonth;
}

YearDays YearDaysAddDays(YearDays yearDays, int days)
{
	int sumDaysOfYear = 0;
	if ((yearDays.year % 4 == 0 && yearDays.yDays % 400 != 0) | yearDays.year % 400 == 0) sumDaysOfYear = 366;
	else sumDaysOfYear = 365;

	yearDays.yDays += days;
	while (yearDays.yDays > sumDaysOfYear)
	{
		yearDays.yDays -= sumDaysOfYear;
		yearDays.year++;
		if ((yearDays.year % 4 == 0 && yearDays.yDays % 400 != 0) | yearDays.year % 400 == 0) sumDaysOfYear = 366;
		else sumDaysOfYear = 365;
	}
	return yearDays;
}
