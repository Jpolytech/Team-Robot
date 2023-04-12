#pragma once
#include "Uart.h"
#include <string.h>
#include <stdio.h>

class SvgPicture
{
public:
    SvgPicture();
    void transfer();
    void startSvgTransmission();
    void endSvgTransmission();

    void header();
    void footer();
    void writeTeamInformation();

    void drawTable();
    void drawGreyDisk(int x, int y);
    void drawGreyDisks();
    void drawBlackDots();
    void drawBlackDot(int x, int y);
    void drawRedDot();
    // int orientation(Point p, Point q, Point r);
    // double calculateConvexHullArea();
    // void addConvexHullArea(); // will call calculateConvexHullArea()

private:
    const int MATRIX_WIDTH = 8;
    const int MATRIX_HEIGHT = 4;

    const int DOT_WIDTH = 10;
    const int DOT_HEIGHT = 10;
    const int FIRST_BLACK_DOT_X_PX= 210;
    const int FIRST_BLACK_DOT_Y_PX = 130;
    const int DOT_SPACE_PX = 100;
    
    ManagementUSART uart;
};