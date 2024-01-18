#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"
#define five 5

int main() {
    // TO DO Task 9

    int T = 0, P = 0;
    scanf("%d", &T);
    char ** tzNames = malloc(T * sizeof(char *));
    int * tzVal = malloc(T * sizeof(int));
    for (int i = 0; i < T; i++) {
        tzNames[i] = malloc(4 * sizeof(char));
        scanf("%s %d", tzNames[i], &tzVal[i]);
    }
    scanf("%d", &P);

    typedef struct {
        char * name;
        char * tz;
        int freeTime;
        TDate * date;
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
        scanf("%s%s%s%d", PNames[i], people[i].name, people[i].tz, &people[i].freeTime);
        people[i].date = malloc(people[i].freeTime * sizeof(TDate));
        people[i].nrHours = malloc(people[i].freeTime * sizeof(TDate));
    }
    int F = 0, duration = 0;;
    scanf("%d%d", &F, &duration);

    for (int i = 0; i < P-1; i++) {
        for (int j = 0; j < P; j++) {
            if (strcmp(PNames[i+1], PNames[i])) {
                tempName = PNames[i+1];
                PNames[i+1] = PNames[i];
                PNames[i] = tempName;

                tempPerson = people[i+1];
                people[i+1] = people[i];
                people[i] = tempPerson;
            }
        }
    }




    return 0;
}
