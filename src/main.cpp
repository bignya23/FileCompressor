#include <bitset>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include "headers/huffman.hpp"


int main(int argc, char **argv) {

    // Avoiding file not given
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        exit(EXIT_FAILURE);
    }

    int option;
    std::cout << "What do you want to do : 1 -> Compress --- 2-> Decompress" <<std::endl;
    std::cin >> option;
    // reading the file

    Huffman hf;

    if (option == 1) {
        // Final calling

        std::string text;
        {
            std::stringstream contents;
            std::fstream file(argv[1] , std::ios::in);
            contents << file.rdbuf();
            text = contents.str();
        }
        std::map<char, int> freq = hf.countFrequency(text);

        std::string strCompressed = hf.compress(freq, text);

        // Writing to file
        std::ofstream outfile("com.txt");
        if (!outfile.is_open()) {
            std::cerr << "Error opening file" << std::endl;
        }
        // Writing frequency to file for building tree while decompressing
        outfile << "<freq>" << "\n" ;
        for (const auto& pair : freq) {
            outfile << pair.first << " " << pair.second << "\n";
        }
        // Writing huffman data
        outfile << "<data>" << "\n" ;
        outfile << strCompressed;
        outfile.close();
    }
    if (option == 2) {
        std::string text{};

        // //opening the file
        // std::ifstream file(argv[1] , std::ios::binary);
        // if (!file.is_open()) {
        //     std::cerr << "Error opening file" << std::endl;
        //     exit(EXIT_FAILURE);
        // }
        // file.seekg(0, std::ios::end);
        // int size = file.tellg();
        // file.seekg(0, std::ios::beg);
        //
        // text.resize(size);
        // file.read(&text[0], size);
        //
        // file.close();
        //
        // // std::cout << "Binary data (as uint8_t):\n";
        // // for (unsigned char byte : text) {
        // //     // Convert each byte to binary using std::bitset
        // //     std::cout << std::bitset<8>(byte);
        // // }

        std::map<char, int> freq = hf.readFrequencyTableFromFile(argv[1], text);
        // std::unordered_map<char, int> reversed;

        // Iterate and reverse
        // for (const auto& pair : freq) {
        //     reversed[pair.first] = pair.second;
        // }
        for (const auto& pair : freq) {
            std::cout << pair.first << " " << pair.second << "\n";
        }
        // std::cout << std::endl;
        // std::cout << text << std::endl;
        //
        // std::cout << "Binary data (as uint8_t):\n";
        // for (unsigned char byte : text) {
        //     // Convert each byte to binary using std::bitset
        //     std::cout << std::bitset<8>(byte);
        // }
        std::cout << text;
        std::string strdecompressed = hf.decompress(freq,text);

        std::cout << strdecompressed;
        std::ofstream ofile("decom.txt");
        ofile << strdecompressed;
        ofile.close();
    }


    return 0;
}