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

    std::unordered_map<char, int> countFrequency(std::string text);

    void printCodes(Node* root, std::string str, std::unordered_map<char, std::string>& huffmap);
    void buildHuffmanTree(const std::unordered_map<char, int> &freq);

    void inorder_traversal(Node *root);

    std::string compress(std::unordered_map<char, int> freq, std::string text);

    std::unordered_map<char, int> readFrequencyTableFromFile(std::string filename, std::string& compressedData);

    std::string decompress(std::unordered_map<char, int> freq, std::string coded);



private:
    std::priority_queue<Node*, std::vector<Node*>, compare> pq;
    std::unordered_map<char, std::string> huffmap;
};