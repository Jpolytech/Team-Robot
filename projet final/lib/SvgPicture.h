#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class SvgPicture
{
public:
    void header();
    void footer();
    void writeTeamInformation();
    void drawTable();
    void drawGreyDisks();
    void drawBlackDots();
    void drawRedDot();
    int orientation(Point p, Point q, Point r);
    double calculateConvexHullArea();
    void addConvexHullArea(); // will call calculateConvexHullArea()

private:
    const int N_BLACK_DOTS = 31;
    const int DOT_WIDTH = 10;
    const int DOT_HEIGHT = 10;
    const int DOT_X = 210;
    const int DOT_Y = 130;
};