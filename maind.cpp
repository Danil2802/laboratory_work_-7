#include <iostream>
#include <string>
#include <cctype>


bool proverka(const std::string& s) {
    int index = 0;
    while (index < s.length()) {
        char c = s[index];
        if (!isdigit(c) && !isalpha(c) && c != '[' && c != ']') {
            return false;
        }
        index++;
    }
    return true;
}

bool proverka2(const std::string& s) {
    int index = 0;
    int count = 0;
    while (index < s.length()) {
        char c = s[index];
        if (isdigit(c)) {
            count = count * 10 + (c - '0');
            if (count < 1) {
                return false;
            }
        }
        else {
            count = 0;
        }
        if (count > 300) {
            return false;
        }
        index++;
    }
    return true;
}




std::string decodeString(const std::string& s, int& index, int& stackDepth) {
    std::string result;
    int count = 0;

    while (index < s.length()) {
        char c = s[index];

        if (isdigit(c)) {
            count = count * 10 + (c - '0');
        }
        else if (isalpha(c)) {
            result.push_back(c);
            count = 0;
        }

        else if (c == '[') {
            index++; // ���������� ������ �� ��������� ������
            stackDepth++; // ����������� ������� ����� ����� ������� ��������
            if (stackDepth > 1000) { // ���������, �� ������������ �� ����
                throw std::runtime_error("Stack overflow detected");
            }
            std::string nested = decodeString(s, index, stackDepth);
            for (int i = 0; i < count; i++) {
                result += nested;
            }
            count = 0; // ���������� ������� ����� ��������� ��������� ������
            continue; // ���������� ��������� �������, ��� ��� �� ��� ������ � ����������� ������
        }
        else if (c == ']') {
            index++; // ���������� ������ �� ��������� ������ ����� ����������� ������
            stackDepth--; // ��������� ������� ����� ����� �������� �� ��������
            return result; // ���������� ��������� ��� ������������ ������ ��������
        }

        index++; // ���������� ������ �� ��������� ������
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string encodedString;
    std::cout << "������� �������������� ������: ";
    std::cin >> encodedString;

    if (encodedString.length() > 30)
    {
        std::cout << "������� ������� ������ " << std::endl;
        return 1;
    }

    if (!proverka(encodedString))
    {
        std::cout << "������������ �������! " << std::endl;
        return 1;
    }

    if (!proverka2(encodedString))
    {
        std::cout << "����� �� ������ � ������ ��������! " << std::endl;
        return 1;
    }

    int index = 0;
    int stackDepth = 0;
    std::string decodedString = decodeString(encodedString, index, stackDepth);
    std::cout << "�������������� ������: " << decodedString << std::endl;
    return 0;
}

