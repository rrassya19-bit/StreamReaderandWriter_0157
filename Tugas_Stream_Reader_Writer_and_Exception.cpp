#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <array>
using namespace std;

// =============================================
//          KELAS TOKO ELEKTRONIK (OOP)
// =============================================
class TokoElektronik 
{
private:
    // Atribut private: array berkapasitas 3 elemen (enkapsulasi)
    array<string, 3> etalase;

public:
    // Constructor: mengisi data awal ke dalam array secara otomatis
    TokoElektronik() 
    {
        etalase[0] = "Laptop ASUS ROG";
        etalase[1] = "Keyboard Mechanical";
        etalase[2] = "Mouse Wireless";
    }
};