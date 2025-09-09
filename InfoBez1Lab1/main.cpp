#include <iostream>

void task1();
void task2();

int main() {
    setlocale(LC_ALL, "ru");

    std::cout << "Выберите задание:\n";
    std::cout << "1 - Задание 1 (Шифр)\n";
    std::cout << "2 - Задание 2 (Сигнализации)\n";
    std::cout << "Ваш выбор: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        task1();
    }
    else if (choice == 2) {
        task2();
    }
    else {
        std::cout << "Неверный выбор!\n";
    }

    return 0;
}
