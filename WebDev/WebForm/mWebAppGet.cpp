#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>


// http://192.168.0.109//cgi-enabled/mWebAppGet.cgi?xxx

using namespace cgicc;

void PrintWebHead() {
    std::cout << "Content-type:text/html\n\n";
    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << " <title>Web Program Get Page demo</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";
    std::cout << " <div style=\"width: 100%; font-size: 36px; font-weight: bold; text-align: center; color: blue;\">\n";
    std::cout << " <h2>Get App Web Page</h2>\n";
    std::cout << " FA1C4 C++ web programing test get page\n";
    std::cout << "</div>\n";
    std::cout << "<br />\n";
}

void PrintWebEnd() {
    std::cout << "</body>\n";
    std::cout << "</html>\n";
}

int main() {
    Cgicc formData;
    form_iterator fi;

    PrintWebHead();
    std::cout << " <div style=\"width: 100%; font-size: 20px; font-weight: bold; text-align: center; color: red;\">\n";
    fi = formData.getElement("name");
    std::cout << "Name : ";
    if (!fi->isEmpty()) {
        std::cout << **fi;
    }
    std::cout << "<br />\n";

    fi = formData.getElement("gender");
    std::cout << "Gender : ";
    if (!fi->isEmpty()) {
        std::cout << **fi;
    }
    std::cout << "<br />\n";

    std::cout << "</div>\n";
    PrintWebEnd();

    return 0;
}