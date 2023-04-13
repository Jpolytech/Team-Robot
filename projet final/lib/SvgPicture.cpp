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

void SvgPicture::drawBlackDot(uint16_t x, uint16_t y)
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

void SvgPicture::drawGreyDisk(uint16_t x, uint16_t y)
{
    char greyDisk[GREY_DISK_ARRAY_SIZE];
    int n = sprintf(greyDisk, "<circle cx=\"%d\" cy=\"%d\" r=\"20\" stroke=\"black\" stroke-width=\"4\" fill=\"gray\" />", x, y);
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
//     uart_.transmitString(area, n);
// }

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
    uart.transmitData(0x04);
}

uint8_t SvgPicture::readPolesFromMemory(Pole poles[8])
{
    const uint8_t NO_MORE_POLES = 0xff; // à mettre en attribut de la classe

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

void SvgPicture::transfer()
{
    Pole poles[8];
    uint8_t nPoles = fetchPositions(poles);

    startSvgTransmission();
    header();
    drawTable();
    drawBlackDots();
    drawRedDot();

    drawGreyDisks(poles, nPoles);

    writeTeamInformation();
    endSvgTransmission();
}

// Memory map
{
    x1,     // 0
        y1, // 1

        x2, // 2
        y2, // 3

        x3, // 4
        y3, // 5

        0xff, // 6
}

int SvgPicture::checkCRC(void)
{
    // voir lien documentation sur Notion
}
