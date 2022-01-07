/***********************
* Name: Lior Bazak
* ID: 207106709
* Assignment: ex_6
***********************/

#include "person.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PERSON_PARAMS 7

/*************************************************************************************************************
* Function Name: personToStr
* Input: Person person, char str[MAX_STR_LEN]
* Output: none
* Function Operation: the function gets a person and a char arr, concatenate the person params into a string
**************************************************************************************************************/
static void personToStr(Person person, char str[MAX_STR_LEN]) {
    sprintf(str, "%s,%s,%d,%d,%d,%d,%.2f\n", person.firstName,
            person.lastName,
            person.dateOfBirth.day,
            person.dateOfBirth.month,
            person.dateOfBirth.year,
            person.height,
            person.weight);
}

/*************************************************************************************************************
* Function Name: strSplit
* Input: char str[], char arr[PERSON_PARAMS][MAX_STR_LEN], char delim[]
* Output: none
* Function Operation: the function gets a string(str- array of chars) and splits the strings in it to separate
*                     words using the delimiter (delim), enter each string to arr.
**************************************************************************************************************/
static void strSplit(char str[], char arr[PERSON_PARAMS][MAX_STR_LEN], char delim[]) {
    int index = 0;
    //get the first token
    char *token = strtok(str, delim);
    //walk through other tokens until reaching a null char/ reach 7 strings ,get each str separated by ',' to an array
    while (token != NULL && index < PERSON_PARAMS) {
        strcpy(arr[index], token);
        //increase the index for the next arr insert
        index++;
        token = strtok(NULL, delim);
    }
}

/*************************************************************************************************************
* Function Name: newPerson
* Input: char arr[PERSON_PARAMS][MAX_STR_LEN]
* Output: Person
* Function Operation: the function gets an array of strings that each one is a person's parameter, and return
*                     the person with the characteristics entered to it.
**************************************************************************************************************/
static Person newPerson(char arr[PERSON_PARAMS][MAX_STR_LEN]) {
    char *eptr;
    Person person;
    //taking the 2 first strings as strings to the first & last names
    strcpy(person.firstName, arr[0]);
    strcpy(person.lastName, arr[1]);
    //taking the next strings, converting it to int using atoi and insert them to persons' params
    person.dateOfBirth.day = atoi(arr[2]);
    person.dateOfBirth.month = atoi(arr[3]);
    person.dateOfBirth.year = atoi(arr[4]);
    person.height = atoi(arr[5]);
    //converting the next string to double and insert it to the weigh param
    person.weight = strtod(arr[6], &eptr);
    return person;
}

/*************************************************************************************************************
* Function Name: bmiCalc
* Input: Person person
* Output: double (BMI)
* Function Operation: the function gets a person, takes its weigh and height, calc & return his BMI
**************************************************************************************************************/
static double bmiCalc(Person person) {
    double heightInM = (double) person.height / 100;
    return person.weight / (heightInM * heightInM);
}

/*************************************************************************************************************
* Function Name: comparePersonByFirstName
* Input: void *arr, int i, int j
* Output: int 
* Function Operation: the function gets an array of persons, and 2 indexes- compare the first names of the
*                     persons in the indexes and returns positive num if the first is bigger than the second
*                     (lexicographic), 0 if equal, else negative num
**************************************************************************************************************/
int comparePersonByFirstName(void *arr, int i, int j) {
    Person *persons = (Person *) arr;
    return strcmp(persons[i].firstName, persons[j].firstName);
}

/*************************************************************************************************************
* Function Name: comparePersonByLastName
* Input: void *arr, int i, int j
* Output: int 
* Function Operation: the function gets an array of persons, and 2 indexes- compare the last names of the
*                     persons in the indexes and returns positive num if the first is bigger than the second
*                     (lexicographic), 0 if equal, else negative num
**************************************************************************************************************/
int comparePersonByLastName(void *arr, int i, int j) {
    Person *persons = (Person *) arr;
    return strcmp(persons[i].lastName, persons[j].lastName);
}

/*************************************************************************************************************
* Function Name: comparePersonByWeight
* Input: void *arr, int i, int j
* Output: int 
* Function Operation: the function gets an array of persons, and 2 indexes- compare the weighs of the persons 
*                     in the indexes and return 1 if the first is bigger than the second, 0 if equal, else -1
**************************************************************************************************************/
int comparePersonByWeight(void *arr, int i, int j) {
    double diff = 0;
    Person *persons = (Person *) arr;
    //calc the difference between the weighs
    diff = persons[i].weight - persons[j].weight;
    if (diff > 0) {
        return 1;
    }
    if (diff < 0) {
        return -1;
    }
    return 0;
}

/*************************************************************************************************************
* Function Name: comparePersonByHeight
* Input: void *arr, int i, int j
* Output: int 
* Function Operation: the function gets an array of persons, and 2 indexes- compare the heights of the persons 
*                     in the indexes and returns positive num if the first is bigger than the second, 
*                     0 if equal, else negative num
**************************************************************************************************************/
int comparePersonByHeight(void *arr, int i, int j) {
    Person *persons = (Person *) arr;
    //the diff will be positive if the first is bigger
    return persons[i].height - persons[j].height;
}

/*************************************************************************************************************
* Function Name: comparePersonByBMI
* Input: void *arr, int i, int j
* Output: int 
* Function Operation: the function gets an array of persons, and 2 indexes- compare the BMIs of the persons in   
*                     the indexes and return 1 if the first is bigger than the second, 0 if equal, else -1
**************************************************************************************************************/
int comparePersonByBMI(void *arr, int i, int j) {
    double diff = 0;
    Person *persons = (Person *) arr;
    //the diff will be positive if the first is bigger
    diff = bmiCalc(persons[i]) - bmiCalc(persons[j]);
    if (diff > 0) {
        return 1;
    }
    if (diff < 0) {
        return -1;
    }
    return 0;
}

/***************************************************************************************************************
* Function Name: comparePersonByDate
* Input: void *arr, int i, int j
* Output: int
* Function Operation: the function gets an array of persons, and 2 indexes- compare the birth dates of the
*                     persons in the indexes and returns positive num if the first is bigger than the second,
*                     0 if equal, else negative num
****************************************************************************************************************/
int comparePersonByDate(void *arr, int i, int j) {
    int yearDiff = 0, monthDiff = 0, dayDiff = 0;
    Person *persons = (Person *) arr;
    //the diff will be positive if the first is bigger
    yearDiff = persons[i].dateOfBirth.year - persons[j].dateOfBirth.year;
    monthDiff = persons[i].dateOfBirth.month - persons[j].dateOfBirth.month;
    dayDiff = persons[i].dateOfBirth.day - persons[j].dateOfBirth.day;
    //start with checking if the year is different and return the diff (positive if the first bigger)
    if (yearDiff) {
        return yearDiff;
    }
    //if the years equal check if the month is different and return the diff (positive if the first bigger)
    if (monthDiff) {
        return monthDiff;
    }
    //if the months also equal return the days diff (positive if the first bigger, 0 if equal, neg if first smaller)
    return dayDiff;
}

/*************************************************************************************************************
* Function Name: swapPersons
* Input: void *arr, int i, int j
* Output: none
* Function Operation: the function gets a persons array and 2 indexes, and swap the places of the persons in
*                     the array
**************************************************************************************************************/
void swapPersons(void *arr, int i, int j) {
    Person *persons = (Person *) arr;
    Person tmp = persons[i];
    persons[i] = persons[j];
    persons[j] = tmp;
}

/*************************************************************************************************************
* Function Name: load
* Input: const char *inputFile, Person persons[], int *numOfPersonsPtr
* Output: none
* Function Operation: the function gets an input file and a person array, and load the persons from the input
*                     file into the array
**************************************************************************************************************/
void load(const char *inputFile, Person persons[], int *numOfPersonsPtr) {
    char str[MAX_STR_LEN];
    char personArr[PERSON_PARAMS][MAX_STR_LEN];
    //open the file in read mode
    FILE *input = fopen(inputFile, "r");
    if (!input) {
        printf("File not found: %s\n", inputFile);
        return;
    }
    //take all of the strings from the file until reaching the end
    while (fgets(str, MAX_STR_LEN, input)) {
        strSplit(str, personArr, DELIM);
        //take the splittes strings to a person and insert the person to the persons arr
        persons[*numOfPersonsPtr] = newPerson(personArr);
        //increase the num of persons
        (*numOfPersonsPtr)++;
    }
    //close the file
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
    }
}

/*************************************************************************************************************
* Function Name: save
* Input: const char *outputFile, Person persons[], int numOfPersons
* Output: none
* Function Operation: the function gets an output file and a person array, and saves the persons from the arr
*                     into the file
**************************************************************************************************************/
void save(const char *outputFile, Person persons[], int numOfPersons) {
    char tmp[MAX_STR_LEN];
    //open the output file in append mode
    FILE *output = fopen(outputFile, "a");
    if (!output) {
        printf("Error with file: %s\n", outputFile);
        return;
    }
    //go through all persons in the array, copy the person details to a row in the output file
    for (int i = 0; i < numOfPersons; ++i) {
        personToStr(persons[i], tmp);
        fputs(tmp, output);
    }
    //close the output file
    if (fclose(output)) {
        printf("Error with closing file: %s\n", outputFile);
    }
}


