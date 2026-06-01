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
string trim(const string& s) 
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

int nextId(const vector<Barang>& daftar) 
{
    int maxId = 0;
    for (const auto& b : daftar) 
    {
        if (b.id > maxId) maxId = b.id;
    }
    return maxId + 1;
}

// =============================================
//              FUNGSI FILE I/O
// =============================================

// READ FILE: Membaca semua data dari gudang.txt ke vector
vector<Barang> bacaGudang() 
{
    vector<Barang> daftar;
    ifstream file("gudang.txt");

    if (!file.is_open()) return daftar;

    string line;
    while (getline(file, line)) 
    {
        line = trim(line);
        if (line.empty()) continue;
        stringstream ss(line);
        Barang b;
        string token;

        try {
            if (!getline(ss, token, ',')) continue; b.id    = stoi(trim(token));
            if (!getline(ss, token, ',')) continue; b.nama  = trim(token);
            if (!getline(ss, token, ',')) continue; b.harga = stoi(trim(token));
            if (!getline(ss, token, ',')) continue; b.stok  = stoi(trim(token));
            daftar.push_back(b);
        } catch (...) { continue; }
    }
    file.close();
    return daftar;
}

// WRITE FILE: Menulis semua data dari vector ke gudang.txt
void simpanGudang(const vector<Barang>& daftar) 
{
    ofstream file("gudang.txt");
    if (!file.is_open()) 
    {
        cout << "Gagal membuka file gudang.txt untuk ditulis!\n";
        return;
    }

    for (const auto& b : daftar) 
    {
        file << b.id << "," << b.nama << "," << b.harga << "," << b.stok << "\n";
    }

    file.close();
}