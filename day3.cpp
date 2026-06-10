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

    // --- DRAWING FUNCTIONS ---

    void drawLine(int x1, int y1, int x2, int y2, char ch = '*') {
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
        drawLine(x1, y1, x2, y1, '_');
        drawLine(x1, y2, x2, y2, '_');
        drawLine(x1, y1 + 1, x1, y2, '*');
        drawLine(x2, y1 + 1, x2, y2, '*');
    }

    // Added in Day 3: Bresenham's Circle Drawing Algorithm
    void drawCircle(int xc, int yc, int r) {
        int x = 0, y = r;
        int d = 3 - 2 * r;
        
        auto plotCirclePoints = [&](int xc, int yc, int x, int y) {
            plot(xc + x, yc + y, '*');
            plot(xc - x, yc + y, '*');
            plot(xc + x, yc - y, '_');
            plot(xc - x, yc - y, '_');
            plot(xc + y, yc + x, '*');
            plot(xc - y, yc + x, '*');
            plot(xc + y, yc - x, '_');
            plot(xc - y, yc - x, '_');
        };

        plotCirclePoints(xc, yc, x, y);
        while (y >= x) {
            x++;
            if (d > 0) {
                y--;
                d = d + 4 * (x - y) + 10;
            } else {
                d = d + 4 * x + 6;
            }
            plotCirclePoints(xc, yc, x, y);
        }
    }

    // Added in Day 3: Triangle logic connecting 3 custom vertices
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
        drawLine(x1, y1, x2, y2, '*');
        drawLine(x2, y2, x3, y3, '_');
        drawLine(x3, y3, x1, y1, '*');
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
        cout << "\n--- 2D Text Graphics Editor (Day 3: Circles & Triangles) ---\n";
        cout << "1. Add Line\n";
        cout << "2. Add Rectangle\n";
        cout << "3. Add Circle\n";
        cout << "4. Add Triangle\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (Max X: " << COLS-1 << ", Y: " << ROWS-1 << "): ";
        cin >> choice;

        if (choice == 5) break;

        int x1, y1, x2, y2, x3, y3, r;

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
                cout << "Enter Center (XC YC) and Radius: ";
                cin >> x1 >> y1 >> r;
                editor.drawCircle(x1, y1, r);
                break;
            case 4:
                cout << "Enter V1(X Y), V2(X Y), V3(X Y): ";
                cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
                editor.drawTriangle(x1, y1, x2, y2, x3, y3);
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
        cout << "\n=========================================\n\n";
    }

    return 0;
}