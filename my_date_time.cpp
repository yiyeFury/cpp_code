#include<iostream>

#include"my_date_time.h"

using namespace std;


// 构造函数
Date::Date() :year(2000), month(1), day(1) {}
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
	int(*mdays)[12] = DaysOfEachMonth();
	int tmp_days = 0;
	for (int ii = 0; ii < month - 1; ii++)  // 计算整月日数
		tmp_days += (*mdays)[ii];
	
	tmp_days += day;
	return tmp_days;
}

void Date::AddMonth(int m)
{
	int tmp_year = 0;

	tmp_year = m / 12;

	year += tmp_year;
    month += m-12*tmp_year;
    if (month > 12) {
        year++;
        month -= 12;
    }

}

void Date::AddDay(int d)
{
	int(*mdays)[12] = DaysOfEachMonth();
	for (day += d; day > (*mdays)[month - 1];) {
		day -= (*mdays)[month - 1];
		month++;
		if (month > 12) {
			month -= 12;
			year++;
			mdays = DaysOfEachMonth();
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
    if (sumDate.IsLeapYear()) monthDays[1] = 29;
    for (sumDate.day = day + date.day; sumDate.day > monthDays[sumDate.month - 1];)
    {
        for (sumDate.day -= monthDays[sumDate.month - 1], sumDate.month++; sumDate.month > 12;)
        {
            sumDate.month -= 12;
            sumDate.year++;
            if (sumDate.IsLeapYear()) monthDays[1] = 29;
            else monthDays[1] = 28;
        }

    }
    return sumDate;
}


// 非类成员函数
//YearMonth AddMonth(YearMonth yearMonth, int m)
//{
//	yearMonth.month += m;
//	if (yearMonth.month > 12) {
//		yearMonth.month -= 12;
//		yearMonth.year++;
//	}
//	return(yearMonth);
//}
//
//void Date::DateFromYearDays(int baseYear, int yearDays)  // 根据年和年积日，计算日期
//{
//	year = baseYear;
//	day = yearDays;
//
//	int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  // 一年中每个月的天数
//	if (IsLeapYear()) monthDays[1] = 29;  //若是闰年，2月有29天
//
//	for (month = 1; day > monthDays[month - 1]; )
//	{
//		day -= monthDays[month - 1];
//		month++;
//		if (month>12)
//		{
//			month -= 12, year++;
//			if (IsLeapYear()) monthDays[1] = 29;
//			else monthDays[1] = 28;
//		}
//	}
//}
//
//YearMonth YearMonthAddMonth(YearMonth yearMonth, int numMonth)
//{
//	yearMonth.month += numMonth;
//	if (yearMonth.month > 12)
//	{
//		yearMonth.month -= 12; yearMonth.year++;
//	}
//	return yearMonth;
//}
//
//YearDays YearDaysAddDays(YearDays yearDays, int days)
//{
//	int sumDaysOfYear = 0;
//	if ((yearDays.year % 4 == 0 && yearDays.yDays % 400 != 0) | yearDays.year % 400 == 0) sumDaysOfYear = 366;
//	else sumDaysOfYear = 365;
//
//	yearDays.yDays += days;
//	while (yearDays.yDays > sumDaysOfYear)
//	{
//		yearDays.yDays -= sumDaysOfYear;
//		yearDays.year++;
//		if ((yearDays.year % 4 == 0 && yearDays.yDays % 400 != 0) | yearDays.year % 400 == 0) sumDaysOfYear = 366;
//		else sumDaysOfYear = 365;
//	}
//	return yearDays;
//}


/*
class Time =============================================================================================================
*/
Time::Time(int h, int m, int sec): hour_(h), minute_(m), second_(sec) {}

void Time::ShowTime()
{
	cout << hour_ << ":" << minute_ << ":" << second_;
}

void Time::SetHour(int hour) {hour_=hour;}

void Time::SetMinute(int minute) {minute_=minute;}

void Time::SetSecond(int second) {second_=second;}

int Time::GetHour() {return hour_;}
int Time::GetMinute() {return minute_;}
int Time::GetSecond() {return hour_;}


void Time::AddHour(int h)
{
	hour_ += h;
	hour_ %= 24;
}

void Time::AddMinute(int minute)
{
	minute_ += minute;
	int tmp_h = minute_ / 60;
	minute_ %= 60;
    AddHour(tmp_h);
}

void Time::AddSecond(int s)
{
	second_ += s;
	int tmp_minute = second_ / 60;
	second_ %= 60;
    AddMinute(tmp_minute);
}

/*
DateTime ===============================================================================================================
*/
DateTime::DateTime(int year, int month, int day,
                   int hour, int minute, int second):
                   Date(year, month, day),
                   Time(hour, minute, second) {}

void DateTime::ShowDateTime()
{
	ShowDate();
	cout << " ";
    ShowTime();
    cout<<endl;
}

void DateTime::AddHour(int hour)
{
	hour_ += hour;
	int tmp_days = hour_ / 24;
	hour_ %= 24;
	AddDay(tmp_days);
}
