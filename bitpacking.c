#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main()
{
    // TO DO Task 7 & 8
    int tasknr = 0;
    scanf ("%d", &tasknr);
    const char sizeOfDay = 5;
    const char sizeOfMonth = 4;
    const char sizeOfYear = 6;
    const int unixStart = 1970;

    switch (tasknr) {
        case 7:
            int N;
            int day = 0, month = 0, year = 0;
            scanf("%d", &N);
            unsigned int * bytes = calloc(N, sizeof(unsigned int));
            for (int i = 0; i < N; i ++) {
                scanf ("%d%d%d", &day, &month, &year);
                year -= unixStart;
                // bytes[i] = day<<(sizeof(unsigned int) - sizeOfDay) + month<<(sizeof(unsigned int) - sizeOfDay - sizeOfMonth) + year<<(sizeof(unsigned int) - sizeOfDay - sizeOfMonth - sizeOfYear)
                bytes[i] = day + (month<<(sizeOfDay)) + (year<<(sizeOfDay + sizeOfMonth));
            }
            qsort(bytes, N, sizeof(unsigned int), cmpfunc);
            for (int i = 0; i < N; i++) {
                printf ("%d\n", bytes[i]);
                printf("%u %u %u\n", (bytes[i]<<(sizeof(unsigned int) - sizeOfDay))>>(sizeof(unsigned int) - sizeOfDay), bytes[i]<<(sizeof(unsigned int) - sizeOfDay - sizeOfMonth), bytes[i]<<(sizeof(unsigned int) - sizeOfDay - sizeOfMonth - sizeOfYear));
            }
//             11111 010101 1010 11011
//                 0 100011 1010 11011
            break;

        case 8:
            break;

        default: printf("error lol");
    }

    return 0;
}
// 11010
// 11010 00000
// 1101000000000000
// 00000000000 11010
