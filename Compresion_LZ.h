#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


struct Pair {
    int position;
    int length;
    char nextChar;

    Pair(int p, int l, char c) : position(p), length(l), nextChar(c) {}
};

class LZCompression {
public:
    std::vector<Pair> comprimir(const std::string& text) {
        std::vector<Pair> compressed;
        std::unordered_map<std::string, int> dictionary;
        int i = 0;

        while (i < text.size()) {
            int maxLength = 0;
            int maxPos = -1;
            char nextChar = '\0';

            for (int length = 1; length <= text.size() - i; ++length) {
                std::string substring = text.substr(i, length);
                auto it = dictionary.find(substring);
                if (it != dictionary.end()) {
                    maxLength = length;
                    maxPos = it->second;
                } else {
                    break;
                }
            }

            if (maxLength > 0) {
                if (i + maxLength < text.size()) {
                    nextChar = text[i + maxLength];
                }
                compressed.push_back(Pair(i - maxPos, maxLength, nextChar));
                dictionary[text.substr(i, maxLength + 1)] = i;
                i += maxLength + 1;
            } else {
                compressed.push_back(Pair(-1, 0, text[i]));
                dictionary[text.substr(i, 1)] = i;
                ++i;
            }
        }

        return compressed;
    }

    std::string descomprimir(const std::vector<Pair>& compressed) {
        std::string decompressed;

        for (const auto& p : compressed) {
            if (p.position != -1) {
                int start = decompressed.size() - p.position;
                for (int i = 0; i < p.length; ++i) {
                    decompressed += decompressed[start + i];
                }
            }
            if (p.nextChar != '\0') {
                decompressed += p.nextChar;
            }
        }

        return decompressed;
    }
};