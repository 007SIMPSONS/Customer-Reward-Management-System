#include <stdio.h> // standard input output
#include <stdlib.h> // standard library
#include <windows.h> // for clearing console screen
#include <time.h> // for animations
#include <dirent.h>
#include <sys/stat.h>
#include <string.h> // to compare strings

void anim1();
void anim2();
void title();
void header();
void welcomeScr();
void memloginMenu();
void emploginMenu();
void mainMenu();
void newCustMenu();
void viewCustMenu();
void editCustMenu();
void viewRevMenu();
void topcusts();
char* concat(const char *s2);
void viewAll();
void mainMenu2(filename2);
void redeemRev(float CPts2, char *filename2); //////////////////

FILE *fp1;

struct customer {
  char nCustNam[30];
  int nCustAge;
  char nCustSex[10];
  char nCustNum[15];
  char nCustEID[20];
  float CAmtSpent;
  float CPts;
}info;

int main(){
    SMALL_RECT windowSize = {0, 0, 110, 27};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize); //to change the window size of the console
    SetConsoleTitle("REWARD MANAGEMENT SYSTEM");    //to change the title of the program console
    system("COLOR 0A");                             //to change colour of the program console text
    struct stat st = {0};
    if (stat("./data/", &st) == -1) {
    mkdir("./data/");}
    title();
    welcomeScr();

    return 0;
}

void anim1(){        // for the "loading header" animation
    printf("\t\t\t");
    int line1=0;
    while(line1<62){
        printf("/");
        line1+=1;
        Sleep(10);
    }
}

void anim2(){       // for the "loading dots" animation
    int line2=0;
    while(line2<5){
        printf(".");
        line2+=1;
        Sleep(50);
    }
}

void title(){
    anim1();
    printf("\n\n\t\t\t\t  ||||---- REWARD MANAGEMENT SYSTEM ----||||\n\n");
    anim1();
    printf("\n\n\nLoading modules"); anim2();
    printf("\nConnecting to Server"); anim2();
    printf("\nLoading Server Policies"); anim2();
    printf("\nInitiating Program"); anim2();
    Sleep(500);
}

void header(){
    system("cls");
    fflush(stdin);
    printf("\t\t\t//////////////////////////////////////////////////////////////");
    printf("\n\n\t\t\t\t  ||||---- REWARD MANAGEMENT SYSTEM ----||||\n\n");
    printf("\t\t\t//////////////////////////////////////////////////////////////");
}

void welcomeScr(){
    header();
    printf("\n\n<<<<<<< WELCOME >>>>>>>\n-----------------------\n");
    int opt1;
    printf("\nAre you a:\n1. Customer?\n2. Employee?\n\nOption: ");
    scanf(" %i", &opt1);
    if (opt1==1)
         memloginMenu();
    else if (opt1==2)
        emploginMenu();
    else{
        printf("\nIncorrect Option! Try Again!\n\n");
        Sleep(1000);
        welcomeScr();}
}

void memloginMenu(){
    header();
    printf("\n\n<<<<<<< Login to System >>>>>>>\n--------------------------------\n");
    char *nCustICPP[15], *pwd[15];
    printf("\nEnter your IC/Passport No.: ");
    scanf(" %[^\n]s", &nCustICPP);
    FILE *fp1;
    char* filename = concat(nCustICPP);
    fp1 = fopen(filename, "r");
    if (fp1 == NULL){
        printf("Customer account does not exist! Try Again! \n");
        Sleep(500);
        memloginMenu();
        }
    else {
        do{
            printf("Enter your Password \n(default password is IC/Passport No.) :");
            fflush(stdin);
            scanf(" %[^\n]s", &pwd);
            if (strcmp(nCustICPP,pwd) != 0)
                printf("\nIncorrect Password! Try Again!\n\n");
            else if (strcmp(nCustICPP,pwd) == 0){
                printf("\nLogin Successful! ");anim2();
                mainMenu2(filename);}
        }while(strcmp(nCustICPP,pwd) != 0);
    }
    Sleep(500);
}

void emploginMenu(){
    header();
    printf("\n\n<<<<<<< Login to System >>>>>>>\n-------------------------------\n");
    char ID[20];
    int PIN;
    do{
        printf("\nEnter your ID: ");
        fflush(stdin);
        scanf(" %[^\n]s", ID);
        printf("Enter your PIN: ");
        fflush(stdin);
        scanf("%i", &PIN);
        if (ID!="admin" && PIN!=1234){
                printf("\nLogin Unsuccessful! Try Again!\n");
                Sleep(500);}
        }while(ID!="admin" && PIN!=1234);
    printf("\nLogin Successful! ");anim2();
    Sleep(500);
    mainMenu();
}

void mainMenu(){
    header();
    printf("\n\n\t\t\t\t\t\t<< Main Menu >>\n\t\t\t\t\t      -------------------\n\n1. Add New Customer\n2. View Customers\n3. Edit Customer Details\n4. View Rewards\n5. View Top Customers\n\n0. Exit Program\n\nPlease Enter Your Choice >> ");
    int ch;
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        newCustMenu();
        break;
    case 2:
        viewCustMenu();
        break;
    case 3:
        editCustMenu();
        break;
    case 4:
        viewRevMenu();
        break;
    case 5:
        topcusts();
        break;
    case 0:
        exit(0); ///////////////////
        break;
    default:
        printf("\nInvalid Input! Please Try Again!\n\n");
        Sleep(1000);
        mainMenu();
        }
}

void takedetails(filename2){
    struct customer info;
    char *nCustICPP[15];
    FILE *fp1;
    fp1 = fopen(filename2, "w");
    printf("\nFull Name          : ");
    scanf(" %[^\n]s", &info.nCustNam); ////////////
    printf("\nAge                : ");
    scanf(" %i", &info.nCustAge);
    printf("\nSex                : ");
    scanf(" %[^\n]s", &info.nCustSex);
    printf("\nPhone Number       : ");
    scanf(" %[^\n]s", &info.nCustNum);
    printf("\nEmail ID           : ");
    scanf(" %[^\n]s", &info.nCustEID);
    printf("\nTotal Amount Spent : RM");
    scanf(" %f", &info.CAmtSpent);
    float Pts; float amt = info.CAmtSpent;
    Pts = (amt * 0.5);   ////////////////////////
    info.CPts = Pts;
    printf("\nReward Points      : %.0f\n",info.CPts);
    fwrite(&info, sizeof(struct customer), 1, fp1);
    fclose(fp1);
    printf("\n\n");
    system("pause");
    mainMenu();
}

void newCustMenu(){
    header();
    FILE *fp1;
    char *nCustICPP[15];
    printf("\n\n<<<<<<< New Customer Menu >>>>>>>\n---------------------------------\n\nPlease Enter the New Customer's Details >> \n\nEnter the Customer's IC/Passport No. : ");
    scanf(" %[^\n]s", &nCustICPP);
    char* filename = concat(nCustICPP);
    takedetails(filename);
}

void viewCustMenu(){
    header();
    FILE *fp1;
    char *nCustICPP[15];
    int ch3;
    printf("\n\n<<<<<<< View Customer Details Menu >>>>>>>\n------------------------------------------\n\n1. View all Customers' IC/Passport No.\n2. View each Customer's details manually\n0. Cancel and return to Main Menu\nOption: ");
    scanf(" %i", &ch3);
    switch (ch3)    {
    case 1:
        viewAll();
        break;
    case 2:
        printf("\nEnter the Customer's IC/Passport No. :");
        fflush(stdin);
        scanf(" %[^\n]s", &nCustICPP);
        char* filename = concat(nCustICPP);
        fp1 = fopen(filename, "r");
        if (fp1 == NULL){
            printf("\nCustomer account does not exist \n");
            viewCustMenu(); }
        else{
            struct customer info;
            while (fread (&info, sizeof(struct customer), 1, fp1))
              printf("\nFull Name          : %s\nAge                : %d\nSex                : %s\nPhone Number       : %s\nEmail ID           : %s\nTotal Amount Spent : RM%.2f\nReward Points      : %.0f",
                     info.nCustNam,info.nCustAge,info.nCustSex,info.nCustNum,info.nCustEID,info.CAmtSpent,info.CPts);
            fclose(fp1);
        }
        break;
    case 0:
        mainMenu();
        break;
    default:
        printf("\nInvalid Input! Please Try Again!\n\n");
        Sleep(1000);
        viewCustMenu();
        }
    printf("\n\n");
    system("pause");
    mainMenu();
}

void editCustMenu(){
    header();
    char *nCustICPP[15];
    FILE *fp1;
    printf("\n\n<<<<<<< Edit Customer Details Menu >>>>>>>\n------------------------------------------\n\nPlease Enter the Customer's IC/Passport No. >> ");
    scanf(" %s", &nCustICPP);
    char* filename = concat(nCustICPP);
    fp1 = fopen(filename, "r");
    if (fp1 == NULL){
        printf("\nCustomer account does not exist \n");
        Sleep(1000);
        mainMenu();
        }
    else{
        printf("\nPlease Enter the Customer's New Details >> \n");
        takedetails(filename);}
}

void viewRevMenu(){
    FILE * fp1;
    header();
    printf("\n\n<<<<<<< View Customer's Rewards Menu >>>>>>>");
    printf("\n--------------------------------------------\n\n");
    printf("Please Enter the Customer's IC/Passport No. >> ");
    char *nCustICPP[15];
    float CAmtSpent2;
    scanf(" %[^\n]s", &nCustICPP);
    printf("\n");
    char* filename = concat(nCustICPP);
    fp1 = fopen(filename, "r");
    if (fp1 == NULL){
        printf("Customer account does not exist \n");
        Sleep(1000);
        mainMenu(); }
    struct customer info;
            while (fread (&info, sizeof(struct customer), 1, fp1))
                printf("Total Amount Spent : RM%.2f\nReward Points      : %.0f",info.CAmtSpent,info.CPts);
    printf("\n\nEnter Additional Amount Spent\n(If Any or Enter any letter) : RM");
    fflush(stdin);
    scanf(" %f", &CAmtSpent2);
    info.CAmtSpent+=CAmtSpent2;
    info.CPts+=(CAmtSpent2*0.5);     /////////////////////////
    fclose(fp1);
    fp1 = fopen(filename, "w");     //reopened file to avoid doubling error /////////////
    printf("\nNew Total Amount Spent = RM%.2f", info.CAmtSpent);
    printf("\nNew Reward Points = %.0f", info.CPts);
    fwrite(&info, sizeof(struct customer), 1, fp1);
    fclose(fp1);
    printf("\n\n");
    system("pause");
    mainMenu();
}

void topcusts(){
    header();
    struct customer info;
    float CAmtSpent3[100];
    struct customer tempfiles[100];
    DIR *dirc;
    struct dirent *dir;
    char *files[100];
    int n=0, a, pos=0;
    dirc = opendir("./data");
    if (dirc)
    {
        while ((dir = readdir(dirc)) != NULL)
        {
            int length = strlen(dir->d_name);
            files[n] = malloc(strlen(dir->d_name)+1);
            strcpy(files[n],dir->d_name);
            FILE *fp2;
            fp2 = fopen(files[n], "r");
            fread (&info, sizeof(struct customer), 1, fp2);
            CAmtSpent3[n] = info.CAmtSpent;
            tempfiles[n] = info;
            fclose(fp2);
            n++;}
        closedir(dirc);}
    float tmp = CAmtSpent3[0];
    for(a=0; a<n;a++)
        {if(tmp < tempfiles[a].CAmtSpent)
            {tmp = tempfiles[a].CAmtSpent;
                pos = a;}}
    printf("\n\nOur Top Customer\n----------------\n\nFull Name          : %s\nTotal Amount Spent : RM%.2f\n\n",tempfiles[pos].nCustNam, tempfiles[pos].CAmtSpent);
    system("pause");
    mainMenu();
}

char* concat(const char *s2){
    char *result = malloc(strlen("./data/")+strlen(s2)+1);//+1 for the zero-terminator
    strcpy(result, "./data/");
    strcat(result, s2);
    return result;
}

void viewAll(){
    DIR *d;
    struct dirent *dir;
    d = opendir("./data");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    printf("\n");
    system("pause");
    mainMenu();
}

void mainMenu2(filename2){
    header();
    printf("\n\n<<<<<<< WELCOME >>>>>>>\n-----------------------\n\n");
    FILE *fp1;
    int opt2;
    fp1 = fopen(filename2, "r");
    struct customer info;
    while (fread (&info, sizeof(struct customer), 1, fp1))
      printf("Full Name          : %s\nAge                : %d\nSex                : %s\nPhone Number       : %s\nEmail ID           : %s\nTotal Amount Spent : RM%.2f\nReward Points      : %.0f",
             info.nCustNam,info.nCustAge,info.nCustSex,info.nCustNum,info.nCustEID,info.CAmtSpent,info.CPts);
    float CPts=info.CPts;
    fclose(fp1);
    printf("\n\n1.View Available Rewards\n0.Exit\nOption: ");
    scanf(" %i", &opt2);
    switch(opt2){
        case 0: exit(0);
        case 1: redeemRev(CPts, filename2);
            break;
        default:
            printf("\nInvalid Input! Please Try Again!\n\n");
            Sleep(1000);
            mainMenu2(filename2);
            }
}

void redeemRev(float CPts2, char *filename2){
    header();
    int opt3;
    int rev2=(int)CPts2/100;
    if (rev2>9)
        rev2=9;
    else if (rev2==0){
        printf("\n\nInsufficient reward points! You're not eligible for any rewards. Sorry!\n\n");system("pause");mainMenu2(filename2);}
    printf("\n\nYou're eligible for the following rewards:\n");
    switch(rev2){
        case 9:printf("\n9.(For 900 points)Free Spa for 2 at The AsiaSpa");
        case 8:
        case 7:printf("\n7.(For 700 points)35% off Total Bill at The Garden Homestay");
        case 6:
        case 5:printf("\n5.(For 500 points)RM25 Voucher at Aku Cafe");
        case 4:
        case 3:printf("\n3.(For 300 points)PappaDelivery RM30 Voucher");
        case 2:
        case 1:printf("\n1.(For 100 points)10%% off on your next purchase\n");break;
        default:printf("\nERROR!");exit(0);
            }
    printf("\nEnter the reward number to redeem it\nOr Enter \"0\" to Exit : ");
    fflush(stdin);
    scanf(" %1i", &opt3);
    float rePts;
    switch(opt3){
        case 0:exit(0);
        case 9:rePts=900; break;
        case 7:rePts=700; break;
        case 5:rePts=500; break;
        case 3:rePts=300; break;
        case 1:rePts=100; break;
        default:printf("\nInvalid Input! Please Try Again!");
            Sleep(1000); redeemRev(CPts2, filename2);
    }
    if ((rePts/100)>rev2){
        printf("\nInvalid Input! Please Try Again!");
            Sleep(1000); redeemRev(CPts2, filename2);
    }
    FILE * fp1;
    fp1 = fopen(filename2, "r");
    struct customer info;
    while (fread (&info, sizeof(struct customer), 1, fp1));
    fclose(fp1);
    fp1 = fopen(filename2, "w");     //reopened file to avoid doubling error
    info.CPts-=rePts;
    printf("\nNew Reward Points = %.0f\n\n", info.CPts);
    fwrite(&info, sizeof(struct customer), 1, fp1);
    fclose(fp1);
    system("pause");
    mainMenu2(filename2);
}

