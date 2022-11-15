#include "ExportVTK.h"
#include "Solver.h"

#include <string>
#include <fstream>
#include <iostream>

ExportVTK::ExportVTK()
{
    
}

void ExportVTK::Out(Solver temp_in, int s, int plot_every)
{
    temp = temp_in;

    std::string step =std::to_string(s/plot_every);
    std::ofstream out_file("Poasson."+step+".vtk");

    out_file << "# vtk DataFile Version 2.0\n" ;
    out_file << "LBE two cylinders\n" ;
    out_file << "ASCII\n";
    out_file << "DATASET STRUCTURED_POINTS\n" ;
    out_file << "DIMENSIONS "<<temp.mesh.nodeList[0].size()<<" "<<temp.mesh.nodeList.size()<<" 1\n" ;
    out_file << "ASPECT_RATIO 1 1 1\n";
    out_file << "ORIGIN 0 0 0\n";
    out_file << "POINT_DATA "<<temp.mesh.nodeList[0].size()*(temp.mesh.nodeList.size())<<"\n";

    out_file << "SCALARS "<<"Temperature[°C] "<<"double 1\n";
    out_file << "LOOKUP_TABLE default\n";
    for (int j = 0; j < temp.U_n.size(); j++)
    {
        for (int i = 0; i < temp.U_n.size(); i++)
        {
            out_file <<temp.U_n[j][i] <<"\n";
        }
    }
    out_file << "SCALARS "<<"nodes "<<"double 1\n";
    out_file << "LOOKUP_TABLE default\n";
     for (int j = 0; j < temp.mesh.nodeList.size(); j++)
    {
        for (int i = 0; i < temp.mesh.nodeList[j].size(); i++)
        {
           int vystup = (int)temp.mesh.nodeList[j][i];
            
            if (vystup > 1)
            {
                
                if(temp.mesh.boundaryNodeList[temp.mesh.nodeList[j][i]].orientation == Mesh::top)
                {
                    vystup = 2;
                }
                else if(temp.mesh.boundaryNodeList[temp.mesh.nodeList[j][i]].orientation == Mesh::right)
                {
                    vystup = 3;
                }
                else if(temp.mesh.boundaryNodeList[temp.mesh.nodeList[j][i]].orientation == Mesh::bottom)
                {
                    vystup = 4;
                }
                else if(temp.mesh.boundaryNodeList[temp.mesh.nodeList[j][i]].orientation == Mesh::left)
                {
                    vystup = 5;
                }
                else if(temp.mesh.boundaryNodeList[temp.mesh.nodeList[j][i]].orientation == Mesh::topRight)
                {
                    vystup = 6;
                }
                else if(temp.mesh.boundaryNodeList[temp.mesh.nodeList[j][i]].orientation == Mesh::bottomRight)
                {
                    vystup = 7;
                }
                else if(temp.mesh.boundaryNodeList[temp.mesh.nodeList[j][i]].orientation == Mesh::bottomLeft)
                {
                    vystup = 8;
                }
                else if(temp.mesh.boundaryNodeList[temp.mesh.nodeList[j][i]].orientation == Mesh::topLeft)
                {
                    vystup = 9;
                }
            }
            out_file <<vystup<<"\n";
        }
    } 
    out_file.close();
}

ExportVTK::~ExportVTK()
{

}