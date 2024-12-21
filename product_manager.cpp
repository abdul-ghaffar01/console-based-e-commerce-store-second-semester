#ifndef PRODUCT_MANAGER
#define PRODUCT_MANAGER

#include "list.cpp"
#include "file handler.cpp"
#include "product.cpp"
#include <iostream>
using namespace std;

class ProductManager
{
private:
    List<Product> productCatalog;
    FileHandler fileHandler;

public:
    ProductManager(const string &filePath);
    void loadProductsFromFile();
    void saveProductsToFile();
    void addProduct(const Product &product);
    bool removeProduct(const string &productID);
    void displayCatalog() const;
    bool updateProduct(const string &productID, const Product &updatedProduct);
    List<Product> getAllProducts();
};

ProductManager::ProductManager(const string &filePath) : fileHandler(filePath)
{
    loadProductsFromFile();
}

void ProductManager::loadProductsFromFile()
{
    List<string> lines = fileHandler.readAllLines();
    for (int i = 0; i < lines.length(); ++i)
    {
        string line = lines.get(i);
        size_t pos = 0;
        string productID, productName, description;
        double price;
        int quantity;

        pos = line.find(",");
        productID = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        productName = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        price = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(",");
        quantity = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        description = line;

        Product product(productID, productName, price, quantity, description);
        productCatalog.push_back(product);
    }
}

void ProductManager::saveProductsToFile()
{
    List<string> lines;
    for (int i = 0; i < productCatalog.length(); ++i)
    {
        Product &product = productCatalog[i];
        string line = product.getProductID() + "," + product.getProductName() + "," +
                      to_string(product.getPrice()) + "," + to_string(product.getQuantity()) + "," +
                      product.getDescription();
        lines.push_back(line);
    }
    fileHandler.writeAllLines(lines);
}

void ProductManager::addProduct(const Product &product)
{
    productCatalog.push_back(product);
    saveProductsToFile();
}

bool ProductManager::removeProduct(const string &productID)
{
    for (int i = 0; i < productCatalog.length(); ++i)
    {
        if (productCatalog[i].getProductID() == productID)
        {
            productCatalog.removeAt(i);
            saveProductsToFile();
            return true;
        }
    }
    return false;
}

void ProductManager::displayCatalog() const
{
    if (productCatalog.length() <= 0)
    {
        cout << "No products to display.\n";
    }
    else
    {
        for (int i = 0; i < productCatalog.length(); ++i)
        {
            productCatalog[i].display();
            cout << endl;
        }
    }
}

bool ProductManager::updateProduct(const string &productID, const Product &updatedProduct)
{
    for (int i = 0; i < productCatalog.length(); ++i)
    {
        if (productCatalog[i].getProductID() == productID)
        {
            productCatalog[i] = updatedProduct;
            saveProductsToFile();
            return true;
        }
    }
    return false;
}

List<Product> ProductManager::getAllProducts(){
    return productCatalog;
}
#endif
