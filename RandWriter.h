/*
    Copyright
    PS6 - Markov Chains
    Charles Baxter
    11/15/2021
    RandWriter.h
    Header file for the RandWriter class
*/

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <exception>
#include <chrono>  //NOLINT
#include <random>

class RandWriter {
 public:
    RandWriter(const std::string& itext, size_t ik);

    char k_Rand(const std::string& k_gram) const;
    std::string generate(const std::string& k_gram, int L) const;

    friend std::ostream& operator<<(std::ostream& out, const RandWriter& r);
 private:
    //  fuck you SummonersDrip420
    mutable std::default_random_engine eng;
    uint16_t k;
    std::map<std::string, std::pair<int, std::map<char, int>>> mp;
};
