#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//classe pour la gestion du bouton sur le portD (PD2)
class {
    public:
    Bouton();
    bool isButtonPressed();
    void allowISR();
    void newISR(vector vecteur); //reverifiers
    bool getLastButtonState();

    private:
    bool buttonIsPushed_;
}