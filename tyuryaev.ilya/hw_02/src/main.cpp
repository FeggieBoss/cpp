#include "huffman.h"
#include <iostream>

void set_operating_mode(std::string &operating_mode, std::string value)
{
    if (!operating_mode.empty())
    {
        std::cout << "Error in command line options";
        exit(0);
    }
    operating_mode = value;
}

int main(int argc, char *argv[])
{
    std::string operating_mode, input_file, output_file;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-c" || arg == "-u")
            set_operating_mode(operating_mode, arg);
        else if (arg == "-f" || arg == "--file")
        {
            if (i + 1 == argc)
            {
                std::cout << "file name not found";
                exit(0);
            }
            input_file = argv[++i];
        }
        else if (arg == "-o" || arg == "--output")
        {
            if (i + 1 == argc)
            {
                std::cout << "file name not found";
                exit(0);
            }
            output_file = argv[++i];
        }
        else
        {
            std::cout << "bad command";
            exit(0);
        }
    }

    huffman::HuffmanArchiver::work_info _work_info;

    std::ifstream input;
    std::ofstream output;
    input.open(input_file, std::ios_base::binary);
    output.open(output_file, std::ios_base::binary);
    if (operating_mode == "-c")
        _work_info = huffman::HuffmanArchiver::encode_file_with_huffman(input, output);
    else
        _work_info = huffman::HuffmanArchiver::decode_file_with_huffman(input, output);
    input.close();
    output.close();

    std::cout << _work_info.old_file_size << std::endl
              << _work_info.new_file_size << std::endl
              << _work_info.other_info_size << std::endl;
    return 0;
}