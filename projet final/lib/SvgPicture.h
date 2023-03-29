#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class SvgPicture
{
private:
    double width_;
    double height_;
    string fileName_;
    string backgroundColour_;
    ofstream outputFile;

public:
    SvgPicture(string filename = "map.svg",
               double width = 937,
               double height = 534,
               string bgColour = "white") : fileName_(filename),
                                            width_(width),
                                            height_(height),
                                            backgroundColour_(bgColour) {}

    void header();
    void foot();
    void writeTeamInformation(double x, double y, string fontFamily, double fontSize, string fontColour);
    void drawTable(double x, double y, double width, double height, string tableColour);
    void drawGreyDisks(double cx, double cy, double r, string stroke, string diskColour);
    void drawDots(double x, double y, double size, double spacing, string dotColour);
    void calculateConvexHullArea();
    void addConvexHullArea(); // will call calculateConvexHullArea()
};