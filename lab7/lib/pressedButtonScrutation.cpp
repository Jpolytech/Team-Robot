#include <Bouton.h>

//*******************************
//Constructeur par defaut:
//Bouton sur le PORTD et PD2
//*******************************
Button::Button() { //pas sûr
    buttonIsPushed_ = false;
    DDRD &= ~(1 << PORTD2);
    portx_ = PIND;
    ddrx_ = DDRD;
}

/*************************/
//methode qui sensibilise les interruptions lors des changements d'état du bouton (rising & falling edges)
//aucun argument et ne renvoie rien
/*************************/
void initialisation (void) {
    cli (); 
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    EICRA &= ~(1 << ISC01); 
    EIFR |= (1 << INTF0); //pour clear les interruptions en + crées par le rebond
    sei ();
}

/*************************/
//methode qui renvoie le dernier etat connu du bouton
//renvoie un booleen
/*************************/
bool Button::getButtonState() {
    return buttonIsPushed_;
}