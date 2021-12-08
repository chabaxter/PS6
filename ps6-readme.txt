/**********************************************************************
 *  readme.txt template                                                   
 *  Random Writer 
 **********************************************************************/

Name: Chares Baxter
Partner: Avinash Kumar

Hours to complete assignment: 4
/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
Ths assignment impliments a markov chain to be used on an input text to
predict the nextcharacter given a specific length k_gram. This allows for
a random weighted choice to be made on what the next character could be.


 /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
A map is used extensively for storing the data for the markov chain. A map
is a key - value pair which is stored using a hash table. This allows for
quick access to each elementand can be indefinately large.

/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
RandWrite.h, line 31
	std::map<std::string, std::pair<int, std::map<char, int>>> mp;

The key of the outer map, a string, is the key of the map. This represents
each order-lengthed k-gram that exists in the whole text. The value of the
outer map, a pair, has two functions. The first element represents the number
of k_grams of that type. The second element is the nested map. The nested map's
key is a character. This character is the character which follows the above
defined k_gram. The value of the nested map is the number of times that character
follows the above k_gram.

RandWriter.cpp, line 45
std::string RandWriter::generate(const std::string& k_gram, int L) const {
    ...
    std::string word = k_gram;
    for (int i = 0; i < L - k; i++)
        word += k_Rand(word.substr(word.length() - k, k));
    return word;
}

The generate function takes a string and an int. The string is the k_gram which
will be used to begin generating characters. The int L is the total length of the
string which will be created. The generate function creates a string to return. 
The first value appened to the string is the k_gram. A random character is then
appended based on the markov chain model. These characters are continually added
until the desired lenght is reached.

RandWriter.cpp, line 27
char RandWriter::k_Rand(const std::string& k_gram) const {
    ...
    std::uniform_int_distribution<size_t> size_t_dist(0, mp.at(k_gram).first);
    int rand_int = size_t_dist(eng);

    for (auto& c : mp.at(k_gram).second) {
        if (rand_int <= c.second)
            return c.first;
        rand_int -= c.second;
    }
    ...
}

The RandWriter object stores a default_random_engine. The k_Rand function 
uses this engine to produce a random int value between 0 and the frequency of
the given k_gram in the markov chain. The next characters are compared to this
random value, starting at the top of the map. If the frequency of that character
is greater than or equal to the random value, that character is returned. If not,
the random value is lowered by the frequency of that chracter, then the next
character is compared. This has the effect of returning a random next character of
the given k_gram with each character carrying its weight.


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
All parts are working. Testing the program on each file yields expected
random outputs and does not throw errors.

/**********************************************************************
 *  Does your implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/
The unit tests pass, the boost libraries do not throw any errors

 /**********************************************************************
 *  Describe where you used exceptions. 
 *  Provide files and lines of the code.
 ***********************************************************************/
Exceptions are used to prevent k_grams which are the wrong size from being
passed to the generate function and k_Rand function. They are also used to
prevent the generate function from generating when the k_gram does not exist.

RandWriter.cpp, line 28
    if (k_gram.length() != k)
        throw(std::invalid_argument("k_Rand: k_gram must be of length k"));

RandWriter.cpp, line 45
    if (k_gram.length() != k)
        throw(std::invalid_argument("generate: k_gram must be of length k"));

    if (!mp.contains(k_gram))
        throw(std::invalid_argument("generate: k_gram must exist"));

 /**********************************************************************
 *  Describe where you used lambda expression if any
 *  Provide files and lines of the code.
 ***********************************************************************/
The lambdda expression is used for the getline function: It takes the text
string by reference then appends the value of getline to it each time.

TextWriter.cpp, line 27
    auto createText = [&text]() {
        std::string this_line;
        while (std::getline(std::cin, this_line)) {
            text += this_line;
        }
    };

/**********************************************************************
 *  Did you implemented program for extra poits? If yes, describe your 
 *  If yes, describe your implementation.
 ***********************************************************************/



/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
The wrong type was used when looping through the text. An unsigned short
was used instead of an unsigned long long. The loop would never complete
as the iterating value would reach its max size before the text was complete


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
