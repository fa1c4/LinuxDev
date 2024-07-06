#include <iostream>
// using namespace std;


// Print web page demo
void PrintWebPage() {
    std::cout << "Content-type:text/html\n\n";
    std::cout << "<html>\n";
    std::cout << " <title>Testing for - First C++ Web Program</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";
    std::cout << " <div style=\"width: 100%; font-size: 36px; font-weight: bold; text-align: center; color: blue;\">\n";
    std::cout << " <h2>Testing Web Page</h2>\n";
    std::cout << " Welcome to FA1C4 timespace!\n";
    std::cout << "</div>\n";
    std::cout << "</body>\n";
    std::cout << "</html>\n";
}

int main() {
    PrintWebPage();

    return 0;
}