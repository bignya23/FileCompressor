#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include "./headers/huffman.hpp"

#include <bitset>
#include <cstdint>
#include <fstream>
#include <sstream>


// After building tree for getting the binary code for each character
void Huffman::printCodes(Node* root, std::string str, std::unordered_map<char, std::string>& huffmap) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        huffmap[root->ch] = str;
    }

    printCodes(root->left, str + "0", huffmap);
    printCodes(root->right, str + "1", huffmap);
}
// To count the freq of the text
std::unordered_map<char, int> Huffman::countFrequency(std::string text) {
    std::unordered_map<char, int> freq;

    // Storing the frequency of each character in the text in a map
    for (char c : text) {
        freq[c]++;
    }
    return freq;

}

// For building the tree based on frequency
void Huffman::buildHuffmanTree(const std::unordered_map<char, int> &freq) {
    // Pushing each character in the priority queue
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Creating the heap
    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;

        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    printCodes(root, "", huffmap);

}

void Huffman::inorder_traversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    inorder_traversal(root->left);
    std::cout << root->ch << " ";
    inorder_traversal(root->right);
}

std::string Huffman::compress(std::unordered_map<char, int> freq, std::string text) {

    buildHuffmanTree(freq);

    // inorder_traversal(pq.top());
    std::vector<uint8_t> compressed;
    uint8_t buffer = 0;
    int bitsize = 0;

    for (char c : text) {
        std::string code = huffmap[c];

        for (char bit : code) {
            buffer = buffer << 1 | bit - '0';
            bitsize++;

            if (bitsize == 8) {
                compressed.push_back(buffer);
                bitsize = 0;
                buffer = 0;
            }
        }
    }

    if (bitsize > 0) {
        buffer = buffer << (8 - bitsize);
        compressed.push_back(buffer);
    }

    return std::string(compressed.begin(), compressed.end());

}


std::unordered_map<char, int> Huffman::readFrequencyTableFromFile(std::string filename , std::string& compressedData) {
    std::unordered_map<char, int> freqMap;
    std::ifstream inFile(filename);
    std::string line;
    while (std::getline(inFile, line)) {
        if (line == "<freq>") {
            // Skip to next lines containing frequency data
            while (std::getline(inFile, line) && line != "<data>") {
                // Parse each line for character and frequency pair
                char ch = line[0];
                int i = 2;
                std::string integer{};
                while (i < line.size()) {
                    integer += line[i];
                    i++;
                }
                freqMap[ch]= std::stoi(integer);
            }
        }
        if (line == "<data>") {
            // Read the compressed data
            std::getline(inFile, compressedData);
        }
    }
    inFile.close();

    return freqMap;


}

// Decoding to original string
std::string Huffman::decompress(std::unordered_map<char ,int> freq, std::string compressedData) {
    std::string decoded{};

    // Rebuilding the tree
    buildHuffmanTree(freq);
    // inorder_traversal(pq.top());
    Node* curr = pq.top();

    // Reading data bit by bit from the byte and find the char from the tree
    for (uint8_t byte : compressedData) {
        for (int i = 7; i >= 0; i--) {
            bool bit = (byte >> i) & 1;
            curr = bit ? curr->right : curr->left;

            if (curr->left == nullptr && curr->right == nullptr) {
                decoded += curr->ch;
                curr = pq.top();
            }
        }
    }
    return decoded;
}






