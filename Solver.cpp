#include "Solver.h"
#include "Mesh.h"
#include <vector>

Solver::Solver()
{
    std::vector<std::vector<double>> U_n;
    std::vector<std::vector<double>> U_n1;
}

void Solver::Init(Mesh mesh_input, double T0)
{
 
    mesh = mesh_input;

    for (int j = 0; j < mesh.nodeList.size(); j++)
    {
        std::vector<double> vh;


        for (int i = 0; i < mesh.nodeList[j].size(); i++)
        {
            if (mesh.nodeList[j][i] == 0)
            {
                vh.push_back(-300.0);
            }

        
            else if (mesh.nodeList[j][i] == 1)
            {
                vh.push_back(T0);
            }

            else if (mesh.boundaryNodeList[mesh.nodeList[j][i]].boundaryConditionType == 1)
            {
                vh.push_back(mesh.boundaryNodeList[mesh.nodeList[j][i]].param1);
            }
            
        }

        U_n.push_back(vh);
        U_n1.push_back(vh);
    }  

}

void Solver::Iter(double timestep, double a, double h)
{
    
    for (int j = 0; j < mesh.nodeList.size(); j++)
    {
        
        for (int i = 0; i < mesh.nodeList[j].size(); i++)
        {
            if (mesh.nodeList[j][i] == 1)
            {
                U_n1[j][i] = timestep*a/h/h* (U_n[j-1][i] + U_n[j+1][i] + U_n[j][i-1] + U_n[j][i+1] - 4*U_n[j][i]) + U_n[j][i];
            }

            else if (mesh.boundaryNodeList[mesh.nodeList[j][i]].boundaryConditionType == 1)
            {
                U_n1[j][i]=U_n[j][i]; 
            }
            
            /*else if(mesh.nodeList[j][i] == 0) 
            {
                U_n1[j][i]=U_n[j][i];
            }

            if(mesh.boundaryNodeList[mesh.nodeList[j][i]].orientation == Mesh::top)
            {
                U_n1[j][i]=U_n[j][i];                       
            }

            else if(mesh.boundaryNodeList[mesh.nodeList[j][i]].orientation == Mesh::right)
            {
                U_n1[j][i]=U_n[j][i];
            }
            else if(mesh.boundaryNodeList[mesh.nodeList[j][i]].orientation == Mesh::bottom)
            {
                U_n1[j][i]=U_n[j][i];
            }
            else if(mesh.boundaryNodeList[mesh.nodeList[j][i]].orientation == Mesh::left)
            {
                U_n1[j][i]=U_n[j][i];
            }
            else if(mesh.boundaryNodeList[mesh.nodeList[j][i]].orientation == Mesh::topRight)
            {
                U_n1[j][i]=U_n[j][i];
            }
            else if(mesh.boundaryNodeList[mesh.nodeList[j][i]].orientation == Mesh::bottomRight)
            {
                U_n1[j][i]=U_n[j][i];
            }
            else if(mesh.boundaryNodeList[mesh.nodeList[j][i]].orientation == Mesh::bottomLeft)
            {
                U_n1[j][i]=U_n[j][i];
            }
            else if(mesh.boundaryNodeList[mesh.nodeList[j][i]].orientation == Mesh::topLeft)
            {
                U_n1[j][i]=U_n[j][i];
            }
            */
        }
    }
}

void Solver::Stream()
{
    for (int j = 0; j < mesh.nodeList.size(); j++)
    {
    
        for (int i = 0; i < mesh.nodeList[j].size(); i++)
        {
            U_n[j][i]=U_n1[j][i];
        }
    }
}

Solver::~Solver()
{

}