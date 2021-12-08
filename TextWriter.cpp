/*
    Copyright
    PS6 - Markov Chains
    Charles Baxter
    11/15/2021
    TextWriter.cpp
    Driver program for random writer object. Redirect the standard
        input to a file. Run with argv[1] as length of k-gram
        and argv[2] as length of text to be generated.
*/

#include <iostream>
#include <fstream>
#include <string>

#include "RandWriter.h"

int main(int argc, char* argv[]) {
    if (argc != 3)
        return 1;

    size_t k = std::stoul(argv[1]);
    size_t L = std::stoul(argv[2]);

    std::string text;

    auto createText = [&text]() {
        std::string this_line;
        while (std::getline(std::cin, this_line)) {
            text += this_line;
        }
    };

    createText();

    RandWriter r(text, k);

    std::cout << r.generate(text.substr(0, k), L);

    //  std::cout << r;

    return 0;
}
