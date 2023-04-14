#pragma once
#include "Uart.h"
#include "Memoire_24.h"
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

class SvgPicture
{
public:
    SvgPicture();

    struct Pole
    {
        int x, y;
    };

    void header();
    void footer();

    void writeTeamInformation();

    void drawTable();
    void drawBlackDot(uint16_t pixelX, uint16_t pixelY);
    void drawBlackDots();
    void drawRedDot();
    void drawGreyDisk(uint16_t pixelX, uint16_t pixelY);
    void drawGreyDisks(Pole poles[], uint8_t nPoles);

    uint8_t readPolesFromMemory(Pole poles[8]);
    uint16_t computeArea(Pole stack[], uint8_t stackSize);
    void writeConvexHullArea(uint16_t areaValue);

    void swapPoles(Pole poles[], uint8_t i, uint8_t j);
    void keepFarthestPoint(Pole poles[], uint8_t &nPoles, Pole unwantedPole);
    int crossProduct(Pole p1, Pole p2, Pole p3);
    int dist(Pole p1, Pole p2);
    uint8_t findAnchorPoint(Pole poles[], uint8_t nPoles);
    void sortByPolarAngle(Pole poles[], uint8_t& nPoles, Pole anchorPoint);
    void drawConvexHull(Pole poles[], uint8_t nPoles);
    void drawPolygon(Pole convexHull[], uint8_t nHullPoints);

    void transfer();

    // Transmission bytes
    void startSvgTransmission();
    void endSvgTransmission();
    void endTransmission();

    // Check CRC
    void updateCrc(const char* s, size_t n);
    void transmitCrc();

private:
    ManagementUSART uart_;
    Memoire24CXXX memory_;

    const int MATRIX_WIDTH = 8;
    const int MATRIX_HEIGHT = 4;

    const int DOT_WIDTH = 10;
    const int DOT_HEIGHT = 10;
    const int FIRST_BLACK_DOT_X_PX = 210;
    const int FIRST_BLACK_DOT_Y_PX = 130;
    const int DOT_SPACE_PX = 100;
    const int DOT_SPACE_INCHES = 11;

    const int BLACK_DOT_ARRAY_SIZE = 110;
    const int GREY_DISK_ARRAY_SIZE = 90;
    const int AREA_ARRAY_SIZE = 110;
    const int POLYGON_ARRAY_SIZE = 90;

    const uint8_t NO_MORE_POLES = 0xff;

    const int START_TEXT = 0x02;
    const int END_TEXT = 0x03;
    const int END_TRANSMISSION = 0x04;

    uint32_t crc_ = 0xFFFFFFFF;
    uint32_t reversed_crc_ = 0xEDB88320;
    const int CRC_ARRAY_SIZE = 9;

};
