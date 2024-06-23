#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>

// Estructura para representar un nodo en un árbol de Huffman.
struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode* left;
    HuffmanNode* right;
    /**
     * Constructor de un nodo de Huffman.
     * 
     * @param data Carácter que el nodo representa.
     * @param freq Frecuencia de aparición del carácter.
     */
    HuffmanNode(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};
// Estructura que define un functor para comparar dos nodos de Huffman por su frecuencia.
struct Compare {
    /**
     * Functor que realiza la comparación.
     *
     * @param l Puntero al primer nodo de Huffman.
     * @param r Puntero al segundo nodo de Huffman.
     * @return True si la frecuencia de h1 es mayor a la de h2, false en caso contrario.
     */
    bool operator()(HuffmanNode* hl, HuffmanNode* h2) {
        return (hl->freq > h2->freq);
    }
};

class HuffmanCoding {
    HuffmanNode* root;
    std::unordered_map<char, std::string> codes;
    std::unordered_map<std::string, char> reverseCodes;

    void buildCodes(HuffmanNode* node, std::string str) {
        if (!node) return;

        if (!node->left && !node->right) {
            codes[node->data] = str;
            reverseCodes[str] = node->data;
        }

        buildCodes(node->left, str + "0");
        buildCodes(node->right, str + "1");
    }

    HuffmanNode* buildTree(std::unordered_map<char, unsigned> freqMap) {
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;

        for (auto pair : freqMap) {
            minHeap.push(new HuffmanNode(pair.first, pair.second));
        }

        while (minHeap.size() != 1) {
            HuffmanNode* left = minHeap.top(); minHeap.pop();
            HuffmanNode* right = minHeap.top(); minHeap.pop();

            HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            minHeap.push(top);
        }

        return minHeap.top();
    }

public:
    HuffmanCoding() : root(nullptr) {}

    std::string codificar(const std::string& text) {
        std::unordered_map<char, unsigned> freqMap;
        for (char c : text) {
            freqMap[c]++;
        }

        root = buildTree(freqMap);
        buildCodes(root, "");

        std::string encodedString;
        for (char c : text) {
            encodedString += codes[c];
        }
        return encodedString;
    }

    std::string decodificar(const std::string& encodedText) {
        std::string decodedString;
        std::string currentCode;
        for (char bit : encodedText) {
            currentCode += bit;
            if (reverseCodes.find(currentCode) != reverseCodes.end()) {
                decodedString += reverseCodes[currentCode];
                currentCode = "";
            }
        }
        return decodedString;
    }
};