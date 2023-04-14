#include "SvgPicture.h"

SvgPicture::SvgPicture()
{
    uart_.initialisation();
}

void SvgPicture::header()
{
    char header[] = "<svg width=\"1000\" height=\"600\" viewBox=\"0 0 1700 600\">";
    uart_.transmitString(header, strlen(header));
}

void SvgPicture::footer()
{
    char footer[] = "</svg>";
    uart_.transmitString(footer, strlen(footer));
}

void SvgPicture::drawTable()
{
    char table[] = "<rect x=\"96\" y=\"48\" width=\"930\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>";
    uart_.transmitString(table, strlen(table));
}

void SvgPicture::drawBlackDot(uint16_t pixelX, uint16_t pixelY)
{
    char blackDot[BLACK_DOT_ARRAY_SIZE];
    int n = sprintf(blackDot, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>", x, y, DOT_WIDTH, DOT_HEIGHT);
    uart_.transmitString(blackDot, n);
}

void SvgPicture::drawBlackDots()
{
    for (uint8_t i = 0; i < MATRIX_WIDTH; i++)
    {
        for (uint8_t j = 0; j < MATRIX_HEIGHT; j++)
        {
            if (i == 0 && j == 3)
            {
                continue;
            }
            uint16_t pixelX = FIRST_BLACK_DOT_X_PX + i * DOT_SPACE_PX;
            uint16_t pixelY = FIRST_BLACK_DOT_Y_PX + j * DOT_SPACE_PX;
            drawBlackDot(pixelX, pixelY);
        }
    }
}

void SvgPicture::drawRedDot()
{
    char redDot[] = "<rect x=\"210\" y=\"430\" width=\"10\" height=\"10\" stroke=\"red\" stroke-width=\"1\" fill=\"red\"/>";
    uart_.transmitString(redDot, strlen(redDot));
}

void SvgPicture::writeTeamInformation()
{
    char teamInfo[] = "<text x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\"> section 01 -- équipe 0108 -- BOB</text>";
    uart_.transmitString(teamInfo, strlen(teamInfo));
}

void SvgPicture::drawGreyDisk(uint16_t pixelX, uint16_t pixelY)
{
    char greyDisk[GREY_DISK_ARRAY_SIZE];
    int n = sprintf(greyDisk, "<circle cx=\"%d\" cy=\"%d\" r=\"20\" stroke=\"black\" stroke-width=\"4\" fill=\"gray\" />", pixelX, pixelY);
    uart_.transmitString(greyDisk, n);
}

void SvgPicture::drawGreyDisks(Pole poles[], uint8_t nPoles)
{
    for (uint8_t i = 0; i < nPoles; i++)
    {
        Pole pole = poles[i];
        uint16_t pixelX = FIRST_BLACK_DOT_X_PX + pole.x * DOT_SPACE_PX;
        uint16_t pixelY = FIRST_BLACK_DOT_Y_PX + pole.y * DOT_SPACE_PX;
        drawGreyDisk(pixelX, pixelY);
    }
}

uint8_t SvgPicture::readPolesFromMemory(Pole poles[8])
{
    uint8_t nPoles = 0;
    uint8_t x, y, nextByte;
    uint8_t address = 0;

    do
    {
        memory_.lecture(address++, &x);
        _delay_ms(5);

        memory_.lecture(address++, &y);
        _delay_ms(5);

        poles[nPoles++] = {x, y};

        memory_.lecture(address, &nextByte);
        _delay_ms(5);
    } while (nextByte != NO_MORE_POLES);

    return nPoles;
}

void SvgPicture::drawPolygon(Pole convexHull[], uint8_t nHullPoints)
{
    // https://developer.mozilla.org/en-US/docs/Web/SVG/Element/polygon
    // dessiner une balise "polygone" avec les points de l'enveloppe
    char polygon[POLYGON_ARRAY_SIZE];
    int n1 = sprintf(polygon, "<polygon points=\" 0,");
    uart_.transmitString(polygon, n1);

    for (int i = 0; i < nHullPoints; i++)
    {
        int n2 = sprintf(polygon, "%d %d,", convexHull[i].x, convexHull[i].y);
        uart_.transmitString(polygon, n2);
    }
    int n3 = sprintf(polygon, "0\" style=\"fill: green;\" />");
    uart_.transmitString(polygon, n3);
}

uint8_t SvgPicture::findAnchorPoint(Pole poles[], uint8_t nPoles)
{
    uint8_t anchorPoint = 0;
    for (uint8_t i = 1; i < nPoles; i++)
    {
        if (poles[i].x < poles[anchorPoint].x && poles[i].y < poles[anchorPoint].y)
        {
            anchorPoint = i;
        }
    }
    return anchorPoint;
}

int SvgPicture::crossProduct(Pole p1, Pole p2, Pole p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

int SvgPicture::dist(Pole p1, Pole p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void SvgPicture::swapPoles(Pole poles[], uint8_t i, uint8_t j)
{
    Pole temp = poles[i];
    poles[i] = poles[j];
    poles[j] = temp;
}

void SvgPicture::keepFarthestPoint(Pole poles[], uint8_t &nPoles, Pole unwantedPole)
{
    for (uint8_t i = 1; i < nPoles; i++)
    {
        for (uint8_t j = 1; j < nPoles - 1 - i; j++)
        {
            if (poles[i] == unwantedPole)
            {
                poles[i] = poles[j];
                nPoles--;
            }
        }
    }
}

void SvgPicture::sortByPolarAngle(Pole poles[], uint8_t nPoles, Pole anchorPoint)
{
    // sort points by polar angle with P0
    for (uint8_t i = 1; i < nPoles; i++)
    {
        for (uint8_t j = 1; j < nPoles - 1 - i; j++)
        {
            int crossProduct = SvgPicture::crossProduct(anchorPoint, poles[i], poles[j]);

            if (crossProduct < 0)
            {
                // if the result is negative, the three points constitute a "right turn" or clockwise orientation
                swapPoles(poles, i, j);
            }
            else if (crossProduct == 0) // colinear
            {
                // if the result is 0, the points are collinear -> take the farthest one and swap it with the next point in the array
                // sort dans ce cas par distance, ça va grandement simplifier la
                // prochaine étape qui consiste à garder les points les plus éloignés
                if (dist(anchorPoint, i) > dist(anchorPoint, j))
                {
                    // TODO : garder le point le plus éloigné au début de la suite colinéaire
                    // et enlever le + proche de la liste
                    swapPoles(poles, i, j);
                    keepFarthestPoint(poles, nPoles, i)
                }
            }
            else
                continue;
        }
    }
}

void SvgPicture::drawConvexHull(Pole poles[], uint8_t nPoles)
{
    Pole convexHull[8]; // "stack" des points de l'enveloppe (résultat du prochain algorithme)
    uint8_t nConvexHull = 0;

    // voir pseudo code : https://en.wikipedia.org/wiki/Graham_scan
    // 1. find the leftmost point p0 and put it in the first position in the output hull
    uint8_t anchorIndex = findAnchorPoint(poles, nPoles);
    Pole anchorPoint = poles[anchorIndex];

    convexHull[nConvexHull++] = anchorPoint;

    // 2. swap p0 with the first point in the array
    swapPoles(poles[0], anchorPoint);

    // 3. sort the points by polar angle with p0
    sortByPolarAngle(poles, nPoles, anchorPoint);
    keepFarthestPoints(poles, nPoles);

    // 4. push p1 to the stack
    convexHull[nConvexHull++] = poles[1];

    // 5. Iterate over each point in the sorted array and see if traversing to a point from the previous two points makes a clockwise
    // or a counter-clockwise direction. If clockwise then reject the point and move on to the next point. Continue this till the end of the sorted array.
    // propably append the points to the stack

    drawPolygon(convexHull[], nConvexHull);
}

// int SvgPicture::findConvexHullArea(){}

void SvgPicture::startSvgTransmission()
{
    uart_.transmitData(0x02);
}

void SvgPicture::endSvgTransmission()
{
    uart_.transmitData(0x03);
}

void SvgPicture::endTransmission()
{
    uart_.transmitData(0x04);
}

void SvgPicture::transfer()
{
    Pole poles[8];
    uint8_t nPoles = readPolesFromMemory(poles);
    // int SvgPicture::checkCRC(void)
    // {
    //     // voir lien documentation sur Notion
    // }

    startSvgTransmission();
    header();
    drawTable();
    drawBlackDots();
    drawRedDot();
    writeTeamInformation();
    drawGreyDisks(poles, nPoles);
    drawConvexHull(poles, nPoles);
    endSvgTransmission();
}
