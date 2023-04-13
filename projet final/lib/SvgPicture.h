#pragma once
#include "Uart.h"
#include "Memoire_24.h"
#include <string.h>
#include <stdio.h>
#include <util/crc16.h>

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

    uint8_t readPolesFromMemory(Pole poles[8]);

    void drawTable();
    void drawGreyDisk(iuint16_tnt pixelX, uint16_t pixelY);
    void drawGreyDisks(Pole poles[], uint8_t nPoles);
    void drawBlackDots();
    void drawBlackDot(uint16_t pixelX, uint16_t pixelY);
    void drawRedDot();
    // int orientation(Point p, Point q, Point r);
    // double calculateConvexHullArea();
    // void addConvexHullArea(); // will call calculateConvexHullArea()
    void transfer();

    // Transmission bytes
    void startSvgTransmission();
    void endSvgTransmission();
    void endTransmission();

    int checkCRC();

private:
    const int MATRIX_WIDTH = 8;
    const int MATRIX_HEIGHT = 4;

    const int DOT_WIDTH = 10;
    const int DOT_HEIGHT = 10;
    const int FIRST_BLACK_DOT_X_PX = 210;
    const int FIRST_BLACK_DOT_Y_PX = 130;
    const int DOT_SPACE_PX = 100;

    const int BLACK_DOT_ARRAY_SIZE = 110;
    const int GREY_DISK_ARRAY_SIZE = 90;

    ManagementUSART uart_;
    Memoire24CXXX memory_;
};
