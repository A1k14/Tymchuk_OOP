#include <iostream>
#include <random>
#include <limits>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Vector {
private:
    double* data;
    int size;
    static int objectCount;

public:
    Vector() {
        cout << "Default constructor called." << endl;
        size = 1;
        data = new double[1];
        if (!data) {
            throw bad_alloc();
        }
        data[0] = 0.0;
        objectCount++;
        cout << "Created a vector of size 1, initialized with 0." << endl;
    }

    Vector(int size) {
        
        if (size <= 0) {
            throw invalid_argument("Vector size must be greater than zero.");
        }

        this->size = size;
        data = new double[size];
        if (!data) {
            throw bad_alloc();
        }
        fill(data, data + size, 0.0);
        objectCount++;
    }

    Vector(int size, double initialValue) {
        cout << "Constructor with size and initial value called (size = " << size << ", initial value = " << initialValue << ")." << endl;
        if (size <= 0) {
            throw invalid_argument("Vector size must be greater than zero.");
        }

        this->size = size;
        data = new double[size];
        if (!data) {
            throw bad_alloc();
        }
        fill(data, data + size, initialValue);
        objectCount++;
        cout << "Created a vector of size " << size << ", initialized with value " << initialValue << "." << endl;
    }

    Vector(const Vector& other) : size(other.size) {
        data = new double[size];
        if (!data) {
            throw bad_alloc();
        }
        copy(other.data, other.data + size, data);
        objectCount++;
        cout << "Created a copy of the vector." << endl;
    }

    Vector& operator=(Vector other) {
        swap(data, other.data);
        swap(size, other.size);
        cout << "Vector assigned." << endl;
        return *this;
    }

    ~Vector() {
        delete[] data;
        objectCount--;
        cout << "Memory freed, vector destroyed." << endl;
    }

    void setElement(int index, double value = 0.0) {
        cout << "setElement called (index = " << index << ", value = " << value << ")." << endl;
        if (index < 0 || index >= size) {
            throw out_of_range("Index is out of range.");
        }
        data[index] = value;
        cout << "Element at index " << index << " set to value " << value << "." << endl;
    }

    double getElement(int index) const {
        cout << "getElement called (index = " << index << ")." << endl;
        if (index < 0 || index >= size) {
            throw out_of_range("Index is out of range.");
        }
        cout << "Retrieved element at index " << index << ": " << data[index] << "." << endl;
        return data[index];
    }

    void print() const {
        cout << " [";
        for (int i = 0; i < size; ++i) {
            cout << data[i];
            if (i < size - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    Vector add(const Vector& other) const {
        if (size != other.size) {
            throw invalid_argument("Vectors must have the same size for addition.");
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    Vector subtract(const Vector& other) const {
        if (size != other.size) {
            throw invalid_argument("Vectors must have the same size for subtraction.");
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        cout << "Vectors subtracted." << endl;
        return result;
    }

    Vector multiplyByScalar(double scalar) const {
        cout << "multiplyByScalar called (scalar = " << scalar << ")." << endl;
        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] * scalar;
        }
        cout << "Vector multiplied by scalar." << endl;
        return result;
    }

    Vector divideByScalar(double scalar) const {
        if (scalar == 0.0) {
            throw invalid_argument("Division by zero is not allowed.");
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] / scalar;
        }
        cout << "Vector divided by scalar." << endl;
        return result;
    }

    void compareVectors(const Vector& other) const {
        if (size != other.size) {
            throw invalid_argument("Vectors must have the same size for comparison.");
        }

        if (isGreaterThan(other)) {
            cout << "Vector 1 is greater than Vector 2." << endl;
        }
        else if (isLessThan(other)) {
            cout << "Vector 1 is less than Vector 2." << endl;
        }
        else {
            cout << "Vector 1 is equal to Vector 2." << endl;
        }
    }

    bool isGreaterThan(const Vector& other) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] <= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool isLessThan(const Vector& other) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] >= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool isEqual(const Vector& other) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    static int getObjectCount() {
        cout << "getObjectCount() called. Object count: " << objectCount << endl;
        return objectCount;
    }

    void inputFromKeyboard() {
        cout << "Enter the elements of the vector:" << endl;
        for (int i = 0; i < size; ++i) {
            cout << "Element " << i << ": ";
            cin >> data[i];
        }
    }
};

int Vector::objectCount = 0;

int main() {
    cout << "Starting the program." << endl;

    try {
        int size1, size2;
        cout << "Enter the size for vector 1: ";
        cin >> size1;
        Vector v1(size1);
        v1.inputFromKeyboard();

        cout << "Enter the size for vector 2: ";
        cin >> size2;
        Vector v2(size2);
        v2.inputFromKeyboard();

        cout << "\n--- Printing vectors ---" << endl;
        cout << "Vector 1: ";
        v1.print();
        cout << "Vector 2: ";
        v2.print();

        if (size1 == size2) {
            cout << "\n--- Arithmetic operations ---" << endl;
            Vector v5 = v1.add(v2);
            cout << "v1 + v2: ";
            v5.print();

            Vector v6 = v1.subtract(v2);
            cout << "v1 - v2: ";
            v6.print();
        }
        else {
            cout << "\n--- Arithmetic operations are not possible because the vector sizes are different. ---" << endl;
        }

        cout << "\n--- Multiplication by a scalar ---" << endl;
        double scalar;
        cout << "Enter the scalar: ";
        cin >> scalar;
        Vector v7 = v1.multiplyByScalar(scalar);
        cout << "v1 * " << scalar << ": ";
        v7.print();

        cout << "\n--- Division by a scalar ---" << endl;
        cout << "Enter the scalar for division: ";
        cin >> scalar;
        Vector v8 = v1.divideByScalar(scalar);
        cout << "v1 / " << scalar << ": ";
        v8.print();

        cout << "\n--- Comparison functions ---" << endl;
        if (size1 == size2) {
            v1.compareVectors(v2);
        }
        else {
            cout << "Vector sizes are different, comparison is not possible." << endl;
        }

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "\nEnding the program." << endl;
    return 0;
}