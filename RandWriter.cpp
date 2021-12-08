/*
    Copyright
    PS6 - Markov Chains
    Charles Baxter
    11/15/2021
    RandWriter.cpp
    Implimentation of the RandWriter class
*/

#include "RandWriter.h"
RandWriter::RandWriter(const std::string& itext, size_t ik)
    : eng(std::chrono::steady_clock::now().time_since_epoch().count()), k(ik) {
    if (itext.length() <= k)
        throw(std::invalid_argument(
            "RandWriter: length of text must be greater than k"));
    std::string circularText = itext + itext.substr(0, k);
    for (size_t i = 0; i < itext.length(); i++) {
        if (mp.contains(circularText.substr(i, k))) {
            mp[circularText.substr(i, k)].first++;
        } else {
            mp[circularText.substr(i, k)].first = 1;
        }
        mp[circularText.substr(i, k)].second[circularText[i + k]]++;
    }
}

char RandWriter::k_Rand(const std::string& k_gram) const {
    if (k_gram.length() != k)
        throw(std::invalid_argument("k_Rand: k_gram must be of length k"));

    std::uniform_int_distribution<size_t> size_t_dist(0, mp.at(k_gram).first);
    int rand_int = size_t_dist(eng);

    for (auto& c : mp.at(k_gram).second) {
        if (rand_int <= c.second)
            return c.first;
        rand_int -= c.second;
    }

    //  In case the for loop fails, which should never happen
    //  (make the compiler happy)
    return '~';
}

std::string RandWriter::generate(const std::string& k_gram, int L) const {
    if (k_gram.length() != k)
        throw(std::invalid_argument("generate: k_gram must be of length k"));

    if (!mp.contains(k_gram))
        throw(std::invalid_argument("generate: k_gram must exist"));

    std::string word = k_gram;
    for (int i = 0; i < L - k; i++)
        word += k_Rand(word.substr(word.length() - k, k));
    return word;
}

std::ostream& operator<<(std::ostream& out, const RandWriter& r) {
    out << "Order: " << r.k << std::endl;
    for (const auto& c : r.mp) {
        out << "  " << c.first << ": " << c.second.first << std::endl;
        for (auto& d : c.second.second) {
            out << "    " << d.first << ": " << d.second << std::endl;
        }
    }

    return out;
}
