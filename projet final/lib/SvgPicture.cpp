#include "SvgPicture.h"
#include "Uart.h"

void SvgPicture::header()
{
    char header[] = "<!DOCTYPE html>\n"
                    "<html>\n"
                    "<body>\n"
                    "<!-- Dimensions image svg -->\n"
                    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\"\n"
                    "     width=\"1000\" height=\"600\" viewBox=\"0 0 1700 600\">";

    transmitString(header, strlen(header));
}

void SvgPicture::foot()
{
    char footer[] = "</svg>\n"
                    "\n"
                    "</body>\n"
                    "</html>";

    transmitString(footer, strlen(footer));
}

void SvgPicture::drawTable()
{
    char table[] = "<rect xmlns=\"http://www.w3.org/2000/svg\" x=\"96\" y=\"48\" width=\"960\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>";

    transmitString(table, strlen(table));
}

void SvgPicture::drawBlackDots()
{
}

void SvgPicture::drawRedDot()
{
}

void SvgPicture::drawGreyDisks()
{
    // the x and y coordinates need to change according to what the Sensor class will detect
    // char greyDisk[] = "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"black\" stroke-width=\"4\" fill=\"black\" />";

    // transmitString(greyDisk, strlen(greyDisk));
}

void SvgPicture::writeTeamInformation()
{
    char infoEquipe[] = "<text xmlns=\"http://www.w3.org/2000/svg\" x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">section 01 -- équipe 0108 -- BOB</text>";

    transmitString(infoEquipe, strlen(infoEquipe));
}
