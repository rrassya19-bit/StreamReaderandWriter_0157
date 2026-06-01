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
    array<string, 3> etalase;

public:
    TokoElektronik() 
    {
        etalase[0] = "Laptop ASUS ROG";
        etalase[1] = "Keyboard Mechanical";
        etalase[2] = "Mouse Wireless";
    }

    string ambilBarang(size_t nomorRak) 
    {
        try 
        {
            return etalase.at(nomorRak);
        } 
        catch (const out_of_range&) 
        {
            throw string("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};

// =============================================
//              STRUCT DATA BARANG
// =============================================
struct Barang 
{
    int id;
    string nama;
    int harga;
    int stok;
};

// =============================================
//               FUNGSI UTILITAS
// =============================================

// Fungsi untuk membersihkan whitespace
string trim(const string& s) 
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

// Fungsi untuk mendapatkan ID berikutnya secara otomatis
int nextId(const vector<Barang>& daftar) 
{
    int maxId = 0;
    for (const auto& b : daftar) 
    {
        if (b.id > maxId) maxId = b.id;
    }
    return maxId + 1;
}