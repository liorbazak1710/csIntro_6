#ifndef PERSON_H
#define PERSON_H

#define MAX_STR_LEN 100
#define DELIM ","

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char firstName[MAX_STR_LEN];
    char lastName[MAX_STR_LEN];
    Date dateOfBirth;
    int height;
    double weight;
} Person;

int comparePersonByFirstName(void* arr, int i, int j);
int comparePersonByLastName(void* arr, int i, int j);
int comparePersonByWeight(void* arr, int i, int j);
int comparePersonByHeight(void* arr, int i, int j);
int comparePersonByBMI(void* arr, int i, int j);
int comparePersonByDate(void* arr, int i, int j);

void swapPersons(void* arr, int i, int j);

void load(const char* inputFile, Person persons[], int* numOfPersonsPtr);
void save(const char* outputFile, Person persons[], int numOfPersons);

#endif
