#include <string>
#include <map>
#include <cstdio>
#include <cassert>
#include <fstream>
#include "matrix.h"

const std::size_t count_of_regs = 10;

std::size_t get_reg_id(char c)
{
    return (c - '0');
}

void load(std::string &fname, std::size_t reg_id, matrix::Matrix *const regs)
{
    std::ifstream in;
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    matrix::Matrix new_matrix;
    try
    {
        in.open(fname);
    }
    catch (const std::ifstream::failure &e)
    {
        throw matrix::MatrixException("LOAD: unable to open file.");
    }

    try
    {
        std::size_t rows, cols;
        in >> rows;
        in >> cols;

        new_matrix = matrix::Matrix(rows, cols);
        for (std::size_t i = 0; i < rows; ++i)
        {
            for (std::size_t j = 0; j < cols; ++j)
            {
                int val;
                in >> val;
                new_matrix.set(i, j, val);
            }
        }
    }
    catch (const std::ifstream::failure &e)
    {
        in.close();
        throw matrix::MatrixException("LOAD: invalid file format.");
    }
    regs[reg_id] = new_matrix;
    in.close();
}

int main()
{
    //std::cin
    //std::cout<<std::endl
    //matrix::Matrix
    //std::size_t

    std::string cmd;
    matrix::Matrix regs[count_of_regs];
    while (std::cin)
    {
        try
        {
            std::cin >> cmd;
            if (cmd == "exit")
            {
                break;
            }
            else if (cmd == "load")
            {
                std::string reg, fname;
                std::cin >> reg >> fname;
                load(fname, get_reg_id(reg[1]), regs);
            }
            else if (cmd == "print")
            {
                std::string reg;
                std::cin >> reg;
                regs[get_reg_id(reg[1])].print();
            }
            else if (cmd == "add")
            {
                std::string reg1, reg2;
                std::cin >> reg1 >> reg2;
                regs[get_reg_id(reg1[1])] += regs[get_reg_id(reg2[1])];
            }
            else if (cmd == "mul")
            {
                std::string reg1, reg2;
                std::cin >> reg1 >> reg2;
                regs[get_reg_id(reg1[1])] *= regs[get_reg_id(reg2[1])];
            }
            else if (cmd == "elem")
            {
                std::string reg;
                std::cin >> reg;
                std::size_t row, col;
                std::cin >> row >> col;

                int val;
                val = regs[get_reg_id(reg[1])].get(row, col);
                std::cout << val << std::endl;
            }
        }
        catch (const std::bad_alloc &e)
        {
            std::cout << "Unable to allocate memory." << std::endl;
        }
        catch (const matrix::MatrixException &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
