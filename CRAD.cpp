#include <iostream>
#include <string>

using namespace std;

// 1. KONSEP CLASS: Blue print untuk Inventaris
class Inventaris {
private:
    double* hargaBarang; // Pointer untuk Array Dinamis
    int kapasitas;
    int jumlah;

public:
    // Constructor
    Inventaris(int size) {
        kapasitas = size;
        jumlah = 0;
        hargaBarang = new double[kapasitas]; // 2. KONSEP ARRAY DINAMIS
        cout << "[Sistem] Memori dialokasikan untuk " << kapasitas << " barang.\n";
    }

    // Destructor: Sangat penting untuk menghapus memori dinamis
    ~Inventaris() {
        delete[] hargaBarang;
        cout << "[Sistem] Memori dibersihkan.\n";
    }

    void tambahBarang(double harga) {
        if (jumlah < kapasitas) {
            hargaBarang[jumlah] = harga;
            jumlah++;
        } else {
            cout << "Inventaris penuh!\n";
        }
    }

    // 3. KONSEP REKURSI: Menghitung total harga
    // Menjumlahkan elemen dari indeks 'n' sampai 0
    double hitungTotalRekursif(int n) {
        // Base Case: Jika tidak ada barang lagi
        if (n < 0) {
            return 0;
        }
        // Langkah Rekursif
        return hargaBarang[n] + hitungTotalRekursif(n - 1);
    }

    // Helper untuk memanggil rekursi
    void tampilkanLaporan() {
        cout << "Jumlah Barang: " << jumlah << endl;
        double total = hitungTotalRekursif(jumlah - 1);
        cout << "Total Nilai Inventaris: Rp" << total << endl;
    }
};

int main() {
    int kapasitasAwal;
    cout << "Masukkan kapasitas gudang: ";
    cin >> kapasitasAwal;

    // Membuat objek dari Class
    Inventaris gudang(kapasitasAwal);

    gudang.tambahBarang(50000.0);
    gudang.tambahBarang(75000.5);
    gudang.tambahBarang(25000.0);

    cout << "\n--- Laporan Inventaris ---" << endl;
    gudang.tampilkanLaporan();

    return 0;
}