#include <pressedButtonScrutation.h>

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
bool pressedButtonScrutation::getButtonState() {
    return buttonIsPushed_;
}