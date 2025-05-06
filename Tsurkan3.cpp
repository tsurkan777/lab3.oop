
#include <iostream>

using namespace std;

class Matrix {
private:
    short* data;
    int rows, cols;
    int state; // 0 - ОК, 1 - помилка пам’яті, 2 - вихід за межі
    static int objectCount;

    int index(int i, int j) const {
        return i * cols + j;
    }

public:
    // --- Конструктори ---
    Matrix() {
        rows = cols = 4;
        data = new(nothrow) short[rows * cols];
        if (!data) {
            state = 1;
        } else {
            for (int i = 0; i < rows * cols; ++i)
                data[i] = 0;
            state = 0;
        }
        objectCount++;
    }

    Matrix(int n) {
        rows = cols = n;
        data = new(nothrow) short[n * n];
        if (!data) {
            state = 1;
        } else {
            for (int i = 0; i < n * n; ++i)
                data[i] = 0;
            state = 0;
        }
        objectCount++;
    }

    Matrix(int n, int m, short value) {
        rows = n;
        cols = m;
        data = new(nothrow) short[n * m];
        if (!data) {
            state = 1;
        } else {
            for (int i = 0; i < n * m; ++i)
                data[i] = value;
            state = 0;
        }
        objectCount++;
    }

    // --- Конструктор копій ---
    Matrix(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;
        data = new(nothrow) short[rows * cols];
        if (!data) {
            state = 1;
        } else {
            for (int i = 0; i < rows * cols; ++i)
                data[i] = other.data[i];
            state = other.state;
        }
        objectCount++;
    }

    // --- Оператор присвоєння ---
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] data;
            rows = other.rows;
            cols = other.cols;
            data = new(nothrow) short[rows * cols];
            if (!data) {
                state = 1;
            } else {
                for (int i = 0; i < rows * cols; ++i)
                    data[i] = other.data[i];
                state = other.state;
            }
        }
        return *this;
    }

    // --- Деструктор ---
    ~Matrix() {
        delete[] data;
        objectCount--;
    }

    // --- Встановити значення ---
    void set(int i, int j, short value = 0) {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            state = 2;
        } else {
            data[index(i, j)] = value;
            state = 0;
        }
    }

    // --- Отримати значення ---
    short get(int i, int j) {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            state = 2;
            return 0;
        }
        state = 0;
        return data[index(i, j)];
    }

    // --- Друк ---
    void print() const {
        cout << "Matrix (" << rows << "x" << cols << "):" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                cout << data[i * cols + j] << " ";
            cout << endl;
        }
        cout << "State: " << state << endl;
    }

    // --- Арифметичні операції ---
    Matrix add(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            return Matrix(); // пустий 4x4 з нулями
        Matrix result(rows, cols, 0);
        for (int i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    Matrix subtract(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            return Matrix();
        Matrix result(rows, cols, 0);
        for (int i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    Matrix multiply(const Matrix& other) const {
        if (cols != other.rows)
            return Matrix();
        Matrix result(rows, other.cols, 0);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i * other.cols + j] += data[i * cols + k] * other.data[k * other.cols + j];
                }
            }
        }
        return result;
    }

    Matrix multiply(short scalar) const {
        Matrix result(rows, cols, 0);
        for (int i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] * scalar;
        return result;
    }

    // --- Порівняння ---
    bool isEqual(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            return false;
        for (int i = 0; i < rows * cols; ++i)
            if (data[i] != other.data[i])
                return false;
        return true;
    }

    bool isNotEqual(const Matrix& other) const {
        return !isEqual(other);
    }

    bool isGreaterThan(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            return false;
        for (int i = 0; i < rows * cols; ++i) {
            if (data[i] > other.data[i])
                return true;
            else if (data[i] < other.data[i])
                return false;
        }
        return false;
    }

    // --- Статичні функції ---
    int getState() const { return state; }
    static int getObjectCount() { return objectCount; }
};

int Matrix::objectCount = 0;

int main() {
    system("chcp 65001");

    cout << "Об'єктів: " << Matrix::getObjectCount() << endl;

    // Конструктор без параметрів
    Matrix a;
    // Конструктор з одним параметром (n x n)
    Matrix b(3);
    // Конструктор з трьома параметрами (n x m з value)
    Matrix c(3, 3, 2);

    cout << "Матриця a:" << endl;
    a.print();
    cout << "Матриця b:" << endl;
    b.print();
    cout << "Матриця c:" << endl;
    c.print();

    // Конструктор копіювання
    Matrix d = c;
    d.set(1, 1, 9);  // Функція set з індексами
    cout << "Матриця d (копія c з зміненим елементом):" << endl;
    d.print();

    // Перевірка функції get
    cout << "Елемент d(1,1): " << d.get(1, 1) << endl;

    // Операція присвоєння
    Matrix e;
    e = d;
    cout << "Матриця e (присвоєна з d):" << endl;
    e.print();

    // Арифметичні операції
    Matrix sum = b.add(c);
    Matrix diff = c.subtract(b);
    Matrix mult = c.multiply(d);
    Matrix scaled = c.multiply(3);

    cout << "Сума (b + c):" << endl;
    sum.print();
    cout << "Різниця (c - b):" << endl;
    diff.print();
    cout << "Множення матриць (c * d):" << endl;
    mult.print();
    cout << "Множення на скаляр (c * 3):" << endl;
    scaled.print();

    // Порівняння
    cout << "c == d ? " << (c.isEqual(d) ? "Так" : "Ні") << endl;
    cout << "c != d ? " << (c.isNotEqual(d) ? "Так" : "Ні") << endl;
    cout << "c > b ? " << (c.isGreaterThan(b) ? "Так" : "Ні") << endl;


    // Перевірка об’єктів
    cout << "Об'єктів: " << Matrix::getObjectCount() << endl;

    return 0;
}

