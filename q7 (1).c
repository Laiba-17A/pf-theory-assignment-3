#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 50
#define MAX_CATEGORIES 5
#define MAX_DEVICES 3

struct Device {
    int resolution;
    float position;
    int bandwidth;
};

struct Content {
    char title[MAX_NAME];
    int rating;
    int runtime;
};

struct User {
    char name[MAX_NAME];
    float* category_scores;
    struct Device* devices;
    int device_count;
};

void addDevice(struct User* user) {
    user->device_count++;
    user->devices = realloc(user->devices, user->device_count * sizeof(struct Device));
    
    printf("Enter resolution (1-4): ");
    scanf("%d", &user->devices[user->device_count-1].resolution);
    printf("Enter last watched position: ");
    scanf("%f", &user->devices[user->device_count-1].position);
    printf("Enter bandwidth (1-10): ");
    scanf("%d", &user->devices[user->device_count-1].bandwidth);
}

void updateScore(struct User* user) {
    int category;
    printf("Categories:\n");
    printf("1. Action\n2. Drama\n3. Comedy\n");
    printf("4. Horror\n5. Scifi\n");
    printf("Select category: ");
    scanf("%d", &category);
    
    if(category > 0 && category <= MAX_CATEGORIES) {
        printf("Enter new score (0-10): ");
        scanf("%f", &user->category_scores[category-1]);
    }
}

void displayUser(struct User user) {
    printf("\nUser: %s\n", user.name);
    
    printf("Category Scores:\n");
    char* categories[] = {"Action", "Drama", "Comedy", "Horror", "Scifi"};
    for(int i = 0; i < MAX_CATEGORIES; i++) {
        printf("%s: %.2f\n", categories[i], user.category_scores[i]);
    }
    
    printf("\nDevices:\n");
    for(int i = 0; i < user.device_count; i++) {
        printf("Device %d:\n", i+1);
        printf("Resolution: %d\n", user.devices[i].resolution);
        printf("Position: %.2f\n", user.devices[i].position);
        printf("Bandwidth: %d\n", user.devices[i].bandwidth);
    }
}

int main() {
    int num_users;
    printf("Enter number of users: ");
    scanf("%d", &num_users);
    
    struct User* users = malloc(num_users * sizeof(struct User));
    struct Content* content_list = malloc(MAX_CATEGORIES * sizeof(struct Content));
    
    for(int i = 0; i < num_users; i++) {
        printf("\nUser %d name: ", i+1);
        scanf("%s", users[i].name);
        
        users[i].category_scores = malloc(MAX_CATEGORIES * sizeof(float));
        for(int j = 0; j < MAX_CATEGORIES; j++) {
            users[i].category_scores[j] = 0;
        }
        
        users[i].device_count = 0;
        users[i].devices = NULL;
    }
    
    int choice, user_num;
    while(1) {
        printf("\n1. Add Device\n2. Update Category Score\n");
        printf("3. Display User\n4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Select user (1-%d): ", num_users);
                scanf("%d", &user_num);
                if(user_num > 0 && user_num <= num_users) 
                    addDevice(&users[user_num-1]);
                break;
                
            case 2:
                printf("Select user (1-%d): ", num_users);
                scanf("%d", &user_num);
                if(user_num > 0 && user_num <= num_users)
                    updateScore(&users[user_num-1]);
                break;
                
            case 3:
                printf("Select user (1-%d): ", num_users);
                scanf("%d", &user_num);
                if(user_num > 0 && user_num <= num_users)
                    displayUser(users[user_num-1]);
                break;
                
            case 4:
                for(int i = 0; i < num_users; i++) {
                    free(users[i].category_scores);
                    free(users[i].devices);
                }
                free(users);
                free(content_list);
                return 0;
        }
    }
    return 0;
}