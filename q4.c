#include <stdio.h>
#include <stdlib.h>

struct Employee{
int** ratings;
int numEmployees;
int numPeriods;
} ;

void inputEmployees(int*** ratings, int numEmployees, int numPeriods) {
for (int i = 0; i < numEmployees; i++) {
printf("Enter ratings for Employee %d (between 1 and 10):\n", i + 1);
for (int j = 0; j < numPeriods; j++) {
do {
printf(" Period %d: ", j + 1);
scanf("%d", &(*ratings)[i][j]);
if ((*ratings)[i][j] < 1 || (*ratings)[i][j] > 10) {
printf("Invalid input! Ratings must be between 1 and 10.\n");
}
} while ((*ratings)[i][j] < 1 || (*ratings)[i][j] > 10);
}
}
}

void displayPerformance(int** ratings, int numEmployees, int numPeriods) {
printf("\nPerformance Ratings:\n");
for (int i = 0; i < numEmployees; i++) {
printf("Employee %d: ", i + 1);
for (int j = 0; j < numPeriods; j++) {
printf("%d\t", ratings[i][j]);
}
printf("\n");
}
}

int findEmployeeOfTheYear(int** ratings, int numEmployees, int numPeriods) {
int maxi = 0;
double maxAvg = 0;
for (int i = 0; i < numEmployees; i++) {
int total = 0;
for (int j = 0; j < numPeriods; j++) {
total += ratings[i][j];
}
double average = (double)total / numPeriods;
if (average > maxAvg) {
maxAvg = average;
maxi = i;
}
}
return maxi;
}

int findHighestRatedPeriod(int** ratings, int numEmployees, int numPeriods) {
int maxi = 0;
double maxAvg = 0;
for (int j = 0; j < numPeriods; j++) {
int total = 0;
for (int i = 0; i < numEmployees; i++) {
total += ratings[i][j];
}
double average = (double)total / numEmployees;
if (average > maxAvg) {
maxAvg = average;
maxi = j;
}
}
return maxi;
}

int findWorstPerformingEmployee(int** ratings, int numEmployees, int numPeriods) {
int mini = 0;
double minAvg = 99999999; 
for (int i = 0; i < numEmployees; i++) {
int total = 0;
for (int j = 0; j < numPeriods; j++) {
total += ratings[i][j];
}
double average = (double)total / numPeriods;
if (average < minAvg) {
minAvg = average;
mini = i;
}
}
return mini;
}
int main() {
struct Employee emp;
printf("Enter the number of employees: ");
scanf("%d", &emp.numEmployees);
printf("Enter the number of evaluation periods: ");
scanf("%d", &emp.numPeriods);

emp.ratings = (int**)malloc(emp.numEmployees * sizeof(int*));
if (emp.ratings == NULL) {
printf("Memory allocation failed!\n");
return 1;
}
for (int i = 0; i < emp.numEmployees; i++) {
emp.ratings[i] = (int*)malloc(emp.numPeriods * sizeof(int));
if (emp.ratings[i] == NULL) {
printf("Memory allocation failed!\n");
return 1;
}
}

inputEmployees(&emp.ratings, emp.numEmployees, emp.numPeriods);

displayPerformance(emp.ratings, emp.numEmployees, emp.numPeriods);

int employeeOfYear = findEmployeeOfTheYear(emp.ratings, emp.numEmployees,
emp.numPeriods);
printf("Employee of the Year: Employee %d\n", employeeOfYear + 1);

int highestRatedPeriod = findHighestRatedPeriod(emp.ratings, emp.numEmployees,
emp.numPeriods);
printf("Highest Rated Period: Period %d\n", highestRatedPeriod + 1);

int worstEmployee = findWorstPerformingEmployee(emp.ratings, emp.numEmployees,
emp.numPeriods);
printf("Worst Performing Employee: Employee %d\n", worstEmployee + 1);

for (int i = 0; i < emp.numEmployees; i++) {
free(emp.ratings[i]);
}
free(emp.ratings);
return 0;
}