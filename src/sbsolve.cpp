#include "ui.h"

using namespace std;

int main() {   
    unsigned int threads = thread::hardware_concurrency(); 
    Solver solver(threads);
    ui ui;
    ui.startUI(solver);

    return 0;
}
