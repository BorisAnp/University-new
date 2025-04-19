#include "libvector.h"

int main() {
    Quaternion q1(1, 2, 3, 4);
    Quaternion q2(2, 3, 4, 5);

    std::cout << "q1: "; q1.print();
    std::cout << "q2: "; q2.print();

    Quaternion sum = q1 + q2;
    std::cout << "q1 + q2: "; sum.print();

    Quaternion product = q1 * q2;
    std::cout << "q1 * q2: "; product.print();

    std::cout << "Euclidean Distance: " << q1.euclideanDistance(q2) << std::endl;
    std::cout << "Chebyshev Norm: " << q1.chebyshevNorm(q2) << std::endl;

    return 0;
}
