#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 50
#define MAX_GPS 20
#define MAX_EQUIPMENT 10

struct Weather {
    float temperature;
    float rainfall;
    float windspeed;
};

struct Crop {
    char type[MAX_NAME];
    int growth_stage;
    float expected_yield;
    struct Weather* weather;
};

struct Equipment {
    char name[MAX_NAME];
    int status;
    float fuel;
};

struct Sensor {
    float nutrients;
    float ph;
    int pest_activity;
};

struct Field {
    char gps[MAX_GPS];
    float soil_health;
    float moisture;
    struct Crop* crops;
    int crop_count;
    struct Equipment* equips;
    int equip_count;
    struct Sensor* sensors;
    int sensor_count;
};

struct Hub {
    char name[MAX_NAME];
    struct Field* fields;
    int field_count;
    float total_yield;
};

void addCrop(struct Field* field) {
    field->crop_count++;
    field->crops = realloc(field->crops, field->crop_count * sizeof(struct Crop));
    
    printf("Enter crop type: ");
    scanf("%s", field->crops[field->crop_count-1].type);
    printf("Enter growth stage (0-5): ");
    scanf("%d", &field->crops[field->crop_count-1].growth_stage);
    printf("Enter expected yield: ");
    scanf("%f", &field->crops[field->crop_count-1].expected_yield);
    
    field->crops[field->crop_count-1].weather = malloc(sizeof(struct Weather));
    printf("Enter temperature, rainfall, windspeed: ");
    scanf("%f %f %f", &field->crops[field->crop_count-1].weather->temperature,
          &field->crops[field->crop_count-1].weather->rainfall,
          &field->crops[field->crop_count-1].weather->windspeed);
}

void addEquipment(struct Field* field) {
    field->equip_count++;
    field->equips = realloc(field->equips, field->equip_count * sizeof(struct Equipment));
    
    printf("Enter equipment name: ");
    scanf("%s", field->equips[field->equip_count-1].name);
    printf("Enter status (1-active, 0-inactive): ");
    scanf("%d", &field->equips[field->equip_count-1].status);
    printf("Enter fuel level: ");
    scanf("%f", &field->equips[field->equip_count-1].fuel);
}

void displayField(struct Field field) {
    printf("\nField GPS: %s\n", field.gps);
    printf("Soil Health: %.2f\n", field.soil_health);
    printf("Moisture: %.2f\n", field.moisture);
    
    printf("\nCrops:\n");
    for(int i = 0; i < field.crop_count; i++) {
        printf("Type: %s, Growth: %d, Yield: %.2f\n", 
               field.crops[i].type, 
               field.crops[i].growth_stage,
               field.crops[i].expected_yield);
        printf("Weather - Temp: %.2f, Rain: %.2f, Wind: %.2f\n",
               field.crops[i].weather->temperature,
               field.crops[i].weather->rainfall,
               field.crops[i].weather->windspeed);
    }
    
    printf("\nEquipment:\n");
    for(int i = 0; i < field.equip_count; i++) {
        printf("Name: %s, Status: %d, Fuel: %.2f\n",
               field.equips[i].name,
               field.equips[i].status,
               field.equips[i].fuel);
    }
}

int main() {
    struct Hub* hub = malloc(sizeof(struct Hub));
    printf("Enter hub name: ");
    scanf("%s", hub->name);
    
    printf("Enter number of fields: ");
    scanf("%d", &hub->field_count);
    
    hub->fields = malloc(hub->field_count * sizeof(struct Field));
    
    for(int i = 0; i < hub->field_count; i++) {
        printf("\nField %d:\n", i+1);
        printf("Enter GPS coordinates: ");
        scanf("%s", hub->fields[i].gps);
        printf("Enter soil health (0-100): ");
        scanf("%f", &hub->fields[i].soil_health);
        printf("Enter moisture level (0-100): ");
        scanf("%f", &hub->fields[i].moisture);
        
        hub->fields[i].crop_count = 0;
        hub->fields[i].equip_count = 0;
        hub->fields[i].crops = NULL;
        hub->fields[i].equips = NULL;
    }
    
    int choice, field_num;
    while(1) {
        printf("\n1. Add Crop\n2. Add Equipment\n");
        printf("3. Display Field\n4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter field number (1-%d): ", hub->field_count);
                scanf("%d", &field_num);
                if(field_num > 0 && field_num <= hub->field_count)
                    addCrop(&hub->fields[field_num-1]);
                break;
                
            case 2:
                printf("Enter field number (1-%d): ", hub->field_count);
                scanf("%d", &field_num);
                if(field_num > 0 && field_num <= hub->field_count)
                    addEquipment(&hub->fields[field_num-1]);
                break;
                
            case 3:
                printf("Enter field number (1-%d): ", hub->field_count);
                scanf("%d", &field_num);
                if(field_num > 0 && field_num <= hub->field_count)
                    displayField(hub->fields[field_num-1]);
                break;
                
            case 4:
                for(int i = 0; i < hub->field_count; i++) {
                    for(int j = 0; j < hub->fields[i].crop_count; j++) {
                        free(hub->fields[i].crops[j].weather);
                    }
                    free(hub->fields[i].crops);
                    free(hub->fields[i].equips);
                }
                free(hub->fields);
                free(hub);
                return 0;
        }
    }
    return 0;
}