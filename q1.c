#include <stdio.h>
#include <string.h>
struct Employee {
    int employeeCode;
    char employeeName[50];
    int dayOfJoining;
    int monthOfJoining;
    int yearOfJoining;
};
void assignDetails(struct Employee *emp);
void calculateTenure(struct Employee employees[], int size);

int main() {
	int i;
    struct Employee employees[4];
    for (i = 0; i < 4; i++) {
        printf("Enter details for Employee %d:\n", i + 1);
        assignDetails(&employees[i]);
    }
    calculateTenure(employees, 4);

    return 0;
}
void assignDetails(struct Employee *emp) {
    printf("Enter employee code: ");
    scanf("%d", &emp->employeeCode);

    printf("Enter employee name: ");
    getchar(); 
    fgets(emp->employeeName, sizeof(emp->employeeName), stdin);
    emp->employeeName[strcspn(emp->employeeName, "\n")] = '\0'; 

    printf("Enter date of joining (day month year): ");
    scanf("%d %d %d", &emp->dayOfJoining, &emp->monthOfJoining, &emp->yearOfJoining);
}
void calculateTenure(struct Employee employees[], int size) {
    int currentDay, currentMonth, currentYear;
    int count = 0,i;
   printf("Enter the current date (day month year): ");
    scanf("%d %d %d", &currentDay, &currentMonth, &currentYear);

    printf("\nEmployees with tenure of more than 3 years:\n");
    printf("\n");
    printf("Code\tName\t\tDate of Joining\t\tTenure (Years)\n");
    printf("\n");

    for (i = 0; i < size; i++) {
        int tenureYears = currentYear - employees[i].yearOfJoining;
        if (currentMonth < employees[i].monthOfJoining || 
           (currentMonth == employees[i].monthOfJoining && currentDay < employees[i].dayOfJoining)) {
            tenureYears--;
        }

        if (tenureYears > 3) {
            printf("%d\t%-15s\t%02d-%02d-%d\t\t%d\n", employees[i].employeeCode, 
                   employees[i].employeeName, 
                   employees[i].dayOfJoining, employees[i].monthOfJoining, employees[i].yearOfJoining, tenureYears);
            count++;
        }
    }

    printf("\n");
    printf("Total employees with tenure > 3 years: %d\n", count);
}