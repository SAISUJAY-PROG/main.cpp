#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Canvas dimensions
const int ROWS = 20;
const int COLS = 50;

// Structure to store shape information for deletion/modification tracking
struct Shape {
    int id;
    string type;
    int x1, y1, x2, y2, extra; // Coords and secondary parameters
};

class GraphicsEditor {
private:
    char canvas[ROWS][COLS];
    vector<Shape> shapes; // Tracks all placed shapes dynamically
    int nextId;

    void clearCanvas() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                canvas[i][j] = ' ';
            }
        }
    }

    void plot(int x, int y, char ch) {
        if (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
            canvas[y][x] = ch;
        }
    }

public:
    GraphicsEditor() {
        nextId = 1;
        clearCanvas();
    }

    // --- GEOMETRIC ALGORITHMS ---

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

    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
        drawLine(x1, y1, x2, y2, '*');
        drawLine(x2, y2, x3, y3, '_');
        drawLine(x3, y3, x1, y1, '*');
    }

    // --- STATE MANAGEMENT AND REDRAW LOGIC ---

    // Wipes the frame canvas clean and sequentially replots all structural elements
    void redrawAll() {
        clearCanvas();
        for (const auto& shape : shapes) {
            if (shape.type == "line") {
                drawLine(shape.x1, shape.y1, shape.x2, shape.y2);
            } else if (shape.type == "rectangle") {
                drawRectangle(shape.x1, shape.y1, shape.x2, shape.y2);
            } else if (shape.type == "circle") {
                drawCircle(shape.x1, shape.y1, shape.extra);
            } else if (shape.type == "triangle") {
                drawTriangle(shape.x1, shape.y1, shape.x2, shape.y2, shape.extra, shape.y2);
            }
        }
    }

    void addShape(string type, int x1, int y1, int x2, int y2, int extra = 0) {
        shapes.push_back({nextId++, type, x1, y1, x2, y2, extra});
        redrawAll();
    }

    bool deleteShape(int id) {
        for (auto it = shapes.begin(); it != shapes.end(); ++it) {
            if (it->id == id) {
                shapes.erase(it);
                redrawAll();
                return true;
            }
        }
        return false;
    }

    bool modifyShape(int id, int x1, int y1, int x2, int y2, int extra = 0) {
        for (auto& shape : shapes) {
            if (shape.id == id) {
                shape.x1 = x1;
                shape.y1 = y1;
                shape.x2 = x2;
                shape.y2 = y2;
                shape.extra = extra;
                redrawAll();
                return true;
            }
        }
        return false;
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

        // Display current objects list under the frame canvas
        cout << "Active Objects List:\n";
        if (shapes.empty()) cout << "  (None)\n";
        for (const auto& shape : shapes) {
            cout << "  ID: " << shape.id << " | Type: " << shape.type;
            if (shape.type == "circle") {
                cout << " | Center: (" << shape.x1 << "," << shape.y1 << ") Radius: " << shape.extra;
            } else if (shape.type == "triangle") {
                cout << " | V1: (" << shape.x1 << "," << shape.y1 << ") Base Width points: " << shape.x2 << " to " << shape.extra;
            } else {
                cout << " | P1: (" << shape.x1 << "," << shape.y1 << ") P2: (" << shape.x2 << "," << shape.y2 << ")";
            }
            cout << "\n";
        }
    }
};

int main() {
    GraphicsEditor editor;
    int choice;

    while (true) {
        editor.display();
        cout << "\n--- 2D Text Graphics Editor (Day 4: Complete System) ---\n";
        cout << "1. Add Line\n";
        cout << "2. Add Rectangle\n";
        cout << "3. Add Circle\n";
        cout << "4. Add Triangle\n";
        cout << "5. Delete Object\n";
        cout << "6. Modify Object\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (Max X: " << COLS-1 << ", Y: " << ROWS-1 << "): ";
        cin >> choice;

        if (choice == 7) break;

        int x1, y1, x2, y2, extra, id;

        switch (choice) {
            case 1:
                cout << "Enter X1 Y1 X2 Y2: ";
                cin >> x1 >> y1 >> x2 >> y2;
                editor.addShape("line", x1, y1, x2, y2);
                break;
            case 2:
                cout << "Enter Top-Left (X1 Y1) and Bottom-Right (X2 Y2): ";
                cin >> x1 >> y1 >> x2 >> y2;
                editor.addShape("rectangle", x1, y1, x2, y2);
                break;
            case 3:
                cout << "Enter Center (X1 Y1) and Radius: ";
                cin >> x1 >> y1 >> extra;
                editor.addShape("circle", x1, y1, 0, 0, extra);
                break;
            case 4:
                cout << "Enter Top Vertex (X1 Y1), Bottom-Right Base X2, and Bottom-Left Base X3: ";
                cin >> x1 >> y1 >> x2 >> extra;
                y2 = y1 + 5; // Formats automated relative height drop for simplicity
                editor.addShape("triangle", x1, y1, x2, y2, extra);
                break;
            case 5:
                cout << "Enter Shape ID to delete: ";
                cin >> id;
                if (!editor.deleteShape(id)) cout << "Error: ID not found.\n";
                break;
            case 6:
                cout << "Enter Shape ID to modify: ";
                cin >> id;
                cout << "Enter New Coordinates (X1 Y1 X2 Y2): ";
                cin >> x1 >> y1 >> x2 >> y2;
                cout << "Enter Extra parameter (Radius or Base X3 if applicable, else 0): ";
                cin >> extra;
                if (!editor.modifyShape(id, x1, y1, x2, y2, extra)) cout << "Error: ID not found.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
        cout << "\n=========================================\n\n";
    }

    return 0;
}