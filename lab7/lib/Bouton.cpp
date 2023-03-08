#include <Bouton.h>

//*******************************
//Constructeur:
//Bouton sur le PORTD et PD2
//*******************************
Bouton::Bouton() {
    buttonIsPushed_ = false;
}


/*************************/
//methode qui verifie si le bouton est appuyé
//renvoie un booleen: vrai si appuyé
/*************************/
bool Bouton::isButtonPressed() {
    if(PIND & (1<<PD2)){
        _delay_ms(10);
        if(PIND & (1<<PD2)) {
            buttonIsPushed_ = true;
            return buttonIsPushed_;
        }
    }
    buttonIsPushed_ = false;
    return buttonIsPushed_;
}


/*************************/
//methode qui autorise les ISR
//aucun argument et ne renvoie rien
/*************************/
void Bouton::allowISR() {
    cli();
    
    // ajustement du registre EIMSK
    EIMSK |= (1 << INT0) ;

    // Ajustement de EICRA
    EICRA |= (1 << ISC00); //Chaque changement d'etat du bouton va generer un signal

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}


/*************************/
//methode d'interruption du bouton
//Prend en argument un vecteur (en general INT0_vect), et une variable volatile indiquant l'etat du bouton
/*************************/
void Bouton::newISR(vector vecteur, volatile bool& var) {
    ISR(vecteur) {
        _delay_ms(10);
        if(PIND & (1<<PD2)) {
            var = true;
            buttonIsPushed_ = true;
        } else{
            var = false;
            buttonIsPushed_ = false
        }
        EIFR |= (1<<INTF0);
    }
}


/*************************/
//methode qui renvoie le dernier etat connu du bouton
//renvoie un booleen
/*************************/
bool bouton::getLastButtonState() {
    return buttonIsPushed_;
}