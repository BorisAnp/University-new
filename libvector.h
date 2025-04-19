#ifndef LIBVECTOR_H
#define LIBVECTOR_H

#include <iostream>
#include <cmath>

class Quaternion {
private:
    double a, b, c, d;
public:
    // ������������
    Quaternion();
    Quaternion(double real, double i, double j, double k);

    // ������
    double norm() const;
    Quaternion conjugate() const;
    Quaternion normalize() const;
    Quaternion inverse() const;

    // ��������
    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator/(const Quaternion& q) const;
    double dot(const Quaternion& q) const;

    // ����������
    double euclideanDistance(const Quaternion& q) const;
    double chebyshevNorm(const Quaternion& q) const;

    // �����
    void print() const;
};

#endif