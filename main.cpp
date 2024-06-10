#include <iostream>
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

    return 0;
}