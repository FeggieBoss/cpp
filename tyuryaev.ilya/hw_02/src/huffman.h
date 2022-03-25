#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <fstream>
#include <vector>
#include <set>
#include <cstddef>
#include <map>

namespace huffman
{
    const std::size_t BITS_PER_BYTE = 8;
    const std::size_t HUFFMAN_DICTIONARY_SIZE = 256;
    typedef uint16_t amount_file_type; // contains the number of each character

    // return the number of each character(content of 1 byte) in the file
    std::vector<std::size_t> get_dictionary(std::ifstream &input);

    class HuffmanArchiver
    {
    private:
        struct file_info
        {
            std::size_t dictionary_size = 0;      // in bytes
            std::size_t compressed_file_size = 0; // in bits // the number of bits that the source file takes after encoding
        };

    public:
        struct work_info // in bytes
        {
            std::size_t old_file_size = 0;
            std::size_t new_file_size = 0;
            std::size_t other_info_size = 0; // the size of the extra memory to restore HuffmanTree
        };

    public:
        static work_info encode_file_with_huffman(std::ifstream &input, std::ofstream &output);
        static work_info decode_file_with_huffman(std::ifstream &input, std::ofstream &output);
    };

    class HuffmanTree
    {
    private:
        class HuffmanTreeNode
        {
        public: // invariant: both children either exist or are absent
            HuffmanTreeNode *left_child = nullptr;
            HuffmanTreeNode *right_child = nullptr;
            std::size_t value;

        public:
            HuffmanTreeNode(std::size_t _value) : value(_value){};
            ~HuffmanTreeNode();
        };

    private:
        HuffmanTreeNode *root;

    public:
        HuffmanTree(std::vector<std::size_t> &dictionary);
        ~HuffmanTree();
        std::vector<std::string> get_hashes() const;

    private:
        void make_hashes(HuffmanTreeNode *node, std::string &current_hash, std::vector<std::string> &hashes) const;
    };
}

#endif // HUFFMAN_H_