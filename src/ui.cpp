#include "ui.h"

ui::ui() {}

void ui::startUI(Solver& solver) {
    bool loop = true;

    while (loop) {
        chrono::time_point<chrono::_V2::system_clock> start, end;
        chrono::duration<float> duration;
        float ms;

        string optionalChars;
        string requiredChars;
        cout << "Input optional characters: ";
        getline(cin, optionalChars);
        cout << "Input required characters: ";
        getline(cin, requiredChars);
        processInput(optionalChars);
        processInput(requiredChars);

        start = chrono::high_resolution_clock::now();
        vector<string> results = solver.solve(optionalChars, requiredChars);
        end = chrono::high_resolution_clock::now();

        duration = end - start;
        ms = duration.count() * 1000.0f;
        cout << "Duration (ms): " << ms << "\n";

        sort(results.begin(), results.end());

        for (auto& result : results) {
            cout << result << endl;
        }

        string in;
        cout << "Go again? <y/n>: ";
        getline(cin, in);
        processInput(in);
        if (in != "y") {
            loop = false;
        } 
    }
}

void ui::processInput(string& input) {
    for (char& c : input) {
        c = tolower(c);
    }

    input.erase(remove_if(input.begin(), input.end(), [](char c) {
        return c < 'a' || c > 'z';
    }), input.end());
}
