#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Nodo del Trie
struct TrieNode {
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    int position;

    TrieNode() : position(-1) {}
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;

public:
    Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string& str, int pos) {
        TrieNode* node = root.get();
        for (char c : str) {
            if (!node->children[c]) {
                node->children[c] = std::make_unique<TrieNode>();
            }
            node = node->children[c].get();
        }
        node->position = pos;
    }

    std::pair<int, int> searchLongestPrefix(const std::string& str, int start) {
        TrieNode* node = root.get();
        int maxLength = 0;
        int position = -1;
        for (int i = start; i < str.size(); ++i) {
            if (!node->children[str[i]]) {
                break;
            }
            node = node->children[str[i]].get();
            maxLength = i - start + 1;
            position = node->position;
        }
        return {position, maxLength};
    }
};

// Estructura para almacenar los pares (posición, longitud)
struct Pair {
    int position;
    int length;
    char nextChar;

    Pair(int pos, int len, char next) : position(pos), length(len), nextChar(next) {}
};

// Clase para la compresión y descompresión LZ
class LZCompression {
public:
    // Método para comprimir el texto
    std::vector<Pair> comprimir(const std::string& text) {
        std::vector<Pair> compressed;
        Trie trie;

        int i = 0;
        while (i < text.size()) {
            int length = 0;
            int position = -1;
            char nextChar = text[i];

            auto [foundPosition, foundLength] = trie.searchLongestPrefix(text, i);

            if (foundPosition != -1) {
                position = foundPosition;
                length = foundLength;
                if (i + length < text.size()) {
                    nextChar = text[i + length];
                }
            }

            compressed.push_back(Pair(position, length, nextChar));

            // Insertar el substring actual en el trie
            std::string currentSubstring = text.substr(i, length + 1);
            trie.insert(currentSubstring, i);

            i += length + 1;
        }
        return compressed;
    }

    // Método para descomprimir la secuencia de pares
    std::string descomprimir(const std::vector<Pair>& compressed) {
        std::string decompressed;

        for (const auto& p : compressed) {
            if (p.position != -1) {
                for (int i = 0; i < p.length; ++i) {
                    decompressed += decompressed[p.position + i];
                }
            }
            if (p.nextChar != '\0') {
                decompressed += p.nextChar;
            }
        }

        return decompressed;
    }
};

