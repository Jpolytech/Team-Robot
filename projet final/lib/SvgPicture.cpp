#include "SvgPicture.h"

SvgPicture::SvgPicture()
{
    uart_.initialisation();
}

void SvgPicture::header()
{
    char header[] = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"600\" viewBox=\"0 0 1700 600\">";
    uart_.transmitString(header, strlen(header));
    updateCrc(header, strlen(header));
}

void SvgPicture::footer()
{
    char footer[] = "</svg>";
    uart_.transmitString(footer, strlen(footer));
    updateCrc(footer, strlen(footer));
}

void SvgPicture::drawTable()
{
    char table[] = "<rect x=\"96\" y=\"48\" width=\"930\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>";
    uart_.transmitString(table, strlen(table));
    updateCrc(table, strlen(table));
}

void SvgPicture::drawBlackDot(uint16_t pixelX, uint16_t pixelY)
{
    char blackDot[BLACK_DOT_ARRAY_SIZE];
    int n = sprintf(blackDot, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>", pixelX, pixelY, DOT_WIDTH, DOT_HEIGHT);
    uart_.transmitString(blackDot, n);
    updateCrc(blackDot, n);
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
    updateCrc(redDot, strlen(redDot));
}

void SvgPicture::writeTeamInformation()
{
    char teamInfo[] = "<text x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\"> section 01 -- equipe 0108 -- BOB</text>";
    uart_.transmitString(teamInfo, strlen(teamInfo));
    updateCrc(teamInfo, strlen(teamInfo));
}

void SvgPicture::writeConvexHullArea(uint16_t areaValue)
{
    char area[AREA_ARRAY_SIZE];
    int n = sprintf(area, "<text x=\"96\" y=\"560\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">AIRE: %d pouces carres </text>", areaValue);
    uart_.transmitString(area, n);
    updateCrc(area, n);
}

void SvgPicture::drawGreyDisk(uint16_t pixelX, uint16_t pixelY)
{
    char greyDisk[GREY_DISK_ARRAY_SIZE];
    int n = sprintf(greyDisk, "<circle cx=\"%d\" cy=\"%d\" r=\"15\" stroke=\"black\" stroke-width=\"4\" fill=\"gray\" />", pixelX, pixelY);
    uart_.transmitString(greyDisk, n);
    updateCrc(greyDisk, n);
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
    char polygon[POLYGON_ARRAY_SIZE];
    int n1 = sprintf(polygon, "<polygon points=\"");
    uart_.transmitString(polygon, n1);
    updateCrc(polygon, n1);

    for (uint8_t i = 0; i < nHullPoints; i++)
    {
        Pole pole = convexHull[i];
        uint16_t pixelX = FIRST_BLACK_DOT_X_PX + pole.x * DOT_SPACE_PX;
        uint16_t pixelY = FIRST_BLACK_DOT_Y_PX + pole.y * DOT_SPACE_PX;
        int n2 = sprintf(polygon, "%d,%d ", pixelX, pixelY);
        uart_.transmitString(polygon, n2);
        updateCrc(polygon, n2);
    }
    int n3 = sprintf(polygon, "\" style=\"fill: green;stroke:black;stroke_width:5\" />");
    uart_.transmitString(polygon, n3);
    updateCrc(polygon, n3);
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

uint16_t SvgPicture::computeArea(Pole stack[], uint8_t stackSize)
{   
    int area = 0;
    int topmostElemIndex = stackSize - 1;
    for (uint8_t i = 0; i < stackSize; i++)
    {
        uint16_t inchTopMostElemX= stack[topmostElemIndex].x * DOT_SPACE_INCHES;
        uint16_t inchTopMostElemY = stack[topmostElemIndex].y * DOT_SPACE_INCHES;

        uint16_t inchCurrentElemX = stack[i].x * DOT_SPACE_INCHES;
        uint16_t inchCurrentElemY = stack[i].y * DOT_SPACE_INCHES;

        area += (inchTopMostElemX + inchCurrentElemX) * (inchTopMostElemY - inchCurrentElemY);
        topmostElemIndex = i;
    }
    return (-1)*(area/2);
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
    sortByPolarAngle(poles, nPoles, anchorPole);

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

    uint16_t area = computeArea(stack, stackSize);
    writeConvexHullArea(area);
}

void SvgPicture::startSvgTransmission()
{
    uart_.transmitData(START_TEXT);
}

void SvgPicture::endSvgTransmission()
{
    uart_.transmitData(END_TEXT);
}

void SvgPicture::endTransmission()
{
    uart_.transmitData(END_TRANSMISSION);
}

void SvgPicture::updateCrc(const char* s, size_t n)
{
    for (size_t i = 0; i < n; i++) 
    {
		char ch = s[i];
		for (size_t j = 0; j < 8; j++) 
        {
			uint32_t b = (ch ^ crc_) & 1;
			crc_>>= 1;
			if (b) crc_ = crc_ ^ reversed_crc_;
			ch>>= 1;
		}
	}
}

void SvgPicture::transmitCrc() 
{
    crc_ = ~crc_;
    char crc[CRC_ARRAY_SIZE];

    uint16_t msb = crc_>>16;
    uint16_t lsb = (uint16_t)crc_;
    int n = sprintf(crc, "%x%x", msb, lsb);

    uart_.transmitString(crc, n);
}

void SvgPicture::transfer()
{
    Pole poles[8];
    uint8_t nPoles = readPolesFromMemory(poles);

    startSvgTransmission();
    header();
    drawTable();
    writeTeamInformation();
    drawConvexHull(poles, nPoles);
    drawBlackDots();
    drawRedDot();
    drawGreyDisks(poles, nPoles);
    footer();
    endSvgTransmission();
    transmitCrc();
    endTransmission();
}
