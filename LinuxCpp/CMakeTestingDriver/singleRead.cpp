#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream filein;
    string last_line = "";
    string tmp_line = "";

    filein.open("./example.txt", std::ios::in);
    if (!filein.is_open()) {
        cout << "can't open the file" << endl;
        exit(0);
    }

    bool is_first_line = true;
    while (getline(filein, tmp_line)) {
        last_line = tmp_line;
        if (is_first_line) {
            cout << "first line of file is: " << tmp_line << endl;
            is_first_line = false;
        }
    }
    cout << "last line of file is: " << last_line << endl;

    filein.close();
    return 0;
}