/*
    Copyright
    PS6 - Markov Chains
    Charles Baxter
    11/15/2021
    test.cpp
    Boost Test file for the RandWriter class
*/

#include <iostream>
#include <string>
#include <exception>

#include "RandWriter.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test1) {
    //  15 is longer than the length of the text, so a k_gram of that length
    //      cannot be generated
    BOOST_REQUIRE_THROW(RandWriter rw("My name jeff", 15),
        std::invalid_argument);

    //  This will work :)_
    BOOST_REQUIRE_NO_THROW(RandWriter rw("My name jeff", 3));

    RandWriter rw("abcabcbcbbbcab", 1);

    //  'a's are only followed by 'b's, so generating a random character from
    //      an'a' should always return a 'b'
    BOOST_REQUIRE(rw.k_Rand("a") == 'b');

    //  'a' exists as a k_gram and is of the correct order
    BOOST_REQUIRE_NO_THROW(rw.k_Rand("a"));

    //  'ab' is not of the correct order
    BOOST_REQUIRE_THROW(rw.k_Rand("ab"), std::invalid_argument);

    //  'a' is a k_gram and 15 is larger than the order
    BOOST_REQUIRE_NO_THROW(rw.generate("a", 15));

    //  'ab' is not of the correct order
    BOOST_REQUIRE_THROW(rw.generate("ab", 14), std::invalid_argument);

    //  'g' is the correct order, but not a k_gram
    BOOST_REQUIRE_THROW(rw.generate("g", 14), std::invalid_argument);
}
