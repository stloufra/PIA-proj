#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "InputFileParser.h"
#include "PolygonBoundary.h"
#include "Mesh.h"
#include "Solver.h"
#include "ExportVTK.h"


int main()
{
    InputFileParser parser = InputFileParser();
    parser.readFile("data.txt");
    parser.parse();
    std::vector<std::vector<int>> data1 = parser.getData();

    double a = 0.12;
    double dt = 0.005;
    double dx = 0.1;
    double endTime = 30;
    int plotEvery = 20;

    PolygonBoundary boundary = PolygonBoundary(data1);

    Mesh mesh = Mesh(boundary, dx);


    /////////////////////////////// Odsud je to vase :-)
    
    Solver Temperature = Solver();
    Temperature.Init(mesh, 20.3);
    
    int iterationEnd = int (endTime/dt);
    ExportVTK Exp = ExportVTK();
    
    for(int iteration; iteration<iterationEnd; iteration++)
    {
        Temperature.Iter(dt, a, dx);
        Temperature.Stream();

        if(iteration%plotEvery==0)
        {
            Exp.Out(Temperature, iteration, plotEvery);
        }
    }
    
// soradnice uzlu
    int x = 2;
    int y = 3;

//pokud 1 uzel uvnitr pokud 0 uzel venku, pokud jine cislo uzel na hranici, hodnota odpovida indexu v seznamu boundary node list
    unsigned char uzel = mesh.nodeList[y][x];
    int adresa = (int)mesh.nodeList[y][x];

//pokud uzel na hranici, parametry uzlu jsou ulozeny v seznamu boundaryNodeList
    mesh.boundaryNodeList[adresa].boundaryConditionType; //pokud je hodnota 1 pak jde o predepsanou teplotu, pokud 2 pak jde o tepelny tok smerem ven, pokud 3 pak jde o konvekci

//orientace hranicniho uzlu př. pokud bottom pak je smerem dolu (y-1) "prazdno" tedy vnitrek oblasti je nad bodem
    mesh.boundaryNodeList[adresa].orientation;

//prvni parametr pokud je boundaryConditionType 1 pak jde o teplotu, pokud 2 pak jde o hodnotu tepelneho toku, pokud 3 pak jde o teplotu T infty
    mesh.boundaryNodeList[adresa].param1;

//pokud je boundaryConditionType pak parametr odpovida koeficientu alfa "konvekce", jinak se nepouziva
    mesh.boundaryNodeList[adresa].param2;




//Doporucuji vytvorit tridu pro resic napriklad "Solver"
//v nem vytvorit instanci "meshe" tedy predat tride instanci mesh (klidne to prejmenujte)
//v tride solver nasledne vytvorit funkci pro vypocet v jedne casove vrstve, bude vracet 2D vector teploty
//a vytvorit dalsi tridu pro ulozeni vypoctu v casove vrstve do souboru

//toto bych doporucil algoritmizovat v cyklu (postupne vypocitat vsechny caseve vrstvy az do zadaneho casu endTime), pro tento cyklus bych vytvoril dalsi funkci, pak se bude tedy z havniho mainu volat pouze jedna funkce

    

    
    return 0;
}