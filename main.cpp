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

int main() {
    HuffmanCoding hc;
    LZCompression lz;

    std::string inputFilePath = "D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/sources.4.4MB";

    /*
    std::string text = "tangananica-tanganana";
    std::string encoded = hc.codificar(text);
    std::cout << "Encoded: " << encoded << std::endl;

    std::string decoded = hc.decodificar(encoded);
    std::cout << "Decoded: " << decoded << std::endl;

    std::vector<Pair> compressed = lz.comprimir(text);
    std::cout << "Compressed: ";
    for (const auto& p : compressed) {
        std::cout << "(" << p.position << "," << p.length << "," << p.nextChar << ") ";
    }
    std::cout << std::endl;

    std::string decompressed = lz.descomprimir(compressed);
    std::cout << "Decompressed: " << decompressed << std::endl;
    */

    std::string compressedFilePath = "compressed.txt";
    std::string decompressedFilePath = "decompressed.txt";
    std::string huffmanEncodedFilePath = "huffman_encoded.txt";
    std::string huffmanDecodedFilePath = "huffman_decoded.txt";

    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string text = buffer.str();
    inputFile.close();

    // Comprimir el texto
    std::vector<Pair> compressed = lz.comprimir(text);
    // Codificar el texto usando Huffman
    std::string huffmanEncoded = hc.codificar(text);

    // Escribir la salida comprimida en un archivo binario
    std::ofstream compressedFile(compressedFilePath, std::ios::binary);
    if (compressedFile.is_open()) {
        for (const auto& p : compressed) {
            compressedFile.write(reinterpret_cast<const char*>(&p.position), sizeof(p.position));
            compressedFile.write(reinterpret_cast<const char*>(&p.length), sizeof(p.length));
            compressedFile.write(&p.nextChar, sizeof(p.nextChar));
        }
        compressedFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo comprimido para escribir." << std::endl;
        return 1;
    }

    // Leer la salida comprimida desde el archivo binario
    std::vector<Pair> loadedCompressed;
    std::ifstream compressedFileIn(compressedFilePath, std::ios::binary);
    if (compressedFileIn.is_open()) {
        while (compressedFileIn.peek() != EOF) {
            int position, length;
            char nextChar;
            compressedFileIn.read(reinterpret_cast<char*>(&position), sizeof(position));
            compressedFileIn.read(reinterpret_cast<char*>(&length), sizeof(length));
            compressedFileIn.read(&nextChar, sizeof(nextChar));
            loadedCompressed.push_back(Pair(position, length, nextChar));
        }
        compressedFileIn.close();
    } else {
        std::cerr << "No se pudo abrir el archivo comprimido para leer." << std::endl;
        return 1;
    }

    std::string decompressed = lz.descomprimir(loadedCompressed);

    // Escribir la salida descomprimida en un archivo
    std::ofstream decompressedFile(decompressedFilePath, std::ios::binary);
    if (decompressedFile.is_open()) {
        decompressedFile.write(decompressed.c_str(), decompressed.size());
        decompressedFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo descomprimido para escribir." << std::endl;
        return 1;
    }

    // Escribir el texto codificado en un archivo
    std::ofstream huffmanEncodedFile(huffmanEncodedFilePath, std::ios::binary);
    if (huffmanEncodedFile.is_open()) {
        huffmanEncodedFile.write(huffmanEncoded.c_str(), huffmanEncoded.size());
        huffmanEncodedFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo codificado para escribir." << std::endl;
        return 1;
    }

    // Leer el texto codificado desde el archivo
    std::ifstream huffmanEncodedFileIn(huffmanEncodedFilePath, std::ios::binary);
    if (!huffmanEncodedFileIn.is_open()) {
        std::cerr << "No se pudo abrir el archivo codificado para leer." << std::endl;
        return 1;
    }

    std::stringstream encodedBuffer;
    encodedBuffer << huffmanEncodedFileIn.rdbuf();
    std::string loadedHuffmanEncoded = encodedBuffer.str();
    huffmanEncodedFileIn.close();

    // Decodificar el texto usando Huffman
    std::string huffmanDecoded = hc.decodificar(loadedHuffmanEncoded);

    // Escribir el texto decodificado en un archivo
    std::ofstream huffmanDecodedFile(huffmanDecodedFilePath, std::ios::binary);
    if (huffmanDecodedFile.is_open()) {
        huffmanDecodedFile.write(huffmanDecoded.c_str(), huffmanDecoded.size());
        huffmanDecodedFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo decodificado para escribir." << std::endl;
        return 1;
    }

    std::cout << "La compresion y descompresion se completaron. Revisa los archivos 'compressed.txt', 'decompressed.txt', 'huffman_encoded.txt' y 'huffman_decoded.txt'." << std::endl;
    return 0;
}