#include <iostream>
#include <string>

using namespace std;

// 1. KONSEP CLASS: Representasi sebuah Buku (Node)
class Buku {
public:
    string judul;
    Buku* bawah; // Pointer ke buku di bawahnya

    Buku(string j) : judul(j), bawah(nullptr) {}
};

// 1. KONSEP CLASS: Pengelola Tumpukan (Stack)
class TumpukanBuku {
private:
    Buku* top; // Menunjuk ke buku paling atas

public:
    TumpukanBuku() : top(nullptr) {}

    // Fungsi Push (Menambah buku ke atas tumpukan)
    void taruhBuku(string judul) {
        Buku* bukuBaru = new Buku(judul);
        bukuBaru->bawah = top;
        top = bukuBaru;
        cout << "Buku '" << judul << "' ditaruh di atas tumpukan.\n";
    }

    // Fungsi Pop (Mengambil buku paling atas)
    void ambilBuku() {
        if (top == nullptr) {
            cout << "Tumpukan kosong!\n";
            return;
        }
        Buku* temp = top;
        cout << "Mengambil buku: " << top->judul << endl;
        top = top->bawah;
        delete temp;
    }

    // 2. KONSEP REKURSI: Menampilkan tumpukan dari dasar ke atas
    // (Memanfaatkan call stack untuk membalik urutan tampilan)
    void tampilkanDariDasar(Buku* node) {
        if (node == nullptr) return; // Base Case

        // Rekursi: Pergi ke buku paling bawah dulu
        tampilkanDariDasar(node->bawah);

        // Setelah kembali dari rekursi, baru cetak judulnya
        cout << " -> " << node->judul << endl;
    }

    // Helper untuk memanggil rekursi
    void lihatIsiGudang() {
        if (top == nullptr) {
            cout << "Gudang Kosong.\n";
            return;
        }
        cout << "\nIsi Tumpukan (Dari Dasar ke Atas):\n";
        tampilkanDariDasar(top);
        cout << endl;
    }
};

int main() {
    TumpukanBuku gudang;

    // Menambah buku (LIFO - Last In First Out)
    gudang.taruhBuku("Dasar Pemrograman C++");
    gudang.taruhBuku("Struktur Data");
    gudang.taruhBuku("Algoritma Jenius");

    // Menampilkan isi dengan teknik Rekursi
    gudang.lihatIsiGudang();

    // Mengambil satu buku
    gudang.ambilBuku();

    cout << "\nSetelah satu buku diambil:";
    gudang.lihatIsiGudang();

    return 0;
}