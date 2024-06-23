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
     * @brief Constructor de un nodo de Huffman.
     * @param data Carácter que el nodo representa.
     * @param freq Frecuencia de aparición del carácter.
     */
    HuffmanNode(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};
// Estructura que define un functor para comparar dos nodos de Huffman por su frecuencia.
struct Compare {
    /**
     * @brief Functor que realiza la comparación.
     * @param l Puntero al primer nodo de Huffman.
     * @param r Puntero al segundo nodo de Huffman.
     * @return True si la frecuencia de h1 es mayor a la de h2, false en caso contrario.
     */
    bool operator()(HuffmanNode* hl, HuffmanNode* h2) {
        return (hl->freq > h2->freq);
    }
};

// Clase para la codificación y decodificación utilizando el algoritmo de Huffman.
class HuffmanCoding {
    HuffmanNode* root;
    std::unordered_map<char, std::string> codes;
    std::unordered_map<std::string, char> reverseCodes;
    /**
     * @brief Función recursiva para construir los códigos binarios de Huffman.
     * @param node Nodo actual en el árbol de Huffman.
     * @param str Cadena de ceros y unos acumulada para el código binario del camino actual.
     */
    void buildCodes(HuffmanNode* node, std::string str) {
        if (!node) return;

        if (!node->left && !node->right) {
            codes[node->data] = str;
            reverseCodes[str] = node->data;
        }

        buildCodes(node->left, str + "0");
        buildCodes(node->right, str + "1");
    }
    /**
     * @brief Función que construye el árbol de Huffman basado en las frecuencias de los caracteres.
     * @param freqMap Mapa que contiene las frecuencias de los caracteres en el texto.
     * @return Puntero a la raíz del árbol de Huffman construido.
     */
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
// Constructor de clases de codificación de Huffman.
public:
    HuffmanCoding() : root(nullptr) {}
    /**
     * @brief Función que codifica una cadena de texto utilizando el algoritmo de Huffman.
     * @param text Cadena de texto sin codificar.
     * @return La cadena codificada usando el algoritmo de Huffman.
     */
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
    /**
     * @brief Función que decodifica una cadena codificada utilizando el algoritmo de Huffman.
     * @param text Cadena codificada.
     * @return La cadena de texto sin codificar.
     */
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