#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"
#include <string.h>

// TO DO Task 1
TTime convertUnixTimestampToTime(unsigned int timestamp) {
    TTime result;
    const int secInMin = 60, minInHour = 60, hourInDay = 24;
    result.sec = timestamp%secInMin;
    result.min = (timestamp/secInMin)%minInHour;
    result.hour = (timestamp/secInMin/minInHour)%hourInDay;
    return result;
}

// TO DO Task 2
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
    TDate result;
    const int secInMin = 60, minInHour = 60, hourInDay = 24;
    const int dayInYear = 365, unixStart = 1970;
    int nrDays = timestamp/secInMin/minInHour/hourInDay;
    int daysThisYear = nrDays%dayInYear;
    result.year = unixStart + nrDays/dayInYear;
    int months[12];
    const int january = 31;             months[0] = january;
    const int february = january + 28;  months[1] = february;
    const int march = february + 31;    months[2] = march;
    const int april = march + 30;       months[3] = april;
    const int may = april + 31;         months[4] = may;
    const int june = may + 30;          months[5] = june;
    const int july = june + 31;         months[6] = july;
    const int august = july + 31;       months[7] = august;
    const int september = august + 30;  months[8] = september;
    const int october = september + 31; months[9] = october;
    const int november = october + 30;  months[10] = november;
    const int december = november + 31; months[11] = december;

    if (daysThisYear <= january) {
        result.month = 1;
        result.day = daysThisYear;
    } else
        for (int i = 1; i < ((int)sizeof(months)/(int)(sizeof(int))); i++) {
            if (daysThisYear <= months[i]) {
                result.month = i + 1;
                result.day = daysThisYear - months[i-1];
                break;
            }
        }
    result.day ++;
    return result;
}

// TO DO Task 3
TDate convertUnixTimestampToDate(unsigned int timestamp) {
    TDate result;
    const int secInMin = 60, minInHour = 60, hourInDay = 24;
    const int dayInYear = 365, unixStart = 1970;
    int nrDays = timestamp/secInMin/minInHour/hourInDay;

    int months[12];
    const int january = 31;             months[0] = january;
    const int february = january + 28;  months[1] = february;
    const int march = february + 31;    months[2] = march;
    const int april = march + 30;       months[3] = april;
    const int may = april + 31;         months[4] = may;
    const int june = may + 30;          months[5] = june;
    const int july = june + 31;         months[6] = july;
    const int august = july + 31;       months[7] = august;
    const int september = august + 30;  months[8] = september;
    const int october = september + 31; months[9] = october;
    const int november = october + 30;  months[10] = november;
    const int december = november + 31; months[11] = december;

    int i = 0, j = 0;
    if (nrDays < dayInYear) {
            i = 1;
        }
    result.year = unixStart;
    while (i != 1) {
        result.year++;
        nrDays -= dayInYear;
        if ((unixStart + j) % 4 == 0) {
            if ((unixStart + j) % 100) {
                if ((unixStart + j) & 400) {
                    nrDays--;
                } else {}
            } else {
                nrDays--;
            }
        }
        if (nrDays < dayInYear) {
            i = 1;
        }
        j++;
    }
    nrDays ++;
    if (nrDays <= january) {
        result.month = 1;
        result.day = nrDays;
    } else {
        for (int i = 1; i < ((int)sizeof(months)/(int)(sizeof(int))); i++) {
            if (nrDays <= (months[i])) {
                if (result.year % 4 == 0) {
                    if (result.year % 100 == 0) {
                        if (result.year % 400 == 0) {
                            result.day = nrDays - months[i-1] - 1;
                        } else {
                            result.day = nrDays - months[i-1];
                        }
                    } else {
                        result.day = nrDays - months[i-1] - 1;
                    }
                } else {
                    result.day = nrDays - months[i-1];
                }
                result.month = i + 1;
                break;
            }
        }
    }

    return result;
}

// TO DO Task 4
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
    TDateTimeTZ result;
    const int secInMin = 60, minInHour = 60;
    timestamp = timestamp + (timezones[timezone_index].utc_hour_difference * secInMin * minInHour);
    result.time = convertUnixTimestampToTime(timestamp);
    result.date = convertUnixTimestampToDate(timestamp);
    result.tz = malloc(sizeof(TTimezone));
    strcpy(result.tz[0].name, timezones[timezone_index].name);
    result.tz[0].utc_hour_difference = timezones[timezone_index].utc_hour_difference;
    return result;
}

// TO DO Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ timezoned) {
    unsigned int result = 0;
    const int secInMin = 60, minInHour = 60, hourInDay = 24;
    const int dayInYear = 365, unixStart = 1970;
    // int nrDays = timestamp/secInMin/minInHour/hourInDay;
    int secInDay = secInMin * minInHour * hourInDay;

    int months[12];
    const int january = 31;             months[0] = january;
    const int february = january + 28;  months[1] = february;
    const int march = february + 31;    months[2] = march;
    const int april = march + 30;       months[3] = april;
    const int may = april + 31;         months[4] = may;
    const int june = may + 30;          months[5] = june;
    const int july = june + 31;         months[6] = july;
    const int august = july + 31;       months[7] = august;
    const int september = august + 30;  months[8] = september;
    const int october = september + 31; months[9] = october;
    const int november = october + 30;  months[10] = november;
    const int december = november + 31; months[11] = december;

    for (unsigned int i = unixStart; i < timezoned.date.year; i++) {
        result = result + (dayInYear * secInDay);
        if (i % 4 == 0) {
            if (i % 100 == 0) {
                if (i % 400 == 0) {
                    result += secInDay;
                }
            } else {
                result += secInDay;
            }
        }
    }
    if (timezoned.date.month == 1) {
        result = result + ((timezoned.date.day-1) * secInDay);
    } else {
        result += ((months[timezoned.date.month-2] + timezoned.date.day -1) * secInDay);
    }
    char leapY = 0;
    result += timezoned.time.hour * secInMin * minInHour;
    result += timezoned.time.min * secInMin;
    result += timezoned.time.sec;
    result -= timezoned.tz[0].utc_hour_difference * secInMin * minInHour;
    if (timezoned.date.year % 4) {
        if (timezoned.date.year % 100) {
            if (timezoned.date.year % 400) {
                leapY = 1;
            }
        } else {
            leapY = 1;
        }
    }
    if (leapY == 1 && timezoned.date.month > 2){
        // result += secInMin * minInHour * hourInDay;
    }

    return result;
}

// TO DO Task 6
void printDateTimeTZ(TDateTimeTZ datetimetz) {
    char months[12][20] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie", "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    printf("%02d %s %02d, ", datetimetz.date.day, months[datetimetz.date.month - 1], datetimetz.date.year);
    printf("%02d:%02d:%02d ", datetimetz.time.hour, datetimetz.time.min, datetimetz.time.sec);
    char *tz_name = datetimetz.tz[0].name;
    printf("%s (UTC", tz_name);
    if (datetimetz.tz[0].utc_hour_difference >= 0) {
        printf("+");
    }
    printf("%d)\n",  datetimetz.tz[0].utc_hour_difference);
}
