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
