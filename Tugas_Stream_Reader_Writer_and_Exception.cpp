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

    // Method public: mengambil produk berdasarkan nomorRak
    string ambilBarang(size_t nomorRak) 
    {
        try 
        {
            // Wajib menggunakan .at() saat mengakses indeks array
            return etalase.at(nomorRak);
        } 

        catch (const out_of_range&) 
        {
            // Tangkap out_of_range lalu lempar ulang pesan kustom
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

// =============================================
//                 FUNGSI CRUD
// =============================================

// READ: Menampilkan semua barang dalam format tabel rapi
void readBarang() 
{
    vector<Barang> daftar = bacaGudang();

    cout << "\n========================================" << endl;
    cout << "      DAFTAR BARANG GUDANG GIBRAN JAYA  " << endl;
    cout << "========================================" << endl;

    if (daftar.empty()) 
    {
        cout << "  (Gudang masih kosong)" << endl;
    } else 
    {
        printf("%-5s %-22s %-12s %-5s\n", "ID", "Nama Barang", "Harga", "Stok");
        cout << "----------------------------------------" << endl;
        for (const auto& b : daftar) 
        {
            printf("%-5d %-22s Rp%-10d %-5d\n", b.id, b.nama.c_str(), b.harga, b.stok);
        }
    }
    cout << "========================================\n" << endl;
}

// CREATE: Menambahkan data barang baru ke dalam file
void createBarang() 
{
    vector<Barang> daftar = bacaGudang();
    Barang b;
    b.id = nextId(daftar);

    cout << "\n--- TAMBAH BARANG BARU ---" << endl;
    cout << "Nama Barang : ";
    getline(cin, b.nama);
    if (b.nama.empty()) getline(cin, b.nama);

    cout << "Harga       : Rp ";
    cin >> b.harga;
    cout << "Stok        : ";
    cin >> b.stok;
    cin.ignore();

    daftar.push_back(b);
    simpanGudang(daftar);
    cout << "Barang berhasil ditambahkan dengan ID " << b.id << "!" << endl;
}

// UPDATE: Memperbarui data barang tertentu berdasarkan ID
void updateBarang() 
{
    vector<Barang> daftar = bacaGudang();
    if (daftar.empty()) 
    {
        cout << "Gudang masih kosong, tidak ada data yang bisa diupdate!" << endl;
        return;
    }

    readBarang();
    int id;
    cout << "Masukkan ID barang yang akan diupdate: ";
    cin >> id;
    cin.ignore();

    auto it = find_if(daftar.begin(), daftar.end(), [id](const Barang& b) { return b.id == id; });
    if (it == daftar.end()) 
    {
        cout << "Barang dengan ID " << id << " tidak ditemukan!" << endl;
        return;
    }

    cout << "\n--- UPDATE DATA BARANG (ID: " << id << ") ---" << endl;

    string input;
    cout << "Nama Baru (Enter jika tidak diubah): ";
    getline(cin, input);
    if (!input.empty()) it->nama = input;

    cout << "Harga Baru (0 jika tidak diubah)  : Rp ";
    int hrg;
    cin >> hrg;
    if (hrg > 0) it->harga = hrg;

    cout << "Stok Baru  (-1 jika tidak diubah) : ";
    int stk;
    cin >> stk;
    if (stk >= 0) it->stok = stk;
    cin.ignore();

    simpanGudang(daftar);
    cout << "Barang berhasil diupdate!" << endl;
}

// DELETE: Menghapus data barang dari file berdasarkan ID
void deleteBarang() 
{
    vector<Barang> daftar = bacaGudang();
    if (daftar.empty()) 
    {
        cout << "Gudang masih kosong, tidak ada data yang bisa dihapus!" << endl;
        return;
    }

    readBarang();
    int id;
    cout << "Masukkan ID barang yang akan dihapus: ";
    cin >> id;
    cin.ignore();

    auto it = find_if(daftar.begin(), daftar.end(), [id](const Barang& b) { return b.id == id; });
    if (it == daftar.end()) 
    {
        cout << "Barang dengan ID " << id << " tidak ditemukan!" << endl;
        return;
    }

    string namaHapus = it->nama;
    daftar.erase(it);
    simpanGudang(daftar);
    cout << "Barang \"" << namaHapus << "\" berhasil dihapus dari gudang!" << endl;
}

// =============================================
//     SIMULASI ETALASE (Exception Handling)
// =============================================
void simulasiEtalase() {
    TokoElektronik toko;

    cout << "\n============================================" << endl;
    cout << "       SIMULASI ETALASE GIBRAN JAYA         " << endl;
    cout << "============================================" << endl;

    // Skenario 1: Pengambilan barang di rak indeks ke-1 (Harus sukses)
    cout << "\n[Skenario 1] Mengambil barang di rak indeks ke-1..." << endl;
    try 
    {
        string barang = toko.ambilBarang(1);
        cout << "Berhasil! Produk ditemukan : " << barang << endl;
    } 
    
    catch (const string& e) 
    {
        cout << "ERROR TERTANGKAP : " << e << endl;
    }

    // Skenario 2: Pengambilan barang di rak indeks ke-5 (Harus gagal)
    cout << "\n[Skenario 2] Mengambil barang di rak indeks ke-5..." << endl;
    try 
    {
        string barang = toko.ambilBarang(5);
        cout << "Berhasil! Produk ditemukan : " << barang << endl;
    } 

    catch (const string& e) 
    {
        cout << "ERROR TERTANGKAP : " << e << endl;
    }

    cout << "============================================\n" << endl;
}

// =============================================
//               FUNGSI MAIN
// =============================================
int main() {
    int pilihan;

    cout << "============================================" << endl;
    cout << "   SELAMAT DATANG DI TOKO ELEKTRONIK       " << endl;
    cout << "          \"GIBRAN JAYA\"                    " << endl;
    cout << "============================================" << endl;

    // Looping menu utama menggunakan do-while
    do {
        // READ otomatis: Menampilkan daftar barang setiap kali menu dibuka
        readBarang();

        cout << "========== MENU UTAMA ==========" << endl;
        cout << "1. Tambah Barang Baru  (Create)"  << endl;
        cout << "2. Lihat Barang        (Read)"    << endl;
        cout << "3. Update Data Barang  (Update)"  << endl;
        cout << "4. Hapus Data Barang   (Delete)"  << endl;
        cout << "5. Simulasi Etalase    (Exception)" << endl;
        cout << "0. Keluar"                         << endl;
        cout << "=================================" << endl;
        cout << "Pilih menu (0-5): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) 
        {
            case 1: 
                createBarang();    
                break;
            case 2: 
                readBarang();      
                break;
            case 3: 
                updateBarang();    
                break;
            case 4: 
                deleteBarang();    
                break;
            case 5: 
                simulasiEtalase(); 
                break;
            case 0:
                cout << "\nTerima kasih telah menggunakan sistem Toko Gibran Jaya!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan pilih antara 0-5." << endl;
                break;
        }

    } while (pilihan != 0);

    return 0;
}