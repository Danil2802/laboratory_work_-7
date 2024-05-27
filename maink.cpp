#include <iostream>
#include <vector>

// ������� ��� ��������, ������������� �� ���� � ���������� �����
bool canUseColor(const std::vector<int>& usedColors, int color) {
    for (int usedColor : usedColors) {
        if (color == usedColor) {
            return false;
        }
    }
    return true;
}

// ������� ��� ��������� ���������� �����
int getNextColor(int currentColor, int K) {
    return (currentColor % K) + 1;
}

// ����������� ������� ��� �������� �����
bool paintHouses(std::vector<std::vector<int>>& houses, int N, int K, int A, int houseIndex, std::vector<int>& usedColors, int depth = 0, int maxDepth = 1000) {
    // �������� �� ������������ ������� ��������
    if (depth > maxDepth) {
        return false;
    }

    if (houseIndex == N) {
        // ��� ���� ���������
        return true;
    }

    int currentColor = houseIndex > 0 ? houses[houseIndex - 1][A - 1] : 0;//���� ������� ����� �� ������ ���������, ���� ��� �� ������
    for (int i = 0; i < A; i++) {
        currentColor = getNextColor(currentColor, K);
        if (canUseColor(usedColors, currentColor)) {
            houses[houseIndex].push_back(currentColor);
        }
        else {
            return false;
        }
    }

    // ��������� ������ �������������� ������
    if (houseIndex >= 2) {
        usedColors.erase(usedColors.begin());
    }
    usedColors.push_back(houses[houseIndex][0]);

    if (paintHouses(houses, N, K, A, houseIndex + 1, usedColors, depth + 1, maxDepth)) {
        // ������� ��������� ��� ����
        return true;
    }
    else {
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int N, K, A;
    std::cout << "������� ���������� ����� (N): ";
    std::cin >> N;
    std::cout << "������� ���������� ������ ��� �������� ������ ���� (A): ";
    std::cin >> A;
    std::cout << "������� ����� ���������� ������ (K): ";
    std::cin >> K;

    // ���������, ���������� �� ������ ��� ��������
    if (K < A) {
        std::cout << "������������ ������ ��� �������� ������ ����." << std::endl;
        return 1;
    }

    // �������� �� ������������� �����
    if (N < 1 || K < 0 || A < 1) {
        std::cout << "�� ���������!" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> houses(N, std::vector<int>());
    std::vector<int> usedColors;

    if (paintHouses(houses, N, K, A, 0, usedColors)) {
        std::cout << "��, ����� ��������� ���� ��������� �������:" << std::endl;
        for (const auto& house : houses) {
            for (int color : house) {
                std::cout << color << " ";
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "���, ���������� ��������� ���� � ������ ���������." << std::endl;
    }

    return 0;
}
