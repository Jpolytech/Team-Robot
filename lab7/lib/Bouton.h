#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//classe pour la gestion du bouton sur le portD (PD2)
class {
    public:
    Bouton();
    Bouton(volatile uint8_t* ddrx,
                        volatile uint8_t* pinx,
                        uint8_t setPos) : 
                        ddrx_(ddrx), 
                        portx_(pinx),
                        setPos_(setPos), 
    {
        *ddrx_ &= ~(1 << setPos);
        buttonIsPushed_ = false;
    }
    bool isButtonPressed();
    void allowISR1();
    void allowISR2();
    void newISR(vector vecteur); //reverifiers
    bool getLastButtonState();

    private:
    bool buttonIsPushed_;
    uint8_t portx_;
    uint8_t setPos_;
    uint8_t* ddrx_;
}