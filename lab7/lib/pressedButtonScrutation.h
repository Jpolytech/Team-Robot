#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//classe pour la gestion du bouton sur le portD (PD2)
class pressedButtonScrutation {
    public:
        pressedButtonScrutation();
        void initialisation();
        bool getButtonState();

    private:
        bool buttonIsPushed_;
        uint8_t* ddrx_;
        uint8_t portx_;
        uint8_t setPos_;
        uint8_t clearPos_;
}

pressedButtonScrutation::pressedButtonScrutation( //constructeur paramétré
    volatile uint8_t* ddrx,
    volatile uint8_t* pinx,
    uint8_t setPos,
    uint8_t clearPos): 
    ddrx_(ddrx), 
    portx_(pinx),
    setPos_(setPos), 
    {
    ddrx_ = DDRD;
    *ddrx_ &= ~(1 << setPos) | (1 << clearPos); //pd2 en entree
    portx_ = PIND;
    buttonIsPushed_ = false;
    }