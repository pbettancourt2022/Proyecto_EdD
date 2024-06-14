#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>


string readFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se puede abrir el archivo: " << filename << endl;
        exit(1);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void writeFile(const string &filename, const string &content) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "No se puede escribir en el archivo: " << filename << endl;
        exit(1);
    }
    file << content;
    file.close();
}

string pairsToString(const vector<Pair> &pairs) {
    string result;
    for (const Pair &p : pairs) {
        if (p.second == 0) {
            result += "(" + string(1, char(p.first)) + ", " + to_string(p.second) + ") ";
        } else {
            result += "(" + to_string(p.first) + ", " + to_string(p.second) + ") ";
        }
    }
    return result;
}