#include <gtest/gtest.h>
#include "Employee.h"
#include <fstream>

// ���� ��� ������� readBinaryFile
TEST(EmployeeTest, ReadBinaryFile) {
    // ������� ��������� �������� ����
    std::string filename = "test_employees.bin";
    std::ofstream outFile(filename, std::ios::binary);
    Employee emp1 = { 1, "Alice", 40.0 };
    Employee emp2 = { 2, "Bob", 30.5 };
    outFile.write(reinterpret_cast<char*>(&emp1), sizeof(Employee));
    outFile.write(reinterpret_cast<char*>(&emp2), sizeof(Employee));
    outFile.close();

    // ������ ����
    auto employees = readBinaryFile(filename);
    ASSERT_EQ(employees.size(), 2);
    EXPECT_EQ(employees[0].num, 1);
    EXPECT_STREQ(employees[0].name, "Alice");
    EXPECT_DOUBLE_EQ(employees[0].hours, 40.0);
    EXPECT_EQ(employees[1].num, 2);
    EXPECT_STREQ(employees[1].name, "Bob");
    EXPECT_DOUBLE_EQ(employees[1].hours, 30.5);

    // ������� ��������� ����
    std::remove(filename.c_str());
}

// ���� ��� ������� printBinaryFile
TEST(EmployeeTest, PrintBinaryFile) {
    std::vector<Employee> employees = {
        {1, "Alice", 40.0},
        {2, "Bob", 30.5}
    };

    // �������������� ����� � ������
    testing::internal::CaptureStdout();
    printBinaryFile(employees);
    std::string output = testing::internal::GetCapturedStdout();

    // ��������� �����
    EXPECT_NE(output.find("1\tAlice\t40"), std::string::npos);
    EXPECT_NE(output.find("2\tBob\t30.5"), std::string::npos);
}

// ���� ��� ������� printTextFile
TEST(EmployeeTest, PrintTextFile) {
    // ������� ��������� ��������� ����
    std::string filename = "test_report.txt";
    std::ofstream outFile(filename);
    outFile << "����� �� ����� \"test_employees.bin\"\n";
    outFile << "ID\t���\t����\t��������\n";
    outFile << "1\tAlice\t40\t1600.00\n";
    outFile << "2\tBob\t30.5\t1220.00\n";
    outFile.close();

    // �������������� ����� � ������
    testing::internal::CaptureStdout();
    printTextFile(filename);
    std::string output = testing::internal::GetCapturedStdout();

    // ��������� �����
    EXPECT_NE(output.find("1\tAlice\t40\t1600.00"), std::string::npos);
    EXPECT_NE(output.find("2\tBob\t30.5\t1220.00"), std::string::npos);

    // ������� ��������� ����
    std::remove(filename.c_str());
}