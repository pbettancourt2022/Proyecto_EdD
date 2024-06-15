#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <chrono>

void printSize(string text, string encodedText, const vector<Pair> &compressed){

    int compressedSize = 0;
    
    for (const Pair &p : compressed) {
        if (p.second == 0) {
            compressedSize += 8; // carácter ASCII (8 bits)
        } else {
            compressedSize += 16; // posición (8 bits) + longitud (8 bits)
        }
    }

    std::cout << "Tamano original: " << text.size() * 8 << " bits" << std::endl;
    std::cout << "Tamano codificado: " << encodedText.size() << " bits" << std::endl;
    std::cout << "Tamano comprimido: " << compressedSize << " bits" << std::endl;
}

double tiempoDeCodificado(string filename){

    auto start = chrono::high_resolution_clock::now();

    HuffmanCoding huffman;

    std::string inputFilePath = filename;

    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string text = buffer.str();
    inputFile.close();

    // Codificación Huffman
    string encodedText = huffman.codificar(text);
    string decodedText = huffman.decodificar(encodedText);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    return duration.count();
}

double tiempoDeCompresion(string filename){

    auto start = chrono::high_resolution_clock::now();

    std::string inputFilePath = filename;

    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string text = buffer.str();
    inputFile.close();

    // Compresión LZ
    vector<Pair> compressedLZ = compress(text);
    string decompressedLZ = decompress(compressedLZ);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    return duration.count();
}



void tiempoDeCodificadoDou(int n_tests,string file_name)
{
    ofstream file_out(file_name + ".csv", ios::app);
    file_out << "Tamaño del archivo, Tiempo" << endl;

        for (int i = 0; i < n_tests; i++)
        {
            file_out << "100KB," << tiempoDeCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/100KB.txt") << endl;
            file_out << "300KB," << tiempoDeCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/300KB.txt") << endl;
            file_out << "500KB," << tiempoDeCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/500KB.txt") << endl;
            file_out << "800KB," << tiempoDeCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/800KB.txt") << endl;
            file_out <<  "1MB,"  << tiempoDeCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/1MB.txt") << endl;
        }

    file_out.close();
}

void tiempoDeCompresionDou(int n_tests,string file_name)
{
    ofstream file_out(file_name + ".csv", ios::app);
    file_out << "Tamaño del archivo, Tiempo" << endl;

        for (int i = 0; i < n_tests; i++)
        {
            file_out << "100KB," << tiempoDeCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/100KB.txt") << endl;
            file_out << "300KB," << tiempoDeCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/300KB.txt") << endl;
            file_out << "500KB," << tiempoDeCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/500KB.txt") << endl;
            file_out << "800KB," << tiempoDeCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/800KB.txt") << endl;
            file_out <<  "1MB,"  << tiempoDeCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/1MB.txt") << endl;
        }

    file_out.close();
}