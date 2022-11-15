#include <cmath>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "PolygonBoundary.h"

PolygonBoundary::PolygonBoundary()
{
    std::vector<BoundarySegment> boundaryEndPoints;
}

PolygonBoundary::PolygonBoundary(std::vector<std::vector<int>> data)
{
    std::vector<BoundarySegment> boundaryEndPoints;

    PolygonBoundary::load(data);
}

void PolygonBoundary::load(std::vector<std::vector<int>> data)
{
    for (int j = 1; j < data.size(); j++)
    {
        BoundarySegment aux;
        Point auxPoint;

        auxPoint.x = data[j][0];
        auxPoint.y = data[j][1];
        aux.endPoint = auxPoint;
        aux.boundaryType = (unsigned char)data[j][2];
        aux.param1 = data[j][3];
        if (data[j].size() == 4)
        {
            aux.param2 = 0;
        }
        else if (data[j].size() == 5)
        {
            aux.param2 = data[j][4];
        }

        boundaryEndPoints.push_back(aux);
    }
}

PolygonBoundary::~PolygonBoundary()
{
    
}