#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

int* supply_counts;

void clearScreen() {
   for(int i = 0; i < 50; i++) printf("\n");
}

void addSupply(char supplies[][MAX_NAME], int species_num, int* count) {
   char new_supply[MAX_NAME];
   printf("Enter supply name: ");
   scanf("%s", new_supply);
   
   strcpy(supplies[*count], new_supply);
   (*count)++;
}

void updateSupply(char supplies[][MAX_NAME], int count) {
   int choice;
   char new_name[MAX_NAME];
   
   printf("Which supply to update? (1-%d): ", count);
   scanf("%d", &choice);
   
   if(choice > 0 && choice <= count) {
       printf("Enter new name: ");
       scanf("%s", new_name);
       strcpy(supplies[choice-1], new_name);
       printf("Updated successfully!\n");
   } else {
       printf("Invalid choice!\n");
   }
}

void displaySupplies(char supplies[][MAX_NAME], int count, char species[]) {
   printf("\nSupplies for %s:\n", species);
   for(int i = 0; i < count; i++) {
       printf("%d. %s\n", i+1, supplies[i]);
   }
}

int main() {
   int num_species;
   char species_names[10][MAX_NAME];
   char supplies[10][50][MAX_NAME];
   supply_counts = malloc(10 * sizeof(int));
   int choice, species_choice;
   
   printf("Enter number of species (max 10): ");
   scanf("%d", &num_species);
   
   for(int i = 0; i < num_species; i++) {
       printf("Enter species %d name: ", i+1);
       scanf("%s", species_names[i]);
       supply_counts[i] = 0;
   }
   
   while(1) {
       printf("\n1. Add Supply\n");
       printf("2. Update Supply\n");
       printf("3. Display Inventory\n");
       printf("4. Exit\n");
       printf("Choice: ");
       scanf("%d", &choice);
       
       switch(choice) {
           case 1:
               printf("For which species? (1-%d): ", num_species);
               scanf("%d", &species_choice);
               if(species_choice > 0 && species_choice <= num_species) {
                   addSupply(supplies[species_choice-1], species_choice-1, &supply_counts[species_choice-1]);
               }
               break;
               
           case 2:
               printf("For which species? (1-%d): ", num_species);
               scanf("%d", &species_choice);
               if(species_choice > 0 && species_choice <= num_species) {
                   updateSupply(supplies[species_choice-1], supply_counts[species_choice-1]);
               }
               break;
               
           case 3:
               for(int i = 0; i < num_species; i++) {
                   displaySupplies(supplies[i], supply_counts[i], species_names[i]);
               }
               break;
               
           case 4:
               free(supply_counts);
               return 0;
               
           default:
               printf("Invalid choice!\n");
       }
   }
   return 0;
}