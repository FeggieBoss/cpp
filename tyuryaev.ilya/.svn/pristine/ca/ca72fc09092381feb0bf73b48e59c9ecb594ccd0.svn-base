#include "employees.h"

int main()
{
    EmployeesArray arr;
    std::string s;
    while (std::cin >> s)
    {
        if (s == "exit")
        {
            break;
        }
        else if (s == "load")
        {
            std::string file_name;
            std::cin >> file_name;
            std::ifstream in(file_name);
            in >> arr;
            in.close();
        }
        else if (s == "save")
        {
            std::string file_name;
            std::cin >> file_name;
            std::ofstream out(file_name);
            out << arr;
            out.close();
        }
        else if (s == "add")
        {
            int32_t t;
            std::cin >> t;
            Employee *emp = arr.get_emp(t);
            std::cin >> *emp;
            arr.add(emp);
        }
        else if (s == "list")
        {
            arr.list();
        }
    }
    return 0;
}