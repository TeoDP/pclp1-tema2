#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"
#define avgMonth 30
#define smallMonth 28
#define bigMonth 31
#define secInMin 60
#define minInHour 60
#define hourInDay 24
#define dayInYear 365
#define unixStart 1970
#define leap 4
#define hungie 100
#define i5 5
#define i6 6
#define i7 7
#define i8 8
#define i9 9
#define i10 10
#define i11 11

// TO DO Task 1
TTime convertUnixTimestampToTime(unsigned int timestamp) {
    TTime result;
    // const int secInMin = 60, minInHour = 60, hourInDay = 24;
    result.sec = timestamp%secInMin;
    result.min = (timestamp/secInMin)%minInHour;
    result.hour = (timestamp/secInMin/minInHour)%hourInDay;
    return result;
}

// TO DO Task 2
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
    TDate result;
    // const int secInMin = 60, minInHour = 60, hourInDay = 24;
    // const int dayInYear = 365, unixStart = 1970;
    unsigned int nrDays = timestamp/secInMin/minInHour/hourInDay;
    unsigned int daysThisYear = nrDays%dayInYear;
    result.year = unixStart + nrDays/dayInYear;
    const int nrMonths = 12;
    unsigned int * months = calloc (nrMonths, sizeof(int));
    months[0] = bigMonth;
    months[1] = months[0] + smallMonth;
    months[2] = months[1] + bigMonth;
    months[3] = months[2] + avgMonth;
    months[4] = months[3] + bigMonth;
    months[i5] = months[4] + avgMonth;
    months[i6] = months[i5] + bigMonth;
    months[i7] = months[i6] + bigMonth;
    months[i8] = months[i7] + avgMonth;
    months[i9] = months[i8] + bigMonth;
    months[i10] = months[i9] + avgMonth;
    months[i11] = months[i10] + bigMonth;

    if (daysThisYear <= months[0]) {
        result.month = 1;
        result.day = daysThisYear;
    } else {
        for (int i = 1; i < nrMonths; i++) {
            if (daysThisYear <= months[i]) {
                result.month = i + 1;
                result.day = daysThisYear - months[i-1];
                break;
            }
        }
    }
    result.day++;
    return result;
}

// TO DO Task 3
TDate convertUnixTimestampToDate(unsigned int timestamp) {
    TDate result;
    // const int secInMin = 60, minInHour = 60, hourInDay = 24;
    // const int dayInYear = 365, unixStart = 1970;
    unsigned int nrDays = timestamp/secInMin/minInHour/hourInDay;

    const int nrMonths = 12;
    unsigned int * months = calloc (nrMonths, sizeof(int));
    months[0] = 0;
    months[0] = bigMonth;
    months[1] = months[0] + smallMonth;
    months[2] = months[1] + bigMonth;
    months[3] = months[2] + avgMonth;
    months[4] = months[3] + bigMonth;
    months[i5] = months[4] + avgMonth;
    months[i6] = months[i5] + bigMonth;
    months[i7] = months[i6] + bigMonth;
    months[i8] = months[i7] + avgMonth;
    months[i9] = months[i8] + bigMonth;
    months[i10] = months[i9] + avgMonth;
    months[i11] = months[i10] + bigMonth;

    int i = 0, j = 0;
    if (nrDays < dayInYear) {
            i = 1;
        }
    result.year = unixStart;
    while (i != 1) {
        result.year++;
        nrDays -= dayInYear;
        if ((unixStart + j) % leap == 0) {
            if ((unixStart + j) % hungie == 0) {
                if ((unixStart + j) % (leap * hungie) == 0) {
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
    nrDays++;
    if (nrDays <= bigMonth) {
        result.month = 1;
        result.day = nrDays;
    } else {
        for (int i = 1; i < (nrMonths); i++) {
            if (nrDays <= (months[i])) {
                if (result.year % leap == 0) {
                    if (result.year % hungie == 0) {
                        if (result.year % (leap * hungie) == 0) {
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
    // const int secInMin = 60, minInHour = 60;
    timestamp = timestamp + (timezones[timezone_index].utc_hour_difference * secInMin * minInHour);
    result.time = convertUnixTimestampToTime(timestamp);
    result.date = convertUnixTimestampToDate(timestamp);
    result.tz = malloc(sizeof(TTimezone));
    snprintf(result.tz[0].name, sizeof(result.tz[0].name), "%s", timezones[timezone_index].name);
    result.tz[0].utc_hour_difference = timezones[timezone_index].utc_hour_difference;
    return result;
}

// TO DO Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ timezoned) {
    unsigned int result = 0;
    // const int secInMin = 60, minInHour = 60, hourInDay = 24;
    // const int dayInYear = 365, unixStart = 1970;
    // int nrDays = timestamp/secInMin/minInHour/hourInDay;
    unsigned int secInDay = secInMin * minInHour * hourInDay;

     const int nrMonths = 12;
    int * months = calloc (nrMonths, sizeof(int));
    months[0] = 0;
    months[0] = bigMonth;
    months[1] = months[0] + smallMonth;
    months[2] = months[1] + bigMonth;
    months[3] = months[2] + avgMonth;
    months[4] = months[3] + bigMonth;
    months[i5] = months[4] + avgMonth;
    months[i6] = months[i5] + bigMonth;
    months[i7] = months[i6] + bigMonth;
    months[i8] = months[i7] + avgMonth;
    months[i9] = months[i8] + bigMonth;
    months[i10] = months[i9] + avgMonth;
    months[i11] = months[i10] + bigMonth;

    for (unsigned int i = unixStart; i < timezoned.date.year; i++) {
        result = result + (dayInYear * secInDay);
        if (i % leap == 0) {
            if (i % hungie == 0) {
                if (i % (leap * hungie) == 0) {
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
    if (timezoned.date.year % leap == 0) {
        if (timezoned.date.year % hungie == 0) {
            if (timezoned.date.year % (leap * hungie) == 0) {
                leapY = 1;
            }
        } else {
            leapY = 1;
        }
    }
    if (leapY == 1 && timezoned.date.month > 2) {
        result += secInMin * minInHour * hourInDay;
    }

    return result;
}

// TO DO Task 6
void printDateTimeTZ(TDateTimeTZ datetimetz) {
    const int nrMonths = 12;
    const int word = 20;
    // char months[12][20] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
        // "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    char ** months = malloc(nrMonths * sizeof(char *));
    for (int i = 0; i < nrMonths; i ++) {
        months[i] = malloc(word * sizeof(char));
    }
    snprintf(months[0], word, "ianuarie");
    snprintf(months[1], word, "februarie");
    snprintf(months[2], word, "martie");
    snprintf(months[3], word, "aprilie");
    snprintf(months[4], word, "mai");
    snprintf(months[i5], word, "iunie");
    snprintf(months[i6], word, "iulie");
    snprintf(months[i7], word, "august");
    snprintf(months[i8], word, "septembrie");
    snprintf(months[i9], word, "octombrie");
    snprintf(months[i10], word, "noiembrie");
    snprintf(months[i11], word, "decembrie");

    printf("%02d %s %02d, ", datetimetz.date.day, months[datetimetz.date.month - 1], datetimetz.date.year);
    printf("%02d:%02d:%02d ", datetimetz.time.hour, datetimetz.time.min, datetimetz.time.sec);
    char *tz_name = datetimetz.tz[0].name;
    printf("%s (UTC", tz_name);
    if (datetimetz.tz[0].utc_hour_difference >= 0) {
        printf("+");
    }
    printf("%d)\n",  datetimetz.tz[0].utc_hour_difference);
}
