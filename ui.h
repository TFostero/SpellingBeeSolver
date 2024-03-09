#ifndef UI_H
#define UI_H

#include <chrono>
#include "Solver.h"

using namespace std;

class ui {
    public:
    ui(Solver);
    void startUI();

    private:
    Solver solver;
    void processInput(string&);
};

#endif