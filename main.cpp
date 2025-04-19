#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

// Предварительное объявление класса Warehouse
class Warehouse;

// Класс Product
class Product {
private:
    std::string article;      // Артикул (строка, генерируется автоматически, 13 символов - префикс "W", затем 9 случайных цифр, уникален)
    std::string name;         // Название продукта (не более 50 символов)
    double price;            // Цена (в рублях)

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
        std::cout << "Артикул: " << article << std::endl;
        std::cout << "Название: " << name << std::endl;
        std::cout << "Цена: " << price << " руб." << std::endl;
    }

private:
    void generateArticle() {
        article = "W";
        for (int i = 0; i < 9; ++i) {
            article += std::to_string(rand() % 10);
        }
    }
};

// Класс Warehouse
class Warehouse {
private:
    std::string id;           // Идентификатор (строка длиной ровно 4 символа, первый символ 'W', остальные - цифры, уникален)
    std::string ownerCode;    // Код пользователя ENUM (для определения 3 возможных значений) - пока оставим как string
    double latitude;        // Широта (градусы)
    double longitude;       // Долгота (градусы)
    int capacity;           // Вместимость (максимальное количество продуктов, которые может хранить склад)
    std::vector<Product> products; // Вектор для хранения продуктов на складе

public:
    Warehouse(const std::string& id, const std::string& ownerCode, double latitude, double longitude, int capacity)
        : id(id), ownerCode(ownerCode), latitude(latitude), longitude(longitude), capacity(capacity) {
        if (id.length() != 4 || id[0] != 'W') {
            throw std::invalid_argument("Идентификатор склада должен быть длиной 4 символа и начинаться с 'W'.");
        }
        for (size_t i = 1; i < id.length(); ++i) {
            if (!isdigit(id[i])) {
                throw std::invalid_argument("Идентификатор склада должен содержать цифры после первого символа.");
            }
        }
        if (latitude < 19 || latitude > 169 || longitude < -180 || longitude > 180) {
            throw std::invalid_argument("Некорректные значения широты или долготы.");
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

    // Добавление продукта на склад
    bool addProduct(const Product& product) {
        if (products.size() < capacity) {
            products.push_back(product);
            return true;
        }
        else {
            std::cout << "Склад " << id << " переполнен. Невозможно добавить продукт." << std::endl;
            return false;
        }
    }

    // Удаление продукта со склада по артикулу
    bool removeProduct(const std::string& articleToRemove) {
        auto it = std::remove_if(products.begin(), products.end(),
            [&](const Product& p) { return p.getArticle() == articleToRemove; });
        if (it != products.end()) {
            products.erase(it, products.end());
            return true;
        }
        else {
            std::cout << "Продукт с артикулом " << articleToRemove << " не найден на складе " << id << "." << std::endl;
            return false;
        }
    }

    // Поиск продукта на складе по артикулу
    const Product* findProduct(const std::string& articleToFind) const {
        for (const auto& product : products) {
            if (product.getArticle() == articleToFind) {
                return &product;
            }
        }
        return nullptr;
    }

    // Вывод информации о складе и его товарах
    void print() const {
        std::cout << "--- Склад: " << id << " ---" << std::endl;
        std::cout << "Код владельца: " << ownerCode << std::endl;
        std::cout << "Широта: " << latitude << std::endl;
        std::cout << "Долгота: " << longitude << std::endl;
        std::cout << "Вместимость: " << capacity << std::endl;
        std::cout << "Текущее количество товаров: " << products.size() << std::endl;
        std::cout << "--- Товары на складе ---" << std::endl;
        if (products.empty()) {
            std::cout << "Склад пуст." << std::endl;
        }
        else {
            for (const auto& product : products) {
                product.print();
                std::cout << "---" << std::endl;
            }
        }
    }

    // Методы-сеттеры (для возможности изменения полей склада)
    void setOwnerCode(const std::string& newOwnerCode) {
        ownerCode = newOwnerCode;
    }

    void setLatitude(double newLatitude) {
        if (newLatitude >= 19 && newLatitude <= 169) {
            latitude = newLatitude;
        }
        else {
            std::cerr << "Ошибка: Некорректное значение широты." << std::endl;
        }
    }

    void setLongitude(double newLongitude) {
        if (newLongitude >= -180 && newLongitude <= 180) {
            longitude = newLongitude;
        }
        else {
            std::cerr << "Ошибка: Некорректное значение долготы." << std::endl;
        }
    }

    void setCapacity(int newCapacity) {
        if (newCapacity >= products.size()) {
            capacity = newCapacity;
        }
        else {
            std::cerr << "Ошибка: Новая вместимость не может быть меньше текущего количества товаров." << std::endl;
        }
    }
};

// Функция для расчета расстояния между двумя складами (приближенно)
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

    // Радиус Земли в километрах (приближенно)
    double R = 6371.0;

    return R * c;
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    // Пример использования классов
    try {
        Warehouse warehouse1("W123", "OWN1", 55.75, 37.62, 10);
        Warehouse warehouse2("W456", "OWN2", 59.93, 30.30, 5);

        Product product1("Яблоко", 50.0);
        Product product2("Молоко", 80.0);
        Product product3("Хлеб", 30.0);

        warehouse1.addProduct(product1);
        warehouse1.addProduct(product2);
        warehouse2.addProduct(product3);
        warehouse2.addProduct(Product("Апельсин", 70.0));
        warehouse2.addProduct(Product("Банан", 60.0));
        warehouse2.addProduct(Product("Сыр", 200.0)); // Склад warehouse2 переполнен

        warehouse1.print();
        warehouse2.print();

        std::cout << std::endl;
        const Product* foundProduct = warehouse1.findProduct("W" + std::to_string(product1.getArticle().substr(1)));
        if (foundProduct) {
            std::cout << "Найден продукт на складе 1:" << std::endl;
            foundProduct->print();
        }
        else {
            std::cout << "Продукт не найден на складе 1." << std::endl;
        }

        warehouse1.removeProduct("W" + std::to_string(product2.getArticle().substr(1)));
        std::cout << "\nПосле удаления продукта из склада 1:" << std::endl;
        warehouse1.print();

        std::cout << "\nРасстояние между складами 1 и 2: " << calculateDistance(warehouse1, warehouse2) << " км." << std::endl;

        warehouse1.setCapacity(15); // Увеличиваем вместимость склада 1
        warehouse1.addProduct(Product("Груша", 65.0));
        std::cout << "\nСклад 1 после увеличения вместимости и добавления товара:" << std::endl;
        warehouse1.print();

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}