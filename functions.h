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

std::pair<double, double> tiempoCodificado(string filename) {
    auto start = chrono::high_resolution_clock::now();

    HuffmanCoding huffman;

    std::string inputFilePath = filename;

    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string text = buffer.str();
    inputFile.close();

    // Codificación Huffman
    string encodedText = huffman.codificar(text);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationencoded = end - start;

    start = chrono::high_resolution_clock::now();

    string decodedText = huffman.decodificar(encodedText);

    end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationdecoded = end - start;

    return {durationencoded.count(), durationdecoded.count()};
}

std::pair<double, double> tiempoCompresion(string filename) {
    auto start = chrono::high_resolution_clock::now();

    std::string inputFilePath = filename;

    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string text = buffer.str();
    inputFile.close();

    // Compresión LZ
    vector<Pair> compressedLZ = compress(text);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationcompress = end - start;

    start = chrono::high_resolution_clock::now();

    string decompressedLZ = decompress(compressedLZ);

    end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationdecompress = end - start;

    return {durationcompress.count(), durationdecompress.count()};
}

void tiempoCodificadoDou(int n_tests,string file_name)
{
    ofstream file_out(file_name + ".csv", ios::app);
    file_out << "Tamaño del archivo, Tiempo de Codificacion(s), Tiempo de Decodificacion(s)" << endl;

        for (int i = 0; i < n_tests; i++) {
        auto tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/100KB.txt");
        file_out << "100KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/300KB.txt");
        file_out << "300KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/500KB.txt");
        file_out << "500KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/800KB.txt");
        file_out << "800KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/1MB.txt");
        file_out << "1MB,"  << tiempos.first << "," << tiempos.second << endl;
    }

    file_out.close();
}

void tiempoCompresionDou(int n_tests,string file_name)
{
    ofstream file_out(file_name + ".csv", ios::app);
    file_out << "Tamaño del archivo, Tiempo de Compresion(s), Tiempo de Decompresion(s)" << endl;

        for (int i = 0; i < n_tests; i++) {
        auto tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/100KB.txt");
        file_out << "100KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/300KB.txt");
        file_out << "300KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/500KB.txt");
        file_out << "500KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/800KB.txt");
        file_out << "800KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/1MB.txt");
        file_out << "1MB,"  << tiempos.first << "," << tiempos.second << endl;
    }

    file_out.close();
}