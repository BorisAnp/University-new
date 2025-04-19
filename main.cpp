#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

// ��������������� ���������� ������ Warehouse
class Warehouse;

// ����� Product
class Product {
private:
    std::string article;      // ������� (������, ������������ �������������, 13 �������� - ������� "W", ����� 9 ��������� ����, ��������)
    std::string name;         // �������� �������� (�� ����� 50 ��������)
    double price;            // ���� (� ������)

public:
    Product(const std::string& name, double price) : name(name), price(price) {
        generateArticle();
    }

    std::string getArticle() const {
        return article;
    }

    std::string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    void print() const {
        std::cout << "�������: " << article << std::endl;
        std::cout << "��������: " << name << std::endl;
        std::cout << "����: " << price << " ���." << std::endl;
    }

private:
    void generateArticle() {
        article = "W";
        for (int i = 0; i < 9; ++i) {
            article += std::to_string(rand() % 10);
        }
    }
};

// ����� Warehouse
class Warehouse {
private:
    std::string id;           // ������������� (������ ������ ����� 4 �������, ������ ������ 'W', ��������� - �����, ��������)
    std::string ownerCode;    // ��� ������������ ENUM (��� ����������� 3 ��������� ��������) - ���� ������� ��� string
    double latitude;        // ������ (�������)
    double longitude;       // ������� (�������)
    int capacity;           // ����������� (������������ ���������� ���������, ������� ����� ������� �����)
    std::vector<Product> products; // ������ ��� �������� ��������� �� ������

public:
    Warehouse(const std::string& id, const std::string& ownerCode, double latitude, double longitude, int capacity)
        : id(id), ownerCode(ownerCode), latitude(latitude), longitude(longitude), capacity(capacity) {
        if (id.length() != 4 || id[0] != 'W') {
            throw std::invalid_argument("������������� ������ ������ ���� ������ 4 ������� � ���������� � 'W'.");
        }
        for (size_t i = 1; i < id.length(); ++i) {
            if (!isdigit(id[i])) {
                throw std::invalid_argument("������������� ������ ������ ��������� ����� ����� ������� �������.");
            }
        }
        if (latitude < 19 || latitude > 169 || longitude < -180 || longitude > 180) {
            throw std::invalid_argument("������������ �������� ������ ��� �������.");
        }
    }

    std::string getId() const {
        return id;
    }

    std::string getOwnerCode() const {
        return ownerCode;
    }

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    int getCapacity() const {
        return capacity;
    }

    int getCurrentStockSize() const {
        return products.size();
    }

    const std::vector<Product>& getProducts() const {
        return products;
    }

    // ���������� �������� �� �����
    bool addProduct(const Product& product) {
        if (products.size() < capacity) {
            products.push_back(product);
            return true;
        }
        else {
            std::cout << "����� " << id << " ����������. ���������� �������� �������." << std::endl;
            return false;
        }
    }

    // �������� �������� �� ������ �� ��������
    bool removeProduct(const std::string& articleToRemove) {
        auto it = std::remove_if(products.begin(), products.end(),
            [&](const Product& p) { return p.getArticle() == articleToRemove; });
        if (it != products.end()) {
            products.erase(it, products.end());
            return true;
        }
        else {
            std::cout << "������� � ��������� " << articleToRemove << " �� ������ �� ������ " << id << "." << std::endl;
            return false;
        }
    }

    // ����� �������� �� ������ �� ��������
    const Product* findProduct(const std::string& articleToFind) const {
        for (const auto& product : products) {
            if (product.getArticle() == articleToFind) {
                return &product;
            }
        }
        return nullptr;
    }

    // ����� ���������� � ������ � ��� �������
    void print() const {
        std::cout << "--- �����: " << id << " ---" << std::endl;
        std::cout << "��� ���������: " << ownerCode << std::endl;
        std::cout << "������: " << latitude << std::endl;
        std::cout << "�������: " << longitude << std::endl;
        std::cout << "�����������: " << capacity << std::endl;
        std::cout << "������� ���������� �������: " << products.size() << std::endl;
        std::cout << "--- ������ �� ������ ---" << std::endl;
        if (products.empty()) {
            std::cout << "����� ����." << std::endl;
        }
        else {
            for (const auto& product : products) {
                product.print();
                std::cout << "---" << std::endl;
            }
        }
    }

    // ������-������� (��� ����������� ��������� ����� ������)
    void setOwnerCode(const std::string& newOwnerCode) {
        ownerCode = newOwnerCode;
    }

    void setLatitude(double newLatitude) {
        if (newLatitude >= 19 && newLatitude <= 169) {
            latitude = newLatitude;
        }
        else {
            std::cerr << "������: ������������ �������� ������." << std::endl;
        }
    }

    void setLongitude(double newLongitude) {
        if (newLongitude >= -180 && newLongitude <= 180) {
            longitude = newLongitude;
        }
        else {
            std::cerr << "������: ������������ �������� �������." << std::endl;
        }
    }

    void setCapacity(int newCapacity) {
        if (newCapacity >= products.size()) {
            capacity = newCapacity;
        }
        else {
            std::cerr << "������: ����� ����������� �� ����� ���� ������ �������� ���������� �������." << std::endl;
        }
    }
};

// ������� ��� ������� ���������� ����� ����� �������� (�����������)
double calculateDistance(const Warehouse& wh1, const Warehouse& wh2) {
    double lat1Rad = wh1.getLatitude() * M_PI / 180.0;
    double lon1Rad = wh1.getLongitude() * M_PI / 180.0;
    double lat2Rad = wh2.getLatitude() * M_PI / 180.0;
    double lon2Rad = wh2.getLongitude() * M_PI / 180.0;

    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;

    double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
        cos(lat1Rad) * cos(lat2Rad) *
        sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    // ������ ����� � ���������� (�����������)
    double R = 6371.0;

    return R * c;
}

int main() {
    srand(time(0)); // ������������� ���������� ��������� �����

    // ������ ������������� �������
    try {
        Warehouse warehouse1("W123", "OWN1", 55.75, 37.62, 10);
        Warehouse warehouse2("W456", "OWN2", 59.93, 30.30, 5);

        Product product1("������", 50.0);
        Product product2("������", 80.0);
        Product product3("����", 30.0);

        warehouse1.addProduct(product1);
        warehouse1.addProduct(product2);
        warehouse2.addProduct(product3);
        warehouse2.addProduct(Product("��������", 70.0));
        warehouse2.addProduct(Product("�����", 60.0));
        warehouse2.addProduct(Product("���", 200.0)); // ����� warehouse2 ����������

        warehouse1.print();
        warehouse2.print();

        std::cout << std::endl;
        const Product* foundProduct = warehouse1.findProduct("W" + std::to_string(product1.getArticle().substr(1)));
        if (foundProduct) {
            std::cout << "������ ������� �� ������ 1:" << std::endl;
            foundProduct->print();
        }
        else {
            std::cout << "������� �� ������ �� ������ 1." << std::endl;
        }

        warehouse1.removeProduct("W" + std::to_string(product2.getArticle().substr(1)));
        std::cout << "\n����� �������� �������� �� ������ 1:" << std::endl;
        warehouse1.print();

        std::cout << "\n���������� ����� �������� 1 � 2: " << calculateDistance(warehouse1, warehouse2) << " ��." << std::endl;

        warehouse1.setCapacity(15); // ����������� ����������� ������ 1
        warehouse1.addProduct(Product("�����", 65.0));
        std::cout << "\n����� 1 ����� ���������� ����������� � ���������� ������:" << std::endl;
        warehouse1.print();

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "������: " << e.what() << std::endl;
    }

    return 0;
}