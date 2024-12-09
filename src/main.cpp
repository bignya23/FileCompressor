#include <iostream>
#include <fstream>
#include <sstream>
#include "headers/huffman.hpp"


int main(int argc, char **argv) {

    // Avoiding file not given
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        exit(EXIT_FAILURE);
    }

    int option;
    std::cout << "What do you want to do : 1 -> Compress .... 2-> Decompress" <<std::endl;
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

        std::string strCompressed = hf.compress(text);

        // Writing to file
        std::ofstream myfile("compress.txt");
        myfile << strCompressed;
        myfile.close();
    }
    if (option == 2) {

        std::string text;
        {
            std::stringstream contents;
            std::fstream file(argv[1] , std::ios::binary);
            contents << file.rdbuf();
            text = contents.str();
        }
        std::string strdecompressed = hf.decompress(text);

        std::cout << strdecompressed;
        // // std::ofstream ofile("decompress124.txt");
        // ofile << strdecompressed;
        // ofile.close();
    }


    return 0;
}