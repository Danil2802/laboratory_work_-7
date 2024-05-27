# Лабараторная работа №7
## «Рекурсивные алгоритмы»
## по дисциплине: «Программирование»
### Цели и задачи работы: изучение рекурсивного программирования, методов разработки эффективных алгоритмов.
### Методика выполнения работы:
#### 1) Изучить технологию использования стека при рекурсивном программировании.
#### 2) Написать рекурсивную программу решения поставленной задачи.
#### 3) Протестировать программу.

### Задание: Имеется N домов и K красок. Проверить, можно ли покрасить дома имеющимся набором красок, чтобы цвет повторялся не раньше, чем через 2 дома.
### Решение задачи в maink.cpp
```C++
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
```
### Задание: Дана закодированная строка, верните её декодированную версию. 
### Решение задачи в maind.cpp
```C++
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
            index++; // Перемещаем индекс на следующий символ
            stackDepth++; // Увеличиваем счетчик стека перед вызовом рекурсии
            if (stackDepth > 1000) { // Проверяем, не переполнился ли стек
                throw std::runtime_error("Stack overflow detected");
            }
            std::string nested = decodeString(s, index, stackDepth);
            for (int i = 0; i < count; i++) {
                result += nested;
            }
            count = 0; // Сбрасываем счетчик после обработки вложенной строки
            continue; // Пропускаем инкремент индекса, так как он уже сделан в рекурсивном вызове
        }
        else if (c == ']') {
            index++; // Перемещаем индекс на следующий символ после закрывающей скобки
            stackDepth--; // Уменьшаем счетчик стека после возврата из рекурсии
            return result; // Возвращаем результат для вышестоящего уровня рекурсии
        }

        index++; // Перемещаем индекс на следующий символ
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string encodedString;
    std::cout << "Введите закодированную строку: ";
    std::cin >> encodedString;

    if (encodedString.length() > 30)
    {
        std::cout << "Слишком длинная строка " << std::endl;
        return 1;
    }

    if (!proverka(encodedString))
    {
        std::cout << "Недопустимые символы! " << std::endl;
        return 1;
    }

    if (!proverka2(encodedString))
    {
        std::cout << "Число не входит в нужный диапозон! " << std::endl;
        return 1;
    }

    int index = 0;
    int stackDepth = 0;
    std::string decodedString = decodeString(encodedString, index, stackDepth);
    std::cout << "Декодированная строка: " << decodedString << std::endl;
    return 0;
}
```
### Задание: Имеется N домов и K красок. Проверить, можно ли покрасить дома имеющимся набором красок, чтобы цвет повторялся не раньше, чем через 2 дома.
### Решение задачи в mainp.txt
```
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите количество домов (N): ");
        int N = scanner.nextInt();
        System.out.print("Введите количество красок для покраски одного дома (A): ");
        int A = scanner.nextInt();
        System.out.print("Введите общее количество красок (K): ");
        int K = scanner.nextInt();

        if (K < A) {
            System.out.println("Недостаточно красок для покраски одного дома.");
            return;
        }

        if (N < 1 || K < 0 || A < 1) {
            System.out.println("Не балуетесь!");
            return;
        }

        List<List<Integer>> houses = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            houses.add(new ArrayList<>());
        }
        List<Integer> usedColors = new ArrayList<>();

        if (paintHouses(houses, N, K, A, 0, usedColors, 0, 1000)) {
            System.out.println("Да, можно покрасить дома следующим образом:");
            for (List<Integer> house : houses) {
                for (int color : house) {
                    System.out.print(color + " ");
                }
                System.out.println();
            }
        } else {
            System.out.println("Нет, невозможно покрасить дома с такими условиями.");
        }
    }

    private static boolean canUseColor(List<Integer> usedColors, int color) {
        for (int usedColor : usedColors) {
            if (color == usedColor) {
                return false;
            }
        }
        return true;
    }

    private static int getNextColor(int currentColor, int K) {
        return (currentColor % K) + 1;
    }

    private static boolean paintHouses(List<List<Integer>> houses, int N, int K, int A, int houseIndex, List<Integer> usedColors, int depth, int maxDepth) {
        if (depth > maxDepth) {
            return false;
        }

        if (houseIndex == N) {
            return true;
        }

        int currentColor = houseIndex > 0 ? houses.get(houseIndex - 1).get(A - 1) : 0;
        for (int i = 0; i < A; i++) {
            currentColor = getNextColor(currentColor, K);
            if (canUseColor(usedColors, currentColor)) {
                houses.get(houseIndex).add(currentColor);
            } else {
                return false;
            }
        }

        if (houseIndex >= 2) {
            usedColors.remove(0);
        }
        usedColors.add(houses.get(houseIndex).get(0));

        return paintHouses(houses, N, K, A, houseIndex + 1, usedColors, depth + 1, maxDepth);
  }
}
```
### Задание: Дана закодированная строка, верните её декодированную версию. 
### Решение задачи в mains.txt
```
import java.util.Scanner;
public class Main {

    public static boolean check(String s) {
        for (char c : s.toCharArray()) {
            if (!Character.isDigit(c) && !Character.isLetter(c) && c != '[' && c != ']') {
                return false;
            }
        }
        return true;
    }

    public static boolean check2(String s) {
        int count = 0;
        for (char c : s.toCharArray()) {
            if (Character.isDigit(c)) {
                count = count * 10 + (c - '0');
                if (count < 1) {
                    return false;
                }
            } else {
                count = 0;
            }
            if (count > 300) {
                return false;
            }
        }
        return true;
    }

    public static String decodeString(String s, int[] index, int stackDepth) {
        StringBuilder result = new StringBuilder();
        int count = 0;

        while (index[0] < s.length()) {
            char c = s.charAt(index[0]);

            if (Character.isDigit(c)) {
                count = count * 10 + (c - '0');
            } else if (Character.isLetter(c)) {
                result.append(c);
                count = 0;
            } else if (c == '[') {
                index[0]++; // Перемещаем индекс на следующий символ
                stackDepth++; // Увеличиваем счетчик стека перед вызовом рекурсии
                if (stackDepth > 1000) { // Проверяем, не переполнился ли стек
                    throw new RuntimeException("Stack overflow detected");
                }
                String nested = decodeString(s, index, stackDepth);
                for (int i = 0; i < count; i++) {
                    result.append(nested);
                }
                count = 0; // Сбрасываем счетчик после обработки вложенной строки
                continue; // Пропускаем инкремент индекса, так как он уже сделан в рекурсивном вызове
            } else if (c == ']') {
                index[0]++; // Перемещаем индекс на следующий символ после закрывающей скобки
                stackDepth--; // Уменьшаем счетчик стека после возврата из рекурсии
                return result.toString(); // Возвращаем результат для вышестоящего уровня рекурсии
            }

            index[0]++; // Перемещаем индекс на следующий символ
        }

        return result.toString();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Введите закодированную строку: ");
        String encodedString = scanner.nextLine();

        if (encodedString.length() > 30) {
            System.out.println("Слишком длинная строка");
            return;
        }

        if (!check(encodedString)) {
            System.out.println("Недопустимые символы!");
            return;
        }

        if (!check2(encodedString)) {
            System.out.println("Число не входит в нужный диапозон!");
            return;
        }

        int[] index = new int[1];
        int stackDepth = 0;
        String decodedString = decodeString(encodedString, index, stackDepth);
        System.out.println("Декодированная строка: " + decodedString);
    }
}
```
