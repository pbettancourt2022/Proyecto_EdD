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
    HuffmanCoding huffman;
    std::string text = "tangananica-tanganana";

    std::string encodedText = huffman.codificar(text);
    std::cout << "Texto codificado: " << encodedText << std::endl;

    std::string decodedText = huffman.decodificar(encodedText);
    std::cout << "Texto decodificado: " << decodedText << std::endl;

    vector<Pair> compressed = compress(text);
    string decompressed = decompress(compressed);
    
    cout << "Texto original: " << text << endl;
    cout << "Texto comprimido: ";
    for (const Pair &p : compressed) {
        if (p.second == 0) {
            cout << "(" << char(p.first) << ", " << p.second << ") ";
        } else {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
    }
    cout << endl;
    cout << "Texto descomprimido: " << decompressed << endl;
    
    pair<int, int> sizes = calculateSizes(text, compressed);
    cout << "Tamano del texto original (bits): " << sizes.first << endl;
    cout << "Tamano del texto comprimido (bits): " << sizes.second << endl;

    return 0;
}