#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <string>
#include <memory>
#include "Codificacion_Huffman.h"
#include "Compresion_LZ.h"
#include "functions.h"

int main() {
/*
    HuffmanCoding huffman;

    std::string inputFilePath = "D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/800KB.txt";

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
    cout << "Iniciando codificacion Huffman..." << endl;
    string encodedText = huffman.codificar(text);
    cout << "Codificacion Huffman completada." << endl;
    string decodedText = huffman.decodificar(encodedText);
    cout << "Decodificacion Huffman completada." << endl;

    // Compresión LZ
    cout << "Iniciando compresion LZ..." << endl;
    vector<Pair> compressedLZ = compress(text);
    cout << "Compresion LZ completada." << endl;
    string decompressedLZ = decompress(compressedLZ);
    cout << "Descompresion LZ completada." << endl;

    printSize(text, encodedText, compressedLZ);
    */
    
    tiempoCodificadoDou(20,"Tiempocodificado");

    return 0;
}
