#include "SvgPicture.h"

SvgPicture::SvgPicture()
{
    uart.initialisation();
}

void SvgPicture::header()
{
    char header[] = "<svg width=\"1000\" height=\"600\" viewBox=\"0 0 1700 600\">";
    uart.transmitString(header, strlen(header));
}

void SvgPicture::footer()
{
    char footer[] = "</svg>";
    uart.transmitString(footer, strlen(footer));
}

void SvgPicture::drawTable()
{
    char table[] = "<rect x=\"96\" y=\"48\" width=\"930\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>";
    uart.transmitString(table, strlen(table));
}

void SvgPicture::drawBlackDot(int x, int y)
{
    char blackDot[BLACK_DOT_ARRAY_SIZE];
    int n = sprintf(blackDot, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>", x, y, DOT_WIDTH, DOT_HEIGHT);
    uart.transmitString(blackDot, n);
}

void SvgPicture::drawBlackDots()
{
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
        for (int j = 0; j < MATRIX_HEIGHT; j++)
        {
            if (i == 0 && j == 3)
            {
                continue;
            }
            int x = FIRST_BLACK_DOT_X_PX + i * DOT_SPACE_PX;
            int y = FIRST_BLACK_DOT_Y_PX + j * DOT_SPACE_PX;
            drawBlackDot(x, y);
        }
    }
}

void SvgPicture::drawRedDot()
{
    char redDot[] = "<rect x=\"210\" y=\"430\" width=\"10\" height=\"10\" stroke=\"red\" stroke-width=\"1\" fill=\"red\"/>";
    uart.transmitString(redDot, strlen(redDot));
}

void SvgPicture::writeTeamInformation()
{
    char teamInfo[] = "<text x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\"> section 01 -- équipe 0108 -- BOB</text>";
    uart.transmitString(teamInfo, strlen(teamInfo));
}

void SvgPicture::drawGreyDisk(int x, int y)
{
    char greyDisk[GREY_DISK_ARRAY_SIZE];
    int n = sprintf(greyDisk, "<circle cx=\"%d\" cy=\"%d\" r=\"20\" stroke=\"black\" stroke-width=\"4\" fill=\"gray\" />", x, y);
    uart.transmitString(greyDisk, n);
}

void SvgPicture::drawGreyDisks()
{
    // methode pour dessiner tous les disques gris
    // prendre les coordonnes de tous les points noirs stockés en memoire et appeler drawGreyDisk() 
    // -> on itere dessus ? probablement envoyer un tableau de coordonnees dans la flash
}

// int SvgPicture::orientation(Point p, Point q, Point r)
// {
//     int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

//     if (val == 0)
//         return 0;             // collinear -> connect the farest points
//     return (val > 0) ? 1 : 2; // clock or counterclock wise
// }

// double SvgPicture::calculateConvexHullArea(double x, double y)
// {
//     // return the area...
// }

// void SvgPicture::addConvexHullArea(double areaValue)
// {
//     int n = sprintf(area, "<text x=\"96\" y=\"560\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">Aire: %.2f</text>", calculateConvexHullArea(areaValue));
//     uart.transmitString(area, n);
// }

void SvgPicture::startSvgTransmission()
{
    uart.transmitData(0x02);
}

void SvgPicture::endSvgTransmission()
{
    uart.transmitData(0x03);
}

void SvgPicture::transfer() 
{
    startSvgTransmission();
    header();
    drawTable();
    drawBlackDots();
    drawRedDot();
    writeTeamInformation();
    endSvgTransmission();    
}