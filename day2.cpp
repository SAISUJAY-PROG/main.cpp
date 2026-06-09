#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Canvas dimensions
const int ROWS = 20;
const int COLS = 50;

class GraphicsEditor {
private:
    char canvas[ROWS][COLS];

    void clearCanvas() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                canvas[i][j] = ' ';
            }
        }
    }

    // Direct plot helper with boundary checks
    void plot(int x, int y, char ch) {
        if (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
            canvas[y][x] = ch;
        }
    }

public:
    GraphicsEditor() {
        clearCanvas();
    }

    // --- DRAWING FUNCTIONS (Added in Day 2) ---

    void drawLine(int x1, int y1, int x2, int y2, char ch = '*') {
        // Bresenham's Line Generation Algorithm
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            plot(x1, y1, ch);
            if (x1 == x2 && y1 == y2) break;
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y1 += sy;
            }
        }
    }

    void drawRectangle(int x1, int y1, int x2, int y2) {
        // Top and bottom horizontal borders using '_'
        drawLine(x1, y1, x2, y1, '_');
        drawLine(x1, y2, x2, y2, '_');
        // Left and right vertical borders using '*'
        drawLine(x1, y1 + 1, x1, y2, '*');
        drawLine(x2, y1 + 1, x2, y2, '*');
    }

    void display() {
        for (int j = 0; j < COLS + 2; ++j) cout << "-";
        cout << "\n";

        for (int i = 0; i < ROWS; ++i) {
            cout << "|";
            for (int j = 0; j < COLS; ++j) {
                cout << canvas[i][j];
            }
            cout << "|\n";
        }

        for (int j = 0; j < COLS + 2; ++j) cout << "-";
        cout << "\n";
    }
};

int main() {
    GraphicsEditor editor;
    int choice;

    while (true) {
        editor.display();
        cout << "\n--- 2D Text Graphics Editor (Day 2: Lines & Rectangles) ---\n";
        cout << "1. Add Line\n";
        cout << "2. Add Rectangle\n";
        cout << "3. Add Circle (Stub)\n";
        cout << "4. Add Triangle (Stub)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (Max X: " << COLS-1 << ", Y: " << ROWS-1 << "): ";
        cin >> choice;

        if (choice == 5) break;

        int x1, y1, x2, y2;

        switch (choice) {
            case 1:
                cout << "Enter X1 Y1 X2 Y2: ";
                cin >> x1 >> y1 >> x2 >> y2;
                editor.drawLine(x1, y1, x2, y2);
                break;
            case 2:
                cout << "Enter Top-Left (X1 Y1) and Bottom-Right (X2 Y2): ";
                cin >> x1 >> y1 >> x2 >> y2;
                editor.drawRectangle(x1, y1, x2, y2);
                break;
            case 3:
            case 4:
                cout << "\n[System] This shape will be unlocked in the Day 3 update!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
        cout << "\n=========================================\n\n";
    }

    return 0;
}