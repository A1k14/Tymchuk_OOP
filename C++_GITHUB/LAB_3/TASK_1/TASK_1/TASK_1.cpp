#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>

using namespace std;

class Rectangle {
private:
    double height;
    double width;
    string color;
    vector<string> allowedColors = { "red", "blue" };

public:
    Rectangle() : height(1.0), width(1.0), color("red") {}

    Rectangle(double h, double w, string c) : height(h), width(w), color(c) {}

    void setHeight(double h) {
        if (h > 0) {
            height = h;
        }
        else {
            cerr << "Invalid height value. Height must be positive." << endl;
        }
    }

    void setWidth(double w) {
        if (w > 0) {
            width = w;
        }
        else {
            cerr << "Invalid width value. Width must be positive." << endl;
        }
    }

    void setColor(string c) {
        bool colorIsValid = false;
        for (const auto& allowedColor : allowedColors) {
            if (c == allowedColor) {
                colorIsValid = true;
                break;
            }
        }

        if (colorIsValid) {
            color = c;
        }
        else {
            cerr << "Invalid color value. Color must be 'red' or 'blue'." << endl;
        }
    }

    double getHeight() const { return height; }
    double getWidth() const { return width; }
    string getColor() const { return color; }

    double calculateArea() const { return height * width; }
    double calculatePerimeter() const { return 2 * (height + width); }

    void print() const {
        cout << "Height: " << height << endl;
        cout << "Width: " << width << endl;
        cout << "Color: " << color << endl;
        cout << "Area: " << calculateArea() << endl;
        cout << "Perimeter: " << calculatePerimeter() << endl;
    }
};

int main() {
    int choice;
    double height, width;
    string color;

    cout << "Choose input method:" << endl;
    cout << "1. Manual input" << endl;
    cout << "2. Random number generation" << endl;
    cin >> choice;

    while (cin.fail()) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();

        cin >> choice;
    }

    if (choice == 1) {
        cout << "Enter height: ";
        cin >> height;
        while (cin.fail() || height <= 0) {
            cout << "Invalid input. Please enter a positive number for height: ";
            cin.clear();

            cin >> height;
        }

        cout << "Enter width: ";
        cin >> width;
        while (cin.fail() || width <= 0) {
            cout << "Invalid input. Please enter a positive number for width: ";
            cin.clear();

            cin >> width;
        }

        cout << "Enter color (red or blue): ";
        cin >> color;
        while (color != "red" && color != "blue") {
            cout << "Invalid input. Please enter 'red' or 'blue' for color: ";
            cin.clear();

            cin >> color;
        }

    }
    else if (choice == 2) {
        srand(time(0)); 

        double min = 0.0;
        double max = 100.0;

        height = min + ((double)rand() / RAND_MAX) * (max - min);
        width = min + ((double)rand() / RAND_MAX) * (max - min);

        int colorIndex = rand() % 2; 
        if (colorIndex == 0) {
            color = "red";
        }
        else {
            color = "blue";
        }
    }
    else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    Rectangle rect(height, width, color);
    rect.print();

    return 0;
}
