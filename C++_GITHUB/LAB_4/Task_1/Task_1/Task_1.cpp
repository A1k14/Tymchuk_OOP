#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <new>
#include <utility>
#include <vector>
#include <limits>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class VectorDouble {
private:
    double* data;
    int size;
    static int objectCount;

    void swap(VectorDouble& other) noexcept {
        using std::swap;
        swap(data, other.data);
        swap(size, other.size);
    }

public:
    VectorDouble() : data(nullptr), size(0) {
        try {
            data = new double[1] {0.0};
            size = 1;
            objectCount++;
        }
        catch (const bad_alloc& e) {
            cerr << "Default Constructor: Memory allocation failed! " << e.what() << endl; throw;
        }
    }

    VectorDouble(int s) : data(nullptr), size(0) {
        if (s <= 0) throw invalid_argument("Size must be greater than 0");
        try {
            data = new double[s]();
            size = s;
            objectCount++;
        }
        catch (const bad_alloc& e) {
            cerr << "Size Constructor: Memory allocation failed! " << e.what() << endl; throw;
        }
    }

    VectorDouble(int s, double value) : data(nullptr), size(0) {
        if (s <= 0) throw invalid_argument("Size must be greater than 0");
        try {
            data = new double[s];
            size = s;
            for (int i = 0; i < size; i++) data[i] = value;
            objectCount++;
        }
        catch (const bad_alloc& e) {
            cerr << "Size/Value Constructor: Memory allocation failed! " << e.what() << endl; throw;
        }
    }

    VectorDouble(const VectorDouble& other) : data(nullptr), size(0) {
        if (other.size <= 0) throw invalid_argument("Cannot copy vector with non-positive size");
        try {
            data = new double[other.size];
            size = other.size;
            for (int i = 0; i < size; ++i) data[i] = other.data[i];
            objectCount++;
        }
        catch (const bad_alloc& e) {
            cerr << "Copy Constructor: Memory allocation failed! " << e.what() << endl; throw;
        }
    }

    ~VectorDouble() noexcept {
        delete[] data;
        objectCount--;
    }

    VectorDouble& operator=(VectorDouble other) noexcept { swap(other); return *this; }

    VectorDouble operator+(const VectorDouble& other) const {
        if (size != other.size) throw invalid_argument("Vectors must have the same size for operator+");
        VectorDouble result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] + other.data[i];
        return result;
    }

    VectorDouble operator*(double scalar) const {
        VectorDouble result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] * scalar;
        return result;
    }

    VectorDouble operator-() const {
        VectorDouble result(size);
        for (int i = 0; i < size; ++i) result.data[i] = -data[i];
        return result;
    }

    VectorDouble operator-(const VectorDouble& other) const {
        if (size != other.size) throw invalid_argument("Vectors must have the same size for operator-");
        VectorDouble result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] - other.data[i];
        return result;
    }

    VectorDouble operator/(double scalar) const {
        if (fabs(scalar) < 1e-10) throw runtime_error("Division by zero in operator /");
        VectorDouble result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] / scalar;
        return result;
    }

    VectorDouble operator++(int) {
        VectorDouble temp = *this;
        for (int i = 0; i < size; ++i) data[i] += 1.0;
        return temp;
    }

    VectorDouble& operator--() {
        for (int i = 0; i < size; ++i) data[i] -= 1.0;
        return *this;
    }

    VectorDouble operator%(int scalar) const {
        if (scalar == 0) throw runtime_error("Division by zero in operator %");
        VectorDouble result(size);
        double double_scalar = static_cast<double>(scalar);
        for (int i = 0; i < size; ++i) {
            result.data[i] = fmod(data[i], double_scalar);
        }
        return result;
    }

    bool operator>(const VectorDouble& other) const {
        if (size != other.size) throw runtime_error("Cannot compare vectors (>) of different sizes.");
        if (size == 0) return false;
        for (int i = 0; i < size; ++i) {
            if (!(data[i] > other.data[i])) {
                return false;
            }
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const VectorDouble& vec) {
        if (!vec.data) { os << "[invalid vector]"; return os; }
        os << fixed << setprecision(2);
        os << "[";
        for (int i = 0; i < vec.size; i++) {
            os << vec.data[i] << (i == vec.size - 1 ? "" : ", ");
        }
        os << "]";
        return os;
    }

    friend istream& operator>>(istream& is, VectorDouble& vec) {
        if (!vec.data || vec.size == 0) {
            is.setstate(ios_base::failbit);
            cerr << "Error: Cannot read into uninitialized or zero-sized vector." << endl;
            return is;
        }
        for (int i = 0; i < vec.size; i++) {
            if (!(is >> vec.data[i])) {
                is.setstate(ios_base::failbit);
                cerr << "\nError: Invalid input while reading element " << i << endl;
                break;
            }
        }
        return is;
    }

    static int getObjectCount() { return objectCount; }

    int getSize() const { return size; }

    double& operator[](int index) {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        return data[index];
    }

    const double& operator[](int index) const {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        return data[index];
    }
};

int VectorDouble::objectCount = 0;

VectorDouble operator*(double scalar, const VectorDouble& vec) {
    return vec * scalar;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    const int vectorSize = 3;
    int choice;

    cout << "--- VectorDouble Operations Demo ---" << endl;
    cout << "Vector size is fixed to: " << vectorSize << endl;
    cout << "Initial object count: " << VectorDouble::getObjectCount() << endl;

    cout << "\nChoose initialization method:" << endl;
    cout << "1 - Manual Input" << endl;
    cout << "2 - Random Integers" << endl;
    cout << "Enter choice (1 or 2): ";

    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    try {
        VectorDouble v1(vectorSize);
        VectorDouble v2(vectorSize);
        VectorDouble v3(vectorSize);

        if (choice == 1) {
            cout << "\n--- Manual Input ---" << endl;
            cout << "Enter " << vectorSize << " values for v1: ";
            if (!(cin >> v1)) { throw runtime_error("Input failed for v1"); }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter " << vectorSize << " values for v2: ";
            if (!(cin >> v2)) { throw runtime_error("Input failed for v2"); }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter " << vectorSize << " values for v3: ";
            if (!(cin >> v3)) { throw runtime_error("Input failed for v3"); }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cout << "\n--- Random Integer Initialization (-10 to 10) ---" << endl;
            for (int i = 0; i < vectorSize; ++i) {
                v1[i] = static_cast<double>(rand() % 21 - 10);
                v2[i] = static_cast<double>(rand() % 21 - 10);
                v3[i] = static_cast<double>(rand() % 21 - 10);
            }
            cout << "Random vectors generated." << endl;
        }

        cout << "\n--- Initial Vectors ---" << endl;
        cout << "v1 = " << v1 << endl;
        cout << "v2 = " << v2 << endl;
        cout << "v3 = " << v3 << endl;
        cout << "Current object count: " << VectorDouble::getObjectCount() << endl;

        cout << "\n--- Calculating Expressions (Showing Operation Results) ---" << endl;

        cout << "\nExpression 1: res1 = (v1 + v2) * 1.5 - v3++ / 2.0" << endl;
        cout << "-------------------------------------------------" << endl;

        VectorDouble temp_sum = v1 + v2;
        cout << "v1 + v2              = " << temp_sum << endl;

        VectorDouble temp_mul = temp_sum * 1.5;
        cout << "(v1+v2) * 1.5          = " << temp_mul << endl;

        VectorDouble v3_original = v3;
        v3++;
        cout << "v3 (before ++)       = " << v3_original << "  (Value used in next step)" << endl;
        cout << "v3 (after ++)        = " << v3 << endl;

        VectorDouble temp_div = v3_original / 2.0;
        cout << "v3_original / 2.0    = " << temp_div << endl;

        VectorDouble res1 = temp_mul - temp_div;
        cout << "Result (step2 - step4) = " << res1 << "  <-- Final Result (res1)" << endl;
        cout << "-------------------------------------------------" << endl;

        cout << "\nExpression 2: res2 = --v1 % 5 + (v2 > v3 ? v2 : v1) * 0.8" << endl;
        cout << "-------------------------------------------------" << endl;

        cout << "v1 (before --)       = " << v1 << endl;
        VectorDouble& v1_decremented_ref = --v1;
        cout << "--v1                 = " << v1_decremented_ref << endl;

        VectorDouble temp_mod = v1_decremented_ref % 5;
        cout << "(--v1) % 5           = " << temp_mod << endl;

        bool comparison_result = (v2 > v3);
        cout << "v2 > v3              = " << (comparison_result ? "true" : "false") << " (v2=" << v2 << ", v3=" << v3 << ")" << endl;

        const VectorDouble& chosen_vec = comparison_result ? v2 : v1;
        cout << "(chosen vector)      = " << chosen_vec << endl;

        VectorDouble temp_mul_chosen = chosen_vec * 0.8;
        cout << "(chosen vec) * 0.8   = " << temp_mul_chosen << endl;

        VectorDouble res2 = temp_mod + temp_mul_chosen;
        cout << "Result (step2 + step5) = " << res2 << "  <-- Final Result (res2)" << endl;
        cout << "-------------------------------------------------" << endl;

    }
    catch (const exception& e) {
        cerr << "\n*** Runtime Error: " << e.what() << " ***" << endl;
    }

    cout << "\nFinal object count before exit: " << VectorDouble::getObjectCount() << endl;
    cout << "--- End of Demo ---" << endl;
    return 0;
}