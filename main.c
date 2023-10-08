#include <stdio.h>
#include <stdlib.h>

//game numbers
int frame = 1;
int start = 0;
int input = 0;
int checkInput = 0;
int room = 0;
int level = 1;
int x = 0;

//player numbers
int playerX = 10;
int playerY = 7;
int damage = 0;
int playerAlive = 1;

//enemy numbers
int enemyX = 10;
int enemyY = 7;
int enemyStop = 0;
int inCombat = 0;

int enemyCount = 1;

//room creation numbers
int tileX = 0;
int tileY = 0;
int doorX = 0;
int doorY = 0;
int door2X = 0;
int door2Y = 0;

//stats
int playerStrength = 5;
int playerHP = 15;
int playerMaxHP = 15;
int playerToughness = 0;
int playerAgility = 4;
int enemyStrength = 3;
int enemyHP = 5;
int enemyToughness = 2;


//skeleton
int skeletonHP = 5;
int skeletonStrength = 3;
int skeletonToughness = 2;
int skeletonDC = 10;

//wolf
int wolfHP = 2;
int wolfStrength = 4;
int wolfToughness = 0;
int wolfDC = 10;

//ghoul
int ghoulHP = 10;
int ghoulStrength = 2;
int ghoulToughness = 2;
int ghoulDC = 5;

//king
int kingHP = 100;
int kingStrength = 15;
int kingToughness = 10;
int kingDC = 10;

//who is
int isSkeleton = 1;
int isWolf = 2;
int isGhoul = 3;
int isKing = 4;
int randEnemy = 0;

//enemy arrays
int enemyRoom[] = {1, 2, 3};
int enemyAlive[] = {1, 1, 1};
int enemyType[] = {1, 2, 3, 4};

//enemy positions
int r1enemy[] = {10, 7};
int r2enemy[] = {10, 7};
int r3enemy[] = {10, 7};

//combat numbers
int thrw = 10;
int enemyThrw = 0;
int dc = 0;

//Inventory and drops
int dropChance = 0;

//inventory
int cArmor = 0;
int rArmor = 0;
int lArmor = 0;

int cSword = 0;
int rSword = 0;
int lSword = 0;

//item stats
int cSwordStrength = 5;
int rSwordStrength = 10;
int lSwordStrength = 25;

int cArmorToughness = 2;
int rArmorToughness = 5;
int lArmorToughness = 15;

//Items equipped
int swordEquipped[] = {0, 0, 0};
int armorEquipped[] = {0, 0, 0};

int lGem = 0;

int sPotion = 0;


//score
FILE *fw, *fr;
int score = 0;
char meno[] = {"Default"};




int saveScore() {

fw = fopen("SCORE.txt", "w");

fprintf(fw, "%s: %d", meno, score);


}


int dropsFunction() {

    dropChance = rand() % 100;

    if(dropChance <= 20){


        dropChance = rand() % 100;

        if(dropChance <= 60){
            cArmor++;
        }else if(dropChance > 60 && dropChance <= 90){
            rArmor++;
        }else if(dropChance > 90 && dropChance <= 100){
            lArmor++;
        }



    }else if(dropChance > 20 && dropChance <= 40){


        dropChance = rand() % 100;

        if(dropChance <= 60){
            cSword++;
        }else if(dropChance > 60 && dropChance <= 90){
            rSword++;
        }else if(dropChance > 90 && dropChance <= 100){
            lSword++;
        }


    }else if(dropChance > 40 && dropChance <= 90){

        lGem++;

    }else if(dropChance > 90 && dropChance <= 100){

        sPotion++;

    }


}

int rng(){
    thrw = rand() % 20 + 1;
    enemyThrw = rand() % 10 + 1;
}

int menu(){
    printf("\n");

    printf("Pokus o hru\n");
    printf("Zacat Y/N?\n");

    scanf("%c", &start);

    if (start == 89){
        system("cls");

    }

}

int gameover(){
    printf("GAME OVER\n");
    printf("Zomrel si.\n");
    printf("Zadajte meno hraca: ");
    scanf("%s", &meno);
}


int movement(){

    checkInput = scanf("%d", &input);

    //check if input is a char
    if(checkInput != 1){
        printf("invalid input");
        exit(0);
    }

    //Input

    if(input == 44 && lGem >= 1){
        lGem--;

        if(playerHP < playerMaxHP){

            if(playerHP >= playerMaxHP - 5){
                playerHP = playerMaxHP;
            }else if(playerHP < playerMaxHP - 5){
                playerHP = playerHP + 5;
            }

        }else if(playerHP == playerMaxHP){
            playerHP = playerHP + 3;
            playerMaxHP = playerMaxHP + 3;

        }else if(playerHP > playerMaxHP){
            playerHP = playerMaxHP;
        }

    }

    if(input == 66 && sPotion >= 1){
        sPotion--;

        playerStrength = playerStrength + 3;
    }

    //equip sword

    if(input == 71 && cSword >= 1 && swordEquipped[0] == 0){


            cSword--;

            playerStrength = playerStrength + cSwordStrength;

        swordEquipped[0] = 1;

        if(swordEquipped[1] == 1){
            swordEquipped[1] = 0;
            playerStrength = playerStrength - rSwordStrength;
            rSword++;
        }else if(swordEquipped[2] == 1){
            swordEquipped[2] = 0;
            playerStrength = playerStrength - lSwordStrength;
            lSword++;
        }

    }

    if(input == 72 && rSword >= 1 && swordEquipped[1] == 0){

            rSword--;

            playerStrength = playerStrength + rSwordStrength;

        swordEquipped[1] = 1;

        if(swordEquipped[0] == 1){
            swordEquipped[0] = 0;
            playerStrength = playerStrength - cSwordStrength;
            cSword++;
        }else if(swordEquipped[2] == 1){
            swordEquipped[2] = 0;
            playerStrength = playerStrength - lSwordStrength;
            lSword++;
        }

    }

    if(input == 73 && lSword >= 1 && swordEquipped[2] == 0){


            lSword--;

            playerStrength = playerStrength + lSwordStrength;

        swordEquipped[2] = 1;

        if(swordEquipped[0] == 1){
            swordEquipped[0] = 0;
            playerStrength = playerStrength - cSwordStrength;
            cSword++;
        }else if(swordEquipped[1] == 1){
            swordEquipped[1] = 0;
            playerStrength = playerStrength - rSwordStrength;
            rSword++;
        }

    }


    //equip armor

    if(input == 81 && cArmor >= 1 && armorEquipped[0] == 0){


            cArmor--;

            playerToughness = playerToughness + cArmorToughness;

        armorEquipped[0] = 1;

        if(armorEquipped[1] == 1){
            armorEquipped[1] = 0;
            playerToughness = playerToughness - rArmorToughness;
            rArmor++;
        }else if(armorEquipped[2] == 1){
            armorEquipped[2] = 0;
            playerToughness = playerToughness - lArmorToughness;
            lArmor++;
        }

    }

    if(input == 82 && rArmor >= 1 && armorEquipped[1] == 0){


            rArmor--;

            playerToughness = playerToughness + rArmorToughness;

        armorEquipped[1] = 1;

        if(armorEquipped[0] == 1){
            armorEquipped[0] = 0;
            playerToughness = playerToughness - cArmorToughness;
            cArmor++;
        }else if(armorEquipped[2] == 1){
            armorEquipped[2] = 0;
            playerToughness = playerToughness - lArmorToughness;
            lArmor++;
        }

    }

    if(input == 83 && lArmor >= 1 && armorEquipped[2] == 0){


            lArmor--;

            playerToughness = playerToughness + lArmorToughness;

        armorEquipped[2] = 1;

        if(armorEquipped[1] == 1){
            armorEquipped[1] = 0;
            playerToughness = playerToughness - rArmorToughness;
            rArmor++;
        }else if(armorEquipped[0] == 1){
            armorEquipped[0] = 0;
            playerToughness = playerToughness - cArmorToughness;
            cArmor++;
        }

    }





    //Discarding items

    if(input == 4444){
        lGem--;

        if(lGem < 0){
            lGem = 0;
        }
    }

    if(input == 6666){
        sPotion--;

        if(sPotion < 0){
            sPotion = 0;
        }
    }

    if(input == 7171){
        cSword--;

        if(cSword < 0){
            cSword = 0;
        }
    }

    if(input == 7272){
        rSword--;

        if(rSword < 0){
            rSword = 0;
        }
    }

    if(input == 7373){
        lSword--;

        if(lSword < 0){
            lSword = 0;
        }
    }

    if(input == 8181){
        cArmor--;

        if(cArmor < 0){
            cArmor = 0;
        }
    }

    if(input == 8282){
        rArmor--;

        if(rArmor < 0){
            rArmor = 0;
        }
    }

    if(input == 8383){
        lArmor--;

        if(lArmor < 0){
            lArmor = 0;
        }
    }





    //move player
    if(input == 5){
        playerY--;
        input = 0;
    }else if(input == 2){
        playerY++;
        input = 0;
    }else if(input == 1){
        playerX--;
        input = 0;
    }else if(input == 3){
        playerX++;
        input = 0;
    }

    //boss fight input

    if(input == 1234 && room == 0){
        room = 0;
        level = 99999;
        enemyAlive[0] = 0;
        enemyAlive[1] = 0;

        enemyType[2] = 4;

        playerHP = playerMaxHP;
    }



    //collisions, nenavidim nested statementy

    //nenavidim tento cely blok kodu
if (room == 0){

    //X collisions
    if(playerX == doorX && (playerY == doorY || playerY == doorY + 1 || playerY == doorY + 2)){
        //room logis
        switch(room){
            case 0: room = 1;
                    break;
            case 1: room = 0;
                    break;
            case 2: room = 3;
                    break;
            case 3: room = 2;
        }

        //Transfer player
        playerX = playerX - 18;

    }else if(playerX == 19){
        playerX--;
    }else if(playerX == 0){
        playerX++;
    }

    //Y collisions
    if(playerY == door2Y && (playerX == door2X || playerX == door2X + 1 || playerX == door2X + 2)){
        //room logic
        switch(room){
            case 0: room = 2;
                    break;
            case 1: room = 3;
                    break;
            case 2: room = 0;
                    break;
            case 3: room = 1;
                    break;
        }

        //transfer player
        playerY = playerY + 13;

    }else if(playerY == 0){
        playerY++;
    }else if(playerY == 14){
        playerY--;
    }


}else if(room == 1){


    //X collisions
    if(playerX == doorX && (playerY == doorY || playerY == doorY + 1 || playerY == doorY + 2)){
        //room logis
        switch(room){
            case 0: room = 1;
                    break;
            case 1: room = 0;
                    break;
            case 2: room = 3;
                    break;
            case 3: room = 2;
        }

        //transfer player
        playerX = playerX + 18;

    }else if(playerX == 19){
        playerX--;
    }else if(playerX == 0){
        playerX++;
    }

    //Y collisions
    if(playerY == door2Y && (playerX == door2X || playerX == door2X + 1 || playerX == door2X + 2)){
        //room logic
        switch(room){
            case 0: room = 2;
                    break;
            case 1: room = 3;
                    break;
            case 2: room = 0;
                    break;
            case 3: room = 1;
                    break;
        }

        //transfer player
        playerY = playerY + 13;


    }else if(playerY == 0){
        playerY++;
    }else if(playerY == 14){
        playerY--;
    }

}else if(room == 2){

    //X collisions
    if(playerX == doorX && (playerY == doorY || playerY == doorY + 1 || playerY == doorY + 2)){
        //room logis
        switch(room){
            case 0: room = 1;
                    break;
            case 1: room = 0;
                    break;
            case 2: room = 3;
                    break;
            case 3: room = 2;
        }

        //transfer player
        playerX = playerX - 18;

    }else if(playerX == 19){
        playerX--;
    }else if(playerX == 0){
        playerX++;
    }

    //Y collisions
    if(playerY == door2Y && (playerX == door2X || playerX == door2X + 1 || playerX == door2X + 2)){
        //room logic
        switch(room){
            case 0: room = 2;
                    break;
            case 1: room = 3;
                    break;
            case 2: room = 0;
                    break;
            case 3: room = 1;
                    break;
        }

        //transfer player
        playerY = playerY - 13;

    }else if(playerY == 0){
        playerY++;
    }else if(playerY == 14){
        playerY--;
    }

}else if(room == 3){

    //X collisions
    if(playerX == doorX && (playerY == doorY || playerY == doorY + 1 || playerY == doorY + 2)){
        //room logis
        switch(room){
            case 0: room = 1;
                    break;
            case 1: room = 0;
                    break;
            case 2: room = 3;
                    break;
            case 3: room = 2;
        }

        //transfer player
        playerX = playerX + 18;

    }else if(playerX == 19){
        playerX--;
    }else if(playerX == 0){
        playerX++;
    }

    //Y collisions
    if(playerY == door2Y && (playerX == door2X || playerX == door2X + 1 || playerX == door2X + 2)){
        //room logic
        switch(room){
            case 0: room = 2;
                    break;
            case 1: room = 3;
                    break;
            case 2: room = 0;
                    break;
            case 3: room = 1;
                    break;
        }

        //transfer player
        playerY = playerY - 13;

    }else if(playerY == 0){
        playerY++;
    }else if(playerY == 14){
        playerY--;
    }

}



}

//START OF ROOM FUNCTIONS
int room0(){

    //set up coordinates
    doorX = 19;
    doorY = 6;
    door2X = 9;
    door2Y = 0;
    room = 0;


    //draw the room, until we reach Y = 15, x++
    while(tileY != 15){

        //draw player
        if( (playerX == tileX && playerY == tileY) && playerAlive == 1){
            printf("%%");
            tileX++;
        }

        //draw walls
        if(tileX == 0 || tileX == 19 || tileY == 0 || tileY == 14){

            //draw doors
            if(tileX == doorX && (tileY == doorY || tileY == doorY + 1 || tileY == doorY + 2)){
                printf("#");
            }else if(tileY == door2Y && (tileX == door2X || tileX == door2X + 1 || tileX == door2X + 2)){
                printf("#");
            }else{
                printf("I");
            }

        }else{
            printf(" ");
        }

        tileX++;

        if(tileX == 20){
           printf("\n");
           tileX = 0;
           tileY++;
        }
    }

}

int room1(){

    //set up new coordinates
    doorX = 0;
    doorY = 6;
    door2X = 9;
    door2Y = 0;
    room = 1;

    //draw the room, until we reach Y = 15, x++
    while(tileY != 15){

        //draw player
        if( (playerX == tileX && playerY == tileY) && playerAlive == 1){
            printf("%%");
            tileX++;
        }

        //draw Enemy
        if(enemyX == tileX && enemyY == tileY && enemyRoom[0] == 1 && enemyAlive[0] == 1){

            if(enemyType[0] == isSkeleton){
                    printf("?");
                    tileX++;
            }else if(enemyType[0] == isWolf){
                    printf("4");
                    tileX++;
            }else if(enemyType[0] == isGhoul){
                    printf("8");
                    tileX++;
            }

        }


        //draw walls
        if(tileX == 0 || tileX == 19 || tileY == 0 || tileY == 14){

            //draw doors
            if(tileX == doorX && (tileY == doorY || tileY == doorY + 1 || tileY == doorY + 2)){
                printf("#");
            }else if(tileY == door2Y && (tileX == door2X || tileX == door2X + 1 || tileX == door2X + 2)){
                printf("#");
            }else{
                printf("I");
            }

        }else{
            printf(" ");
        }

        tileX++;

        if(tileX == 20){
           printf("\n");
           tileX = 0;
           tileY++;
        }
    }
}

int room2(){

    //set up coordinates
    doorX = 19;
    doorY = 6;
    door2X = 9;
    door2Y = 14;
    room = 2;

    //draw the room, until we reach Y = 15, x++
    while(tileY != 15){

        //draw player
        if( (playerX == tileX && playerY == tileY) && playerAlive == 1){
            printf("%%");
            tileX++;
        }

        //draw Enemy
        if(enemyX == tileX && enemyY == tileY && enemyRoom[1] == 2 && enemyAlive[1] == 1){

            if(enemyType[1] == isSkeleton){
                    printf("?");
                    tileX++;
            }else if(enemyType[1] == isWolf){
                    printf("4");
                    tileX++;
            }else if(enemyType[1] == isGhoul){
                    printf("8");
                    tileX++;
            }

        }


        //draw walls
        if(tileX == 0 || tileX == 19 || tileY == 0 || tileY == 14){

            //draw doors
            if(tileX == doorX && (tileY == doorY || tileY == doorY + 1 || tileY == doorY + 2)){
                printf("#");
            }else if(tileY == door2Y && (tileX == door2X || tileX == door2X + 1 || tileX == door2X + 2)){
                printf("#");
            }else{
                printf("I");
            }

        }else{
            printf(" ");
        }

        tileX++;

        if(tileX == 20){
           printf("\n");
           tileX = 0;
           tileY++;
        }
    }

}

int room3(){

    //set up new coordinates
    doorX = 0;
    doorY = 6;
    door2X = 9;
    door2Y = 14;
    room = 3;

    //draw the room, until we reach Y = 15, x++
    while(tileY != 15){

        //draw player
        if( (playerX == tileX && playerY == tileY) && playerAlive == 1){
            printf("%%");
            tileX++;
        }

        //draw Enemy
        if(enemyX == tileX && enemyY == tileY && enemyRoom[2] == 3 && enemyAlive[2] == 1){

            if(enemyType[2] == isSkeleton){
                    printf("?");
                    tileX++;
            }else if(enemyType[2] == isWolf){
                    printf("4");
                    tileX++;
            }else if(enemyType[2] == isGhoul){
                    printf("8");
                    tileX++;
            }else if(enemyType[2] == isKing){
                    printf("*");
                    tileX++;
            }

        }


        //draw walls
        if(tileX == 0 || tileX == 19 || tileY == 0 || tileY == 14){

            //draw doors
            if(tileX == doorX && (tileY == doorY || tileY == doorY + 1 || tileY == doorY + 2)){
                printf("#");
            }else if(tileY == door2Y && (tileX == door2X || tileX == door2X + 1 || tileX == door2X + 2)){
                printf("#");
            }else{
                printf("I");
            }

        }else{
            printf(" ");
        }

        tileX++;

        if(tileX == 20){
           printf("\n");
           tileX = 0;
           tileY++;
        }
    }

}
//END OF ROOM FUNCTIONS

int enemyGeneration(){

    while(x < 3){


    if(x == 1){
    randEnemy = rand() % 3 + 1;
    enemyType[0] = randEnemy;
    }else if(x == 2){
    randEnemy = rand() % 3 + 1;
    enemyType[1] = randEnemy;
    }else if(x == 3){
    randEnemy = rand() % 3 + 1;
    enemyType[2] = randEnemy;
    }

    x = x + 1;

    }

}



int enemyMovement(){

    if(room == 1){
        enemyX = r1enemy[0];
        enemyY = r1enemy[1];
    }else if(room == 2){
        enemyX = r2enemy[0];
        enemyY = r2enemy[1];
    }else if(room == 3){
        enemyX = r3enemy[0];
        enemyY = r3enemy[1];
    }


        int dx = playerX - enemyX;
        int dy = playerY - enemyY;

    if(enemyType[2] != isKing){
        if(enemyStop == 0){
            if(dx < 0){
                enemyX--;
            }else if(dx > 0){
                enemyX++;
            }else if(dx == 0){
                enemyX;
            }

            enemyStop = 1;
        }else if(enemyStop == 1){

            if(dy < 0){
                enemyY--;
            }else if(dy > 0){
                enemyY++;
            }else if(dy == 0){
                enemyY;
            }

            enemyStop = 0;
        }
    }else if(enemyType[3] == isKing){
        if(enemyStop == 0){
            if(dx < 0){
                enemyX = enemyX - 2;
            }else if(dx > 0){
                enemyX++;
            }else if(dx == 0){
                enemyX = enemyX + 2;
            }

            enemyStop = 1;
        }else if(enemyStop == 1){

            if(dy < 0){
                enemyY =  enemyY - 2;
            }else if(dy > 0){
                enemyY = enemyY + 2;
            }else if(dy == 0){
                enemyY;
            }

            enemyStop = 0;
        }
    }

    if(room == 1){
        r1enemy[0] = enemyX;
        r1enemy[1] = enemyY;
    }else if(room == 2){
        r2enemy[0] = enemyX;
        r2enemy[1] = enemyY;
    }else if(room == 3){
        r3enemy[0] = enemyX;
        r3enemy[1] = enemyY;
    }

}

int combat(){

        if(room == 1){

            if(enemyType[0] == isSkeleton){
                printf("Si v boji s kostlivcom!\n");

                //stat allocation
                dc = skeletonDC;
                enemyToughness = skeletonToughness;
                enemyHP = skeletonHP;
                enemyStrength = skeletonStrength;

            }else if(enemyType[0] == isWolf){
                printf("Si v boji s vlkom!\n");

                //stat allocation
                dc = wolfDC;
                enemyToughness = wolfToughness;
                enemyHP = wolfHP;
                enemyStrength = wolfStrength;

            }else if(enemyType[0] == isGhoul){
                printf("Si v boji s upirom!\n");

                //stat allocation
                dc = ghoulDC;
                enemyToughness = ghoulToughness;
                enemyHP = ghoulHP;
                enemyStrength = ghoulStrength;
            }

        }else if(room == 2){

            if(enemyType[1] == isSkeleton){
                printf("Si v boji s kostlivcom!\n");

                //stat allocation
                dc = skeletonDC;
                enemyToughness = skeletonToughness;
                enemyHP = skeletonHP;
                enemyStrength = skeletonStrength;

            }else if(enemyType[1] == isWolf){
                printf("Si v boji s vlkom!\n");

                //stat allocation
                dc = wolfDC;
                enemyToughness = wolfToughness;
                enemyHP = wolfHP;
                enemyStrength = wolfStrength;

            }else if(enemyType[1] == isGhoul){
                printf("Si v boji s upirom!\n");

                //stat allocation
                dc = ghoulDC;
                enemyToughness = ghoulToughness;
                enemyHP = ghoulHP;
                enemyStrength = ghoulStrength;
            }

        }else if(room == 3){

            if(enemyType[2] == isSkeleton){
                printf("Si v boji s kostlivcom!\n");

                //stat allocation
                dc = skeletonDC;
                enemyToughness = skeletonToughness;
                enemyHP = skeletonHP;
                enemyStrength = skeletonStrength;

            }else if(enemyType[2] == isWolf){
                printf("Si v boji s vlkom!\n");

                //stat allocation
                dc = wolfDC;
                enemyToughness = wolfToughness;
                enemyHP = wolfHP;
                enemyStrength = wolfStrength;

            }else if(enemyType[2] == isGhoul){
                printf("Si v boji s upirom!\n");

                //stat allocation
                dc = ghoulDC;
                enemyToughness = ghoulToughness;
                enemyHP = ghoulHP;
                enemyStrength = ghoulStrength;
            }else if(enemyType[2] == isKing){
                printf("Si v boji s Kralom!\n");

                //stat allocation
                dc = kingDC;
                enemyToughness = kingToughness;
                enemyHP = kingHP;
                enemyStrength = kingStrength;
            }

        }

        while (inCombat == 1){

            rng();


            if(enemyHP <= 0){

                if(room == 1){
                    enemyAlive[0] = 0;
                }else if(room == 2){
                    enemyAlive[1] = 0;
                }else if(room == 3){
                    enemyAlive[2] = 0;
                }

                score = score + 10;
                inCombat = 0;
                break;
            }

            if(playerHP <= 0){

                inCombat = 0;
                playerAlive = 0;
                frame = -10;
                break;

            }


            printf("Utocis:\n");
                if(thrw >= dc){
                    damage = playerStrength - enemyToughness;
                    if(damage < 0){
                        damage = 0;
                    }
                    enemyHP = enemyHP - damage;
                    printf("Zasiahol si nepriatela za %d HP\n", damage);
                }else{
                    printf("Netrafil si nepriatela\n");
                }

            sleep(2);



            if(enemyHP <= 0){

                if(room == 1){
                    enemyAlive[0] = 0;
                }else if(room == 2){
                    enemyAlive[1] = 0;
                }else if(room == 3){
                    enemyAlive[2] = 0;
                }

                score = score + 10;
                inCombat = 0;
                break;
            }

            if(playerHP <= 0){

                inCombat = 0;
                playerAlive = 0;
                frame = -10;
                break;

            }

            printf("Utoci nepriatel:\n");

                if(enemyThrw >= playerAgility){
                    int playerDamage = enemyStrength - playerToughness;

                    if (playerDamage < 0){
                        playerDamage = 0;
                    }

                    playerHP = playerHP - playerDamage;

                    if(enemyStrength - playerToughness >= 0){
                    printf("Nepriatel ta zasiahol za %d HP\n", enemyStrength - playerToughness);
                    }else if(enemyStrength - playerToughness < 0){
                    printf("Odolal si utoku nepriatela\n");
                    }
                }else{
                    printf("Nepriatel ta netrafil\n");
                }



             sleep(2);
        }

}

int reset(){
    tileX = 0;
    tileY = 0;
    input = 0;

}

int main()
{

    //main game play loop
    menu();

    if(start != 89){
        return 0;
    }

    x = 0;

    enemyGeneration();

    while(frame > 0){

    switch(room){
        case 0: room0();
                break;
        case 1: room1();
                break;
        case 2: room2();
                break;
        case 3: room3();
                break;
    }

    printf("5 - hore, 2 - dole, \n1 - vlavo, 3 - vpravo\n");
    printf("\nStaty:\n");

    printf("Sila: %d", playerStrength);

    if(swordEquipped[0] == 1 && swordEquipped[1] == 0 && swordEquipped[2] == 0){
            printf("/%d", cSwordStrength);
    }else if(swordEquipped[1] == 1 && swordEquipped[2] == 0){
            printf("/%d", rSwordStrength);
    }else if(swordEquipped[2] == 1){
            printf("/%d", lSwordStrength);
    }

    printf("\n", playerStrength);
    printf("HP: %d/%d\n", playerHP, playerMaxHP);
    printf("Odolnost: %d\n", playerToughness);
    printf("Obratnost: %d\n", playerAgility);

    printf("Level: %d\n", level);

    printf("\nInventar:\n");

    if(lGem >= 1){

        printf("Kamen Zivota - %d [44]\n", lGem);

    }

    if(sPotion >= 1){

        printf("Kamen Sily - %d [66]\n", sPotion);

    }

    if(cArmor >= 1){

        printf("Jednoduche Brnenie - %d [81]\n", cArmor);

    }

    if(rArmor >= 1){

        printf("Vzacne Brnenie - %d [82]\n", rArmor);

    }

    if(lArmor >= 1){

        printf("Legendarne Brnenie - %d [83]\n", lArmor);

    }

    if(cSword >= 1){

        printf("Jednoduchy Mec - %d [71]\n", cSword);

    }

    if(rSword >= 1){

        printf("Vzacny Mec - %d [72]\n", rSword);

    }

    if(lSword >= 1){

        printf("Legendarny Mec - %d [73]\n", lSword);

    }

    if(level > 2 && room == 0){
    printf("[1234]\n");
    }


    //combat

    if( ( (playerX == enemyX || playerX == enemyX+1 || playerX == enemyX-1) && (playerY == enemyY ||playerY == enemyY+1 || playerY == enemyY-1) ) &&  ( (room == enemyRoom[0] && enemyAlive[0] == 1) || (room == enemyRoom[1] && enemyAlive[1] == 1)  || (room == enemyRoom[2] && enemyAlive[2] == 1) )  ){


            inCombat = 1;
            combat();
            dropsFunction();


    }else if(inCombat == 0){

        movement();

    if((room == enemyRoom[0] && enemyAlive[0] == 1) || (room == enemyRoom[1] && enemyAlive[1] == 1) || (room == enemyRoom[2] && enemyAlive[2] == 1)){
        enemyMovement();

      }


    }


    if(playerHP <= 0){
        system("cls");

    }

    if(playerHP > playerMaxHP){
        playerHP = playerMaxHP;
    }


    if(enemyAlive[0] == 0 && enemyAlive[1] == 0 && enemyAlive[2] == 0){
        level++;

        x = 0;

        enemyGeneration();


        playerHP = playerMaxHP;

        room = 0;
        playerX = 10;
        playerY = 7;
        enemyAlive[0] = 1;
        enemyAlive[1] = 1;
        enemyAlive[2] = 1;
        r1enemy[0] = 10;
        r1enemy[1] = 7;
        r2enemy[0] = 10;
        r2enemy[1] = 7;
        r3enemy[0] = 10;
        r3enemy[1] = 7;

    }

    reset();

    system("cls");

    frame++;

    }

    system("cls");
    gameover();
    saveScore();

}
