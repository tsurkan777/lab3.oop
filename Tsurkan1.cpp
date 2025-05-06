#include <iostream>

#include <string>

using namespace std;

class Parallelogram {
private:
    double base;
    double height;
    double side;
    string color;

public:
    // Конструктор за замовчуванням
    Parallelogram() {
        base = 1.0;
        height = 1.0;
        side = 1.0;
        color = "білий";
    }

    // Конструктор із параметрами
    Parallelogram(double b, double h, double s, string c) {
        setBase(b);
        setHeight(h);
        setSide(s);
        setColor(c);
    }

    // Сетери з перевіркою
    void setBase(double b) {
        if (b > 0)
            base = b;
        else
            cout << "Помилка: основа повинна бути додатною." << endl;
    }

    void setHeight(double h) {
        if (h > 0)
            height = h;
        else
            cout << "Помилка: висота повинна бути додатною." << endl;
    }

    void setSide(double s) {
        if (s > 0)
            side = s;
        else
            cout << "Помилка: бічна сторона повинна бути додатною." << endl;
    }

    void setColor(string c) {
        if (!c.empty())
            color = c;
        else
            cout << "Помилка: колір не може бути порожнім." << endl;
    }

    // Геттери
    double getBase() const { return base; }
    double getHeight() const { return height; }
    double getSide() const { return side; }
    string getColor() const { return color; }

    double area() const {
        return base * height;
    }

    double perimeter() const {
        return 2 * (base + side);
    }

    void print() const {
        cout << "Паралелограм: "
             << "\n  Основа: " << base
             << "\n  Висота: " << height
             << "\n  Бічна сторона: " << side
             << "\n  Колір: " << color
             << "\n  Площа: " << area()
             << "\n  Периметр: " << perimeter()
             << endl;
    }
};


int main() {
    system("chcp 65001");
    // Тест конструктора за замовчуванням
    Parallelogram p1;
    cout << "Тест конструктора за замовчуванням:" << endl;
    p1.print();

    // Тест конструктора з параметрами
    Parallelogram p2(5.0, 3.0, 4.0, "синій");
    cout << "\nТест конструктора з параметрами:" << endl;
    p2.print();

    // Тест геттерів і сеттерів
    cout << "\nЗміна параметрів об'єкта p1:" << endl;
    p1.setBase(6.0);
    p1.setHeight(4.0);
    p1.setSide(5.0);
    p1.setColor("зелений");
    p1.print();

    // Тест некоректних значень
    cout << "\nСпроба встановити некоректні значення:" << endl;
    p1.setBase(-2.0);
    p1.setHeight(0.0);
    p1.setSide(-1.0);
    p1.setColor("");

    return 0;
}
