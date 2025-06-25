#include "Employee.h"

std::vector<Employee> readBinaryFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "������ �������� ����� " << filename << ".\n";
        return {};
    }

    std::vector<Employee> employees;
    Employee emp;
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        employees.push_back(emp);
    }

    inFile.close();
    return employees;
}

void printBinaryFile(const std::vector<Employee>& employees) {
    std::cout << "���������� ��������� �����:\nID\t���\t����\n";
    for (const auto& emp : employees) {
        std::cout << emp.num << "\t" << emp.name << "\t" << emp.hours << "\n";
    }
}

void printTextFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "������ �������� ����� " << filename << ".\n";
        return;
    }

    std::string line;
    std::cout << "���������� ������:\n";
    while (std::getline(inFile, line)) {
        std::cout << line << "\n";
    }
}
