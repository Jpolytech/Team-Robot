#include <avr/io.h>
#include <util/twi.h>

class ManagementUSART
{
public:
    ManagementUSART() = default;
    void initialisation();
    void transmission(uint8_t data);
    void transmissionString(char word[], uint8_t length);
};