#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"
#define five 5

int cmpfunc(const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main() {
    /*
    // TO DO Task 9

    int T = 0, P = 0;
    // T = nr timezones

    scanf("%d", &T);
    // char ** tzNames = malloc(T * sizeof(char *));
    // int * tzVal = malloc(T * sizeof(int));
    TTimezone * timezones = malloc (T * sizeof(TTimezone));
    for (int i = 0; i < T; i++) {
        timezones[i].name = malloc(five * sizeof(char));
        scanf("%s %d", timezones[i].name, &timezones[i].utc_hour_difference);
    }
    scanf("%d", &P);

    typedef struct {
        char * name;
        int freeTime;
        TDateTimeTZ * interval;
        int * nrHours;
    } PList;

    char ** PNames = malloc(P * sizeof(char *));
    char * tempName = NULL;
    PList * people = malloc(P * sizeof(PList));
    PList tempPerson;
    for (int i = 0; i < P; i++) {
        PNames = malloc(five * 2 * sizeof(char));
        people[i].name = malloc(five * 2 * sizeof(char));
        people[i].tz = malloc(five * sizeof(char));
        scanf("%s%s%d", people[i].name, people[i].interval.tz->name, &people[i].freeTime);
        people[i].interval = malloc(people[i].freeTime * sizeof(TDateTimeTZ));
        people[i].nrHours = malloc(people[i].freeTime * sizeof(int));
        for (int j = 0; j < people[i].freeTime; j++) {
            scanf("%d%d%d%d", people[i].interval[j].date.year, people[i].interval[j].date.month, people[i].interval[j].date.day, people[i].nrHours);
        }
    }
    int F = 0, duration = 0;
    // F = nr minim de persoane
    scanf("%d%d", &F, &duration);

    for (int i = 0; i < P; i ++) {
        strcpy(PNames[i], people[i]->name);
    }

    for (int i = 0; i < P-1; i++) {
        for (int j = 0; j < P; j++) {
            if (strcmp(PNames[i+1], PNames[i]) < 0) {
                tempName = PNames[i+1];
                PNames[i+1] = PNames[i];
                PNames[i] = tempName;

                tempPerson = people[i+1];
                people[i+1] = people[i];
                people[i] = tempPerson;
            }
        }
    }


*/
    return 0;
}
