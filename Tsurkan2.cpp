#include <iostream>

using namespace std;

class Vector {
private:
    short* data;
    int size;
    int state; // 0 - ок, 1 - помилка пам’яті, 2 - вихід за межі
    static int objectCount;

public:
    // --- Конструктори ---
    Vector() {
        size = 1;
        data = new(nothrow) short[size];
        if (!data) {
            state = 1;
        } else {
            data[0] = 0;
            state = 0;
        }
        objectCount++;
    }

    Vector(int s) {
        size = s;
        data = new(nothrow) short[size];
        if (!data) {
            state = 1;
        } else {
            for (int i = 0; i < size; ++i)
                data[i] = 0;
            state = 0;
        }
        objectCount++;
    }

    Vector(int s, short value) {
        size = s;
        data = new(nothrow) short[size];
        if (!data) {
            state = 1;
        } else {
            for (int i = 0; i < size; ++i)
                data[i] = value;
            state = 0;
        }
        objectCount++;
    }

    // --- Конструктор копій ---
    Vector(const Vector& other) {
        size = other.size;
        data = new(nothrow) short[size];
        if (!data) {
            state = 1;
        } else {
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
            state = other.state;
        }
        objectCount++;
    }

    // --- Оператор присвоєння ---
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new(nothrow) short[size];
            if (!data) {
                state = 1;
            } else {
                for (int i = 0; i < size; ++i)
                    data[i] = other.data[i];
                state = other.state;
            }
        }
        return *this;
    }

    // --- Деструктор ---
    ~Vector() {
        delete[] data;
        objectCount--;
    }

    // --- Присвоєння елементу ---
    void set(int index, short value = 0) {
        if (index < 0 || index >= size) {
            state = 2;
        } else {
            data[index] = value;
            state = 0;
        }
    }

    // --- Отримання елементу ---
    short get(int index) {
        if (index < 0 || index >= size) {
            state = 2;
            return 0;
        }
        state = 0;
        return data[index];
    }

    // --- Друк ---
    void print() const {
        cout << "Vector: ";
        for (int i = 0; i < size; ++i)
            cout << data[i] << " ";
        cout << "| Size: " << size << " | State: " << state << endl;
    }

    // --- Арифметика ---
    Vector add(const Vector& other) const {
        int minSize = (size < other.size) ? size : other.size;
        Vector result(minSize);
        for (int i = 0; i < minSize; ++i)
            result.data[i] = this->data[i] + other.data[i];
        return result;
    }

    Vector subtract(const Vector& other) const {
        int minSize = (size < other.size) ? size : other.size;
        Vector result(minSize);
        for (int i = 0; i < minSize; ++i)
            result.data[i] = this->data[i] - other.data[i];
        return result;
    }

    Vector multiply(unsigned char multiplier) const {
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result.data[i] = data[i] * multiplier;
        return result;
    }

    // --- Порівняння ---
    bool isEqual(const Vector& other) const {
        if (size != other.size)
            return false;
        for (int i = 0; i < size; ++i)
            if (data[i] != other.data[i])
                return false;
        return true;
    }

    bool isNotEqual(const Vector& other) const {
        return !isEqual(other);
    }

    bool isGreaterThan(const Vector& other) const {
        int minSize = (size < other.size) ? size : other.size;
        for (int i = 0; i < minSize; ++i) {
            if (data[i] > other.data[i])
                return true;
            else if (data[i] < other.data[i])
                return false;
        }
        return size > other.size;
    }

    // --- Додаткове ---
    int getState() const { return state; }
    static int getObjectCount() { return objectCount; }
};

int Vector::objectCount = 0;

// --- main() ---
int main() {
    system("chcp 65001");
    cout << "Кількість об'єктів: " << Vector::getObjectCount() << endl;

    Vector v1;
    Vector v2(5);
    Vector v3(5, 7);

    v1.print();
    v2.print();
    v3.print();

    Vector v4 = v3;
    v4.print();

    v2.set(2, 99);
    v2.set(10, 5); // помилка
    cout << "Елемент [2] = " << v2.get(2) << ", Елемент [10] = " << v2.get(10) << endl;
    v2.print();

    Vector sum = v2.add(v3);
    Vector diff = v3.subtract(v2);
    Vector mult = v3.multiply(2);

    cout << "Сума:\n"; sum.print();
    cout << "Різниця:\n"; diff.print();
    cout << "Множення:\n"; mult.print();

    cout << "v2 == v3 " << (v2.isEqual(v3) ? "Так" : "Ні") << endl;
    cout << "v2 != v3 " << (v2.isNotEqual(v3) ? "Так" : "Ні") << endl;
    cout << "v3 > v2 " << (v3.isGreaterThan(v2) ? "Так" : "Ні") << endl;

    cout << "Кількість об'єктів: " << Vector::getObjectCount() << endl;
    return 0;
}


