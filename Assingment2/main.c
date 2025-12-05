#include <stdio.h>
#include <stdlib.h>


bool userLogIn(int PIN)
{
    int userAttempts= 0;
    int userInput;
    while(true){
        if(userAttempts==3){
            printf("\n\nTOO MANY ATTEMPTS! ACCESS DENIED\n\n");
            return false;
        }
        printf("ENTER PIN: ");
        scanf("%d",&userInput);
        if(userInput==PIN){
            printf("\n\nACCESS GRANTED. DOOR UNLOCKED\n\n");
            return true;
        }else if(userAttempts<2){
            printf("\n\nYOU ENTERED AN INCORRECT PIN, %d ATTEMPTS REMAINING\n\n",2-userAttempts);
        }
        userAttempts ++;
    }

}

int customerOptions()
{
    int selectedTask;
    printf("\nSELECT A TASK:\n");
    printf("1. BALANCE INQUIRY\n");
    printf("2. DEPOSIT\n");
    printf("3. WITHDRAW\n");
    printf("4. EXIT\n\n");
    scanf("%d",&selectedTask);
    return selectedTask;
}

float* checkBalance()
{
    //Retrieves the user account balance and returns an address to it
    static float accountBalance = 25000.84;
    return &accountBalance;
}

void deposit(float amount)
{
    //adds the given amount to account balance
    *checkBalance() +=amount;
}

bool withdraw(float amount)
{
    float* accountBalanceAdrress = checkBalance();
    if(*accountBalanceAdrress<amount) return false;
    else{
        *checkBalance() -=amount;
        return true;
    }
}

int main()
{
    int PIN=8474;
    bool loginSuccessfull=userLogIn(PIN);
    float depositAmount,withdrawalAmount;
    float accountBalance = 8700.00;
    if(loginSuccessfull){
        int userChoice=customerOptions();
        while(userChoice != 4){
            switch(userChoice)
            {
                case 1:
                    printf("\n\nYOUR CURRENT ACCOUNT BALANCE IS KSH. %.2f\n\n",*checkBalance());
                    userChoice=customerOptions();
                    break;
                case 2:
                    printf("ENTER AMOUNT TO DEPOSIT: ");
                    scanf("%f",&depositAmount);
                    if(depositAmount<1.0)printf("\n\nYOU CANNOT DEPOSIT KSH. %f\n\n",depositAmount);
                    else{
                        deposit(depositAmount);
                        printf("\n\nKSH. %.2f HAS BEEN SUCCESSFULLY CREDITED TO YOUR ACCOUNT\n",depositAmount);
                        printf("YOUR NEW ACCOUNT BALANCE IS %.2f\n\n",*checkBalance());
                    }

                    userChoice=customerOptions();
                    break;
                case 3:
                    printf("ENTER AMOUNT TO WITHDRAW: ");
                    scanf("%f",&withdrawalAmount);
                    if(withdrawalAmount<1.0)printf("\n\nYOU CANNOT WITHDRAW KSH. %f\n\n",withdrawalAmount);
                    else if (withdraw(withdrawalAmount)){
                        printf("\n\nKSH. %.2f HAS BEEN SUCCESSFFULLY DEBITED FROM YOUR ACCOUNT\n", withdrawalAmount);
                        printf("YOUR NEW ACCOUNT BALANCE IS %.2f\n\n",*checkBalance());
                    }
                    else{
                        printf("\n\nYOU HAVE INSUFFICIENT BALANCE IN YOUR ACCOUNT. YOUR CURRENT ACCOUNT BALANCE IS KSH. %.2f\n\n",*checkBalance());
                    }
                    userChoice=customerOptions();
                    break;
                default:
                    printf("\n\nINVALID CHOICE! PLEASE ENTER A VALID MENU OPTION NUMBER\n\n");
                    userChoice = customerOptions();

            }
        }
        printf("\n\nYOU HAVE SUCCESSFULLY EXITED THE SYSTEM\n\n");

    }
    else printf("\n\nFAILED LOGIN! EXITING THE SYSTEM\n\n");
    return 0;
}
