#include "barang.h"

void createListUser(list_users &LU){
    first(LU)= nil;
    last(LU)= nil;
}

void createListGudang(list_gudang &LG){
    first(LG)= nil;
}

void createListBarang(list_barang &LB){
    first(LB)= nil;
}
void createListTranksaksi(list_tranksaksi &LT){
    first(LT)= nil;
}

adrUser allocateUser(infotypeUser dataUser){
    adrUser newUser = new elemuser;
    infoU(newUser) = dataUser;
    //infoU(newUser).id = dataUser.id;
    //infoU(newUser).password = dataUser.password;
    nextG(newUser) = NULL;
    prevU(newUser) = NULL;
    //firstT(newUser) = NULL;
    return newUser;
}

adrGud allocateGud(infotypeGud dataGudang){
    adrGud newGudang = new elemgud;
    infoG(newGudang)= dataGudang;
    nextG(newGudang)= NULL;
    return newGudang;
}

adrTrank allocateTrank(infotypeTrank dataTranksaksi){
    adrTrank newTrank = new elemtrank;
    infoT(newTrank)= dataTranksaksi;
    nextG(newTrank)= NULL;
    nextU(newTrank)= NULL;
    return newTrank;
}

adrBar allocateBarang(infotypeBar dataBarang) {
    adrBar newBarang = new elembar;
    infoB(newBarang) = dataBarang;
    nextB(newBarang) = NULL;
    prevB(newBarang) = NULL;
    firstG(newBarang) = NULL;
    nextG(newBarang) = NULL;

    return newBarang;
}


void insertUser(list_users &LU, infotypeUser dataUser) {
    adrUser newUser = allocateUser(dataUser);

    if (first(LU) == NULL) {
        // If the list is empty, make the new user the first and last user
        first(LU) = last(LU) = newUser;
        nextG(newUser) = prevU(newUser) = newUser; // Circular connections
    } else {
        // Insert the new user at the end
        nextG(last(LU)) = newUser;
        prevU(newUser) = last(LU);
        nextG(newUser) = first(LU); // Make it circular
        prevU(first(LU)) = newUser; // Update the previous of the first user
        last(LU) = newUser;
    }
}

/*void deleteUser(list_users &LU, int userIdToDelete) {
    if (first(LU) != NULL) {
        adrUser currentUser = first(LU);
        adrUser prevUser = NULL;

        // Find the user to delete
        while (currentUser != NULL && infoU(currentUser).id != userIdToDelete) {
            prevUser = currentUser;
            currentUser = nextG(currentUser);
        }

        if (currentUser != NULL) {
            // If the user is found

            // Update the next and prev pointers of adjacent nodes
            if (nextG(currentUser) != currentUser) {
                if (prevUser != NULL) {
                    nextG(prevUser) = nextG(currentUser);
                } else {
                    // The user is at the beginning of the list
                    first(LU) = nextG(currentUser);
                }

                prevU(nextG(currentUser)) = prevU(currentUser);

                // Update the first and last pointers if necessary
                if (last(LU) == currentUser) {
                    last(LU) = prevU(currentUser);
                }
            } else {
                // If there is only one user in the list
                first(LU) = last(LU) = NULL;
            }

            // Set the pointer to NULL instead of using delete
            currentUser = NULL;
        }
    }
}*/

void deleteUser(list_users &LU, string namaUser) {
    if (first(LU) != NULL) {
        adrUser currentUser = first(LU);

        // Temukan pengguna yang akan dihapus
        while (nextU(currentUser) != first(LU) && infoU(currentUser).nama != namaUser) {
            currentUser = nextU(currentUser);
        }

        if (infoU(currentUser).nama == namaUser) {
            // Pengguna ditemukan

            // Perbarui pointer next dan prev dari node-node yang terkait
            adrUser prevUser = prevU(currentUser);
            adrUser nextUser = nextU(currentUser);

            if (prevUser != currentUser) {
                nextU(prevUser) = nextUser;
                prevU(nextUser) = prevUser;

                // Perbarui pointer first dan last jika diperlukan
                if (first(LU) == currentUser) {
                    first(LU) = nextUser;
                }
                if (last(LU) == currentUser) {
                    last(LU) = prevUser;
                }
            } else {
                // Jika hanya ada satu pengguna dalam daftar
                first(LU) = last(LU) = NULL;
            }

            // Setel pointer menjadi NULL tanpa menggunakan delete
            currentUser = NULL;
        }
    }
}


void printUser(list_users &listUsers) {
    if (first(listUsers) == NULL) {
        cout << "No users to display." << endl;
        return;
    }

    adrUser current = first(listUsers);
    do {
        cout << "ID: " << infoU(current).id << endl;
        cout << "Nama: " << infoU(current).nama << endl;
        cout << "Password: " << infoU(current).password << endl;
        cout << "-----------------------------" << endl;
        current = nextG(current);
    } while (current != first(listUsers) && current != NULL);
}

// Function to search for a user by name
adrUser searchUser(list_users &LU, string namaUser) {
    adrUser currentUser = first(LU);

    while (currentUser != NULL) {
        if (infoU(currentUser).nama == namaUser) {
            return currentUser; // Found the user
        }
        currentUser = nextG(currentUser);
    }

    return NULL; // User not found
}


void insertFirstGudang(list_gudang &listGudang, infotypeGud dataGudang) {
    adrGud newGudang = allocateGud(dataGudang);

    if (newGudang != NULL) {
        nextG(newGudang) = first(listGudang);
        first(listGudang) = newGudang;
    } else {
        cout << "Memory allocation failed for the new gudang." << endl;
    }
}

void deleteGudangbyNama(list_gudang &listGudang, string namaGudang) {
    adrGud current = first(listGudang);
    adrGud prev = NULL;

    // Search for the gudang to be deleted
    while (current != NULL && infoG(current).namaG != namaGudang) {
        prev = current;
        current = nextG(current);
    }

    // Check if the gudang is found
    if (current != NULL) {
        // Remove the gudang from the list
        if (prev != NULL) {
            nextG(prev) = nextG(current);
        } else {
            // The gudang is at the beginning of the list
            first(listGudang) = nextG(current);
        }

        // Set the pointer to NULL instead of using delete
        current = NULL;

        cout << "Gudang '" << namaGudang << "' has been deleted." << endl;
    } else {
        cout << "Gudang '" << namaGudang << "' not found." << endl;
    }
}




// Function to search for a gudang by name
adrGud searchGudang(list_gudang &listGudang, string namaGudang) {
    adrGud currentGudang = first(listGudang);

    while (currentGudang != NULL) {
        if (infoG(currentGudang).namaG == namaGudang) {
            return currentGudang; // Found the gudang
        }
        currentGudang = nextG(currentGudang);
    }

    return NULL; // Gudang not found
}

void connectUserToGudang(list_users &LU, list_gudang &LG, string namaUser, string namaGudang) {
    adrUser user = searchUser(LU, namaUser);
    adrGud gudang = searchGudang(LG, namaGudang);

    if (user != NULL && gudang != NULL) {
        // Cek apakah user sudah terhubung dengan gudang
        if (firstG(user) == NULL) {
            // User belum terhubung dengan gudang manapun
            firstG(user) = gudang;
        } else {
            // User sudah terhubung dengan gudang lain, tambahkan gudang baru
            nextG(gudang) = firstG(user);
            firstG(user) = gudang;
        }

        // Hubungkan user ke gudang
        firstG(gudang) = user;

        cout << "User '" << namaUser << "' berhasil terhubung dengan gudang '" << namaGudang << "'." << endl;
    } else {
        cout << "Data User atau Gudang tidak ditemukan." << endl;
    }
}


/*adrGud findGudangByUser(list_users &listUsers, string namaUser) {
    adrUser currentUser = first(listUsers);

    // Cari user
    while (currentUser != NULL && infoU(currentUser).nama != namaUser) {
        currentUser = nextG(currentUser);
    }

    // Periksa apakah user ditemukan
    if (currentUser != NULL) {
        // Dapatkan gudang yang terkait dengan user
        adrGud associatedGudang = firstG(currentUser);
        return associatedGudang;
    } else {
        cout << "User '" << namaUser << "' tidak ditemukan." << endl;
        return NULL; // User tidak ditemukan
    }
}*/

/*void insertBarang(list_barang &listBarang, adrBar newBarang) {
    if (first(listBarang) == NULL) {
        first(listBarang) = newBarang;
    } else {
        adrBar currentBarang = first(listBarang);
        while (nextB(currentBarang) != NULL) {
            currentBarang = nextB(currentBarang);
        }
        nextB(currentBarang) = newBarang;
    }
}*/

// Function to search for a barang in list_barang
adrBar searchBarang(list_barang &LB, string namaBarang) {
    adrBar currentBarang = first(LB);

    while (currentBarang != NULL) {
        // Assuming the barang has a member function or data member called nama_barang
        if (infoB(currentBarang).nama_barang == namaBarang) {
            return currentBarang; // Found the barang
        }

        currentBarang = nextB(currentBarang);
    }

    return NULL; // Barang not found
}

void insertTranksaksi(list_tranksaksi &LT, adrTrank newTranksaksi) {
    if (first(LT) == nil) {
        first(LT) = newTranksaksi;
    } else {
        adrTrank currentTranksaksi = first(LT);
        while (nextT(currentTranksaksi) != nil) {
            currentTranksaksi = nextT(currentTranksaksi);
        }
        nextT(currentTranksaksi) = newTranksaksi;
    }
}

void connectUserToGudangWithTranksaksi(list_users &LU, list_tranksaksi &LT, list_gudang &LG, string namaUser, string namaGudang, string tanggalTranksaksi, string jenisTranksaksi, int jumlahTranksaksi) {
    adrUser user = searchUser(LU, namaUser);
    adrGud gudang = searchGudang(LG, namaGudang);

    if (user != NULL && gudang != NULL) {
        // Membuat transaksi baru
        infotypeTrank dataTranksaksi;
        dataTranksaksi.tanggal_trank = tanggalTranksaksi;
        dataTranksaksi.jenis = jenisTranksaksi;
        dataTranksaksi.jml_trank = jumlahTranksaksi;

        adrTrank newTranksaksi = allocateTrank(dataTranksaksi);
        insertTranksaksi(LT, newTranksaksi);

        // Menghubungkan transaksi dengan user dan gudang
        nextU(newTranksaksi) = user;
        nextG(newTranksaksi) = gudang;

        cout << "User '" << namaUser << "' berhasil terhubung dengan Gudang '" << namaGudang << "' melalui transaksi." << endl;
    } else {
        cout << "Data User atau Gudang tidak ditemukan atau transaksi tidak dapat dibuat." << endl;
    }
}

/*void addBarangToGudang(list_gudang &LG, string namaBarang, string namaGudang, int jumlahbarang) {
    adrGud gudang = searchGudang(LG, namaGudang);

    if (gudang != NULL) {
        // Check if the inventory is at its limit
        int currentInventory = 0;
        adrBar currentBarang = firstB(gudang);

        while (currentBarang != NULL) {
            currentInventory += infoB(currentBarang).jml_barang;
            currentBarang = nextB(currentBarang);
        }

        if (currentInventory + jumlahbarang <= infoG(gudang).limit) {
            // Create a new barang and connect it to the gudang
            infotypeBar dataBarang;
            dataBarang.nama_barang = namaBarang;
            dataBarang.jml_barang = jumlahbarang;

            adrBar newBarang = allocateBarang(dataBarang);

            if (firstB(gudang) == NULL) {
                firstB(gudang) = newBarang;
            } else {
                nextB(newBarang) = firstB(gudang);
                firstB(gudang) = newBarang;
            }

            cout << "Barang '" << namaBarang << "' berhasil ditambahkan ke Gudang '" << namaGudang << "'." << endl;
        } else {
            cout << "Gudang '" << namaGudang << "' penuh. Tidak dapat menambahkan barang." << endl;
        }
    } else {
        cout << "Gudang '" << namaGudang << "' tidak ditemukan." << endl;
    }
}*/



/*int countChildGudang(adrGud gudang) {
    int child = 0;
    adrBar currentBarang = firstB(gudang);

    while (currentBarang != NULL) {
        child++;
        currentBarang = nextB(currentBarang);
    }

    return child;
}*/

void printTranksaksi(list_tranksaksi &LT, list_users &LU, list_gudang &LG) {
    adrTrank currentTranksaksi = first(LT);

    if (currentTranksaksi == NULL) {
        cout << "Tidak ada transaksi saat ini." << endl;
        return;
    }

    cout << "Daftar Transaksi:" << endl;
    while (currentTranksaksi != nil) {
        cout << "Tanggal Transaksi : " << infoT(currentTranksaksi).tanggal_trank << endl;
        cout << "Jenis Transaksi   : " << infoT(currentTranksaksi).jenis << endl;
        cout << "Jumlah Transaksi  : " << infoT(currentTranksaksi).jml_trank << endl;

        // Check if currentTranksaksi is not nil before accessing nextU and nextG
        if (nextU(currentTranksaksi) != nil && nextG(currentTranksaksi) != nil) {
            cout << "USER" << endl;
            cout << "Nama User   : " << infoU(nextU(currentTranksaksi)).nama << endl;
            cout << "ID          : " << infoU(nextU(currentTranksaksi)).id << endl;
            cout << "Password    :  " << infoU(nextU(currentTranksaksi)).password << endl;

            cout << "GUDANG" << endl;
            cout << "Nama Gudang : " << infoG(nextG(currentTranksaksi)).namaG << endl;
            cout << "Limit Gudang : " << infoG(nextG(currentTranksaksi)).limit << endl;
            cout << "Isi : " << infoG(nextG(currentTranksaksi)).isi << endl;
        }

        cout << "-----------------------------" << endl;

        currentTranksaksi = nextT(currentTranksaksi);
    }
}



int selectMenu() {
    cout<<endl<<endl;
    cout << "    *********************** SELAMAT DATANG **********************"<<endl;
    cout << "    *                           MENU                            *"<<endl;
    cout << "    * 1. Tambahkan Data User                                    *"<<endl;
    cout << "    * 2. Menampilkan Semua Data User                            *"<<endl;
    cout << "    * 3. Mengahapus Data User serta Tranksaksi                  *"<<endl;
    cout << "    * 4. Mencari Data User                                      *"<<endl;
    cout << "    * 5. Tambahkan Data Gudang                                  *"<<endl;
    cout << "    * 6. Mencari Data Gudang                                    *"<<endl;
    cout << "    * 7. Hapus Data Gudang                                      *"<<endl;
    cout << "    * 8. Tampilkan Data Gudang                                  *"<<endl;
    cout << "    * 9. Tambahkan Tranksaksi                                   *"<<endl;
    cout << "    * 10. Menampilkan Tranksaksi                                *"<<endl;
    cout << "    * 11. Tambahkan Data Barang                                 *"<<endl;
    cout << "    * 12. Hubungkan Barang dan Gudang                           *"<<endl;
    cout << "    * 13. Tampilkan Barang dan Gudang yang terhubung            *"<<endl;
    cout << "    * 14. Mencari Data Gudang pada User Tertentu                *"<<endl;
    cout << "    * 15. Menghitung Jumlah Gudang                              *"<<endl;
    cout << "    * 0. Exit                                                   *"<<endl;
    cout << "    *************************************************************"<<endl;
    cout << ">>  Masukkan menu: ";

    int input = 0;
    cin>> input;

    if (input != 0 && input > 16) {
        cout<<"    >>>MAAF MENU TIDAK TERSEDIA<<<";
    }

    return input;
}

/*void deleteTransactionsWithUser(list_tranksaksi &LT, string userName) {
    adrTrank currentTranksaksi = first(LT);
    adrTrank prevTranksaksi = NULL;

    while (currentTranksaksi != NULL) {
        if (nextU(currentTranksaksi) != NULL && infoU(nextU(currentTranksaksi)).nama == userName) {
            // Remove the transaction from the list
            if (prevTranksaksi != NULL) {
                nextT(prevTranksaksi) = nextT(currentTranksaksi);
            } else {
                // The transaction is at the beginning of the list
                first(LT) = nextT(currentTranksaksi);
            }

            // Move to the next transaction
            adrTrank temp = currentTranksaksi;
            currentTranksaksi = nextT(currentTranksaksi);

            // Set the pointer to NULL instead of using delete
            temp = NULL;
        } else {
            // Move to the next transaction
            prevTranksaksi = currentTranksaksi;
            currentTranksaksi = nextT(currentTranksaksi);
        }
    }

}*/
void deleteTransactionsWithUser(list_tranksaksi &LT, string userName) {
    adrTrank currentTranksaksi = first(LT);
    adrTrank prevTranksaksi = NULL;
    bool userFound = false;

    while (currentTranksaksi != NULL) {
        if (infoU(nextU(currentTranksaksi)).nama == userName) {
            // Remove the transaction from the list
            adrTrank temp = currentTranksaksi;

            if (prevTranksaksi != NULL) {
                nextT(prevTranksaksi) = nextT(currentTranksaksi);
            } else {
                // The transaction is at the beginning of the list
                first(LT) = nextT(currentTranksaksi);
            }

            // Notify user deletion
            cout << "User '" << userName << "' and associated transactions have been deleted." << endl;

            // Deallocate memory
            delete temp;

            userFound = true;
        } else {
            // Move to the next transaction
            prevTranksaksi = currentTranksaksi;
        }

        // Move to the next transaction
        currentTranksaksi = nextT(currentTranksaksi);
    }

    if (!userFound) {
        // Notify that the user was not found
        cout << "User '" << userName << "' not found. No transactions deleted." << endl;
    }
}



/*adrGud findGudangConnectedWithUser(list_tranksaksi LT, list_users LU, string userName) {
    adrUser user = searchUser(LU, userName);

    if (user != NULL) {
        adrTrank currentTranksaksi = first(LT);

        while (currentTranksaksi != NULL) {
            // Periksa apakah transaksi melibatkan pengguna yang dicari
            if (infoU(infoT(currentTranksaksi)).nama == user) {
                // Dapatkan gudang yang terhubung dengan transaksi
                adrGud connectedGudang = infoG(infoT(currentTranksaksi));

                // Pastikan gudang ditemukan
                if (connectedGudang != NULL) {
                    return connectedGudang;
                }
            }

            currentTranksaksi = nextT(currentTranksaksi);
        }
    }

    // User tidak ditemukan atau tidak terhubung dengan gudang
    return NULL;
}*/



void printGudang(list_gudang LG) {
    cout << "Daftar Gudang:" << endl;

    adrGud current = first(LG);

    while (current != NULL) {
        cout << "Nama Gudang: " << infoG(current).namaG << endl;
        cout << "Kapasitas: " << infoG(current).limit << endl;
        cout << "Isi: " << infoG(current).isi << endl;

        // Mencetak informasi lebih lanjut sesuai kebutuhan

        cout << "-----------------------------" << endl;

        current = nextG(current);
    }

    if (first(LG) == NULL) {
        cout << "Tidak ada gudang yang tersedia." << endl;
    }
}

/*void addBarangToGudang(list_gudang &LG, list_barang &LB, string namaGudang, infotypeBar infoBarang) {
    adrGud gudangTujuan = searchGudang(LG, namaGudang);

    if (gudangTujuan != NULL) {
        adrBar newBarang = allocateBarang(infoBarang);

        // Hubungkan barang dengan gudang
        nextG(newBarang) = gudangTujuan;

        // Tambahkan barang ke dalam list barang
        if (firstB(gudangTujuan) == NULL) {
            firstB(gudangTujuan) = newBarang;
        } else {
            nextB(newBarang) = firstB(gudangTujuan);
            firstB(gudangTujuan) = newBarang;
        }

        cout << "Barang berhasil ditambahkan ke dalam gudang '" << namaGudang << "'." << endl;
    } else {
        cout << "Gudang dengan nama '" << namaGudang << "' tidak ditemukan." << endl;
    }
}*/

adrGud searchGudangByUser(list_gudang &LG, string namaUser) {
    adrGud currentGudang = first(LG);

    while (currentGudang != NULL) {
        adrUser firstUserInGudang = firstG(currentGudang);

        // Cek setiap user dalam gudang
        while (firstUserInGudang != NULL) {
            if (infoU(firstUserInGudang).nama == namaUser) {
                // User ditemukan, return gudang
                return currentGudang;
            }

            firstUserInGudang = nextG(firstUserInGudang);
        }

        // Lanjut ke gudang berikutnya
        currentGudang = nextG(currentGudang);
    }

    // User tidak ditemukan dalam semua gudang
    return NULL;
}

/*adrGud findConnectedGudang(list_users LU, list_tranksaksi LT, string userName) {
    adrUser currentUser = firstU(LU);

    while (currentUser != NULL) {
        if (infoU(currentUser).nama == userName) {
            adrTrank currentTranksaksi = firstT(currentUser);

            while (currentTranksaksi != NULL) {
                // Pastikan infoG menyimpan alamat gudang (adrGud), bukan infotypeGud
                if (infoG(currentTranksaksi) != NULL) {
                    // Pastikan gudang ditemukan dengan benar
                    adrGud connectedGudang = searchGudang(LT, infoG(currentTranksaksi)->infoG.nama);

                    if (connectedGudang != NULL) {
                        return connectedGudang;
                    }
                }

                currentTranksaksi = nextT(currentTranksaksi);
            }
        }

        currentUser = nextU(currentUser);
    }

    // User tidak ditemukan atau tidak terhubung dengan gudang
    return NULL;
}*/
// Fungsi untuk mencari gudang yang terhubung dengan user

adrGud findConnectedGudang(list_tranksaksi LT, list_users LU, string userName) {
    adrTrank currentTranksaksi = LT.first;

    while (currentTranksaksi != NULL) {
        if (nextU(currentTranksaksi) != NULL && infoU(nextU(currentTranksaksi)).nama == userName) {
            // User ditemukan, cari gudang terkait
            adrGud connectedGudang = nextU(currentTranksaksi)->firstG;

            // Jika gudang terkait ditemukan, kembalikan alamat elemen elemgud
            if (connectedGudang != NULL) {
                return connectedGudang;
            }
        }

        // Move to the next transaction
        currentTranksaksi = nextT(currentTranksaksi);
    }

    // Jika tidak ada gudang terhubung, return NULL atau sesuai kebutuhan
    return NULL;
}


void displayConnectedUsersAndGudang(list_users &LU, list_gudang &LG) {
    adrUser currentUser = LU.first;

    if (currentUser == NULL) {
        cout << "Tidak ada data user." << endl;
        return;
    }

    cout << "Data User dan Gudang yang Terhubung:" << endl;

    while (currentUser != NULL) {
        cout << "USER" << endl;
        cout << "Nama: " << infoU(currentUser).nama << endl;
        cout << "ID " << infoU(currentUser).id << endl;
        cout << "Password: " << infoU(currentUser).password << endl;

        // Cek apakah user terhubung dengan gudang
        if (firstG(currentUser) != NULL) {
            adrGud connectedGudang = firstG(currentUser);

            cout << "   Gudang yang terhubung: " << endl;
            cout << "Nama: " << infoG(connectedGudang).namaG << endl;
            cout << "Limit: " << infoG(connectedGudang).limit << endl;
            cout << "Isi: " << infoG(connectedGudang).isi << endl;
        } else {
            cout << "   Tidak terhubung dengan gudang." << endl;
        }

        cout << endl;

        currentUser = nextU(currentUser);
    }
}

void insertBarang(list_barang &LB, infotypeBar dataBarang) {
    adrBar newBarang = allocateBarang(dataBarang);

    if (first(LB) == NULL) {
        // If the list is empty, make the new barang the first and last barang
        first(LB) = newBarang;
    } else {
        // Insert the new barang at the end
        adrBar current = first(LB);
        while (nextB(current) != NULL) {
            current = nextB(current);
        }
        nextB(current) = newBarang;
    }

    cout << "Barang berhasil ditambahkan." << endl;
}

/*void connectBarangToGudang(list_barang &LB, list_gudang &LG, string namaBarang, string namaGudang) {
    // Search for the barang and gudang in their respective lists
    adrBar barangToConnect = searchBarang(LB, namaBarang);
    adrGud gudangToConnect = searchGudang(LG, namaGudang);

    if (barangToConnect != NULL && gudangToConnect != NULL) {
        // Connect the barang to the gudang
        nextG(barangToConnect) = gudangToConnect;

        // Optionally, update the gudang to include the connected barang
        // (Assuming gudang has a list of connected barangs)
        if (firstB(gudangToConnect) == NULL) {
            firstB(gudangToConnect) = barangToConnect;
        } else {
            adrBar currentBarang = firstB(gudangToConnect);
            while (nextB(currentBarang) != NULL) {
                currentBarang = nextB(currentBarang);
            }
            nextB(currentBarang) = barangToConnect;
        }

        cout << "Barang '" << namaBarang << "' berhasil terhubung dengan gudang '" << namaGudang << "'." << endl;
    } else {
        if (barangToConnect == NULL) {
            cout << "Barang dengan nama '" << namaBarang << "' tidak ditemukan." << endl;
        }
        if (gudangToConnect == NULL) {
            cout << "Gudang dengan nama '" << namaGudang << "' tidak ditemukan." << endl;
        }
    }
}*/


/*void deleteGudangAndTransactionsWithUser(list_tranksaksi &LT, list_gudang &LG, string userName) {
    adrTrank currentTranksaksi = first(LT);
    adrTrank prevTranksaksi = NULL;

    while (currentTranksaksi != NULL) {
        if (nextU(currentTranksaksi) != NULL && infoU(nextU(currentTranksaksi)).nama == userName) {
            // Remove the transaction from the list
            if (prevTranksaksi != NULL) {
                nextT(prevTranksaksi) = nextT(currentTranksaksi);
            } else {
                // The transaction is at the beginning of the list
                first(LT) = nextT(currentTranksaksi);
            }

            // Delete the associated gudang
            adrGud associatedGudang = infoG(infoT(currentTranksaksi));
            deleteGudang(LG, associatedGudang);

            // Move to the next transaction
            adrTrank temp = currentTranksaksi;
            currentTranksaksi = nextT(currentTranksaksi);

            // Set the pointer to NULL instead of using delete
            delete temp;
        } else {
            // Move to the next transaction
            prevTranksaksi = currentTranksaksi;
            currentTranksaksi = nextT(currentTranksaksi);
        }
    }
}*/

void deleteGudang(list_gudang &LG, adrGud gudangToDelete) {
    adrGud current = first(LG);
    adrGud prev = NULL;

    while (current != NULL && current != gudangToDelete) {
        prev = current;
        current = nextG(current);
    }

    if (current != NULL) {
        if (prev != NULL) {
            nextG(prev) = nextG(current);
        } else {
            first(LG) = nextG(current);
        }

        delete current;
        cout << "Gudang berhasil dihapus." << endl;
    } else {
        cout << "Gudang tidak ditemukan." << endl;
    }
}

int countItemsInGudang(list_gudang LG, string namaGudang) {
    adrGud currentGudang = searchGudang(LG, namaGudang);

    if (currentGudang != NULL) {
        int totalCount = 0;
        adrBar currentBarang = firstB(currentGudang);

        while (currentBarang != NULL) {
            totalCount += infoB(currentBarang).jml_barang;
            currentBarang = nextB(currentBarang);
        }

        return totalCount;
    } else {
        cout << "Gudang tidak ditemukan." << endl;
        return -1; // Indicate an error or absence of the warehouse
    }
};

/*void displayGudangAndConnectedBarangs(list_gudang LG, string namaGudang) {
    adrGud currentGudang = LG.first;

    while (currentGudang != NULL) {
        // Check if the current gudang matches the specified namaGudang
        if (currentGudang->infoG.namaG == namaGudang || namaGudang.empty()) {
            cout << "Gudang '" << currentGudang->infoG.namaG << "':" << endl;

            adrBar currentBarang = firstB(currentGudang);
            while (currentBarang != NULL) {
                // Display connected barang information
                cout << "- " << currentBarang->infoB.nama_barang << endl;
                currentBarang = nextB(currentBarang);
            }

            if (firstB(currentGudang) == NULL) {
                cout << "Tidak ada barang yang terhubung pada gudang '" << currentGudang->infoG.namaG << "'." << endl;
            }
        }

        currentGudang = nextG(currentGudang);
    }

    if (LG.first == NULL) {
        cout << "Tidak ada gudang yang terhubung dengan barang." << endl;
    }
}*/



int countGudang(list_gudang LG) {
    int count = 0;
    adrGud currentGudang = LG.first;

    while (currentGudang != nil) {
        count++;
        currentGudang = currentGudang->nextG;
    }

    return count;
}
int countGudangFromUser(list_users LU, list_gudang LG, list_tranksaksi LT, string namaUser) {
    adrUser user = LU.first;

    // Find the user with the specified name
    while (user != nil && user->infoU.nama != namaUser) {
        user = user->nextU;
    }

    if (user != nil) {
        // User found, count the associated gudangs through transactions
        int count = 0;
        adrTrank currentTrank = LT.first;

        while (currentTrank != nil) {
            // Check if the current transaction is associated with the target user
            if (currentTrank->infoU == user) {
                // Now, find the corresponding gudang
                adrGud currentGudang = LG.first;

                while (currentGudang != nil) {
                    // Check if the current gudang is associated with the current transaction
                    if (currentTrank->infoG == currentGudang) {
                        count++;
                        break; // No need to continue checking the same gudang for this transaction
                    }
                    currentGudang = currentGudang->nextG;
                }
            }
            currentTrank = currentTrank->nextT;
        }

        return count;
    } else {
        // User not found
        cout << "User dengan nama '" << namaUser << "' tidak ditemukan." << endl;
        return 0; // You can return -1 or any other value to indicate an error, or 0 if you prefer.
    }
}

void printListBarang(list_barang LB) {
    adrBar currentBarang = LB.first;

    cout << "Daftar Barang:" << endl;

    while (currentBarang != NULL) {
        // Tampilkan informasi barang
        cout << "Nama Barang: " << currentBarang->infoB.nama_barang << endl;
        cout << "Tanggal Produksi: " << currentBarang->infoB.tgl_produksi << endl;
        cout << "Tanggal Kedaluwarsa: " << currentBarang->infoB.tgl_kedaluwarsa << endl;
        cout << "Jumlah Barang: " << currentBarang->infoB.jml_barang << endl;
        cout << "Harga Barang: " << currentBarang->infoB.hrg_barang << endl;

        // Pindah ke barang selanjutnya
        currentBarang = nextB(currentBarang);

        // Pisahkan setiap barang dengan garis pembatas
        cout << "-------------------------" << endl;
    }

    if (LB.first == NULL) {
        cout << "Tidak ada barang dalam daftar." << endl;
    }
}

// Fungsi untuk menghubungkan barang ke gudang
void connectBarangToGudang(list_gudang &LG, list_barang &LB, adrGud G, adrBar B) {
    // Connect barang to gudang
    nextB(B) = firstB(G);
    firstB(G) = B;

    // Connect gudang to barang
    nextG(B) = G;

    cout << "Barang '" << infoB(B).nama_barang << "' berhasil terhubung dengan gudang '" << infoG(G).namaG << "'." << endl;
}


void displayBarangInGudang(list_gudang LG, list_barang LB, string namaGudang) {
    adrGud gudangTujuan = searchGudang(LG, namaGudang);

    if (gudangTujuan != NULL) {
        cout << "Barang yang terhubung pada gudang '" << namaGudang << "':" << endl;

        adrBar currentBarang = firstB(gudangTujuan);
        while (currentBarang != NULL) {
            cout << "- " << infoB(currentBarang).nama_barang << endl;
            currentBarang = nextB(currentBarang);
        }

        if (firstB(gudangTujuan) == NULL) {
            cout << "Tidak ada barang yang terhubung pada gudang '" << namaGudang << "'." << endl;
        }
    } else {
        cout << "Gudang dengan nama '" << namaGudang << "' tidak ditemukan." << endl;
    }
}

adrBar searchBarangInGudang(adrGud G, string namaBarang) {
    adrBar currentBarang = firstB(G);

    while (currentBarang != NULL) {
        if (infoB(currentBarang).nama_barang == namaBarang) {
            return currentBarang; // Mengembalikan pointer barang jika ditemukan
        }
        currentBarang = nextB(currentBarang);
    }

    return NULL; // Mengembalikan NULL jika barang tidak ditemukan pada gudang
}

string searchGudangByBarang(list_gudang LG, list_barang LB, string namaBarang) {
    adrBar currentBarang = LB.first;

    while (currentBarang != NULL) {
        if (infoB(currentBarang).nama_barang == namaBarang) {
            // Barang ditemukan, cari gudang yang terhubung ke barang
            adrGud currentGudang = LG.first;

            while (currentGudang != NULL) {
                adrBar barangDiGudang = searchBarangInGudang(currentGudang, namaBarang);

                if (barangDiGudang != NULL) {
                    // Gudang ditemukan yang terhubung dengan barang
                    return infoG(currentGudang).namaG;
                }

                currentGudang = nextG(currentGudang);
            }

            return ""; // Jika tidak ada gudang yang terhubung dengan barang
        }

        currentBarang = nextB(currentBarang);
    }

    return ""; // Jika barang tidak ditemukan
}

int countJenisBarangInGudang(adrGud G, list_barang LB) {
    int count = 0;
    adrBar currentBarang = firstB(G);

    while (currentBarang != NULL) {
        count++;
        currentBarang = nextB(currentBarang);
    }

    return count;
}

void deleteTransactionsWithGudang(list_tranksaksi &LT, adrGud G) {
    adrTrank currentTranksaksi = LT.first;
    adrTrank prevTranksaksi = NULL;

    while (currentTranksaksi != NULL) {
        if (infoG(currentTranksaksi) == G) {
            // Remove the transaction from the list
            adrTrank temp = currentTranksaksi;

            if (prevTranksaksi != NULL) {
                nextT(prevTranksaksi) = nextT(currentTranksaksi);
            } else {
                // The transaction is at the beginning of the list
                LT.first = nextT(currentTranksaksi);
            }

            // Deallocate memory
            delete temp;
        } else {
            // Move to the next transaction
            prevTranksaksi = currentTranksaksi;
        }

        // Move to the next transaction
        currentTranksaksi = nextT(currentTranksaksi);
    }
}


void deleteGudangWithTransactions(list_gudang &LG, list_tranksaksi &LT, string namaGudang) {
    adrGud currentGudang = LG.first;
    adrGud prevGudang = NULL;
    bool gudangFound = false;

    while (currentGudang != NULL) {
        if (infoG(currentGudang).namaG == namaGudang) {
            // Remove transactions associated with the gudang
            deleteTransactionsWithGudang(LT, currentGudang);

            // Remove the gudang from the list
            adrGud temp = currentGudang;

            if (prevGudang != NULL) {
                nextG(prevGudang) = nextG(currentGudang);
            } else {
                // The gudang is at the beginning of the list
                LG.first = nextG(currentGudang);
            }

            // Notify gudang deletion
            cout << "Gudang '" << namaGudang << "' and associated transactions have been deleted." << endl;

            // Deallocate memory
            delete temp;

            gudangFound = true;
        } else {
            // Move to the next gudang
            prevGudang = currentGudang;
        }

        // Move to the next gudang
        currentGudang = nextG(currentGudang);
    }

    if (!gudangFound) {
        // Notify that the gudang was not found
        cout << "Gudang '" << namaGudang << "' not found. No transactions or gudang deleted." << endl;
    }
}

