#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "InputFileParser.h"
#include "PolygonBoundary.h"
#include "Mesh.h"


int main()
{
    InputFileParser parser1 = InputFileParser();
    parser1.readFile("data.txt");
    parser1.parse();
    std::vector<std::vector<int>> data1 = parser1.getData();

    double a = 0.12;
    double dt = 0.01;
    double dx = 0.2;
    double endTime = 10;

    PolygonBoundary boundary1 = PolygonBoundary(data1);

    Mesh mesh1 = Mesh(boundary1, dx);


    /////////////////////////////// Odsud je to vase :-)

// soradnice uzlu
    int x = 2;
    int y = 3;

//pokud 1 uzel uvnitr pokud 0 uzel venku, pokud jine cislo uzel na hranici, hodnota odpovida indexu v seznamu boundary node list
    unsigned char uzel = mesh1.nodeList[y][x];
    int adresa = (int)mesh1.nodeList[y][x];

//pokud uzel na hranici, parametry uzlu jsou ulozeny v seznamu boundaryNodeList
    mesh1.boundaryNodeList[adresa].boundaryConditionType; //pokud je hodnota 1 pak jde o predepsanou teplotu, pokud 2 pak jde o tepelny tok smerem ven, pokud 3 pak jde o konvekci

//orientace hranicniho uzlu př. pokud bottom pak je smerem dolu (y-1) "prazdno" tedy vnitrek oblasti je nad bodem
    mesh1.boundaryNodeList[adresa].orientation;

//prvni parametr pokud je boundaryConditionType 1 pak jde o teplotu, pokud 2 pak jde o hodnotu tepelneho toku, pokud 3 pak jde o teplotu T infty
    mesh1.boundaryNodeList[adresa].param1;

//pokud je boundaryConditionType pak parametr odpovida koeficientu alfa "konvekce", jinak se nepouziva
    mesh1.boundaryNodeList[adresa].param2;




//Doporucuji vytvorit tridu pro resic napriklad "Solver"
//v nem vytvorit instanci "meshe" tedy predat tride instanci mesh1 (klidne to prejmenujte)
//v tride solver nasledne vytvorit funkci pro vypocet v jedne casove vrstve, bude vracet 2D vector teploty
//a vytvorit dalsi tridu pro ulozeni vypoctu v casove vrstve do souboru

//toto bych doporucil algoritmizovat v cyklu (postupne vypocitat vsechny caseve vrstvy az do zadaneho casu endTime), pro tento cyklus bych vytvoril dalsi funkci, pak se bude tedy z havniho mainu volat pouze jedna funkce

    

    // debug, zde je mozne vypsat hodnoty orientace a typ uzlu
    /*std::ofstream zapisDoSouboru("vystup.txt");    
    for (int j = 0; j < mesh1.nodeList.size(); j++)
    {
        for (int i = 0; i < mesh1.nodeList[j].size(); i++)
        {
            int vystup = (int)mesh1.nodeList[j][i];
            
            if (vystup > 1)
            {
                //vystup = (mesh1.boundaryNodeList[mesh1.nodeList[j][i]].param1);
                if(mesh1.boundaryNodeList[mesh1.nodeList[j][i]].orientation == Mesh::top)
                {
                    vystup = 2;
                }
                else if(mesh1.boundaryNodeList[mesh1.nodeList[j][i]].orientation == Mesh::right)
                {
                    vystup = 3;
                }
                else if(mesh1.boundaryNodeList[mesh1.nodeList[j][i]].orientation == Mesh::bottom)
                {
                    vystup = 4;
                }
                else if(mesh1.boundaryNodeList[mesh1.nodeList[j][i]].orientation == Mesh::left)
                {
                    vystup = 5;
                }
                else if(mesh1.boundaryNodeList[mesh1.nodeList[j][i]].orientation == Mesh::topRight)
                {
                    vystup = 6;
                }
                else if(mesh1.boundaryNodeList[mesh1.nodeList[j][i]].orientation == Mesh::bottomRight)
                {
                    vystup = 7;
                }
                else if(mesh1.boundaryNodeList[mesh1.nodeList[j][i]].orientation == Mesh::bottomLeft)
                {
                    vystup = 8;
                }
                else if(mesh1.boundaryNodeList[mesh1.nodeList[j][i]].orientation == Mesh::topLeft)
                {
                    vystup = 9;
                }
            }

            zapisDoSouboru << vystup << " ";
        }
        zapisDoSouboru << std::endl;
    }*/
    
    return 0;
}