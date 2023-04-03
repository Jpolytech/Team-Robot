#include "SvgPicture.h"
#include "Uart.h"

void SvgPicture::header()
{
    char header1[] = "<!DOCTYPE html>\n"
                     "<html>\n"
                     "<body>\n";

    char header2[] = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\"\n"
                     "     width=\"1000\" height=\"600\" viewBox=\"0 0 1700 600\">";

    transmitString(header1, strlen(header1));
    transmitString(header2, strlen(header2));
}

void SvgPicture::foot()
{
    char footer[] = "</svg>"
                    "</body>"
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
    char blackDot[NUM_DOTS][100];

    for (int i = 0; i < NUM_DOTS; i++)
    {
        int x = DOT_X + i * DOT_WIDTH;
        int y = DOT_Y;
        sprintf(blackDot[i], "<rect xmlns=\"http://www.w3.org/2000/svg\" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>", x, y, DOT_WIDTH, DOT_HEIGHT);
        transmitString(blackDot[i], strlen(blackDot[i]));
    }
}

void SvgPicture::drawRedDot()
{
    char redDot[] = "<rect xmlns=\"http://www.w3.org/2000/svg\" x=\"210\" y=\"430\" width=\"10\" height=\"10\" stroke=\"red\" stroke-width=\"1\" fill=\"red\"/>";

    transmitString(redDot, strlen(redDot));
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
