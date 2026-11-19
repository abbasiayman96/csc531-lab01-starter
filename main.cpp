#include <iostream>
#include "lab01.hpp"

namespace {
constexpr int CAP = 8;

void displayArray(const int a[], int size, int cap) {
    std::cout << "Logical size: " << size << " / Capacity: " << cap << "\n";
    std::cout << "Active elements: [";
    for (int i = 0; i < size; ++i) {
        std::cout << a[i];
        if (i + 1 < size) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

void runBoundaryDemo() {
    int demo[CAP] = {10, 20, 30};
    int demoSize = 3;

    std::cout << "\n--- Boundary & Operations Demo (CAP = " << CAP << ") ---\n";
    displayArray(demo, demoSize, CAP);

    if (insertAt(demo, demoSize, CAP, 1, 15)) {
        std::cout << "Inserted 15 at index 1.\n";
    }
    displayArray(demo, demoSize, CAP);

    if (deleteAt(demo, demoSize, 2)) {
        std::cout << "Deleted element at index 2.\n";
    }
    displayArray(demo, demoSize, CAP);

    while (demoSize < CAP) {
        insertAt(demo, demoSize, CAP, demoSize, (demoSize + 1) * 100);
    }
    std::cout << "Array filled to capacity:\n";
    displayArray(demo, demoSize, CAP);

    if (!insertAt(demo, demoSize, CAP, 0, 999)) {
        std::cout << "Rejected insertion (999) because array is full. Size remains " << demoSize << ".\n";
    }

    while (demoSize > 0) {
        deleteAt(demo, demoSize, 0);
    }
    std::cout << "Array emptied:\n";
    displayArray(demo, demoSize, CAP);

    if (!deleteAt(demo, demoSize, 0)) {
        std::cout << "Rejected deletion because array is empty. Size remains " << demoSize << ".\n";
    }
    std::cout << "--------------------------------------------------\n\n";
}
} // namespace

int main() {
    int arr[CAP] = {10, 20, 30, 40};
    int size = 4;

    runBoundaryDemo();

    int choice = 0;
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Display\n";
        std::cout << "2. Insert\n";
        std::cout << "3. Delete\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number (1-4).\n";
            continue;
        }

        if (choice == 1) {
            displayArray(arr, size, CAP);
        } else if (choice == 2) {
            int pos = 0;
            int val = 0;
            std::cout << "Enter index (0 to " << size << "): ";
            if (!(std::cin >> pos)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid index input.\n";
                continue;
            }
            std::cout << "Enter value: ";
            if (!(std::cin >> val)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid value input.\n";
                continue;
            }

            if (insertAt(arr, size, CAP, pos, val)) {
                std::cout << "Insertion successful.\n";
            } else {
                std::cout << "Insertion failed (invalid position or array full). State unchanged.\n";
            }
        } else if (choice == 3) {
            int pos = 0;
            std::cout << "Enter index to delete (0 to " << (size > 0 ? size - 1 : 0) << "): ";
            if (!(std::cin >> pos)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid index input.\n";
                continue;
            }

            if (deleteAt(arr, size, pos)) {
                std::cout << "Deletion successful.\n";
            } else {
                std::cout << "Deletion failed (invalid index or array empty). State unchanged.\n";
            }
        } else if (choice == 4) {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cout << "Please select a valid option (1-4).\n";
        }
    }

    return 0;
}
