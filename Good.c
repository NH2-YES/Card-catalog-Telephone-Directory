#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

struct tel_dir{
    char name[80];
    char number[20];
    unsigned code;
}tel[MAX];
int top=0;

int menu();
void enter();
void load();
void save();
void find();

int main(void){
    int choice;
    load();

        do{
            choice = menu();            
            switch(choice){
                case 1: enter();
                    break;
                case 2: load();
                    break;
                case 3: save();
                    break;
                case 4: find();
                    break;
                case 5: break;
            }
        }while(choice!=5);

    return 0;
}

int menu(void){

    char str[80];
    int i;

    printf("1. Enter\n");
    printf("2. Load\n");
    printf("3. save\n");
    printf("4. find\n");
    printf("5. Exit\n");

    do{
        printf("Enter your choice:\n ");
        gets(str);
        i = atoi(str);
        
        printf("\n");
    }while(i<1 || i>5);
    return i;
}

void enter(void){
    char temp[MAX];
    int i;
    for(i=top; i<MAX; i++){
        printf("Enter the name: ");
        fgets(tel[i].name, sizeof(tel[i].name), stdin);
        tel[i].name[strcspn(tel[i].name, "\n")]='\0';
        if(!*tel[i].name) break;

        printf("Enter the area code: ");
        gets(temp);
        tel[i].code= atoi(temp);

        printf("Enter the number: ");
        fgets(tel[i].number, sizeof(tel[i].number), stdin);
        tel[i].number[strcspn(tel[i].number, "\n")]='\0';
    }
    top=i;
}
 
 void display(int i){
    printf("Name: %s\n", tel[i].name);
    printf("With area code: %u\n", tel[i].code);
    printf("And number: %s\n", tel[i].number);
}


void find_name(){
    char name[80];
    int found,i;

    printf("Enter the name to find: \n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")]='\0';
    found=0;
    for(i=0; i<top; i++){
        if(!strcmp(name, tel[i].name)){
            display(i);
            found=1;
            printf("\n");
        }
        if(!found){
            printf("Name not found");
        }
    }    
}

void find_number(){
    char number[80];
    int found,i;

    printf("Enter the number to find: \n");
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")]='\0';
    found=0;
    for(i=0; i<top; i++){
        if(!strcmp(number, tel[i].number)){
            display(i);
            found=1;
            printf("\n");
        }
        if(!found){
            printf("Name not found");
        }
    }    
}
void load(void){

    FILE *fp;

    if((fp=fopen("tel_dir", "rb"))==NULL){
        printf("tel_dir file not on disk\n");
        return;
    }
    if((fread(&top, sizeof top, 1, fp))!=1){
        printf("Error reading count.\n");
        exit(1);
    }
    if((fread(tel, sizeof tel, 1, fp))!=1){
        printf("Error reading telephone directory data.\n");
        exit(1);
    }
    fclose(fp);
}
void save(void){
    
    FILE *fp;

    if((fp=fopen("tel_dir", "wb"))==NULL){
        printf("tel_dir file not on disk");
        return;
    }
    if((fwrite(&top, sizeof top, 1, fp))!=1){
        printf("Error writing count.\n");
        exit(1);
    }
    if((fwrite(tel, sizeof tel, 1, fp))!=1){
        printf("Error writing telephone directory data.\n");
        exit(1);
    }
    fclose(fp);
}

void find(void){
    char name[80];
    int found,i;
    int ch;
    printf("What do you want to search ?\n");
    printf("1. Name\n");
    printf("2. Number\n");
    ch=getchar();
    getchar();
    switch(ch){
        case '1':
            find_name();
          break;
        case '2':
            find_number();
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}

