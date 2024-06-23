#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>

using namespace std;

typedef pair<int, int> Pair;
/**
 * @brief Encuentra la coincidencia más larga en una cadena de texto.
 * @param s La cadena en la que se busca la coincidencia.
 * @param currentPosition La posición actual dentro de la cadena donde se está buscando la coincidencia.
 * @return Dos enteros que representan la posición y longitud de la coincidencia más larga.
 */
Pair findLongestMatch(const string &s, int currentPosition) {
    int maxMatchLength = 0;
    int matchPosition = 0;

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

/**
 * @brief Comprime una cadena de texto utilizando el algoritmo de compresión LZ
 * @param t La cadena de texto que se desea comprimir.
 * @return Un vector de pares que representa la versión comprimida de la cadena de texto `t`.
 */
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

/**
 * @brief Descomprime una secuencia de pares para obtener el texto original.
 * @param c Vector de pares que representa la versión comprimida del texto.
 * @return El texto original descomprimido.
 */
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
