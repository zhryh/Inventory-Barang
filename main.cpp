#include <iostream>
#include "barang.h"
#include <string>

using namespace std;

int main()
{

    list_users LU;
    list_gudang LG;
    list_barang LB;
    list_tranksaksi LT;

    createListUser(LU);
    createListGudang(LG);
    createListBarang(LB);
    createListTranksaksi(LT);

    adrUser U;
    adrGud G;
    adrBar B;
    adrTrank T;

    //Deklarasi Variabel Data Pelanggan
    infotypeUser DU;

    //Deklarasi Variabel Data Barang
    infotypeGud DG;
    infotypeBar DB;

    int pilihan = selectMenu();
    while (pilihan != 0 ) {
        switch(pilihan) {
        case 1:
            {
            cout << "Tambahkan Data User" << endl;
            cout << "Nama    : ";
            cin >> DU.nama;
            cout << "ID      : ";
            cin >> DU.id;
            cout << "Password: ";
            cin >> DU.password;
            insertUser(LU,DU);
            }
            break;
        case 2:
            {
            cout <<"MENAMPILKAN SELURUH DATA USER"<<endl;
            printUser(LU);
            }
            break;
        case 3:
            {
            string namaUser;
            cout << "HAPUS DATA USER" <<endl;
            cout << "Nama : ";
            cin >> namaUser;
            deleteTransactionsWithUser(LT, namaUser);
            deleteUser(LU, namaUser);
            }
            break;
        case 4:
            {
            string namaUser;
            adrUser found;
            cout << "Mencari Data User" <<endl;
            cout <<"Masukkan Nama User: ";
            cin >> namaUser;
            found = searchUser(LU,namaUser);
            if (found != nil) {
                cout << endl <<"Data Yang Dicari: "<<endl;
                cout << "Nama          : " << infoU(found).nama <<endl;
                cout << "ID            : " << infoU(found).id<<endl;
                cout << "Password      : "<<infoU(found).password<<endl;
            } else {
                cout << "===================================="<<endl;
                cout << "|  DATA PELANGGAN TIDAK DITEMUKAN   |"<<endl;
                cout << "===================================="<<endl;
            }
            }
            break;
        case 5:
            {
            cout << "Tambahkan Data Gudang" <<endl;
            cout << "Nama Gudang       : ";
            cin >> DG.namaG;
            cout << "Limit Gudang      : ";
            cin >> DG.limit;
            cout << "Terisi sekarang   : ";
            cin >> DG.isi;
            insertFirstGudang(LG,DG);
            }
            break;
        case 6:
            {
            string namaGudang;
            adrGud found;
            cout << "Mencari Data Gudang" <<endl;
            cout <<"Masukkan Nama Gudang: ";
            cin >> namaGudang;
            found = searchGudang(LG,namaGudang);
            if (found != nil) {
                cout << endl <<"Data Yang Dicari: "<<endl;
                cout << "Nama Gudang         : " << infoG(found).namaG <<endl;
                cout << "Limit Gudang        : " << infoG(found).limit<<endl;
                cout << "Terisi sekarang     : " <<infoG(found).isi<<endl;
            } else {
                cout << "===================================="<<endl;
                cout << "|  DATA GUDANG TIDAK DITEMUKAN   |"<<endl;
                cout << "===================================="<<endl;
            }
            }
            break;
        case 7:
            {
            string namagudang;
            cout << "nama gudang yang ingin dihapus :"   ;
            cin >> namagudang;
            deleteGudangbyNama(LG, namagudang);
            }
            break;
        case 8:
            {
                printGudang(LG);
            }
            break;
        case 9:
            {
            string namaUser, namaGudang, tanggalTranksaksi, jenisTranksaksi;
            int jumlahTranksaksi;
            cout << "Buat Tranksaksi Baru" << endl;
            cout << "Nama User : ";
            cin >> namaUser;
            cout << "Nama Gudang ";
            cin >> namaGudang;
            cout << "Tanggal Tranksaksi : ";
            cin >> tanggalTranksaksi;
            cout << "Jenis Tranksaksi : ";
            cin >> jenisTranksaksi;
            cout << "Jumlah Tranksaksi: ";
            cin >> jumlahTranksaksi;
            connectUserToGudangWithTranksaksi(LU,LT,LG,namaUser,namaGudang, tanggalTranksaksi, jenisTranksaksi, jumlahTranksaksi);
            }
            break;
        case 10:
            {
                    printTranksaksi(LT, LU, LG);
            }
            break;
        case 11:
            {
            cout << "Tambahkan Data Barang" << endl;
            cout << "Nama\t\: ";
            cin >> DB.nama_barang;
            cout << "Tanggal Produksi\t\: ";
            cin >> DB.tgl_produksi;
            cout << "Tanggal Kedaluarsa\t\: ";
            cin >> DB.tgl_kedaluwarsa;
            cout << "Jumlah Barang\t\: ";
            cin >> DB.jml_barang;
            cout << "Harga\t\: ";
            cin >> DB.hrg_barang;
            insertBarang(LB, DB);
            }
            break;
        case 12:
            {
            string namaGudang, namaBarang;
            cout << "Masukkan Gudang Tujuan : ";
            cin >> namaGudang;
            cout << "Barang yang akan Ditambahkan : ";
            cin >> namaBarang;

        // Cari elemen gudang dan barang sesuai dengan nama yang dimasukkan
            adrGud G = searchGudang(LG, namaGudang);
            adrBar B = searchBarang(LB, namaBarang);

            if (G != NULL && B != NULL) {
        // Menghubungkan barang ke gudang jika elemen ditemukan
                connectBarangToGudang(LG, LB, G, B);
            } else {
                cout << "Gudang atau Barang tidak ditemukan." << endl;
            }
            }
            break;
        case 13:
            {
            string namaGudang;
            cout << "Gudang : ";
            cin >> namaGudang;
            displayBarangInGudang(LG,LB, namaGudang);
            }
            break;
        case 14:
            {
            string namaBarang;
            cout << "Barang yang akan Dicari : ";
            cin >> namaBarang;

            // Cari gudang yang memiliki barang
            string namaGudang = searchGudangByBarang(LG, LB, namaBarang);

            if (!namaGudang.empty()) {
                cout << "Barang '" << namaBarang << "' ditemukan pada gudang '" << namaGudang << "'." << endl;
            } else {
                cout << "Barang '" << namaBarang << "' tidak ditemukan pada gudang manapun." << endl;
            }
            }
            break;
         case 15:
            {
            string namaGudang;
            cout << "Gudang : ";
            cin >> namaGudang;

            // Cari elemen gudang sesuai dengan nama yang dimasukkan
            adrGud G = searchGudang(LG, namaGudang);

            if (G != NULL) {
            // Hitung jenis barang dalam gudang
                int jumlahJenisBarang = countJenisBarangInGudang(G, LB);
                cout << "Jumlah jenis barang dalam gudang '" << namaGudang << "' adalah: " << jumlahJenisBarang << endl;
            } else {
                cout << "Gudang dengan nama '" << namaGudang << "' tidak ditemukan." << endl;
            }
            }
            break;
        case 16:
            {
            string namaGudang;
            cout << "Masukkan Nama Gudang yang akan dihapus beserta transaksinya: ";
            cin >> namaGudang;
            deleteGudangWithTransactions(LG, LT, namaGudang);
            }
            break;



        }

        pilihan = selectMenu();
        }
    cout<<"|-------------------------------------------------|"<<endl;
    cout<<"|=========ANDA TELAH KELUAR DARI PROGRAM==========|"<<endl;
    cout<<"|-------------------------------------------------|"<<endl;

    return 0;
}


