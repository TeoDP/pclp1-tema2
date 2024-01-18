#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"
#define task1 7
#define task2 8
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
    const char sizeOfYear = 6;
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
             masks[2] = 1; masks[2] = masks[2] << (sizeOfDay + sizeOfMonth + sizeOfYear); masks[2]--;
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
            unsigned int mask = 0, k = 0, pixel = 0, counter = 0;
            unsigned int day = 0, month = 0, year = 0;

            scanf ("%d", &N);
            unsigned int *array = malloc(((N * (sizeOfDay + sizeOfMonth + sizeOfYear))/sizeof(unsigned int)*8 + 1 ) * sizeof(unsigned int));
            unsigned int *control = malloc((N/sizeof(unsigned int)/8 + 1) * sizeof(unsigned int));
            unsigned int * bytesToo = calloc(N, sizeof(unsigned int));


            // for (int i = 0; i < N; i++) {
            //     k = (nrDates * (sizeOfDay + sizeOfMonth + sizeOfYear))/sizeof(unsigned int);
            //     printf("%d", k);
            //     scanf("%u", &tempByte);
            //     startPos = (nrDates * (sizeOfDay + sizeOfMonth + sizeOfYear)) % sizeof(unsigned int);
            //     mask = tempByte<<startPos;
            //     array[k] = array[k] | mask;
            //     if (startPos + sizeOfDay + sizeOfMonth + sizeOfYear > (int)sizeof(unsigned int)) {
            //         mask = tempByte>>(startPos + sizeOfDay + sizeOfMonth + sizeOfYear - sizeof(unsigned int));
            //         array[k + 1] = array[k + 1] | mask;
            //     }
            //     nrDates++;
            // }

            k = (N * (sizeOfDay + sizeOfMonth + sizeOfYear))/sizeof(unsigned int)/8;
            if ((N * (sizeOfDay + sizeOfMonth + sizeOfYear))%(sizeof(unsigned int)*8) != 0) k++;
            for (int i = 0; i < k; i++) {
                scanf("%u", &array[i]);
            }

            for (int i = 0; i < (N/(sizeof(unsigned int) * 8) + 1); i++) {
                g = i/sizeof(unsigned int)/8;
                scanf("%d", &temp);
                control[g] = temp;
            }
//////////////////////////////////////////////////////
            // int h = 0;
            // for (int i = 0; i < k; i++) {
                // // pixel = (control[h] >> i) & 1;
                // counter = 0;
                // for (int j = 0; j < sizeof(unsigned int); j++) {
                    // counter += ((array[(i * 15)/(sizeof(unsigned int))]>>j)&1);
                // }
                // if (pixel == (counter%2)) {
                    // // e ok
                // } else {
                    // array[i] = 0;
                // }
            // }
/////////////////////////////////////////////////////////////////////////////////////////////////
            int h = 0;
            pixel = (control[0] >> 0) & 1;
            counter = 0;
            for (int j = 0; j < sizeof(unsigned int); j++) {
                counter += ((array[(0 * 15)/(sizeof(unsigned int))]>>j)&1);
            }
            if (pixel == (counter%2)) {
            mask = 1 << 15; mask--;
            bytesToo[0] = array[0] & mask;
            } else {
                bytesToo[0] = 0;
            }

            for (int i = 1; i < N; i++) {
                int index = (i*(sizeOfDay + sizeOfMonth + sizeOfYear))/(sizeof(unsigned int) * 8);
                int rest = (i*(sizeOfDay + sizeOfMonth + sizeOfYear))%(sizeof(unsigned int) * 8);
                h = 0;
                pixel = (control[0] >> i) & 1;
                counter = 0;
                for (int j = 0; j < sizeof(unsigned int); j++) {
                    counter += ((array[(i * 15)/(sizeof(unsigned int))]>>j)&1);
                }
                if (pixel == (counter%2)) {
                if (rest < (sizeOfDay + sizeOfMonth + sizeOfYear)) {
                    h = 0;
                    pixel = (control[0] >> i) & 1;
                    counter = 0;
                    for (int j = 0; j < sizeof(unsigned int); j++) {
                        counter += ((array[(i * 15)/(sizeof(unsigned int)) - 1]>>j)&1);
                    }
                    if (pixel != counter%2) {
                        continue;
                    }
                    mask = 0; mask--;
                    mask = mask ^ (1 << (sizeof(unsigned int) - (sizeOfDay + sizeOfMonth + sizeOfYear - rest)));

                    bytesToo[i] = array[index] & mask;
                    bytesToo[i] = bytesToo[i] >> (sizeof(unsigned int) * 8 - rest);

                    mask = 1 << rest; mask--;
                    bytesToo[i] = (array[index+1] & mask) << (sizeOfDay + sizeOfMonth + sizeOfYear - rest);
                } else if (rest >= (sizeOfDay + sizeOfMonth + sizeOfYear)) {
                    mask = 1 << rest; mask--;
                    mask = mask ^ (1 << (rest - (sizeOfDay + sizeOfMonth + sizeOfYear)));
                    bytesToo[i] = (array[index] & mask) >> (rest - (sizeOfDay + sizeOfMonth + sizeOfYear));
                }
                } else {
                    bytesToo[i] = 0;
                }
            }


            // // k = (N * (sizeOfDay + sizeOfMonth + sizeOfYear))/sizeof(unsigned int)/8;
            // for (int i = 0; i < k; i++) {
            //     counter = 0;
            //     for (int j = 0; j < sizeof(unsigned int)*8; j++) {
            //         counter += ((array[i]>>j)&1);
            //     }
            //     g = i/sizeof(unsigned int)/8;
            //     if (counter%2 == (control[g]>>i)) {
            //         if (i == 0) {
            //             mask = (1<<(sizeOfDay + sizeOfMonth + sizeOfYear)) - 1;
            //             bytesToo[0] = array[0] & mask;
            //         } else {
            //             tempByte = array[i];
            //             mask = (1<<(sizeof(unsigned int)*8 - i * 2))-1;
            //             mask = mask ^ ((1<<(sizeOfDay + sizeOfMonth + sizeOfYear - i*2))-1);
            //             bytesToo[i] = array[i] & mask;
            //         }
            //     }
            // }

            //----------?
             unsigned int masks[3] = {0, 0, 0};
             masks[0] = 1; masks[0] = masks[0] << (sizeOfDay); masks[0]--;
             masks[1] = 1; masks[1] = masks[1] << (sizeOfDay + sizeOfMonth); masks[1]--;
             masks[1] = masks[1] ^ masks[0];
             masks[2] = 1; masks[2] = masks[2] << (sizeOfDay + sizeOfMonth + sizeOfYear); masks[2]--;
             masks[2] = (masks[2] ^ masks[1]) ^ masks[0];
             // printf("hey3\n");
            qsort(bytesToo, N, sizeof(unsigned int), cmpfunc);
            // printf("hey4\n");
            const char months[12][20] = {"ianuarie", "februarie", "martie", "aprilie",
                "mai", "iunie", "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
            for (int i = 0; i < N; i++) {
                // printf ("%d\n", bytes[i]);

                // printf("mask= %d\n", mask);
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
