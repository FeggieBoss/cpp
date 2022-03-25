#include "employees.h"

std::ostream &operator<<(std::ostream &out, const Employee &emp)
{
    emp.write_text_data(out);
    return out;
}
std::istream &operator>>(std::istream &in, Employee &emp)
{
    emp.read_text_data(in);
    return in;
}
std::ofstream &operator<<(std::ofstream &out, const Employee &emp)
{
    emp.write_bin_data(out);
    return out;
}
std::ifstream &operator>>(std::ifstream &in, Employee &emp)
{
    emp.read_bin_data(in);
    return in;
}
Employee::Employee(int32_t _vocation_id, std::string _vocation_name) : vocation_id(_vocation_id), vocation_name(_vocation_name){};
std::string Employee::get_vocation_name() const
{
    return vocation_name;
}
int32_t Employee::get_vocation_id() const
{
    return vocation_id;
}
void Employee::read_text_data(std::istream &in)
{
    in >> _name >> _base_salary;
}
void Employee::write_text_data(std::ostream &out) const
{
    out << "Name: " << _name << std::endl;
    out << "Base Salary: " << _base_salary << std::endl;
}
void Employee::read_bin_data(std::ifstream &in)
{
    char buffer[max_len];
    in.getline(buffer, sizeof(char) * (max_len), '\0');
    _name = std::string(buffer);
    in.read((char *)&_base_salary, sizeof(_base_salary));
}
void Employee::write_bin_data(std::ofstream &out) const
{
    int32_t t = get_vocation_id();
    out.write((char *)&t, sizeof(t));
    out.write(_name.c_str(), sizeof(char) * (_name.size() + 1));
    out.write((char *)&_base_salary, sizeof(_base_salary));
}

Developer::Developer() : Employee(1, "Developer"){};

int32_t Developer::salary() const
{
    int32_t salary = _base_salary;
    if (_has_bonus)
    {
        salary += 1000;
    }
    return salary;
}
void Developer::read_text_data(std::istream &in)
{
    Employee::read_text_data(in);
    in >> _has_bonus;
}
void Developer::write_text_data(std::ostream &out) const
{
    Employee::write_text_data(out);
    out << "Has bonus: " << (_has_bonus ? '+' : '-') << std::endl;
}
void Developer::read_bin_data(std::ifstream &in)
{
    Employee::read_bin_data(in);
    in.read((char *)&_has_bonus, sizeof(_has_bonus));
}
void Developer::write_bin_data(std::ofstream &out) const
{
    Employee::write_bin_data(out);
    out.write((char *)&_has_bonus, sizeof(_has_bonus));
}

SalesManager::SalesManager() : Employee(2, "Sales Manager"){};
int32_t SalesManager::salary() const
{
    return _base_salary + _sold_nm * _price * 0.01;
}
void SalesManager::read_text_data(std::istream &in)
{
    Employee::read_text_data(in);
    in >> _sold_nm >> _price;
}
void SalesManager::write_text_data(std::ostream &out) const
{
    Employee::write_text_data(out);
    out << "Sold items: " << _sold_nm << std::endl;
    out << "Item price: " << _price << std::endl;
}
void SalesManager::read_bin_data(std::ifstream &in)
{
    Employee::read_bin_data(in);
    in.read((char *)&_sold_nm, sizeof(_sold_nm));
    in.read((char *)&_price, sizeof(_price));
}
void SalesManager::write_bin_data(std::ofstream &out) const
{
    Employee::write_bin_data(out);
    out.write((char *)&_sold_nm, sizeof(_sold_nm));
    out.write((char *)&_price, sizeof(_price));
}

EmployeesArray::~EmployeesArray()
{
    for (size_t i = 0; i < _employees.size(); ++i)
        delete (_employees[i]);
}
void EmployeesArray::add(Employee *const e)
{
    _employees.push_back(e);
}
void EmployeesArray::list() const
{
    for (size_t i = 0; i < _employees.size(); ++i)
    {
        std::cout << i + 1 << ". " << _employees[i]->get_vocation_name() << std::endl;
        std::cout << *_employees[i];
    }
    std::cout << "== Total salary: " << total_salary() << std::endl
              << std::endl;
}
int32_t EmployeesArray::total_salary() const
{
    int32_t _total_salary = 0;
    for (size_t i = 0; i < _employees.size(); ++i)
        _total_salary += _employees[i]->salary();
    return _total_salary;
}
Employee *EmployeesArray::get_emp(int32_t t) const
{
    if (t == 1)
        return new Developer();
    else if (t == 2)
        return new SalesManager();
    assert(false);
}

std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &arr)
{
    int32_t counter = arr._employees.size();
    out.write((char *)&counter, sizeof(counter));
    for (int32_t i = 0; i < counter; ++i)
        out << *arr._employees[i];
    return out;
}
std::ifstream &operator>>(std::ifstream &in, EmployeesArray &arr)
{
    int32_t counter;
    in.read((char *)&counter, sizeof(counter));
    for (int32_t i = 0; i < counter; ++i)
    {
        int32_t t;
        in.read((char *)&t, sizeof(t));
        Employee *emp = arr.get_emp(t);
        in >> *emp;
        arr.add(emp);
    }
    return in;
}