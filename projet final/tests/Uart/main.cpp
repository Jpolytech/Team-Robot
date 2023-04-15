#include <Uart.h>

ManagementUSART managementUSART = ManagementUSART();

int main()
{
    managementUSART.initialisation();
    char word[] = "Je suis à bout :D\n";
    managementUSART.transmissionString(word, sizeof(word));
}