#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

// ����� ��� ������������� ������ ��������
class Polynomial {
private:
    vector<double> coefficients; // ������������ ��������

public:
    // ����������� �� ���������
    Polynomial() {}

    // ����������� �� ����������
    Polynomial(const vector<double>& coeffs) : coefficients(coeffs) {}

    // ����������� �����������
    Polynomial(const Polynomial& other) : coefficients(other.coefficients) {}

    // ������� ��� ����������� ������� ��������
    int degree() const {
        return coefficients.size() - 1;
    }

    // ������� ��� ��������� ������������ ��� ���������� �������
    double getCoefficient(int power) const {
        if (power < 0 || power > degree()) {
            throw out_of_range("������� ������� �� ������� ��������.");
        }
        return coefficients[power];
    }

    // ������� ��� ��������� ������������ ��� ���������� �������
    void setCoefficient(int power, double value) {
        if (power < 0 || power > degree()) {
            throw out_of_range("������� ������� �� ������� ��������.");
        }
        coefficients[power] = value;
    }

    // ������� ��� ���������� �������� �������� ��� ��������� x
    double evaluate(double x) const {
        double result = 0.0;
        for (int i = 0; i <= degree(); i++) {
            result += coefficients[i] * pow(x, i);
        }
        return result;
    }

    // ����� ��������
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

// ����� ��� ������ � �������� ���������
class VectPolynomial {
private:
    vector<Polynomial> polynomials;

public:
    // �����������
    VectPolynomial(const vector<Polynomial>& polys) : polynomials(polys) {}

    // ������� ��� ��������� ���������� ���������
    int getCount() const {
        return polynomials.size();
    }

    // ������� ��� ���������� �������� �������� ����� ����������
    VectPolynomial add(const VectPolynomial& other) const {
        if (polynomials.size() != other.getCount()) {
            throw invalid_argument("�������� ������ ��������.");
        }

        vector<Polynomial> resultPolynomials;
        for (size_t i = 0; i < polynomials.size(); i++) {
            vector<double> resultCoefficients;
            int maxDegree = max(polynomials[i].degree(), other.polynomials[i].degree());
            resultCoefficients.resize(maxDegree + 1, 0);

            // �������� ��������������� ���������
            for (int j = 0; j <= maxDegree; j++) {
                resultCoefficients[j] = polynomials[i].getCoefficient(j) + other.polynomials[i].getCoefficient(j);
            }

            resultPolynomials.push_back(Polynomial(resultCoefficients));
        }
        return VectPolynomial(resultPolynomials);
    }

    // ������� ��� ������ ���� ��������� � �������
    void printAll() const {
        for (const auto& poly : polynomials) {
            poly.print();
        }
    }

    // ������� ��� ��������� ������ � �������� ���������
    void processEvenOddPolynomials() const {
        vector<Polynomial> oddPolys, evenPolys;

        // ��������� �������� �� ������ � ��������
        for (const auto& poly : polynomials) {
            if (poly.degree() % 2 == 0) {
                evenPolys.push_back(poly);
            }
            else {
                oddPolys.push_back(poly);
            }
        }

        // ������� ������ ��������
        cout << "������ ��������:" << endl;
        for (const auto& poly : evenPolys) {
            poly.print();
        }

        // ������� �������� ��������
        cout << "�������� ��������:" << endl;
        for (const auto& poly : oddPolys) {
            poly.print();
        }
    }
};

// �������� ���������
int main() {
    setlocale(LC_ALL, "Russian");
    // ������ �������� ��������� � �� ������
    Polynomial p1({ 1, -2, 3 }); // p1 = 1 - 2x + 3x^2 (������� 2, ������)
    Polynomial p2({ 4, 0, -1, 2 }); // p2 = 4 - x^2 + 2x^3 (������� 3, ��������)
    Polynomial p3({ 2, 3, 0, -1 }); // p3 = 2 + 3x - x^3 (������� 3, ��������)
    Polynomial p4({ 5, -6, 7, -8 }); // p4 = 5 - 6x + 7x^2 - 8x^3 (������� 3, ��������)

    // ������� ������ ���������
    vector<Polynomial> polys = { p1, p2, p3, p4 };
    VectPolynomial vectPolys(polys);

    cout << "�������� � �������: " << endl;
    vectPolys.printAll();

    // ��������� � ������� ������ � �������� ��������
    vectPolys.processEvenOddPolynomials();

    // �������� ���������
    VectPolynomial result = vectPolys.add(vectPolys);
    cout << "��������� �������� ���������: " << endl;
    result.printAll();

    // ���������� �������� �������� p1 ��� x = 2
    cout << "�������� p1 ��� x = 2: " << p1.evaluate(2) << endl;

    return 0;
}
