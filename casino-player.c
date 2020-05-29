#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <stdio_ext.h>

//function main menu
void menuAndChoice (int *choice) {
    int vetifyInput;
    printf("Welcome to the Casino. Here are your choices:\n");
    printf("1) Buy chips\n");
    printf("2) Sell chips\n");
    printf("3) Play Craps\n");
    printf("4) Play Arup's Game of Dice\n");
    printf("5) Status Report\n");
    printf("6) Quit\n");

    do {
        vetifyInput = scanf("%d", choice);
        fflush(stdin);
        //__fpurge(stdin);
    } while (vetifyInput != 1);
}

//function to roll dice
int rollDice () {
    int dice1, dice2;
    srand(time(NULL));

    dice1 = rand() % 6 + 1;
    dice2 = rand() % 6 + 1;

    printf("Your rolled a %d\n", dice1 + dice2);
    return dice1 + dice2;
}

//1 for win - 0 for lost
void winOrLost (int check, int spend, int *chip) {
    if (check == 1) {
        printf("You win!\n");
        *chip += spend * 2;
    } else if (check == 0) {
        printf("You lose!\n");
    }
}

//function to enter R and enter
void pressRAndEnter(char *check) {
    fflush(stdin);
    //__fpurge(stdin);
    *check = getchar();
}

// SELECT 1
void buyChip (int *money, int *chip) {
    int spend, check;

    do {
        printf("How much cash do you want to spend for chips?\n");
        check = scanf("%d", &spend);
        fflush(stdin);
        //__fpurge(stdin);
    } while (spend < 0 || check != 1);

    //if you spend more than money you have => error
    if (spend > *money) {
        printf("Sorry, you do not have that much money. No chips bought.\n");
    } else {
        *money -= spend;
        *chip += spend / 11;
        *money += spend % 11;
    }
}        

// SELECT 2
void sellChip (int *money, int *chip) {
    int spend, check;
    do {
        printf("How many chips do you want to sell?\n");
        check = scanf("%d", &spend);
        fflush(stdin);
        //__fpurge(stdin);
    } while (spend < 0 || check != 1);

    //if you spend more than chip you have => error
    if (spend > *chip) {
        printf("Sorry you do not have that many chip. No chips sold.\n");
    } else {    
        *money += spend*10;
        *chip -= spend;
    }
}

// SELECT 3
void playCraps (int *chip) {
    int dice, diceRoll, spend, checkType;
    char check, check1;
    
    do {
        printf("How many chips would you like to bet ?\n");
        fflush(stdin);
        //__fpurge(stdin);
        checkType = scanf("%d", &spend);
    } while (checkType != 1);    

    if (spend > *chip || spend < 1){
        printf("Sorry, that is not allowed. No game played.\n");
    } else {
        *chip -= spend;
        do {
            printf("press \"r\" and hit enter for first roll\n");
            pressRAndEnter(&check);
        } while (check != 'r');
        
        dice = rollDice();
            
        if (dice == 7 || dice == 11) {        
            winOrLost(1, spend, chip);    
        } else if (dice == 2 || dice == 3 || dice == 12) {        
            winOrLost(0, spend, chip);     
        } else {
            do {
                do {        
                    printf("press \"r\" and hit enter for next roll\n");
                    pressRAndEnter(&check1);
                } while (check1 != 'r');
    
                diceRoll = rollDice();

                if (diceRoll == dice) {
                    winOrLost(1, spend, chip);
                } else if (diceRoll == 7) {                                        
                    winOrLost(0, spend, chip);
                }        
            } while (diceRoll != dice && diceRoll != 7);      
        } 
    }
}

// SELECT 4
void playArup (int *chip) {
    int dice, diceRoll, spend, checkType;
    char check, check1;
    
    do {
        printf("How many chips would you like to bet ?\n");
        fflush(stdin);
        //__fpurge(stdin);
        checkType = scanf("%d", &spend);
    } while (checkType != 1);    

    if (spend > *chip || spend < 1){
        printf("Sorry, that is not allowed. No game played.\n");
    } else {
        *chip -= spend;
        do {
            printf("press \"r\" and hit enter for first roll\n");
            pressRAndEnter(&check);
        } while (check != 'r');
        
        dice = rollDice();
            
        if (dice == 11 || dice == 12) {        
            winOrLost(1, spend, chip);    
        } else if (dice == 2) {        
            winOrLost(0, spend, chip);     
        } else {
            do {        
                printf("press \"r\" and hit enter for next roll\n");
                pressRAndEnter(&check1);
            } while (check1 != 'r');
      
            diceRoll = rollDice();

            if (diceRoll > dice) {
                winOrLost(1, spend, chip);
            } else if (diceRoll <= 7) {                                        
                winOrLost(0, spend, chip);
            }     
        } 
    }
}

// SELECT 5
void displayMoneyChip (int money, int chip) {
    printf("You currently have $%d left and %d chips.\n", money, chip);
}

//SELECT 6
void sellChipAndDisplayMoney(int money, int chip){
    printf("after selling your chips, you have $%d. Thanks for playing\n", money + chip * 10);
}

//main
int main () {

    //money
    int money = 1000;
    int chip = 0;
    int choice;

    do {
        menuAndChoice(&choice);

        switch (choice) {
            case 1:
                buyChip(&money, &chip);
                break;
            
            case 2:
                sellChip(&money, &chip);
                break;
            
            case 3:
                playCraps(&chip);
                break;

            case 4:
                playArup(&chip);
                break;

            case 5:
                displayMoneyChip(money, chip);
                break;

            case 6:
                sellChipAndDisplayMoney(money, chip);
                break;
        }
    } while (choice != 6); 
}