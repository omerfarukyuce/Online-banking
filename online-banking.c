#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct user {
  char phoneNo[50];
  char accountNo[50];
  char password[50];
  float balance;
};

int main(){
  struct user user,usr;
  char filename[50],phone[50],password[50],phone2[50];
  FILE *fp,*fptr;
  int opt,choice;
  int amount;
  char cont = 'y';
  
  printf("\nWhat do you want to do?");
  printf("\n\n1. Register your account.");
  printf("\n2. Login to your account.");

  printf("\n\nPlease enter your choice:\t");
  scanf("%d",&opt);
  
  if(opt == 1){
    system("clear");
    printf("\nEnter your account number:\t");
    scanf("%s",user.accountNo);
    printf("Enter your phone number:\t");
    scanf("%s",user.phoneNo);
    printf("Enter your new password:\t");
    scanf("%s",user.password);
    user.balance=0;
    
    stpcpy(filename,user.phoneNo);
    fp=fopen(strcat(filename,".dat"),"w");
    fwrite(&user,sizeof(user),1,fp);
    
    if(fwrite != 0){
      printf("Succesfully registered.");
    }
  }
  else if(opt == 2){
    system("clear");
    printf("\nPhone No.:\t");
    scanf("%s",phone);
    printf("Password:\t");
    scanf("%s",password);
    
    fp = fopen(strcat(phone,".dat"),"r");
    if(fp == NULL) printf("Account number not registered.");
    else {
      fread(&user,sizeof(struct user),1,fp);
      fclose(fp);
      if(!strcmp(password,user.password)){
        while(cont == 'y'){
        system("clear");
        printf("\n\tWelcome %s.",user.phoneNo);
        printf("\n1. Balance inquiry.");
        printf("\n2. Adding fund.");
        printf("\n3. Cash withdraw.");
        printf("\n4. Online transfer.");
        printf("\n5. Changing password.\n\n");
        scanf("%d",&choice);
        switch(choice){
          case 1:
            printf("Your current balance is $ %.2f.",user.balance);
            break;

          case 2:
            system("clear");
            printf("Enter amount to be added:\t");
            scanf("%d",&amount);
            user.balance += amount;
            fp = fopen(phone,"w");
            fwrite(&user,sizeof(struct user),1,fp);
            if(fwrite !=0) printf("\n\nYou have depostied $ %d.",amount);
            fclose(fp);
            break;

          case 3:
            system("clear");
            printf("Enter withdrawl amount:\t");
            scanf("%d",&amount);
            if(amount % 100 != 0) printf("\nSorry amount should be multiple of 100.");
            else if(amount>user.balance) printf("\nSorry insufficeint balance.");
            else {
              user.balance -= amount;
            fp = fopen(phone,"w");
            fwrite(&user,sizeof(struct user),1,fp);
            if(fwrite !=0) printf("\n\nYou have withdrawn $ %d.",amount);
            fclose(fp);
            }
            break;

          case 4://You can only transfer online with previously registered account.
            printf("Please enter the phone number to trasnfer balance:\t");
            scanf("%s",phone);
            printf("Enter the amount to transfer:\t");
            scanf("%d",&amount);
            
            if(amount > user.balance) printf("\nSorry insufficent balance.");
            else {
              fptr = fopen(strcat(phone,".dat"),"r");
              if(fptr==NULL) printf("Sorry number is not registered.");
              else {
                fread(&usr,sizeof(struct user),1,fptr);
                fclose(fptr);

                usr.balance += amount;

                fptr = fopen(phone,"w");
                fwrite(&usr,sizeof(struct user),1,fptr);
                if(fwrite != 0){          
                  printf("Your trasfer is completed. You have trasnfered $ %d to %s.",amount,usr.phoneNo);
                  fclose(fptr);
                  user.balance -= amount;
                  strcpy(filename,user.phoneNo);
                  fp = fopen(strcat(filename,".dat"),"w");
                  fwrite(&user,sizeof(struct user),1,fp);
                  fclose(fp);
                }
              }
            }
            break;
          case 5:
            printf("\n\nPlease enter your old password:\t");
            scanf("%s",password);
            if(!strcmp(password,user.password)){
              printf("\n\nPlease enter your new password:\t");
              scanf("%s",password);
              strcpy(user.password,password);
              strcpy(filename,user.phoneNo);
              
              fp = fopen(strcat(filename,".dat"),"w");
              fwrite(&user,sizeof(struct user),1,fp);
              fclose(fp);	
              printf("\nPassword succesfullly changed.");
            }else printf("\nSorry your password is wrong. Please try again.");

          default:
          break;
        }
        printf("\n\nDo you want to continue?[y/n]:\t");//Press y for yes, n for nor.
        scanf("%s",&cont);
        }
      }
      else {
        printf("Invalid password. Please try again.");
      }	
    }
    printf("\n\nThank you for banking with YUCE bank.\n\n");
  }else{
    printf("You should enter 1 or 2.");
  }

  return 0;
}
