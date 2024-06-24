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

    //Esta primera parte es solo para saber el tamaño del archivo normal, codificado y comprimido en bits, se cambia el nombre del archivo 
    //dependiendo de que archivo se quiera medir.
    HuffmanCoding huffman;

    std::string inputFilePath = "800KB.txt";

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

    // Se imprimen en pantalla los tamaños en bits
    printSize(text, encodedText, compressedLZ);
    
    //Esta segunda parte es para hacer las respectivas pruebas para poder hacer las graficas 
    tiempoCodificadoDou(20,"TiempoCodificado");
    tiempoCompresionDou(20,"TiempoComprimido");

    //Si quiere hacer solo una parte, solo se tiene que comentar la parte que se quiere saltar 

    return 0;
}
