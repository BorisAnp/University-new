#include <iostream>
#include <cmath>
#include <clocale>  
using namespace std;

const double PI = 3.14159265358979323846; 

class Ellipse {
private:
    double h, k; // ���������� ������
    double a, b; // ������� � ����� �������

    // �������� ������������ ����������
    void validate() {
        if (a < b) {
            swap(a, b);
            cout << "��������������: �������� a � b ���� �������� �������, ��� ��� a ������ ���� ������ b.\n";
        }
    }

public:
    // ����������� �� ���������
    Ellipse() : h(0), k(0), a(1), b(1) {}

    // ����������� � �����������
    Ellipse(double h, double k, double a, double b) : h(h), k(k), a(a), b(b) {
        validate();
    }

    // ���������� �����������
    Ellipse(const Ellipse& other) : h(other.h), k(other.k), a(other.a), b(other.b) {}

    // ���������� �������������� c
    double calculateC() const {
        return sqrt(a * a - b * b);
    }

    // ���������� �������
    void getFoci() const {
        double c = calculateC();
        cout << "������: (" << h - c << ", " << k << ") � (" << h + c << ", " << k << ")\n";
    }

    // ����� ��� �������� �������������� ����� (x, y) �������
    bool isInside(double x, double y) const {
        return (pow(x - h, 2) / (a * a) + pow(y - k, 2) / (b * b)) <= 1;
    }

    // ���������� ��������� (�����������)
    double perimeter() const {
        return PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
    }

    // ���������� �������
    double area() const {
        return PI * a * b;
    }

    // ������� � �������
    void setCenter(double newH, double newK) { h = newH; k = newK; }
    void setAxes(double newA, double newB) {
        a = newA; b = newB;
        validate();
    }
    double getA() const { return a; }
    double getB() const { return b; }
    double getH() const { return h; }
    double getK() const { return k; }

    // ����� ��������� ����� (LR)
    double focalChord() const {
        return (2 * b * b) / a;
    }

    // ��������������
    double eccentricity() const {
        return calculateC() / a;
    }

    // ��������� �������
    void printEquation() const {
        cout << "��������� �������: (x - " << h << ")^2 / " << a * a << " + (y - " << k << ")^2 / " << b * b << " = 1\n";
    }

    // ���������� ������ ���������� y ��� �������� x
    double calculateY(double x) const {
        return k + b * sqrt(1 - pow((x - h) / a, 2));
    }

    // ���������� ������ ���������� x ��� �������� y
    double calculateX(double y) const {
        return h + a * sqrt(1 - pow((y - k) / b, 2));
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Ellipse e(2, 3, 5, 3);

    // ����� �������
    e.getFoci();

    // ����� ��������� � �������
    cout << "��������: " << e.perimeter() << "\n";
    cout << "�������: " << e.area() << "\n";

    // �������� ����� ������ �������
    cout << "����� (3,3) ������ �������? " << (e.isInside(3, 3) ? "��" : "���") << "\n";

    // ����� ��������� �������
    e.printEquation();

    // ����� ��������������� � ��������� �����
    cout << "��������������: " << e.eccentricity() << "\n";
    cout << "����� ��������� �����: " << e.focalChord() << "\n";

    // ������ ���������� ������ ���������� �� ������
    double x = 3;
    cout << "��� x = " << x << ", y = " << e.calculateY(x) << "\n";

    double y = 2;
    cout << "��� y = " << y << ", x = " << e.calculateX(y) << "\n";

    return 0;
}
