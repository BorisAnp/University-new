#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

// Класс для представления одного полинома
class Polynomial {
private:
    vector<double> coefficients; // Коэффициенты полинома

public:
    // Конструктор по умолчанию
    Polynomial() {}

    // Конструктор по параметрам
    Polynomial(const vector<double>& coeffs) : coefficients(coeffs) {}

    // Конструктор копирования
    Polynomial(const Polynomial& other) : coefficients(other.coefficients) {}

    // Функция для определения степени полинома
    int degree() const {
        return coefficients.size() - 1;
    }

    // Функция для получения коэффициента для конкретной степени
    double getCoefficient(int power) const {
        if (power < 0 || power > degree()) {
            throw out_of_range("Степень выходит за пределы полинома.");
        }
        return coefficients[power];
    }

    // Функция для установки коэффициента для конкретной степени
    void setCoefficient(int power, double value) {
        if (power < 0 || power > degree()) {
            throw out_of_range("Степень выходит за пределы полинома.");
        }
        coefficients[power] = value;
    }

    // Функция для вычисления значения полинома для заданного x
    double evaluate(double x) const {
        double result = 0.0;
        for (int i = 0; i <= degree(); i++) {
            result += coefficients[i] * pow(x, i);
        }
        return result;
    }

    // Вывод полинома
    void print() const {
        for (int i = degree(); i >= 0; i--) {
            if (i != degree()) {
                cout << (coefficients[i] >= 0 ? " + " : " - ");
            }
            cout << abs(coefficients[i]);
            if (i > 0) {
                cout << "x^" << i;
            }
        }
        cout << endl;
    }
};

// Класс для работы с вектором полиномов
class VectPolynomial {
private:
    vector<Polynomial> polynomials;

public:
    // Конструктор
    VectPolynomial(const vector<Polynomial>& polys) : polynomials(polys) {}

    // Функция для получения количества полиномов
    int getCount() const {
        return polynomials.size();
    }

    // Функция для выполнения операции сложения между полиномами
    VectPolynomial add(const VectPolynomial& other) const {
        if (polynomials.size() != other.getCount()) {
            throw invalid_argument("Полиномы разных размеров.");
        }

        vector<Polynomial> resultPolynomials;
        for (size_t i = 0; i < polynomials.size(); i++) {
            vector<double> resultCoefficients;
            int maxDegree = max(polynomials[i].degree(), other.polynomials[i].degree());
            resultCoefficients.resize(maxDegree + 1, 0);

            // Сложение соответствующих полиномов
            for (int j = 0; j <= maxDegree; j++) {
                resultCoefficients[j] = polynomials[i].getCoefficient(j) + other.polynomials[i].getCoefficient(j);
            }

            resultPolynomials.push_back(Polynomial(resultCoefficients));
        }
        return VectPolynomial(resultPolynomials);
    }

    // Функция для вывода всех полиномов в векторе
    void printAll() const {
        for (const auto& poly : polynomials) {
            poly.print();
        }
    }

    // Функция для обработки четных и нечетных полиномов
    void processEvenOddPolynomials() const {
        vector<Polynomial> oddPolys, evenPolys;

        // Разделяем полиномы на четные и нечетные
        for (const auto& poly : polynomials) {
            if (poly.degree() % 2 == 0) {
                evenPolys.push_back(poly);
            }
            else {
                oddPolys.push_back(poly);
            }
        }

        // Выводим четные полиномы
        cout << "Четные полиномы:" << endl;
        for (const auto& poly : evenPolys) {
            poly.print();
        }

        // Выводим нечетные полиномы
        cout << "Нечетные полиномы:" << endl;
        for (const auto& poly : oddPolys) {
            poly.print();
        }
    }
};

// Основная программа
int main() {
    setlocale(LC_ALL, "Russian");
    // Пример создания полиномов и их работы
    Polynomial p1({ 1, -2, 3 }); // p1 = 1 - 2x + 3x^2 (степень 2, четный)
    Polynomial p2({ 4, 0, -1, 2 }); // p2 = 4 - x^2 + 2x^3 (степень 3, нечетный)
    Polynomial p3({ 2, 3, 0, -1 }); // p3 = 2 + 3x - x^3 (степень 3, нечетный)
    Polynomial p4({ 5, -6, 7, -8 }); // p4 = 5 - 6x + 7x^2 - 8x^3 (степень 3, нечетный)

    // Создаем вектор полиномов
    vector<Polynomial> polys = { p1, p2, p3, p4 };
    VectPolynomial vectPolys(polys);

    cout << "Полиномы в векторе: " << endl;
    vectPolys.printAll();

    // Разделяем и выводим четные и нечетные полиномы
    vectPolys.processEvenOddPolynomials();

    // Сложение полиномов
    VectPolynomial result = vectPolys.add(vectPolys);
    cout << "Результат сложения полиномов: " << endl;
    result.printAll();

    // Вычисление значения полинома p1 при x = 2
    cout << "Значение p1 при x = 2: " << p1.evaluate(2) << endl;

    return 0;
}
