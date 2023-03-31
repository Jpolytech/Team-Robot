#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class SvgPicture
{
public:
    void header();
    void foot();
    void writeTeamInformation();
    void drawTable();
    void drawGreyDisks();
    void drawBlackDots();
    void drawRedDot();
    void calculateConvexHullArea();
    void addConvexHullArea(); // will call calculateConvexHullArea()

private:
    const int numDots = 31;
    const int dotWidth = 10;
    const int dotHeight = 10;
    const int dotX = 210;
    const int dotY = 130;
};