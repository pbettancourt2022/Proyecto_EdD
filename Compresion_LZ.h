#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>

using namespace std;

typedef pair<int, int> Pair;

// Función para encontrar la coincidencia más larga del substring en la ventana
Pair findLongestMatch(const string &s, int currentPosition) {
    int maxMatchLength = 0;
    int matchPosition = 0;

    // Ventana deslizante para encontrar la coincidencia más larga
    for (int i = 0; i < currentPosition; ++i) {
        int length = 0;
        while (s[i + length] == s[currentPosition + length] && (currentPosition + length) < s.size()) {
            ++length;
        }
        if (length > maxMatchLength) {
            maxMatchLength = length;
            matchPosition = i;
        }
    }
    return {matchPosition, maxMatchLength};
}

// Comprimir el texto usando compresión LZ
vector<Pair> compress(const string &t) {
    vector<Pair> compressed;
    int i = 0;
    
    while (i < t.size()) {
        Pair match = findLongestMatch(t, i);
        
        if (match.second > 0) {
            compressed.push_back(match);
            i += match.second;
        } else {
            compressed.push_back({t[i], 0});
            ++i;
        }
    }
    
    return compressed;
}

// Descomprimir la secuencia de pares para obtener el texto original
string decompress(const vector<Pair> &c) {
    string decompressed;
    
    for (const Pair &p : c) {
        if (p.second == 0) {
            decompressed += char(p.first);
        } else {
            int start = p.first;
            for (int i = 0; i < p.second; ++i) {
                decompressed += decompressed[start + i];
            }
        }
    }
    
    return decompressed;
}
