#ifndef EXPORTVTK_H
#define EXPORTVTK_H

#include <string>
#include <fstream>
#include <iostream>
#include "Solver.h"



class ExportVTK
{
public:

    Solver temp;

    ExportVTK();
    void Out(Solver temp_in, int s, int plot_every);
    ~ExportVTK();

private:

};

#endif