#include <stdio.h>
#include "sorting.h"
#include "person.h"

#define MAX_LINES 100

const char* INPUTFILE = "persons.txt";
const char* OUTPUTFILE = "sorted.txt";

void plot(const char* inputFile) {
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("File not found: %s\n", inputFile);
        return;
    }
    char buffer[MAX_STR_LEN];
    while (fgets(buffer, MAX_STR_LEN, input)) {
        printf("%s", buffer);
    }
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
    }
}

int main() {
    Person persons[MAX_LINES];
    int numOfPersons = 0;
    load(INPUTFILE, persons, &numOfPersons);
    quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByFirstName);
    // quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByLastName);
    // quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByDate);
    // quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByWeight);
    // quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByHeight);
    // quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByBMI);
    save(OUTPUTFILE, persons, numOfPersons);
    plot(INPUTFILE);
    printf("sorting...");
    plot(OUTPUTFILE);
    return 0;
}
