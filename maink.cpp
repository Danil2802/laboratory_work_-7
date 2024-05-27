#include <iostream>
#include <vector>

// Функция для проверки, использовался ли цвет в предыдущих домах
bool canUseColor(const std::vector<int>& usedColors, int color) {
    for (int usedColor : usedColors) {
        if (color == usedColor) {
            return false;
        }
    }
    return true;
}

// Функция для получения следующего цвета
int getNextColor(int currentColor, int K) {
    return (currentColor % K) + 1;
}

// Рекурсивная функция для покраски домов
bool paintHouses(std::vector<std::vector<int>>& houses, int N, int K, int A, int houseIndex, std::vector<int>& usedColors, int depth = 0, int maxDepth = 1000) {
    // Проверка на максимальную глубину рекурсии
    if (depth > maxDepth) {
        return false;
    }

    if (houseIndex == N) {
        // Все дома покрашены
        return true;
    }

    int currentColor = houseIndex > 0 ? houses[houseIndex - 1][A - 1] : 0;//если условие верно то первое выражение, если нет то второе
    for (int i = 0; i < A; i++) {
        currentColor = getNextColor(currentColor, K);
        if (canUseColor(usedColors, currentColor)) {
            houses[houseIndex].push_back(currentColor);
        }
        else {
            return false;
        }
    }

    // Обновляем список использованных цветов
    if (houseIndex >= 2) {
        usedColors.erase(usedColors.begin());
    }
    usedColors.push_back(houses[houseIndex][0]);

    if (paintHouses(houses, N, K, A, houseIndex + 1, usedColors, depth + 1, maxDepth)) {
        // Удалось покрасить все дома
        return true;
    }
    else {
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int N, K, A;
    std::cout << "Введите количество домов (N): ";
    std::cin >> N;
    std::cout << "Введите количество красок для покраски одного дома (A): ";
    std::cin >> A;
    std::cout << "Введите общее количество красок (K): ";
    std::cin >> K;

    // Проверяем, достаточно ли красок для покраски
    if (K < A) {
        std::cout << "Недостаточно красок для покраски одного дома." << std::endl;
        return 1;
    }

    // Проверка на отрицательные числа
    if (N < 1 || K < 0 || A < 1) {
        std::cout << "Не балуетесь!" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> houses(N, std::vector<int>());
    std::vector<int> usedColors;

    if (paintHouses(houses, N, K, A, 0, usedColors)) {
        std::cout << "Да, можно покрасить дома следующим образом:" << std::endl;
        for (const auto& house : houses) {
            for (int color : house) {
                std::cout << color << " ";
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "Нет, невозможно покрасить дома с такими условиями." << std::endl;
    }

    return 0;
}
