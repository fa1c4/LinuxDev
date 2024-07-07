#include <iostream>
// using namespace std;


// Print web page demo
void PrintWebHead() {
    std::cout << "Content-type:text/html\n\n";
    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << " <title>Registrator Demo</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";
    std::cout << " <div style=\"width: 100%; font-size: 36px; font-weight: bold; text-align: center; color: blue;\">\n";
    std::cout << " <h2>Testing Web Page</h2>\n";
    std::cout << " Welcome to FA1C4 timespace!\n";
    std::cout << "</div>\n";
    std::cout << "<br />\n";
}

void PrintWebForm() {
    std::cout << "<div style=\"width: 100%; font-size: 20px; font-weight: bold; text-align: center; color: blue;\">\n";
    std::cout << "<form action = \"/cgi-enabled/mWebAppGet.cgi\" method = \"get\">\n";
    std::cout << "Name  : <input type = \"text\" name = \"name\"> <br />\n";
    std::cout << "Gender: <input type = \"text\" name = \"gender\" /> <br /><br />\n";
    std::cout << "<input type = \"submit\" value = \"Submit\" />\n";
    std::cout << "</form>\n";
    std::cout << "</div>\n";
}

void PrintWebEnd() {
    std::cout << "</body>\n";
    std::cout << "</html>\n";
}

int main() {
    PrintWebHead();
    PrintWebForm();
    PrintWebEnd();

    return 0;
}