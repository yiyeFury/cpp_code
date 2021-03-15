#include<iostream>

#include"my_date_time.h"

using namespace std;


// 构造函数
Date::Date() :year(0), month(0), day(0) {}
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

// 显示 和 输入输出函数 ----------------------------------------------------------------------------------------------------
void Date::ShowDate()  // 输出日期
{
    cout << year << "-" << month << "-" << day;
}

// 给对象的数据成员的赋值
void Date::SetYear(int y) { year = y; }

void Date::SetMonth(int m) { month = m; }

void Date::SetDay(int d) { day = d; }

// 获取对象的数据成员的值
int Date::GetYear() { return year; }

int Date::GetMonth() { return month; }

int Date::GetDay() { return day; }

bool Date::IsLeapYear()
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

int (*(Date::DaysOfEachMonth()))[12]
{
    static int tmp_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // 一年中每个月的天数
    int (*days)[12] = &tmp_days;
	if (IsLeapYear())
		(*days)[1] = 29;
	return days;
}

int Date::DaysOfYear()
{
	// 计算年积日
	int(*mdays)[12] = days_in_month();
	int tmp_days = 0;
	for (int ii = 0; ii < month - 1; ii++)
		tmp_days += (*mdays)[ii];
	
	tmp_days += day;
	return tmp_days;
}


void Date::AddMonth(int m)
{
	int tmp_year = 0;
	month += m;
	tmp_year = month / 12;
	month %= 12;
	year += tmp_year;
}


void Date::AddDay(int d)
{
	int(*mdays)[12] = days_in_month();
	for (day += d; day > (*mdays)[month - 1];) {
		day -= (*mdays)[month - 1];
		month++;
		if (month > 12) {
			month -= 12;
			year++;
			mdays = days_in_month();
		}
	}
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


// 非类成员函数
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


/*
class Time =============================================================================================================
*/
Time::Time(int h=0, int m=0, int sec=0): hour(h), minute(m), second(sec) {}

void Time::show_time()
{
	cout << hour << ":" << minute << ":" << second;
}

void Time::add_hour(int h)
{
	hour += h;
	hour %= 24;
}

void Time::add_minute(int m)
{
	minute += m;
	int tmp_h = minute / 60;
	minute %= 60;
	add_hour(tmp_h);
}

void Time::add_second(int s)
{
	second += s;
	int tmp_minute = second / 60;
	second %= 60;
	add_minute(tmp_minute);
}

/*
DateTime ===============================================================================================================
*/
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second): Date(year, month, day), Time(hour, minute, second) {}

void DateTime::show_date_time()
{
	show_date();
	cout << " ";
	show_time();
}

void DateTime::add_hour(int h)
{
	hour += h;
	int tmp_days = hour / 24;
	hour %= 24;
	add_day(tmp_days);
}

void DateTime::add_minute(int m)
{
	minute += m;
	int tmp_h = minute / 60;
	minute %= 60;
	add_hour(tmp_h);
}

void DateTime::add_second(int s)
{
	second += s;
	int tmp_minute = second / 60;
	second %= 60;
	add_minute(tmp_minute);
}
