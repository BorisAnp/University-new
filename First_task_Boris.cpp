#include <iostream>
#include <cmath>
#include <clocale>  
using namespace std;

const double PI = 3.14159265358979323846; 

class Ellipse {
private:
    double h, k; // Координаты центра
    double a, b; // Большая и малая полуоси

    // Проверка корректности параметров
    void validate() {
        if (a < b) {
            swap(a, b);
            cout << "Предупреждение: Значения a и b были поменяны местами, так как a должно быть больше b.\n";
        }
    }

public:
    // Конструктор по умолчанию
    Ellipse() : h(0), k(0), a(1), b(1) {}

    // Конструктор с параметрами
    Ellipse(double h, double k, double a, double b) : h(h), k(k), a(a), b(b) {
        validate();
    }

    // Копирующий конструктор
    Ellipse(const Ellipse& other) : h(other.h), k(other.k), a(other.a), b(other.b) {}

    // Вычисление гиперпараметра c
    double calculateC() const {
        return sqrt(a * a - b * b);
    }

    // Координаты фокусов
    void getFoci() const {
        double c = calculateC();
        cout << "Фокусы: (" << h - c << ", " << k << ") и (" << h + c << ", " << k << ")\n";
    }

    // Метод для проверки принадлежности точки (x, y) эллипсу
    bool isInside(double x, double y) const {
        return (pow(x - h, 2) / (a * a) + pow(y - k, 2) / (b * b)) <= 1;
    }

    // Вычисление периметра (приближенно)
    double perimeter() const {
        return PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
    }

    // Вычисление площади
    double area() const {
        return PI * a * b;
    }

    // Сеттеры и геттеры
    void setCenter(double newH, double newK) { h = newH; k = newK; }
    void setAxes(double newA, double newB) {
        a = newA; b = newB;
        validate();
    }
    double getA() const { return a; }
    double getB() const { return b; }
    double getH() const { return h; }
    double getK() const { return k; }

    // Длина фокальной хорды (LR)
    double focalChord() const {
        return (2 * b * b) / a;
    }

    // Эксцентриситет
    double eccentricity() const {
        return calculateC() / a;
    }

    // Уравнение эллипса
    void printEquation() const {
        cout << "Уравнение эллипса: (x - " << h << ")^2 / " << a * a << " + (y - " << k << ")^2 / " << b * b << " = 1\n";
    }

    // Вычисление второй координаты y для заданной x
    double calculateY(double x) const {
        return k + b * sqrt(1 - pow((x - h) / a, 2));
    }

    // Вычисление второй координаты x для заданной y
    double calculateX(double y) const {
        return h + a * sqrt(1 - pow((y - k) / b, 2));
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Ellipse e(2, 3, 5, 3);

    // Вывод фокусов
    e.getFoci();

    // Вывод периметра и площади
    cout << "Периметр: " << e.perimeter() << "\n";
    cout << "Площадь: " << e.area() << "\n";

    // Проверка точки внутри эллипса
    cout << "Точка (3,3) внутри эллипса? " << (e.isInside(3, 3) ? "Да" : "Нет") << "\n";

    // Вывод уравнения эллипса
    e.printEquation();

    // Вывод эксцентриситета и фокальной хорды
    cout << "Эксцентриситет: " << e.eccentricity() << "\n";
    cout << "Длина фокальной хорды: " << e.focalChord() << "\n";

    // Пример вычисления второй координаты по первой
    double x = 3;
    cout << "Для x = " << x << ", y = " << e.calculateY(x) << "\n";

    double y = 2;
    cout << "Для y = " << y << ", x = " << e.calculateX(y) << "\n";

    return 0;
}
