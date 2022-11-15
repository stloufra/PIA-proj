#ifndef POLYGONBOUNDARY_H
#define POLYGONBOUNDARY_H

struct Point
{
    double x;
    double y;
};

class PolygonBoundary
{
    
    public:
        struct BoundarySegment
        {
            Point endPoint;
            unsigned char boundaryType;
            float param1;
            float param2;
        };
    
        PolygonBoundary();
        PolygonBoundary(std::vector<std::vector<int>> data);
        virtual ~PolygonBoundary();

        void load(std::vector<std::vector<int>> data);

        std::vector<BoundarySegment> boundaryEndPoints;
};

#endif // POLYGONBOUNDARY_H