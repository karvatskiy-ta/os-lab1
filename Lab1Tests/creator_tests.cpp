#include <windows.h>
#include <gtest/gtest.h>
#include "Employee.h"
#include <fstream>
#include <sstream>

TEST(CreatorTest, CreatesBinaryFile) {
    std::string filename = "test_creator.bin";  // ��� ��������� �����
    std::string inputFile = "test_input.txt";   // ��� �������� �����
    std::string command = "Creator.exe " + filename + " 2 " + inputFile;  // ������� � 4 �����������

    // ������� ������� ���� � �������
    std::ofstream inFile(inputFile);
    inFile << "1 Alice 40\n";  // ������ ������
    inFile << "2 Bob 30.5\n";  // ������ ������
    inFile.close();

    // ��������� Creator
    testing::internal::CaptureStdout();
    system(command.c_str());
    std::string output = testing::internal::GetCapturedStdout();

    // ���������, ��� ���� ������
    std::ifstream outFile(filename, std::ios::binary);
    ASSERT_TRUE(outFile.is_open()) << "���� �� ��� ������: " << filename;

    // ������ ����
    Employee emp1, emp2;
    outFile.read(reinterpret_cast<char*>(&emp1), sizeof(Employee));
    outFile.read(reinterpret_cast<char*>(&emp2), sizeof(Employee));
    outFile.close();

    // ��������� ����������
    EXPECT_EQ(emp1.num, 1);
    EXPECT_STREQ(emp1.name, "Alice");
    EXPECT_DOUBLE_EQ(emp1.hours, 40.0);
    EXPECT_EQ(emp2.num, 2);
    EXPECT_STREQ(emp2.name, "Bob");
    EXPECT_DOUBLE_EQ(emp2.hours, 30.5);

    // ������� ��������� �����
    std::remove(filename.c_str());
    std::remove(inputFile.c_str());
}