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
};