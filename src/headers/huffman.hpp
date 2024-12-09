#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
class Huffman {



public:
    Huffman() {}

    struct Node {
        char ch;
        int freq;
        Node* left;
        Node* right;

        Node(char ch,  int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {
        }

        Node(char ch,  int freq, Node* left, Node* right) : ch(ch), freq(freq), left(left), right(right) {}


    };
    // Comparison operator to arrange the heap
    struct compare {
        bool operator() (Node* left, Node* right) {
            return left->freq > right->freq;
        }
    };

    void printCodes(Node* root, std::string str, std::unordered_map<char, std::string>& huffmap);
    void buildHuffmanTree(std::string text);
    std::string compress(std::string text);
    std::string decompress(std::string coded);

private:
    std::priority_queue<Node*, std::vector<Node*>, compare> pq;
    std::unordered_map<char, std::string> huffmap;
};