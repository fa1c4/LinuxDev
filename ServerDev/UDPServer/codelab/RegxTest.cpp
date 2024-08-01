/*
Usage: echo "string_to_match" | ./RegxTest
        cat <file_to_match> | ./RegxTest
*/

#include <iostream>
#include <boost/regex.hpp>
#include <string>


// verify credit card number example: 1234-5678-4321-9876
int main(int argc, char* argv[]) {
    std::string line;
    boost::regex pattern("(\\d{4})[- ]?(\\d{4})[- ]?(\\d{4})[- ]?(\\d{4})");
    boost::smatch matches;

    std::getline(std::cin, line);
    if (boost::regex_match(line, matches, pattern)) {
        std::cout << "Matched Pattern: " << std::endl;
        for (auto it = matches.begin(); it != matches.end(); it++) {
            std::cout << "Number: " << *it << std::endl;
        }
    } else {
        std::cout << "--> Not Matched Credit Card Pattern" << std::endl;
    }

    return 0;
}
