#include "mbed.h"
#include "C12832.h"
#include "LM75B.h"
#include <stdlib.h>     /* srand, rand */
#include <list>         /* liste from stl */


C12832 LCD(p5,p7,p6,p8,p11);
DigitalIn ju(p15);
DigitalIn jd(p12);
DigitalIn jl(p13);
DigitalIn jc(p14);
DigitalIn jr(p16);
AnalogIn pot1 (p19);
AnalogIn pot2 (p20);
DigitalOut Led1 (LED1);
DigitalOut Led2 (LED2);
DigitalOut Led3 (LED3);
DigitalOut Led4 (LED4);

int GuessNum(int Players){
    float res;
    int s1=0;
    int s2=0;
    float g1;
    float g2;
    int w=0;
    float t = 0;
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("Regle :\n Nous allons generer un nombre entre 0 et 1...");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("Tourner votre potentiometre dans\nle temps impartie pour essayer\nde le deviner...");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("la personne qui devine\nle plus proche gagne 1 point!");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("Le premier a 3 point gagne.");
    wait(2);
    while(jc!=1){
        wait(0.2);
    }
    t=0;
    while(s1!= 3 and s2!= 3){  //On sot de ce while si l'un des deux jouers atteint 3 points
        t=0; //t gets reset
        res=rand()%100; //genere le nombre a deviner entre 0 et 1 random
        res=res/100;
        while(t<5){ //On sort de cette boucle quand le timer s'écroule/quand on dépase le temps donné
            g1=pot1.read(); //Guess of player 1
            if(Players==1){
                g2=rand()%100;  //Guess of the AI
                g2=g2/100;
            }
            else{g2=pot2.read();} //Guess of player 2
            LCD.cls();
            LCD.locate(0,0);
            LCD.printf("Estimation j1 : %.2f \nEstimation j2 : %.2f\nTemps restant %.2f",g1,g2,5-t); //change res back to g2
            wait(0.2);
            t = t+ 0.2;
        }
        LCD.cls();
        if(((res-g1)*(res-g1))<=((res-g2)*(res-g2))){
            s1=s1+1;
            LCD.locate(0,0);
            LCD.printf("Joueur 1 gagne 1 point!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
        }
        else{
            s2=s2+1;
            LCD.locate(0,0);
            LCD.printf("Joueur 2 gagne 1 point!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
        }
        wait(2);
    }  //Fin du jeu
    LCD.cls();
    if(s1==3){ //Joueur 1 gagne
        w=1;
        LCD.locate(0,0);
        LCD.printf("Joueur 1 gagne!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
    }
    else{ //Joueur 2 gagne
        w=2;
        LCD.locate(0,0);
        LCD.printf("Joueur 2 gagne!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
    }
    wait(2);
    return w; //Renvoie le joueur qui a gagné
}
int PFC(int Players){
 int res;
    int s1=0;
    int s2=0;
    int g1;
    int g2;
    int w=0;
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("Regle :\nLe ciseau coupe la feuille...");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("la feuille envelope\nla pierre et la pierre\ncasse les ciseau.");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("Choisissez l'un des trois a\nl'aide du joystick...");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("si vous jouez à 2, faite\nle chacun votre tour.\nPremier a 3 points!!");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("Appuyer sur le joystick\npour commencer a jouer!");
    while(jc !=1){
        wait(0.2);
    }
    
    while(s1!= 3 and s2!= 3){  //On sot de ce while si l'un des deux joueurs atteint 3 points
	    g1= 4;
        g2= 4;
	    LCD.cls();
        LCD.locate(0,0);
        LCD.printf("Tour J1\nJoystick : en haut pierre,\n--> ciseau, <-- papier");
        while (g1 == 4){
            if ( ju ==1) { g1 = 0;} //input of of player 1
	        if ( jl ==1) { g1 = 1;}
	        if ( jr ==1) { g1 = 2;}
	    }

        if(Players==1){
            res = rand();  //choice of the AI 
	      	g2= res%3;
		}
        else{ 
            LCD.cls();
            wait(0.2);
            LCD.locate(0,0);
            LCD.printf("Tour J2\nJoystick : en haut pierre, --> ciseau, <-- papier");
	        while (g2 == 4){ //Turn of player 2
                if ( ju ==1) { g2 = 0;} //input of of player 1
                if ( jl ==1) { g2 =1;}
                if ( jr ==1) { g2 = 2;}
	        }
        }
        LCD.cls();

	    if(g1==g2){
            LCD.locate(0,0);
            LCD.printf("Pas de gagnant\nJoueur 1:%d\nJoueur 1:%d",s1,s2);
        }
        if((g1==0 and g2==2) or (g1==1 and g2==0) or (g1==2 and g2==1)){
            s1=s1+1;
            LCD.locate(0,0);
            LCD.printf("Joueur 1 gagne 1 point!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
        }
        if((g1==0 and g2==1) or (g1==1 and g2==2) or (g1==2 and g2==0)){
            s2=s2+1;
            LCD.locate(0,0);
            LCD.printf("Joueur 2 gagne 1 point!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
        }
        wait(2);
    }
        
    if(s1==3){ //Joueur 1 gagne
        w=1;
        LCD.locate(0,0);
        LCD.printf("Joueur 1 gagne!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
    }
    else{ //Joueur 2 gagne
        w=2;
        LCD.locate(0,0);
        LCD.printf("Joueur 2 gagne!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
    }
    wait(2);
    return w; //Renvoie le joueur qui a gagné
}

int MemoGame(int Players){
    int s1=0; //score du joueur 1
    int s2=0; //score du joueur 2
    int r=1; //round
    int w=0;
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("Regles: Une series de LEDs\nva s'allumer et...");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("vous devez retenir l'ordre\ndans lequel ils apparaisent.");
    wait(2);
    LCD.cls();
    LCD.locate(0,0);
    LCD.printf("Appuyer sur le joystick pour commencer.");
    while(jc==0){wait(0.2);}
    while(r<4){ // Repete pour 3 tours
        wait(0.2);
        int t[r+1];
        for(int i=0;i<=r;i++){
            int l=rand()%4; //Randomly chooses a led to turn on
            if(l==0){
                Led1=1;
                t[i]=1;
            }
            if(l==1){
                Led2=1;
                t[i]=2;
            }
            if(l==2){
                Led3=1;
                t[i]=3;
            }
            if(l==3){
                Led4=1;
                t[i]=4;
            }
            wait(0.7);
            Led1=0; //Resets Leds
            Led2=0;
            Led3=0;
            Led4=0;
            wait(0.4);
        }
        bool res1=true;
        int ErrP1=0; //Si le joueur 1 fait ume erreur cela indinque l'emplacement
        LCD.cls();
        LCD.locate(0,0);
        LCD.printf("Joueur 1, a votre tour de deviner");
        wait(1);
        LCD.cls();
        int input=0;
        for(int j=0;j<=r;j++){ //checks if the input of the player 1 is correct
            input=0;
            while(input==0){ //Wait for player input
                LCD.cls();
                LCD.locate(0,0);
                LCD.printf("Joystick up:Led1, right:led2, down:led3, left:led4\nLed:%d",j+1);
                if(ju==1){input=1;}
                if(jr==1){input=2;}
                if(jd==1){input=3;}
                if(jl==1){input=4;}
                wait(0.1);
            }
            if(input != t[j]){
                res1=false;
                ErrP1=j;
                LCD.cls();
                LCD.locate(0,0);
                LCD.printf("Joueur 1 se trompe a la lumiere %d",j+1);
                break;
            }
            input=0;
        }
        wait(0.5);
        bool res2=true;
        int ErrP2=0; //Si le joueur 2 fait ume erreur cela indinque l'emplacement
        LCD.cls();
        LCD.locate(0,0);
        LCD.printf("Joueur 2, a votre tour de deviner");
        wait(1);
        LCD.cls();
        for(int h=0;h<=r;h++){ //checks if the input of the player 2/AI is correct
            input=0;
            while(input==0){ //Wait for player input
                LCD.cls();
                LCD.locate(0,0);
                LCD.printf("Joystick up:Led1, right:led2, down:led3, left:led4\nLed:%d",h+1);
                if(Players==1){
                    if(ju==1){input=1;}
                    if(jr==1){input=2;}
                    if(jd==1){input=3;}
                    if(jl==1){input=4;}
                }
                else{
                input=((rand()%4)+1);
                }
                wait(0.2);
            }
            if(input != t[h]){
                res2=false;
                ErrP2=h;
                LCD.cls();
                LCD.locate(0,0);
                LCD.printf("Joueur 2 se trompe a la lumiere %d",h+1);
                break;
            }
            input=0;
        }
        wait(0.5);
        if(res1==true and res2==true){  //Assigne les points, 1 point chacun si les deux ont bon ou faux au meme endroit, si l'un des deux a bon et l'autre a faux ou faux avant celui qui a bon ou faux apres gagne 1 point
            s1+=1;
            s2+=1;
            LCD.cls();
            LCD.locate(0,0);
            LCD.printf("Vous avez tout les deux bon, 1 point chacun!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
        }
        if(res1==true and res2==false){
            s1+=1;
            LCD.cls();
            LCD.locate(0,0);
            LCD.printf("Joueur 2 a faux, 1 point au joueur 1!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
        }
        if(res1==false and res2==true){
            s2+=1;
            LCD.cls();
            LCD.locate(0,0);
            LCD.printf("Joueur 1 a faux, 1 point au joueur 2!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
        }
        if(res1==false and res2==false){
            if(ErrP1==ErrP2){
                s1+=1;
                s2+=1;
                LCD.cls();
                LCD.locate(0,0);
                LCD.printf("Vous avez tout les deux faux, 1 point chacun!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
            }
            if(ErrP1>ErrP2){
                s1+=1;
                LCD.cls();
                LCD.locate(0,0);
                LCD.printf("Joueur 2 a faux en premier, 1 point au joueur 1!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
            }
            if(ErrP1<ErrP2){
                s2+=1;
                LCD.cls();
                LCD.locate(0,0);
                LCD.printf("Joueur 1 a faux en premier, 1 point au joueur 2!\nJoueur 1:%d\nJoueur 2:%d",s1,s2);
            }
        }
        r+=1;
    }
    if(s1>s2){ //Designe le gagnant en fonction des points
        w=1;
        LCD.cls();
        LCD.locate(0,0);
        LCD.printf("Joueur 1 a plus de points, joueur 1 gagne!!");
    } 
    if(s1<s2){
        w=2;
        LCD.cls();
        LCD.locate(0,0);
        LCD.printf("Joueur 2 a plus de points, joueur 2 gagne!!");
    }
    if(s1==s2){
        w=3;
        LCD.cls();
        LCD.locate(0,0);
        LCD.printf("Vous avez tout les deux le meme nombre de points.\nOn a deux gagnants");
    }
    wait(0.5);
    return w;
}

int Games(int GameSelect,int PlayersNi){
    int w=0;
    if(GameSelect==1){w=PFC(PlayersNi);}
    if(GameSelect==2){w=GuessNum(PlayersNi);}
    if(GameSelect==3){w=MemoGame(PlayersNi);}
    return w;
}

int main() {
    /*x=64
    y=16
    while(1) {
        LCD.cls();
        LCD.rect(64,16,x+4,y-8,-1);
        wait(0.2);
    }
    */
    int G1=16;
    int G2=16;
    int r=0;// r=1 if player 1 gets to the end first and r=2 if player 2 gets to the end first
    int GameSelect;
    int PlayersN=0;
    LCD.locate(0,0);
    LCD.printf("Select number of players:\nJoystick up for 1\nJoystick down for 2");
    while(PlayersN==0){              //Select number of players
        if(ju==1){PlayersN=1;}
        if(jd==1){PlayersN=2;}
    }
    while(r==0){
        GameSelect=(rand()%3)+1;
        LCD.cls();
        LCD.fillcircle(16,8,2,-1);
        LCD.fillcircle(48,8,2,-1);
        LCD.fillcircle(80,8,2,-1);
        LCD.fillcircle(112,8,2,-1);
        LCD.fillcircle(16,24,2,-1);
        LCD.fillcircle(48,24,2,-1);
        LCD.fillcircle(80,24,2,-1);
        LCD.fillcircle(112,24,2,-1);

        LCD.circle(G1,8,4,-1);
        LCD.circle(G2,24,4,-1);
        wait(1);
        int w=Games(GameSelect,PlayersN);
        if(w==1){G1=G1+32;}
        if(w==2){G2=G2+32;}
        if(w==3){G1=G1+32; G2=G2+32;}
        if(G1>112 and G2<112){
            LCD.cls();
            LCD.printf("Player 1 won!");
            r=1;
        }
        if(G2>112 and G1<112){
            LCD.cls();
            LCD.printf("Player 2 won!");
            r=2;
        }
        if(G2>112 and G1>112){
            LCD.cls();
            LCD.printf("Both players won!");
            r=3;
        }
        wait(0.2);
    }
    if(r==1){
        return 69;
    }
    else{
        return 0;
    }
}

