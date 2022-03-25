#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

const int32_t max_len = 500;

class Employee
{
public:
    Employee(int32_t _vocation_id, std::string _vocation_name);
    virtual ~Employee(){};
    std::string get_vocation_name() const;
    int32_t get_vocation_id() const;
    friend std::ostream &operator<<(std::ostream &out, const Employee &emp);
    friend std::istream &operator>>(std::istream &in, Employee &emp);
    friend std::ofstream &operator<<(std::ofstream &out, const Employee &emp);
    friend std::ifstream &operator>>(std::ifstream &in, Employee &emp);
    virtual void read_text_data(std::istream &in);
    virtual void write_text_data(std::ostream &out) const;
    virtual void read_bin_data(std::ifstream &in);
    virtual void write_bin_data(std::ofstream &out) const;
    virtual int32_t salary() const = 0;

protected:
    const int32_t vocation_id;
    const std::string vocation_name;
    int32_t _base_salary;
    std::string _name;
};

class Developer : public Employee
{
public:
    Developer();
    void read_text_data(std::istream &in) override;
    void write_text_data(std::ostream &out) const override;
    void read_bin_data(std::ifstream &in) override;
    void write_bin_data(std::ofstream &out) const override;
    int32_t salary() const override;

private:
    bool _has_bonus;
};

class SalesManager : public Employee
{
public:
    SalesManager();
    void read_text_data(std::istream &in) override;
    void write_text_data(std::ostream &out) const override;
    void read_bin_data(std::ifstream &in) override;
    void write_bin_data(std::ofstream &out) const override;
    int32_t salary() const override;

private:
    int32_t _sold_nm, _price;
};

class EmployeesArray
{
public:
    ~EmployeesArray();
    friend std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &arr);
    friend std::ifstream &operator>>(std::ifstream &in, EmployeesArray &arr);
    void add(Employee *const e);
    int32_t total_salary() const;
    void list() const;
    Employee *get_emp(int32_t t) const;

private:
    std::vector<Employee *> _employees;
};

#endif