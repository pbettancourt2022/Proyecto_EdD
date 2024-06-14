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

    HuffmanCoding huffman;

    std::string inputFilePath = "D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/500KB.txt";

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
    cout << "Iniciando codificación Huffman..." << endl;
    string encodedText = huffman.codificar(text);
    cout << "Codificación Huffman completada." << endl;
    string decodedText = huffman.decodificar(encodedText);
    cout << "Decodificación Huffman completada." << endl;

    // Escribir resultados en archivos
    writeFile("decoded.txt", decodedText);
    
    writeFile("encoded.txt", encodedText);

    // Compresión LZ
    cout << "Iniciando compresión LZ..." << endl;
    vector<Pair> compressedLZ = compress(text);
    cout << "Compresión LZ completada." << endl;
    string decompressedLZ = decompress(compressedLZ);
    cout << "Descompresión LZ completada." << endl;

    auto sizesLZ = calculateSizes(text, compressedLZ);
    cout << "LZ - Tamaño original: " << sizesLZ.first << " bits, Tamaño comprimido: " << sizesLZ.second << " bits" << endl;

    // Guardar el texto descomprimido LZ
    writeFile("decompressedLZ.txt", decompressedLZ);
    writeFile("compressedLZ.txt", pairsToString(compressedLZ));

    return 0;
}
