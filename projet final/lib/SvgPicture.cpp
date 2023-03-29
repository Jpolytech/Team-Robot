#include "SvgPicture.h"

void SvgPicture::header()
{
    outputFile.open(fileName_);
    outputFile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl
               << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.0//EN\"" << endl
               << " \"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">" << endl
               << "<svg width=\"" << width_
               << "\" height=\"" << height_ << "\">" << endl;
}

void SvgPicture::foot()
{
    outputFile << "</svg>" << endl;
    outputFile.close();
}

void SvgPicture::drawTable(double x = 96, double y = 48, int width = 900, int height = 500, string tableColour = "black")
{
    outputFile << "<rect x=\"" << x
               << "\" y=\"" << y
               << "\" width=\"" << width
               << "\" height=\"" << height
               << "\" fill=\"" << tableColour << "\"/>\n";
}

void SvgPicture::drawDots(double x, double y, double size = 35, double spacing, string dotColour = "black")
{
    for (double i = x; i < x + size; i += spacing)
    {
        for (double j = y; j < y + size; j += spacing)
        {
            outputFile << "<rect x=\"" << i
                       << "\" y=\"" << j
                       << "\" width=\"" << size
                       << "\" height=\"" << size
                       << "\" fill=\"" << dotColour
                       << "\"/>\n";
        }
    }
}

void SvgPicture::drawGreyDisks(double cx, double cy, double r, string stroke = "black", string diskColour = "grey")
{
    outputFile << "<circle cx=\"" << cx
               << "\" cy=\"" << cy
               << "\" r=\"" << r
               << "\" stroke=\"" << stroke
               << "\" fill=\"" << diskColour
               << "\"/>\n";
}

void SvgPicture::writeTeamInformation(double x = 96, double y = 36, string fontFamily = "arial", double fontSize = 20, string fontColour = "blue")
{
    outputFile << "<text x=\"" << x
               << "\" y=\"" << y
               << "\" font-family=\"" << fontFamily
               << "\" font-size=\"" << fontSize
               << "\" fill=\"" << fontColour
               << "\"/>"
               << "\"section 01 -- équipe 0108 -- BOB"
               << "\"</text>\n";
}
