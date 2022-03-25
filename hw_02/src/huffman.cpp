#include "huffman.h"

using namespace huffman;

std::vector<std::size_t> huffman::get_dictionary(std::ifstream &input)
{
    std::vector<std::size_t> dictionary(HUFFMAN_DICTIONARY_SIZE, 0);

    input.clear();
    input.seekg(0, std::ios::beg);
    while (true)
    {
        uint8_t byte;
        input.read((char *)&byte, sizeof(char));
        if (input.eof())
            break;

        ++dictionary[byte];
    }
    return dictionary;
}

// compressed file [file_info|dictionary|compressed_file]
HuffmanArchiver::work_info HuffmanArchiver::encode_file_with_huffman(std::ifstream &input, std::ofstream &output)
{
    work_info _work_info;
    file_info _file_info;

    std::vector<std::size_t> dictionary = get_dictionary(input);
    _file_info.dictionary_size = _work_info.other_info_size = HUFFMAN_DICTIONARY_SIZE * sizeof(amount_file_type);

    std::vector<std::string> hashes = HuffmanTree(dictionary).get_hashes();
    for (std::size_t i = 0; i < HUFFMAN_DICTIONARY_SIZE; ++i)
        _file_info.compressed_file_size += dictionary[i] * hashes[i].size();

    output.write((char *)&_file_info, sizeof(_file_info));
    _work_info.other_info_size += sizeof(_file_info);

    // the size of the source file is not more than 5MB, so the amount will fit into int16_t
    for (amount_file_type el : dictionary)
        output.write((char *)&el, sizeof(amount_file_type));

    input.clear();
    input.seekg(0, std::ios::beg);
    uint8_t cur_byte = 0;
    std::size_t cur_bit_id = 0;
    while (true)
    {
        uint8_t data;
        input.read((char *)&data, sizeof(char));
        if (input.eof())
            break;
        ++_work_info.old_file_size;

        for (char c : hashes[data])
        {
            std::size_t id_of_bite = cur_bit_id % BITS_PER_BYTE;
            if (id_of_bite == 0)
            {
                if (cur_bit_id)
                {
                    output.write((char *)&cur_byte, sizeof(char));
                    ++_work_info.new_file_size;
                }
                cur_byte = 0;
            }
            cur_byte ^= (c == '1') * (1 << id_of_bite);
            ++cur_bit_id;
        }
    }

    // residue
    if (cur_bit_id)
    {
        output.write((char *)&cur_byte, sizeof(char));
        ++_work_info.new_file_size;
    }

    return _work_info;
}

HuffmanArchiver::work_info HuffmanArchiver::decode_file_with_huffman(std::ifstream &input, std::ofstream &output)
{
    work_info _work_info;
    file_info _file_info;

    input.clear();
    input.seekg(0, std::ios::beg);
    input.read((char *)&_file_info, sizeof(file_info));

    _work_info.other_info_size = sizeof(_file_info) + _file_info.dictionary_size;
    _work_info.old_file_size = (_file_info.compressed_file_size + BITS_PER_BYTE - 1) / BITS_PER_BYTE;

    std::vector<std::size_t> dictionary(HUFFMAN_DICTIONARY_SIZE);
    for (std::size_t i = 0; i < HUFFMAN_DICTIONARY_SIZE; ++i)
        input.read((char *)&dictionary[i], sizeof(amount_file_type));

    HuffmanTree huff_tree = HuffmanTree(dictionary);
    std::vector<std::string> hashes = huff_tree.get_hashes();

    std::map<std::string, std::size_t> character_by_hash;
    for (std::size_t character = 0; character < HUFFMAN_DICTIONARY_SIZE; ++character)
        character_by_hash[hashes[character]] = character;

    std::string current_hash = "";
    std::size_t readed_bites = 0;
    for (std::size_t i = 0; i < (_file_info.compressed_file_size + BITS_PER_BYTE - 1) / BITS_PER_BYTE; ++i)
    {
        uint8_t byte;
        input.read((char *)&byte, sizeof(char));

        std::size_t ctr = BITS_PER_BYTE;
        // process byte bits either until they run out or until we reach the end
        while (readed_bites < _file_info.compressed_file_size && ctr)
        {
            std::size_t id_of_bite = readed_bites % BITS_PER_BYTE;
            // 0 - go to the left subtree
            // 1 - go to the right subtree
            current_hash += (((byte & (1 << id_of_bite)) > 0) + '0');

            // check for being in the leaf
            if (character_by_hash.find(current_hash) != character_by_hash.end())
            {
                output.write((char *)&character_by_hash[current_hash], sizeof(char));
                ++_work_info.new_file_size;
                current_hash = ""; // back to the root
            }

            ++readed_bites;
            --ctr;
        }
    }
    return _work_info;
}

HuffmanTree::HuffmanTreeNode::~HuffmanTreeNode()
{
    if (left_child)
    {
        delete left_child;
        delete right_child;
    }
}

HuffmanTree::HuffmanTree(std::vector<std::size_t> &dictionary)
{
    std::set<std::pair<std::size_t, HuffmanTreeNode *>> characters; // {amount,character}
    for (std::size_t c = 0; c < HUFFMAN_DICTIONARY_SIZE; ++c)
        characters.emplace(dictionary[c], new HuffmanTreeNode(c));

    while (characters.size() != 1) // always at least 1 at the beginning
    {
        auto first = *(characters.begin());
        characters.erase(characters.begin());

        auto second = *(characters.begin());
        characters.erase(characters.begin());

        auto new_node = new HuffmanTreeNode(first.first + second.first);
        new_node->left_child = first.second;
        new_node->right_child = second.second;
        characters.emplace(new_node->value, new_node);
    }
    root = characters.begin()->second;
}
HuffmanTree::~HuffmanTree()
{
    delete root;
}

void HuffmanTree::make_hashes(HuffmanTreeNode *node, std::string &current_hash, std::vector<std::string> &hashes) const
{
    if (!node->left_child)
    {
        // The only case when the root of a tree is its leaf - the tree consists of 1 vertex
        // in this case we will get an empty code which we will encode with zero
        hashes[node->value] = (current_hash.empty() ? "0" : current_hash);
        return;
    }

    current_hash += '0';
    make_hashes(node->left_child, current_hash, hashes);
    current_hash.pop_back();

    current_hash += '1';
    make_hashes(node->right_child, current_hash, hashes);
    current_hash.pop_back();
}

std::vector<std::string> HuffmanTree::get_hashes() const
{
    std::vector<std::string> hashes(HUFFMAN_DICTIONARY_SIZE);
    std::string current_hash = "";
    make_hashes(root, current_hash, hashes);
    return hashes;
}