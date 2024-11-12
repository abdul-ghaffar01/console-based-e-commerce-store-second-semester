#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <iostream>
#include <fstream>
#include <string>
#include "list.cpp"

using namespace std;

class FileHandler {
private:
    string filename; // File path for storing data

public:
    // Constructor to initialize filename
    FileHandler(const string &filename) : filename(filename) {}

    // Read all lines from the file into a List
    List<string> readAllLines() {
        List<string> lines;
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return lines;
        }

        string line;
        while (getline(file, line)) {
            lines.push_back(line); // Assuming List has push_back method
        }
        file.close();
        return lines;
    }

    // Write all lines from a List to the file (overwrites file contents)
    void writeAllLines(const List<string> &lines) {
        ofstream file(filename, ios::trunc);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        for (int i = 0; i < lines.length(); ++i) {
            file << lines[i] << endl;
        }
        file.close();
    }

    // Append a single line to the file
    void appendLine(const string &line) {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        file << line << endl;
        file.close();
    }

    // Append multiple lines from a List to the file
    void appendLines(const List<string> &lines) {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        for (int i = 0; i < lines.length(); ++i) {
            file << lines[i] << endl;
        }
        file.close();
    }
};

#endif