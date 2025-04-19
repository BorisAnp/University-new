#include "libvector.h"

Quaternion::Quaternion() : a(1), b(0), c(0), d(0) {}
Quaternion::Quaternion(double real, double i, double j, double k) : a(real), b(i), c(j), d(k) {}

double Quaternion::norm() const {
    return sqrt(a * a + b * b + c * c + d * d);
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(a, -b, -c, -d);
}

Quaternion Quaternion::normalize() const {
    double n = norm();
    return Quaternion(a / n, b / n, c / n, d / n);
}

Quaternion Quaternion::inverse() const {
    Quaternion conj = conjugate();
    double n = norm();
    return Quaternion(conj.a / (n * n), conj.b / (n * n), conj.c / (n * n), conj.d / (n * n));
}

Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion(a + q.a, b + q.b, c + q.c, d + q.d);
}

Quaternion Quaternion::operator-(const Quaternion& q) const {
    return Quaternion(a - q.a, b - q.b, c - q.c, d - q.d);
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(
        a * q.a - b * q.b - c * q.c - d * q.d,
        a * q.b + b * q.a + c * q.d - d * q.c,
        a * q.c - b * q.d + c * q.a + d * q.b,
        a * q.d + b * q.c - c * q.b + d * q.a
    );
}

Quaternion Quaternion::operator/(const Quaternion& q) const {
    return *this * q.inverse();
}

double Quaternion::dot(const Quaternion& q) const {
    return a * q.a + b * q.b + c * q.c + d * q.d;
}

double Quaternion::euclideanDistance(const Quaternion& q) const {
    return sqrt(pow(a - q.a, 2) + pow(b - q.b, 2) + pow(c - q.c, 2) + pow(d - q.d, 2));
}

double Quaternion::chebyshevNorm(const Quaternion& q) const {
    return std::max({ fabs(a - q.a), fabs(b - q.b), fabs(c - q.c), fabs(d - q.d) });
}

void Quaternion::print() const {
    std::cout << "(" << a << ", " << b << "i, " << c << "j, " << d << "k)" << std::endl;
}
