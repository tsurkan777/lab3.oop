#include <iostream>
#include <cstdlib>
using namespace std;

class Vector {
private:
    short* data;
    int size;
    int state;
    static int count;

public:
    // Конструктор без параметрів
    Vector() {
        data = new short[1];
        if (data == nullptr) {
            state = 1;
        } else {
            data[0] = 0;
            size = 1;
            state = 0;
        }
        count++;
    }

    // Конструктор з одним параметром
    Vector(int n) {
        data = new short[n];
        if (data == nullptr) {
            state = 1;
        } else {
            for (int i = 0; i < n; i++) {
                data[i] = 0;
            }
            size = n;
            state = 0;
        }
        count++;
    }

    // Конструктор з двома параметрами
    Vector(int n, short value) {
        data = new short[n];
        if (data == nullptr) {
            state = 1;
        } else {
            for (int i = 0; i < n; i++) {
                data[i] = value;
            }
            size = n;
            state = 0;
        }
        count++;
    }

    // Конструктор копіювання
    Vector(const Vector& other) {
        data = new short[other.size];
        if (data == nullptr) {
            state = 1;
        } else {
            for (int i = 0; i < other.size; i++) {
                data[i] = other.data[i];
            }
            size = other.size;
            state = other.state;
        }
        count++;
    }

    // Оператор присвоєння
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            data = new short[other.size];
            if (data == nullptr) {
                state = 1;
            } else {
                for (int i = 0; i < other.size; i++) {
                    data[i] = other.data[i];
                }
                size = other.size;
                state = other.state;
            }
        }
        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] data;
        count--;
    }

    // Функція присвоєння значення елементу
    void set(int index, short value = 0) {
        if (index >= 0 && index < size) {
            data[index] = value;
            state = 0;
        } else {
            state = 2;
        }
    }

    // Функція отримання елементу
    short get(int index) {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            state = 2;
            return 0;
        }
    }

    // Функція друку
    void print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Функція додавання
    Vector add(Vector& other) {
        int minSize;
        if (size < other.size) {
            minSize = size;
        } else {
            minSize = other.size;
        }

        Vector result(minSize);
        for (int i = 0; i < minSize; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Функція віднімання
    Vector subtract(Vector& other) {
        int minSize;
        if (size < other.size) {
            minSize = size;
        } else {
            minSize = other.size;
        }

        Vector result(minSize);
        for (int i = 0; i < minSize; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Функція множення на число
    void multiply(unsigned char num) {
        for (int i = 0; i < size; i++) {
            data[i] = data[i] * num;
        }
    }

    // Функція порівняння більше
    bool isGreater(Vector& other) {
        int minSize;
        if (size < other.size) {
            minSize = size;
        } else {
            minSize = other.size;
        }

        for (int i = 0; i < minSize; i++) {
            if (data[i] <= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    // Функція рівності
    bool isEqual(Vector& other) {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }

        return true;
    }

    // Функція нерівності
    bool isNotEqual(Vector& other) {
        return !isEqual(other);
    }

    // Функція отримання стану
    int getState() {
        return state;
    }

    // Функція отримання розміру
    int getSize() {
        return size;
    }

    // Функція кількості об'єктів
    static int getCount() {
        return count;
    }
};

int Vector::count = 0;

// Тестування
int main() {
    system("chcp 65001");
    Vector v1;
    v1.print();

    Vector v2(5);
    v2.print();

    Vector v3(5, 7);
    v3.print();

    v3.set(2, 99);
    cout << "Елемент 2: " << v3.get(2) << endl;
    v3.print();

    Vector v4 = v3;
    v4.print();

    v4.multiply(2);
    v4.print();

    Vector v5 = v3.add(v4);
    v5.print();

    Vector v6 = v4.subtract(v3);
    v6.print();

    cout << "Кількість об'єктів: " << Vector::getCount() << endl;

    if (v3.isEqual(v4)) {
        cout << "Вектори рівні" << endl;
    } else {
        cout << "Вектори НЕ рівні" << endl;
    }

    if (v4.isGreater(v3)) {
        cout << "v4 більше за v3" << endl;
    } else {
        cout << "v4 не більше за v3" << endl;
    }

    return 0;
}

