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

void SvgPicture::footer()
{
    char footer[] = "</svg>"
                    "</body>"
                    "</html>";
    transmitString(footer, strlen(footer));
}

void SvgPicture::drawTable()
{
    char table[] = "<rect xmlns=\"http://www.w3.org/2000/svg\" x=\"96\" y=\"48\" width=\"930\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>";
    transmitString(table, strlen(table));
}

void SvgPicture::drawBlackDots()
{
    char blackDot[N_BLACK_DOTS][];

    for (int i = 0; i < N_BLACK_DOTS; i++)
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

void SvgPicture::writeTeamInformation()
{
    char teamInfo1[] = "<text xmlns=\"http://www.w3.org/2000/svg\" x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">";
    char teamInfo2[] = "section 01 -- équipe 0108 -- BOB</text>";
    transmitString(teamInfo1, strlen(teamInfo1));
    transmitString(teamInfo2, strlen(teamInfo2));
}

void SvgPicture::drawGreyDisk(double x, double y)
{
    // the x and y coordinates need to change according to what the Sensor class will detect
    // coordinates need to be converted to px
    char greyDisk[] = "<circle cx=\"%d\" cy=\"%d\" r=\"20\" stroke=\"black\" stroke-width=\"4\" fill=\"gray\" />";
    sprintf(greyDisk, x, y);
    transmitString(greyDisk, strlen(greyDisk));
}

void SvgPicture::drawLine()
{
}

// int SvgPicture::orientation(Point p, Point q, Point r)
// {
//     int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

//     if (val == 0)
//         return 0;             // collinear -> connect the farest points
//     return (val > 0) ? 1 : 2; // clock or counterclock wise
// }

double SvgPicture::calculateConvexHullArea(double x, double y)
{
    // return the area...
}

void SvgPicture::addConvexHullArea(double areaValue)
{
    sprintf(area, "<text xmlns=\"http://www.w3.org/2000/svg\" x=\"96\" y=\"560\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">Aire: %.2f</text>", areaValue);
    transmitString(area, strlen(area));
}