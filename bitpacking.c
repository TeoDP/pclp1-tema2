#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"
#define task1 7
#define task2 8
#define byteSize 8
int cmpfunc(const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main() {
    // TO DO Task 7 & 8
    int tasknr = 0;
    scanf("%d", &tasknr);
    // const int task1 = 7;
    // const int task2 = 8;
    const char sizeOfDay = 5;
    const char sizeOfMonth = 4;
    // const char sizeOfYear = 6;
    const char sizeOfDate = 15;
    const int unixStart = 1970;

    switch (tasknr) {
        case task1: {
            // printf("hey\n");
            int N = 0;
            unsigned int day = 0, month = 0, year = 0;
            scanf("%d", &N);
            unsigned int * bytes = calloc(N, sizeof(unsigned int));
            /*
            for (int i = 0; i < N; i ++) {
                scanf ("%d%d%d", &day, &month, &year);
                year -= unixStart;
                // bytes[i] = day<<(sizeof(unsigned int) - sizeOfDay) + month<<(sizeof(unsigned int) - sizeOfDay - sizeOfMonth) + year<<(sizeof(unsigned int) - sizeOfDay - sizeOfMonth - sizeOfYear)
                bytes[i] = day + (month<<(sizeOfDay)) + (year<<(sizeOfDay + sizeOfMonth));
            }
            */
            for (int i = 0; i < N; i++) {
                scanf("%u", &bytes[i]);
            }
            // printf("hey2");
            unsigned int masks[3] = {0, 0, 0};
             masks[0] = 1; masks[0] = masks[0] << (sizeOfDay); masks[0]--;
             masks[1] = 1; masks[1] = masks[1] << (sizeOfDay + sizeOfMonth); masks[1]--;
             masks[1] = masks[1] ^ masks[0];
             masks[2] = 1; masks[2] = masks[2] << sizeOfDate; masks[2]--;
             masks[2] = (masks[2] ^ masks[1]) ^ masks[0];
             // printf("hey3\n");
            qsort(bytes, N, sizeof(unsigned int), cmpfunc);
            // printf("hey4\n");
            const char months[12][20] = {"ianuarie", "februarie", "martie", "aprilie",
                "mai", "iunie", "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
            for (int i = 0; i < N; i++) {
                // printf ("%d\n", bytes[i]);

                // printf("mask= %d\n", mask);
                day = (bytes[i]) & masks[0];
                month = (bytes[i]) & masks[1];
                month = month >> sizeOfDay;
                year = bytes[i] & masks[2];
                year = year >> (sizeOfDay + sizeOfMonth);
                year += unixStart;
                printf("%u %s %u\n", day, months[month-1], year);
            }

            break;
        }
        case task2: {
            int temp = 0, g = 0;
            int N = 0;
            unsigned int mask = 0, k = 0, pixel = 0, counter = 0, element = 0, temp2 = 0;
            unsigned int day = 0, month = 0, year = 0;

            scanf("%d", &N);
            unsigned int *array = malloc(((N * sizeOfDate)/
            (sizeof(unsigned int)*byteSize) + 2 ) * sizeof(unsigned int));
            unsigned int *control = malloc((N/sizeof(unsigned int)/byteSize + 1) * sizeof(unsigned int));
            unsigned int * bytesToo = calloc(N + 1, sizeof(unsigned int));

            k = (N * sizeOfDate)/sizeof(unsigned int)/byteSize;
            if ((N * sizeOfDate)%(sizeof(unsigned int)*byteSize) != 0) k++;
            for (int i = 0; i < k; i++) {
                scanf("%u", &array[i]);
            }
            for (int i = 0; i < (N/(sizeof(unsigned int) * byteSize) + 1); i++) {
                g = i/(int)sizeof(unsigned int)/byteSize;
                scanf("%d", &temp);
                control[g] = temp;
            }
            for (int i = 0; i < k; i++) {
                pixel = (control[i/(sizeof(unsigned int) * byteSize)] >> i) & 1;
                counter = 0;
                for (int j = 0; j < sizeof(unsigned int) * byteSize; j++) {
                    counter += ((array[i] >> j) & 1);
                }
                if (pixel != counter%2) {
                    array[i] = 0;
                }
            }
            if (array[k-2] == 0) {
                array[k-1] = 0;
            }
            for (int i = 0; i < k; i++) {
                if (array[i] == 0) {
                    continue;
                }
                element++;
                mask = 1 << sizeOfDate; mask--;
                mask = mask << (((element * sizeOfDate) % ((i+1) * sizeof(unsigned int) * byteSize)) - sizeOfDate);
                bytesToo[element] = array[i] & mask;
                if ((element * sizeOfDate) % ((i+1) * sizeof(unsigned int) * byteSize) - sizeOfDate <= 2) {
                    element++;
                    mask = 1 << sizeOfDate; mask--;
                    mask = mask << ((element * sizeOfDate) % ((i+1) * sizeof(unsigned int) * byteSize) - sizeOfDate);
                    bytesToo[element] = array[i] & mask;
                    bytesToo[element] = bytesToo[element] >> ((element * sizeOfDate) %
                    ((i+1) * sizeof(unsigned int) * byteSize) - sizeOfDate);
                }
                if (array[i+1] != 0) {
                    // element++;
                    mask = 1 << sizeOfDate; mask--;
                    mask = mask << (sizeof(unsigned int) * byteSize -
                    ((element * sizeOfDate) % ((i+1) * sizeof(unsigned int) * byteSize) - sizeOfDate));
                    bytesToo[element] = array[i] & mask;
                    bytesToo[element] = bytesToo[element] >> (sizeof(unsigned int) * byteSize -
                    ((element * sizeOfDate) % ((i+1) * sizeof(unsigned int) * byteSize) - sizeOfDate));
                    mask = 1 << sizeOfDate; mask--;
                    mask = mask >> (sizeOfDate - (sizeof(unsigned int) * byteSize -
                    ((element * sizeOfDate) % ((i+1) * sizeof(unsigned int) * byteSize) - sizeOfDate)));
                    temp2 = array[i+1] & mask;
                    temp2 = temp2 << (sizeOfDate - (sizeof(unsigned int) * byteSize -
                    ((element * sizeOfDate) % ((i+1) * sizeof(unsigned int) * byteSize) - sizeOfDate)));
                    element++;
                    bytesToo[element] = bytesToo[element] | temp2;
                }
            }
            //----------?
             unsigned int masks[3] = {0, 0, 0};
             masks[0] = 1; masks[0] = masks[0] << (sizeOfDay); masks[0]--;
             masks[1] = 1; masks[1] = masks[1] << (sizeOfDay + sizeOfMonth); masks[1]--;
             masks[1] = masks[1] ^ masks[0];
             masks[2] = 1; masks[2] = masks[2] << sizeOfDate; masks[2]--;
             masks[2] = (masks[2] ^ masks[1]) ^ masks[0];
             qsort(bytesToo, N, sizeof(unsigned int), cmpfunc);
            const char months[12][20] = {"ianuarie", "februarie", "martie", "aprilie",
                "mai", "iunie", "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
            for (int i = 0; i < N; i++) {
                if (bytesToo[i] == 0) {
                    continue;
                }
                day = (bytesToo[i]) & masks[0];
                month = (bytesToo[i]) & masks[1];
                month = month >> sizeOfDay;
                year = bytesToo[i] & masks[2];
                year = year >> (sizeOfDay + sizeOfMonth);
                year += unixStart;
                printf("%u %s %u\n", day, months[month-1], year);
            }
            //----------?
            break;
        }

        default: printf("error lol");
    }

    return 0;
}
