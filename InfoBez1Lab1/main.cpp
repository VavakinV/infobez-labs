#include <iostream>

void task1();
void task2();

int main() {
    setlocale(LC_ALL, "ru");

    std::cout << "�������� �������:\n";
    std::cout << "1 - Task1 (������������)\n";
    std::cout << "2 - Task2 (����)\n";
    std::cout << "��� �����: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        task1();
    }
    else if (choice == 2) {
        task2();
    }
    else {
        std::cout << "�������� �����!\n";
    }

    return 0;
}
