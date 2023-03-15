#include <Debug.h>
ManagementUSART uart;

void print(uint16_t number)
{
    char buff[5];
    snprintf(buff, 5, "%d", number);
    print(buff);
}

void print(const char *message)
{
    uart.initialisation();
    uint16_t i = 0;
    while (message[i] != '\0')
    {
        uart.transmission(message[i++]);
    }
}