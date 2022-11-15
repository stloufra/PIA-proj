#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include "PolygonBoundary.h"
#include "Mesh.h"


Mesh::Mesh()
{
    dx = 0.2;
    dy = dx;

    std::vector<std::vector<short>> nodeList;
    std::vector<BoundaryNode> boundaryNodeList;
}

Mesh::Mesh(PolygonBoundary boundary, double dxx)
{
    dx = dxx;
    dy = dx;

    std::vector<std::vector<short>> nodeList;
    std::vector<BoundaryNode> boundaryNodeList;

    create(boundary);
}

void Mesh::create(PolygonBoundary boundary)
{
    int boundaryNodeId = 2;
    int size = boundary.boundaryEndPoints.size();
    double xMax = boundary.boundaryEndPoints[size-1].endPoint.x;
    double yMax = boundary.boundaryEndPoints[size-1].endPoint.y;

    for (int i = 0; i < boundary.boundaryEndPoints.size(); i++)
    {
        if (xMax < boundary.boundaryEndPoints[i].endPoint.x)
        {
            xMax = boundary.boundaryEndPoints[i].endPoint.x;
        }
        if (yMax < boundary.boundaryEndPoints[i].endPoint.y)
        {
            yMax = boundary.boundaryEndPoints[i].endPoint.y;
        }
    }

    nodeSumX = (((float)xMax)/dx) + 1;
    nodeSumY = (((float)yMax)/dy) + 1;

    nodeList.push_back(std::vector<short>());

    BoundaryNode auxBoundaryNode;
    boundaryNodeList.push_back(auxBoundaryNode);
    boundaryNodeList.push_back(auxBoundaryNode);
    
    for (int j = 0; j < nodeSumY; j++)
    {
        for (int i = 0; i < nodeSumX; i++)
        {
            Point auxPoint;
            auxPoint.x = i*dx;
            auxPoint.y = j*dy;
            PolygonBoundary::BoundarySegment boundarySegment;
            
            if(isPointOnBoundary(boundary, auxPoint, boundarySegment))
            {
                nodeList[j].push_back(boundaryNodeId);
                BoundaryNode auxBoundaryNode;
                auxBoundaryNode.boundaryConditionType = boundarySegment.boundaryType;
                auxBoundaryNode.param1 = boundarySegment.param1;
                auxBoundaryNode.param2 = boundarySegment.param2;
                boundaryNodeList.push_back(auxBoundaryNode);

                boundaryNodeId++;
            }
            else if(isPointInside(boundary, auxPoint))
            {
                nodeList[j].push_back(1);
            }
            else
            {
                nodeList[j].push_back(0);
            }
        }
        nodeList.push_back(std::vector<short>());
    }

    setBoundaryNodesOrientation();
}

bool Mesh::isPointInside(PolygonBoundary boundary, Point point)
{
    double t = 0;
    double u = 0;
    int cnt1 = 0;
    int cnt2 = 0;

    double x1 = point.x;
    double y1 = point.y;
    double x2 = 99;
    double y2 = y1;
    double x22 = x1;
    double y22 = 99;
    double x3, x4, y3, y4;
    
    for (int i = 0; i < boundary.boundaryEndPoints.size(); i++)
    {        
        if (i == 0)
        {
            x3 = boundary.boundaryEndPoints[boundary.boundaryEndPoints.size()].endPoint.x;
            y3 = boundary.boundaryEndPoints[boundary.boundaryEndPoints.size()].endPoint.y;
        }
        else
        {
            x3 = boundary.boundaryEndPoints[i-1].endPoint.x;
            y3 = boundary.boundaryEndPoints[i-1].endPoint.y;
        }
        x4 = boundary.boundaryEndPoints[i].endPoint.x;
        y4 = boundary.boundaryEndPoints[i].endPoint.y;

        if ((((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4))) != 0)
        {
            t = (((x1-x3)*(y3-y4))-(y1-y3)*(x3-x4))/(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)));
            u = (((x1-x3)*(y1-y2))-(y1-y3)*(x1-x2))/(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)));
        }
        else
        {
            t = 2;
            u = 2;
        }        
        if (0 <= t && t <= 1 && 0 <= u && u <= 1)
        {
            cnt1++;
        }

        if ((((x1-x22)*(y3-y4))-((y1-y22)*(x3-x4))) != 0)
        {
            t = (((x1-x3)*(y3-y4))-(y1-y3)*(x3-x4))/(((x1-x22)*(y3-y4))-((y1-y22)*(x3-x4)));
            u = (((x1-x3)*(y1-y22))-(y1-y3)*(x1-x22))/(((x1-x22)*(y3-y4))-((y1-y22)*(x3-x4)));
        }
        else
        {
            t = 2;
            u = 2;
        }        
        if (0 <= t && t <= 1 && 0 <= u && u <= 1)
        {
            cnt2++;
        }
    }
    
    if ((cnt1 % 2) != 0 || (cnt2 % 2) != 0 )
    {
        return true;
    }
    return false;
}

bool Mesh::isPointOnBoundary(PolygonBoundary boundary, Point point, PolygonBoundary::BoundarySegment boundarySegment)
{
    double x1 = point.x;
    double y1 = point.y;
    double x3, x4, y3, y4;
    
    for (int i = 0; i < boundary.boundaryEndPoints.size(); i++)
    {
        if (i == 0)
        {
            x3 = boundary.boundaryEndPoints[boundary.boundaryEndPoints.size()].endPoint.x;
            y3 = std::round(boundary.boundaryEndPoints[boundary.boundaryEndPoints.size()].endPoint.y*1000)/1000;
        }
        else
        {
            x3 = boundary.boundaryEndPoints[i-1].endPoint.x;
            y3 = boundary.boundaryEndPoints[i-1].endPoint.y;
        }
        x4 = boundary.boundaryEndPoints[i].endPoint.x;
        y4 = boundary.boundaryEndPoints[i].endPoint.y;
        
        if ((x3 <= x1 && x4 >= x1 && y3 == y4 && y1 == y3) || (x4 <= x1 && x3 >= x1 && y3 == y4 && y1 == y3) || (y3 <= y1 && y4 >= y1 && x3 == x4 && x1 == x3) || (y4 <= y1 && y3 >= y1 && x3 == x4 && x1 == x3))
        {
            boundarySegment = boundary.boundaryEndPoints[i];
            return true;
        }
    }    
    
    return false;
}

Mesh::nodeOrientationType Mesh::getBoundaryNodeOrientation(int pointIndexX, int pointIndexY)
{
    /*int pointIndexX = point.x/dx;
    int pointIndexY = point.y/dy;*/
    bool isVoidOnLeft = false;
    bool isVoidOnRight = false;
    bool isVoidOnTop = false;
    bool isVoidOnBottom = false;

    Mesh::nodeOrientationType boundaryNodeOrientation;
    //left side
    if (pointIndexX == 0)
    {
        isVoidOnLeft = true;
    }
    else
    if (nodeList[pointIndexY][pointIndexX - 1] == 0)
    {
        isVoidOnLeft = true;
    }

    //right side
    if (pointIndexX == nodeSumX - 1)
    {
        isVoidOnRight = true;
    }
    else if (nodeList[pointIndexY][pointIndexX + 1] == 0)
    {
        isVoidOnRight = true;
    }

    //bottom side
    if (pointIndexY == 0)
    {
        isVoidOnBottom = true;
    }
    else if (nodeList[pointIndexY - 1][pointIndexX] == 0)
    {
        isVoidOnBottom = true;
    }

    //top side
    if (pointIndexY == nodeSumY - 1)
    {
        isVoidOnTop = true;
    }
    else if (nodeList[pointIndexY + 1][pointIndexX] == 0)
    {
        isVoidOnTop = true;
    }

    //final enum
    if (isVoidOnLeft)
    {
        if (isVoidOnBottom)
        {
            boundaryNodeOrientation = Mesh::bottomLeft;
        }
        else if (isVoidOnTop)
        {
            boundaryNodeOrientation = Mesh::topLeft;
        }
        else
        {
            boundaryNodeOrientation = Mesh::left;
        }
    }
    else if (isVoidOnRight)
    {
        if (isVoidOnBottom)
        {
            boundaryNodeOrientation = Mesh::bottomRight;
        }
        else if (isVoidOnTop)
        {
            boundaryNodeOrientation = Mesh::topRight;
        }
        else
        {
            boundaryNodeOrientation = Mesh::right;
        }
    }
    else if (isVoidOnTop)
    {
        boundaryNodeOrientation = Mesh::top;
    }
    else if (isVoidOnBottom)
    {
        boundaryNodeOrientation = Mesh::bottom;
    }

    return boundaryNodeOrientation;
}

void Mesh::setBoundaryNodesOrientation()
{
    int boundaryNodeId = 0;

    for (int j = 0; j < nodeSumY; j++)
    {
        for (int i = 0; i < nodeSumX; i++)
        {
            if(nodeList[j][i] > 1)
            {
                boundaryNodeList[nodeList[j][i]].orientation = getBoundaryNodeOrientation(i, j);
            }
        }
    }
}

Mesh::~Mesh()
{
    
}