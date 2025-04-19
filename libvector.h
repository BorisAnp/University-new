#ifndef LIBVECTOR_H
#define LIBVECTOR_H

#include <iostream>
#include <cmath>

class Quaternion {
private:
    double a, b, c, d;
public:
    // Конструкторы
    Quaternion();
    Quaternion(double real, double i, double j, double k);

    // Методы
    double norm() const;
    Quaternion conjugate() const;
    Quaternion normalize() const;
    Quaternion inverse() const;

    // Операции
    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator/(const Quaternion& q) const;
    double dot(const Quaternion& q) const;

    // Расстояние
    double euclideanDistance(const Quaternion& q) const;
    double chebyshevNorm(const Quaternion& q) const;

    // Вывод
    void print() const;
};

#endif