#include "lunar.h"

//Lunar dates
/*
  bit23 bit22 bit21 bit20:means the leap month this year
              while 0 means there is no leap month this year
  bit19 bit18 bit17 bit16 bit15 bit14 bit13 bit12 bit11 bit10 bit9 bit8 bit7
  1     2     3     4     5     6     7     8     9     10    11   12   13
  the amount of this month while 1 means 30 days and 0 means 29 days
  bit6 bit5                         bit4 bit3 bit2 bit1 bit0
  solor month of Spring Fesital   solor dates of Spring Festival
*/
unsigned int lunar200y[199] = {
  0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/
  0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/
  0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/
  0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/
  0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/
  0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/
  0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/
  0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/
  0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB,/*1981-1990*/
  0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/
  0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/
  0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/
  0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/
  0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/
  0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/
  0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/
  0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/
  0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/
  0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/
  0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/
};

const int MonthsCount[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

int Lunar::getLunarMonthDays(int _year, int _monthIndex) {
	if ((lunar200y[_year - 1901] & (0x080000 >> (_monthIndex - 1))) == 0)
		return 29;
	else
		return 30;
}

Lunar::Lunar() {
	syear = 0;
	smonth = 0;
	sdate = 0;
	year = 0;
	month = 0;
	date = 0;
}

Lunar::Lunar(int _year, int _month, int _day) {
	syear = _year;
	smonth = _month;
	sdate = _day;

	int LunarYearIndex = _year - 1901;
	int SpringSolorMonth = (lunar200y[LunarYearIndex] & 0x60) >> 5;
	int SpringSolordate = lunar200y[LunarYearIndex] & 0x1f;

	int SpringFromSolorNew = 0;
	if (SpringSolorMonth == 1)
		SpringFromSolorNew = SpringSolordate - 1;
	else
		SpringFromSolorNew = SpringSolordate + 31 - 1;

	int DaysFromSolorNew = MonthsCount[_month - 1] + _day - 1;
	if ((((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0)) && (_month > 2))
		DaysFromSolorNew++;

	int ThisYearLeapMonth = (lunar200y[LunarYearIndex] & 0xf00000) >> 20;
	int LastYearLeapMonth = (lunar200y[LunarYearIndex - 1] & 0xf00000) >> 20;
	if (DaysFromSolorNew < SpringFromSolorNew) {
		int DaysFromSpring = SpringFromSolorNew - DaysFromSolorNew;
		int MonthIndex = 0;
		year = _year - 1;
		month = 12;
		bool isPassLeapMonth = false;
		if (LastYearLeapMonth == 0) {
			MonthIndex = 12;
			isPassLeapMonth = true;
		}
		else {
			MonthIndex = 13;
			isPassLeapMonth = false;
		}

		for (; 1 != 0; ) {
			int DaysInThisMonth = getLunarMonthDays(year, MonthIndex);
			if (DaysFromSpring > DaysInThisMonth) {
				if ((LastYearLeapMonth == month) && (!isPassLeapMonth))
					isPassLeapMonth = true;
				else
					month--;
				MonthIndex--;
				DaysFromSpring -= DaysInThisMonth;
			}
			else {
				date = DaysInThisMonth - DaysFromSpring + 1;
				if ((LastYearLeapMonth == month) && (!isPassLeapMonth))
					isLeap = true;
				else
					isLeap = false;
				break;
			}
		}
	}
	else {
		int DaysFromSpring = DaysFromSolorNew - SpringFromSolorNew;
		int MonthIndex = 1;
		year = _year;
		month = 1;
		bool isPassLeapMonth = false;

		/*Serial.print("SpringFromSolorNew");
		Serial.println(SpringFromSolorNew);
		Serial.print("DaysFromSolorNew:");
		Serial.println(DaysFromSolorNew);
		Serial.print("DaysFromSpring:");
		Serial.println(DaysFromSpring);
		Serial.print("MonthIndex:");
		Serial.println(MonthIndex);
		Serial.print("ThisYearLeapMonth:");
		Serial.println(ThisYearLeapMonth);
		Serial.print("LastYearLeapMonth:");
		Serial.println(LastYearLeapMonth);*/
		for (int i = 0; 1 != 0; ++i) {
			int DaysInThisMonth = getLunarMonthDays(year, MonthIndex);
			Serial.print("DaysInThisMonth:");
			Serial.println(DaysInThisMonth);
			if (DaysFromSpring >= DaysInThisMonth) {
				if ((ThisYearLeapMonth == month) && (!isPassLeapMonth))
					isPassLeapMonth = true;
				else
					month++;
				MonthIndex++;
				DaysFromSpring -= DaysInThisMonth;
			}
			else {
				date = DaysFromSpring + 1;
				if ((ThisYearLeapMonth == month) && (!isPassLeapMonth))
					isLeap = true;
				else
					isLeap = false;
				break;
			}
			/*Serial.print("DaysFromSpring:");
			Serial.println(DaysFromSpring);*/
		}
	}
}
