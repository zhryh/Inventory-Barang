#ifndef BARANG_H_INCLUDED
#define BARANG_H_INCLUDED

#include <string>
#include <iostream>

#define firstU(P) (P)->firstU
#define firstT(P) (P)->firstT
#define firstG(P) (P)->firstG
#define prevB(P) (P)->prevB
#define firstB(P) (P)->firstB
#define infoG(P) (P)->infoG
#define infoU(P) (P)->infoU
#define infoT(P) (P)->infoT
#define infoB(P) (P)->infoB
#define nextG(P) (P)->nextG
#define nextU(P) (P)->nextU
#define nextB(P) (P)->nextB
#define nextT(P) (P)->nextT
#define prevU(P) (P)->prevU
#define last(L) ((L).last)
#define first(L) ((L).first)
#define nil NULL

using namespace std;

typedef struct tranksaksi infotypeTrank;
typedef struct barang infotypeBar;
typedef struct gudang infotypeGud;
typedef struct users infotypeUser;

typedef struct elemuser *adrUser;
typedef struct elemtrank *adrTrank;
typedef struct elembar *adrBar;
typedef struct elemgud *adrGud;

struct users {
    string password;
    string nama;
    int id;
};

struct tranksaksi {
    string tanggal_trank, jenis;
    int jml_trank;
};

struct barang {
    string nama_barang,tgl_produksi, tgl_kedaluwarsa;
    int jml_barang, hrg_barang;
};

struct gudang {
    string namaG;
    int isi;
    int limit;
};

struct elemuser {
    infotypeUser infoU;
    adrUser nextU;
    adrUser nextG;
    adrUser prevU;
    adrTrank firstT;
    adrGud firstG;
    adrGud infoG;
};

struct elemtrank {
    infotypeTrank infoT;
    adrUser infoU;
    adrGud infoG;
    adrUser nextU;
    adrTrank nextT;
    adrGud nextG;
};

struct elembar {
    infotypeBar infoB;
    adrBar nextB;
    adrBar prevB;
    adrGud firstG;
    adrGud nextG;
};

struct elemgud {
    infotypeGud infoG;
    adrGud nextG;
    adrUser firstG;
    adrBar firstB;
};

struct list_users {
    adrUser first;
    adrUser last;
};

struct list_tranksaksi {
    adrTrank first;
};

struct list_barang {
    adrBar first;
    adrBar last;
};

struct list_gudang {
    adrGud first;
};

void createListUser(list_users &LU);
void createListGudang(list_gudang &LG);
void createListBarang(list_barang &LB);
void createListTranksaksi(list_tranksaksi &LT);

adrUser allocateUser(infotypeUser dataUser);
adrGud allocateGud(infotypeGud dataGudang);
adrTrank allocateTrank(infotypeTrank dataTranksaksi);
adrBar allocateBarang(infotypeBar dataBarang);

void insertUser(list_users &LU, infotypeUser dataUser);
void deleteUser(list_users &LU, string namUser);
void printUser(list_users &listUsers);

void insertFirstGudang(list_gudang &listGudang, infotypeGud dataGudang);
void deleteGudangonly(list_gudang &listGudang, string namaGudang);
adrGud findGudangByUser(list_users &listUsers, string namaUser);

adrUser searchUser(list_users &LU, string namaUser);
adrGud searchGudang(list_gudang &listGudang, string namaGudang);

void connectUserToGudang(list_users &LU, list_gudang &LG, string namaUser, string namaGudang);
void deleteUserWithTransactions(list_users &listUsers, list_tranksaksi &listTranksaksi, string namaUser);
void showUserWithTransactionAndGudang(list_users &listUsers, string namaUser);

//void insertBarang(list_barang &listBarang, adrBar newBarang);
adrBar searchBarang(list_barang &LB, string namaBarang);
void connectBarangToGudang(list_barang &LB, list_gudang &LG, string namaBarang, string namaGudang);
int countChildGudang(adrGud gudang);

int selectMenu();
void insertTranksaksi(list_tranksaksi &LT, adrTrank newTranksaksi);
void connectUserToGudangWithTranksaksi(list_users &LU, list_tranksaksi &LT, list_gudang &LG, string namaUser, string namaGudang, string tanggalTranksaksi, string jenisTranksaksi, int jumlahTranksaksi);
void printTranksaksi(list_tranksaksi &LT, list_users &LU, list_gudang &LG);

void addBarangToGudang(list_gudang &LG, string namaBarang, string namaGudang, int jumlahbarang);
void deleteTransactionsWithUser(list_tranksaksi &LT, string userIdToDelete);
void deleteUserWithTransactions(list_users &LU, list_tranksaksi &LT, int userIdToDelete);

void deleteGudangWithUser(list_gudang &LG, list_users &LU, list_tranksaksi &LT, string namaUser);
void deleteUserWithGudang(list_users &LU, list_gudang &LG, list_tranksaksi &LT, string namaUser);

void deleteGudang(list_gudang &LG, list_users &LU, string namaUser);
void deleteTranksaksiWithUser(list_tranksaksi &LT, list_users &LU, string namaUser);
void deleteUserWithGudang(list_users &LU, list_gudang &LG, list_tranksaksi &LT, string namaUser);

void deleteGudangbyNama(list_gudang &listGudang, string namaGudang);
void printGudang(list_gudang LG);

adrGud searchGudangByUser(list_gudang &LG, string namaUser);
adrGud findGudangConnectedWithUser(list_tranksaksi LT, list_users LU, string userName);

adrGud findConnectedGudang(list_tranksaksi LT, list_users LU, string userName);
int countGudang(list_gudang LG);

void displayConnectedUsersAndGudang(list_users &LU, list_gudang &LG);
void connectBarangToGudang(list_barang &LB, list_gudang &LG, string namaBarang, string namaGudang);
void insertBarang(list_barang &LB, infotypeBar dataBarang);

int countItemsInGudang(list_gudang LG, string namaGudang);
void displayBarangInGudang(list_gudang LG, list_barang LB, string namaGudang);
int countGudangFromUser(list_users LU, list_gudang LG, list_tranksaksi LT, string namaUser);

void displayBarangInGudang(list_gudang LG, string namaGudang);
void displayGudangAndConnectedBarangs(list_gudang LG, string namaGudang);
void printListBarang(list_barang LB);

void connectBarangToGudang(list_gudang &LG, list_barang &LB, adrGud G, adrBar B);
void displayBarangInGudang(elemgud* gudang);
void displayBarangInGudang(list_gudang LG, list_barang LB, string namaGudang);

adrBar searchBarangInGudang(adrGud G, string namaBarang);
string searchGudangByBarang(list_gudang LG, list_barang LB, string namaBarang);

int countJenisBarangInGudang(adrGud G, list_barang LB);
void deleteGudangWithTransactions(list_gudang &LG, list_tranksaksi &LT, string namaGudang);
#endif // BARANG_H_INCLUDED

