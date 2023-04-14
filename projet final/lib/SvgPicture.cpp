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
    int n = sprintf(blackDot, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>", pixelX, pixelY, DOT_WIDTH, DOT_HEIGHT);
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

void SvgPicture::printPoles(Pole poles[], uint8_t nPoles) 
{
    for (int i=0; i<nPoles; i++) {
        char buffer[15];
        Pole pole = poles[i];
        int n = sprintf(buffer, "x=%d, y=%d\n", pole.x, pole.y);
        uart_.transmitString(buffer, n);
    }
}

void SvgPicture::drawPolygon(Pole convexHull[], uint8_t nHullPoints)
{
    char polygon[POLYGON_ARRAY_SIZE];
    int n1 = sprintf(polygon, "<polygon points=\"");
    uart_.transmitString(polygon, n1);
    // updateCrcString(polygon, n1);

    for (uint8_t i = 0; i < nHullPoints; i++)
    {
        Pole pole = convexHull[i];
        uint16_t pixelX = FIRST_BLACK_DOT_X_PX + pole.x * DOT_SPACE_PX;
        uint16_t pixelY = FIRST_BLACK_DOT_Y_PX + pole.y * DOT_SPACE_PX;
        int n2 = sprintf(polygon, "%d,%d ", pixelX, pixelY);
        uart_.transmitString(polygon, n2);
        // updateCrcString(polygon, n2);

    }
    int n3 = sprintf(polygon, "\" style=\"fill: green;stroke:black;stroke_width:5\" />");
    uart_.transmitString(polygon, n3);
    // updateCrcString(polygon, n3);
}


uint8_t SvgPicture::findAnchorPoint(Pole poles[], uint8_t nPoles)
{
    uint8_t anchorPoint = 0;
    for (uint8_t i = 1; i < nPoles; i++)
    {
        bool yGreater = poles[i].y > poles[anchorPoint].y;
        bool yEqual = poles[i].y == poles[anchorPoint].y;
        bool xLess = poles[i].x < poles[anchorPoint].x;

        if (yGreater || (yEqual && xLess)) 
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

void SvgPicture::sortByPolarAngle(Pole poles[], uint8_t& nPoles, Pole anchorPoint)
{
    bool done;
    do 
    {
        done = true;

        for (uint8_t j = 1; j < nPoles - 1; j++)
        {
            int crossProduct = SvgPicture::crossProduct(anchorPoint, poles[j], poles[j + 1]);

            if (crossProduct < 0)
            {
                swapPoles(poles, j, j + 1);
                done = false;
            }
            else if (crossProduct == 0)
            {
                if (dist(anchorPoint, poles[j]) < dist(anchorPoint, poles[j + 1]))
                {
                    swapPoles(poles, j, j + 1);
                    done = false;
                    swapPoles(poles, j+1, nPoles - 1);
                    nPoles--;

                }
            }
        }
    }
    while(!done); 

}

void SvgPicture::drawConvexHull(Pole poles[], uint8_t nPoles)
{
    Pole stack[8];
    uint8_t stackSize = 0;

    uint8_t anchorIndex = findAnchorPoint(poles, nPoles);
    Pole anchorPole = poles[anchorIndex];
    swapPoles(poles, 0, anchorIndex);
    
    // char buffer[30];
    // int n = sprintf(buffer, "Anchor point: x=%d y=%d", anchorPoint.x, anchorPoint.y);
    // uart_.transmitString(buffer, n);

    sortByPolarAngle(poles, nPoles, anchorPole);

    // printPoles(poles, nPoles);

    stack[stackSize++] = poles[0];
    stack[stackSize++] = poles[1];

    for (uint8_t i = 2; i < nPoles; i++)
    {
        Pole pole = poles[i];
        while (stackSize >= 2 && crossProduct(stack[stackSize - 2], stack[stackSize - 1], pole) <= 0)
        {
            stackSize--;
        }
        stack[stackSize++] = pole;
    }

    drawPolygon(stack, stackSize);

    // uint16_t area = computeArea(stack, stackSize);
    // drawArea(area);
}

void SvgPicture::startSvgTransmission()
{
    uart_.transmitData(START_TEXT);
    // updateCrc(START_TEXT);
}

void SvgPicture::endSvgTransmission()
{
    uart_.transmitData(END_TEXT);
}

void SvgPicture::endTransmission()
{
    uart_.transmitData(END_TRANSMISSION);
}

// void SvgPicture::updateCrc(char){
//     // https://lxp32.github.io/docs/a-simple-example-crc32-calculation/
// }

// void SvgPicture::updateCrcString(tab, n) {
//     iterere dans tab:
//         updateCrc(elem)
// }

// void SvgPicture::transmitCrc() {
//     crc = ~crc;
//     // mettre crc dans un buffer en hexadecimal (prendre en compte que c'est 32 bits et %x s'attend à des 16
//     // bits, donc split en 2)

//     // transmettre buffer (sans update crc 🥲)
// }

void SvgPicture::transfer()
{
    Pole poles[8];
    uint8_t nPoles = readPolesFromMemory(poles);

    startSvgTransmission();
    header();
    drawTable();
    drawBlackDots();
    drawRedDot();
    writeTeamInformation();
    drawConvexHull(poles, nPoles);
    drawGreyDisks(poles, nPoles);
    endSvgTransmission();
    // transmitCrc();
    endTransmission();
}
