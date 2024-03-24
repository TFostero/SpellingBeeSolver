#ifndef UI_H
#define UI_H

#include <chrono>
#include "Solver.h"

using namespace std;

class ui {
    public:
    ui();
    void startUI(Solver&);

    private:
    void processInput(string&);
};

#endif