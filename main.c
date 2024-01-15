#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"
#include <string.h>

int main() {
    unsigned int n = 0;
    printf("insert unix time: ");
    scanf("%d", &n);
    TTime final_time = convertUnixTimestampToTime(n);
    printf("%d:%d:%d\n", final_time.hour, final_time.min, final_time.sec);
    // TDate final_date = convertUnixTimestampToDateWithoutLeapYears(n);
    // printf("%d-%d-%d\n", final_date.year, final_date.month, final_date.day);
    TDate final_date_bi = convertUnixTimestampToDate(n);
    printf("%d-%d-%d\n", final_date_bi.year, final_date_bi.month, final_date_bi.day);

    TTimezone hell[3];
    strcpy(hell[0].name, "UTC");
    hell[0].utc_hour_difference = 0;
    strcpy(hell[1].name, "EET");
    hell[1].utc_hour_difference = 2;
    strcpy(hell[2].name, "PST");
    hell[2].utc_hour_difference = -8;

    TDateTimeTZ heaven = convertUnixTimestampToDateTimeTZ(n, hell, 0);
    printf("%d-%d-%d %d:%d:%d 0\n", heaven.date.year, heaven.date.month, heaven.date.day, heaven.time.hour, heaven.time.min, heaven.time.sec);
    heaven = convertUnixTimestampToDateTimeTZ(n, hell, 1);
    printf("%d-%d-%d %d:%d:%d 2\n", heaven.date.year, heaven.date.month, heaven.date.day, heaven.time.hour, heaven.time.min, heaven.time.sec);
    heaven = convertUnixTimestampToDateTimeTZ(n, hell, 2);
    printf("%d-%d-%d %d:%d:%d -8\n", heaven.date.year, heaven.date.month, heaven.date.day, heaven.time.hour, heaven.time.min, heaven.time.sec );

    unsigned int k = convertDateTimeTZToUnixTimestamp(heaven);
    printf("%d\n", k);

    printDateTimeTZ(heaven);
}
