#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Canvas dimensions
const int ROWS = 20;
const int COLS = 50;

class GraphicsEditor {
private:
    char canvas[ROWS][COLS];

    // Fills the background grid with empty spaces
    void clearCanvas() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                canvas[i][j] = ' ';
            }
        }
    }

public:
    GraphicsEditor() {
        clearCanvas();
    }

    // Displays the current state of the canvas surrounded by a border frame
    void display() {
        // Print top border frame
        for (int j = 0; j < COLS + 2; ++j) cout << "-";
        cout << "\n";

        for (int i = 0; i < ROWS; ++i) {
            cout << "|"; // Left border frame
            for (int j = 0; j < COLS; ++j) {
                cout << canvas[i][j];
            }
            cout << "|\n"; // Right border frame
        }

        // Print bottom border frame
        for (int j = 0; j < COLS + 2; ++j) cout << "-";
        cout << "\n";
    }
};

int main() {
    GraphicsEditor editor;
    int choice;

    while (true) {
        editor.display();
        cout << "\n--- 2D Text Graphics Editor (Day 1: Canvas Setup) ---\n";
        cout << "1. Add Line (Stub)\n";
        cout << "2. Add Rectangle (Stub)\n";
        cout << "3. Add Circle (Stub)\n";
        cout << "4. Add Triangle (Stub)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) {
            cout << "Exiting editor...\n";
            break;
        }

        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
                cout << "\n[System] Drawing functions will be implemented in the next update!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
        cout << "\n=========================================\n\n";
    }

    return 0;
}