#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>

// Estructura para los nodos del árbol de Huffman
struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
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