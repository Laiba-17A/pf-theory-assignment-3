
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int validateEmail(char* email){
    if (email==NULL || strlen(email)==0){
        return 0;
    }
    int count=0,i;
    for(i=0;i<strlen(email);i++){
        if(email[i]=='@'){
            count++;
        }
    }
    if (count!=1){
        return 0;
    }
    char* atPosition=strchr(email,'@');
    if (atPosition==NULL || strchr(atPosition,'.')==NULL){
        return 0;
    }
    return 1;
}
int main(){
    char* email=NULL;
    size_t size=0;
    printf("Enter an email address: ");
    email=(char*)malloc(100*sizeof(char));
    if(email==NULL){
        printf("Memory allocation failed!\n");
        return 1;
    }
    fgets(email,100,stdin);
    email[strcspn(email,"\n")]=0;
    if(validateEmail(email)){
        printf("Valid Email\n");
    }
	else{
        printf("Invalid Email\n");
    }
    free(email);
    return 0;
}