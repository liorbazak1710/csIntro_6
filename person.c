#include "person.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PERSON_PARAMS 7

static char* personToStr(Person person, char str[MAX_STR_LEN]){
    sprintf(str, "%s,%s,%d,%d,%d,%d,%.2f\n",person.firstName,
                                                    person.lastName,
                                                    person.dateOfBirth.day,
                                                    person.dateOfBirth.month,
                                                    person.dateOfBirth.year,
                                                    person.height,
                                                    person.weight);
}

static void strSplit(char str[], char arr[PERSON_PARAMS][MAX_STR_LEN], char delim[]) {
    int index = 0;
    //get the first token
    char* token = strtok(str, delim);
    //walk through other tokens until reaching a null char ('\0') ,get each word separated by ',' to an array
    while (token != NULL && index < PERSON_PARAMS) {
        strcpy(arr[index], token);
        //counting the tokens
        index++;
        token = strtok(NULL, delim);
    }
}

static Person newPerson(char arr[PERSON_PARAMS][MAX_STR_LEN]){
    char* eptr;
    Person person;
    strcpy(person.firstName, arr[0]);
    strcpy(person.lastName, arr[1]);
    person.dateOfBirth.day = atoi(arr[2]);
    person.dateOfBirth.month = atoi(arr[3]);
    person.dateOfBirth.year = atoi(arr[4]);
    person.height = atoi(arr[5]);
    person.weight = strtod(arr[6], &eptr);
    return person;
}

static double bmiCalc(Person person){
    return person.weight / (person.height * person.height);
}

int comparePersonByFirstName(void *arr, int i, int j) {
    Person *persons = (Person *) arr;
    return strcmp(persons[i].firstName, persons[j].firstName);
}

int comparePersonByLastName(void *arr, int i, int j) {
    Person *persons = (Person *) arr;
    return strcmp(persons[i].lastName, persons[j].lastName);
}

int comparePersonByWeight(void *arr, int i, int j) {
    double diff = 0;
    Person *persons = (Person *) arr;
    diff = persons[i].weight - persons[j].weight;
    if(diff > 0){
        return 1;
    }
    if(diff < 0){
        return -1;
    }
    return 0;
}

int comparePersonByHeight(void *arr, int i, int j){
    Person *persons = (Person *) arr;
    return persons[i].height - persons[j].height;
}

int comparePersonByBMI(void *arr, int i, int j){
    double diff = 0;
    Person *persons = (Person *) arr;
    diff = bmiCalc(persons[i]) - bmiCalc(persons[j]);
    if(diff > 0){
        return 1;
    }
    if(diff < 0){
        return -1;
    }
    return 0;
}

int comparePersonByDate(void *arr, int i, int j){
    int yearDiff = 0, monthDiff = 0, dayDiff = 0;
    Person *persons = (Person *) arr;
    yearDiff = persons[i].dateOfBirth.year - persons[j].dateOfBirth.year;
    monthDiff = persons[i].dateOfBirth.month - persons[j].dateOfBirth.month;
    dayDiff = persons[i].dateOfBirth.day - persons[j].dateOfBirth.day;
    if(yearDiff){
        return yearDiff;
    }
    if(monthDiff){
        return monthDiff;
    }
    return dayDiff;
}

void swapPersons(void *arr, int i, int j){
    Person *persons = (Person *) arr;
    Person tmp = persons[i];
    persons[i] = persons[j];
    persons[j] = tmp;
}

void load(const char* inputFile, Person persons[], int* numOfPersonsPtr){
    char str[MAX_STR_LEN];
    char personArr[PERSON_PARAMS][MAX_STR_LEN];
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("File not found: %s\n", inputFile);
        return;
    }
    while (fgets(str, MAX_STR_LEN, input)){
        strSplit(str, personArr, DELIM);
        persons[*numOfPersonsPtr] = newPerson(personArr);
        (*numOfPersonsPtr)++;
    }
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
    }
}

void save(const char* outputFile, Person persons[], int numOfPersons){
    char tmp[MAX_STR_LEN];
    FILE* output = fopen(outputFile, "a");
    if (!output) {
        printf("Error with file: %s\n", outputFile);
        return;
    }
    for (int i = 0; i < numOfPersons; ++i) {
        personToStr(persons[i], tmp);
        fputs(tmp, output);
    }
    if (fclose(output)) {
        printf("Error with closing file: %s\n", outputFile);
    }
}


