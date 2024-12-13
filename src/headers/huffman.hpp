#pragma once

#include <iostream>
#include <map>
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

    std::map<char, int> countFrequency(std::string text);

    void printCodes(Node* root, std::string str, std::map<char, std::string>& huffmap);
    void buildHuffmanTree(const std::map<char, int> &freq);

    void inorder_traversal(Node *root);


    std::string compress(std::map<char, int> freq, std::string text);

    std::map<char, int> readFrequencyTableFromFile(std::string filename, std::string& compressedData);

    std::string decompress(std::map<char, int> freq, std::string coded);



private:
    std::priority_queue<Node*, std::vector<Node*>, compare> pq;
    std::map<char, std::string> huffmap;
};