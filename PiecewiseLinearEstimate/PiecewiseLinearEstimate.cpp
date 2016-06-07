// PiecewiseLinearEstimate.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

const int G_SIZE = 16;
const double G_DATA[G_SIZE] = {0.0,0.0,  1.0,1.0,  2.0,2.0,  3.0,3.0,  5.0,4.0,  7.0,5.0,  8.0,7.0,  9.0,9.0};
const double THRESHOLD = 0.05;

struct Point
{
    Point(double _x, double _y): x(_x), y(_y) {}
    double x;
    double y;
};

class LinearEstimate
{
public:
    LinearEstimate();
    ~LinearEstimate() {}
    void printData();
    void printPairs();
    void determineLinearEstimates();
private:
    std::vector<std::pair<Point, Point> > pairs;
    std::vector<Point> data;
};

LinearEstimate::LinearEstimate()
{
    for (int i = 0; i < (G_SIZE / 2); ++i)
    {
        data.push_back(Point(G_DATA[i * 2], G_DATA[i * 2 + 1]));
    }
}

void LinearEstimate::printData()
{
    std::cout << "Data: ";
    for(int i = 0; i < data.size(); ++i)
    {
        std::cout << "(" << data[i].x << "," << data[i].y << ") ";
    }
    std::cout << std::endl;
}

void LinearEstimate::printPairs()
{
    std::cout << "Pairs: ";
    for(int i = 0; i < pairs.size(); ++i)
    {
        std::cout << "(" << pairs[i].first.x << "," << pairs[i].first.y << " - " << pairs[i].second.x << "," << pairs[i].second.y << ") ";
    }
    std::cout << std::endl;
}

void LinearEstimate::determineLinearEstimates()
{
    // Default to starting with the first point
    Point start = data[0];
    // Calculate the first angle so the for logic below works
    double startAngle = atan2((data[1].y - data[0].y), (data[1].x - data[0].x));
    // currentAngle will be calculated in the for loop
    double currentAngle = 0.0;
    // Loop over data and calculate the pairs
    for (int i = 1; i < data.size(); ++i)
    {
        // Calculate the angle from the start point to current point
        currentAngle = atan2((data[i].y - start.y), (data[i].x - start.x));
        if (abs(currentAngle - startAngle) > THRESHOLD)
        {
            // We've gone past the threshold, time to create a pair and set a new start point
            pairs.push_back(std::make_pair(start, data[i - 1]));
            start = data[i - 1];
            // Calculate the new start angle from new start point to current point (first point out of threshold)
            startAngle = atan2((data[i].y - start.y), (data[i].x - start.x));
        }
    }
    // Add the final pair (may need to make sure last point isn't a new start point, either way should be fine)
    pairs.push_back(std::make_pair(start, data[data.size() - 1]));
}


int _tmain(int argc, _TCHAR* argv[])
{
    LinearEstimate test;
    test.printData();
    test.printPairs();
    test.determineLinearEstimates();
    test.printData();
    test.printPairs();

    system("PAUSE");
	return 0;
}

