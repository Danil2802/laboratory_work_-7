# ������������ ������ �7
## ������������ ����������
## �� ����������: �����������������
### ���� � ������ ������: �������� ������������ ����������������, ������� ���������� ����������� ����������.
### �������� ���������� ������:
#### 1) ������� ���������� ������������� ����� ��� ����������� ����������������.
#### 2) �������� ����������� ��������� ������� ������������ ������.
#### 3) �������������� ���������.

### �������: ������� N ����� � K ������. ���������, ����� �� ��������� ���� ��������� ������� ������, ����� ���� ���������� �� ������, ��� ����� 2 ����.
### ������� ������ � maink.cpp
```C++
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
```
### �������: ���� �������������� ������, ������� � �������������� ������. 
### ������� ������ � maind.cpp
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
```
### �������: ������� N ����� � K ������. ���������, ����� �� ��������� ���� ��������� ������� ������, ����� ���� ���������� �� ������, ��� ����� 2 ����.
### ������� ������ � mainp.txt
```
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("������� ���������� ����� (N): ");
        int N = scanner.nextInt();
        System.out.print("������� ���������� ������ ��� �������� ������ ���� (A): ");
        int A = scanner.nextInt();
        System.out.print("������� ����� ���������� ������ (K): ");
        int K = scanner.nextInt();

        if (K < A) {
            System.out.println("������������ ������ ��� �������� ������ ����.");
            return;
        }

        if (N < 1 || K < 0 || A < 1) {
            System.out.println("�� ���������!");
            return;
        }

        List<List<Integer>> houses = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            houses.add(new ArrayList<>());
        }
        List<Integer> usedColors = new ArrayList<>();

        if (paintHouses(houses, N, K, A, 0, usedColors, 0, 1000)) {
            System.out.println("��, ����� ��������� ���� ��������� �������:");
            for (List<Integer> house : houses) {
                for (int color : house) {
                    System.out.print(color + " ");
                }
                System.out.println();
            }
        } else {
            System.out.println("���, ���������� ��������� ���� � ������ ���������.");
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
### �������: ���� �������������� ������, ������� � �������������� ������. 
### ������� ������ � mains.txt
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
                index[0]++; // ���������� ������ �� ��������� ������
                stackDepth++; // ����������� ������� ����� ����� ������� ��������
                if (stackDepth > 1000) { // ���������, �� ������������ �� ����
                    throw new RuntimeException("Stack overflow detected");
                }
                String nested = decodeString(s, index, stackDepth);
                for (int i = 0; i < count; i++) {
                    result.append(nested);
                }
                count = 0; // ���������� ������� ����� ��������� ��������� ������
                continue; // ���������� ��������� �������, ��� ��� �� ��� ������ � ����������� ������
            } else if (c == ']') {
                index[0]++; // ���������� ������ �� ��������� ������ ����� ����������� ������
                stackDepth--; // ��������� ������� ����� ����� �������� �� ��������
                return result.toString(); // ���������� ��������� ��� ������������ ������ ��������
            }

            index[0]++; // ���������� ������ �� ��������� ������
        }

        return result.toString();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("������� �������������� ������: ");
        String encodedString = scanner.nextLine();

        if (encodedString.length() > 30) {
            System.out.println("������� ������� ������");
            return;
        }

        if (!check(encodedString)) {
            System.out.println("������������ �������!");
            return;
        }

        if (!check2(encodedString)) {
            System.out.println("����� �� ������ � ������ ��������!");
            return;
        }

        int[] index = new int[1];
        int stackDepth = 0;
        String decodedString = decodeString(encodedString, index, stackDepth);
        System.out.println("�������������� ������: " + decodedString);
    }
}
```