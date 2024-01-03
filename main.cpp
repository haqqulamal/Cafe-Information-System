#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Struktur data untuk item menu
struct itemMenu{
  string namaMenu;
  float harga;
  int stok;
};

// Tree untuk menyimpan data menu
struct menuNode{
  string kategori;
  string subKategori;
  vector<itemMenu> items;
  vector<menuNode*> children;
};

// Struktur data untuk event
struct Event {
    string namaEvent;
    string tanggal;
    string keterangan;
};

// Node untuk menyimpan data event
struct eventNode {
    Event data;
    eventNode* next;
};

// Buat variabel global
menuNode* menuTree;
eventNode* headEvent = nullptr;
// Inisialisasi menu
menuNode* dataMenu(){
  // inisialisasi node root
  menuTree = new menuNode{"", "", {},{
  new menuNode{"Roti dan kue", "Viennoiseries", {{"Croissant", 10.000, 20}, {"Pain au Chocolate", 12.000, 25}, {"Brioche", 15.000, 25}}, {}},
  new menuNode{"Roti dan kue", "Pastry", {{"Éclair", 18.0, 10}, {"Mille-feuille", 20.0, 12}, {"Tarte Tatin", 25.0, 8}, {"Tarlet", 15.0, 20}}, {}},
  new menuNode{"Roti dan kue", "Bread", {{"Baguette", 8.0, 30}, {"Sourdough", 10.0, 25}, {"Brioche Long", 15.0, 20}}, {}},
  new menuNode{"Roti dan kue", "Bun", {{"Bagel", 7.0, 15}, {"Burger", 12.0, 20}, {"Hotdog", 9.0, 18}}},
  new menuNode{"Minuman", "Juice", {{"Apple Juice", 8.0, 30}, {"Orange Juice", 7.0, 25}, {"Strawberry Juice", 9.0, 20}}, {}},
  new menuNode{"Minuman", "Teh", {{"Earl Grey", 5.0, 25}, {"Chamomile", 4.0, 20}, {"English Breakfast", 6.0, 22}, {"Darjeeling", 5.5, 18}, {"Oolong", 7.0, 15}, {"Matcha", 8.0, 12}, {"Jasmine", 6.5, 20}}, {}},
  new menuNode{"Minuman", "Kopi", {{"Long black", 9.0, 30}, {"Cappucino", 10.0, 25}, {"Latte", 11.0, 22}, {"Espresso", 8.0, 28}, {"Machiato", 9.5, 20}, {"Piccolo", 10.5, 18}}, {}},
  new menuNode{"Makanan Utama", "Salad", {{"Caesar Salad", 15.0, 20}, {"Caprese Salad", 14.0, 18}, {"Waldorf Salad", 16.0, 15}, {"Nicoise Salad", 17.0, 12}}, {}},
  new menuNode{"Makanan Utama", "Sup", {{"Pumpkin Soup", 12.0, 25}, {"Mushroom Soup", 13.0, 22}, {"Corn Soup", 11.0, 28}}, {}},
  new menuNode{"Makanan Utama", "Sandwich", {{"Club Sandwich", 18.0, 15}, {"Tuna Sandwich", 16.0, 20}}, {}},
  new menuNode{"Makanan Utama", "Pasta", {{"Gnocchi", 20.0, 12}, {"Aglio Olio", 15.0, 18}, {"Lasagna", 22.0, 15}, {"Fettucine", 16.0, 20}, {"Carbonara", 18.0, 18}}, {}}
  }};

  return menuTree;
}

// Fungsi untuk menampilkan struktur menu
void viewMenuStructure(menuNode* node, int level = 0) {
    if (node != nullptr) {
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << "- " << node->kategori;
        if (!node->subKategori.empty()) {
            cout << " > " << node->subKategori;
        }
        cout << endl;

        for (auto& child : node->children) {
            viewMenuStructure(child, level + 1);
        }
    }
}

// Fungsi untuk menampilkan daftar menu
void viewFlatMenu(menuNode* node) {
    if (node != nullptr) {
        for (const auto& item : node->items) {
            cout << item.namaMenu << " (Rp" << item.harga << ") - Stok: " << item.stok << endl;
        }

        for (auto& child : node->children) {
            viewFlatMenu(child);
        }
    }
}

// Fungsi untuk menambahkan kategori baru
void addKategori(menuNode*& root) {
    string kategori;
    cout << "Masukkan nama kategori baru: ";
    cin >> kategori;

    if (root != nullptr) {
        menuNode* newCategory = new menuNode{kategori, "", {}, {}};
        root->children.push_back(newCategory);
        cout << "Kategori berhasil ditambahkan!\n";
    } else {
        cout << "Node root tidak valid!\n";
    }
}

// Fungsi untuk menghapus kategori
void deleteKategori(menuNode*& root, const string& kategori) {
    for (auto it = root->children.begin(); it != root->children.end(); ++it) {
        if ((*it)->kategori == kategori) {
            delete *it;
            root->children.erase(it);
            cout << "Kategori berhasil dihapus!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Fungsi untuk mencari kategori
void searchKategori(menuNode* root, const string& kategori) {
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            cout << "Kategori ditemukan!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Fungsi untuk mereset kategori (menghapus semua subkategori dan item)
void resetKategori(menuNode*& root, const string& kategori) {
    for (auto it = root->children.begin(); it != root->children.end(); ++it) {
        if ((*it)->kategori == kategori) {
            // Hapus semua subkategori dan item pada kategori yang dimaksud
            for (auto& child : (*it)->children) {
                delete child;
            }
            (*it)->children.clear();
            (*it)->items.clear();
            cout << "Kategori berhasil direset!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Menambahkan menu baru
void addMenu(menuNode* node, const string& kategori, const string& subKategori, const itemMenu& item){
  // mencari node yang sesuai  dengan kategori dan subkategori
  if(node != nullptr){
    if(node->kategori == kategori && node->subKategori == subKategori){
      // menambahkan item menu kedalam vektor items pada node yg sesuai
      node->items.push_back(item);
      cout << "Menu berhasil ditambahkan!\n";
      return;
    }
    // Mencari di anak-anak node
    for(auto& child : node->children){
      addMenu(child, kategori, subKategori, item);
    }
  }else{
    cout << "Kategori atau subkategori tidak ditemukan!\n";
  }
}

void addStokitem(menuNode* node, const string& itemName) {
    // mencari node yang sesuai dengan nama item
    if (node != nullptr) {
        // mencari item dalam vektor items pada node yang sesuai
        for (auto& item : node->items) {
            if (item.namaMenu == itemName) {
                int additionalStok;
                cout << "Masukkan jumlah stok tambahan untuk " << itemName << ": ";
                cin >> additionalStok;

                // menambahkan stok pada item yang sesuai
                item.stok += additionalStok;
                cout << "Stok berhasil ditambahkan!\n";
                return;
            }
        }
        // Mencari di anak-anak node
        for (auto& child : node->children) {
            addStokitem(child, itemName);
        }
    } else {
        cout << "Item tidak ditemukan!\n";
    }
}



// isi data menu yg mau ditambahkan
void addItem(menuNode* menuTree) {
    string namaItem, kategori, subKategori;
    float harga;
    int stok;
// harus pake getline utk cin ya ganteng
    cout << "Masukkan nama item menu : ";
    cin >> namaItem;
    cout << "Masukkan harga : ";
    cin >> harga;
    cout << "Masukkan stok : ";
    cin >> stok;
    cout << "Masukkan ke kategori : ";
    cin >> kategori;
    cout << "Masukkan ke subkategori : ";
    cin >> subKategori;

itemMenu newItemMenu{namaItem, harga, stok};
    addMenu(menuTree, kategori, subKategori, newItemMenu);
}

void addKategori(menuNode*& root) {
    string kategori;
    cout << "Masukkan nama kategori baru: ";
    cin >> kategori;

    if (root != nullptr) {
        menuNode* newCategory = new menuNode{kategori, "", {}, {}};
        root->children.push_back(newCategory);
        cout << "Kategori berhasil ditambahkan!\n";
    } else {
        cout << "Node root tidak valid!\n";
    }
}

// Fungsi untuk menambahkan subkategori baru
void addSubkategori(menuNode*& root) {
    string kategori, subKategori;
    cout << "Masukkan nama kategori: ";
    cin >> kategori;
    cout << "Masukkan nama subkategori baru: ";
    cin >> subKategori;

    // Cari node dengan kategori yang sesuai
    menuNode* targetNode = nullptr;
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            targetNode = node;
            break;
        }
    }
    if (targetNode != nullptr) {
        // Tambahkan subkategori ke node yang sesuai
        menuNode* newSubCategory = new menuNode{kategori, subKategori, {}, {}};
        targetNode->children.push_back(newSubCategory);
        cout << "Subkategori berhasil ditambahkan!\n";
    } else {
        cout << "Kategori tidak ditemukan!\n";
    }
}

// Fungsi untuk menghapus subkategori
void deleteSubkategori(menuNode*& root) {
    string kategori, subKategori;
    cout << "Masukkan nama kategori: ";
    cin >> kategori;
    cout << "Masukkan nama subkategori yang ingin dihapus: ";
    cin >> subKategori;

    // Cari node dengan kategori dan subkategori yang sesuai
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            for (auto it = node->children.begin(); it != node->children.end(); ++it) {
                if ((*it)->subKategori == subKategori) {
                    delete *it;
                    node->children.erase(it);
                    cout << "Subkategori berhasil dihapus!\n";
                    return;
                }
            }
            cout << "Subkategori tidak ditemukan!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Fungsi untuk mencari subkategori
void searchSubkategori(menuNode* root) {
    string kategori, subKategori;
    cout << "Masukkan nama kategori: ";
    cin >> kategori;
    cout << "Masukkan nama subkategori yang ingin dicari: ";
    cin >> subKategori;

    // Cari node dengan kategori dan subkategori yang sesuai
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            for (auto& subNode : node->children) {
                if (subNode->subKategori == subKategori) {
                    cout << "Subkategori ditemukan!\n";
                    return;
                }
            }
            cout << "Subkategori tidak ditemukan!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Fungsi untuk mereset subkategori (menghapus semua item pada subkategori)
void resetSubkategori(menuNode*& root) {
    string kategori, subKategori;
    cout << "Masukkan nama kategori: ";
    cin >> kategori;
    cout << "Masukkan nama subkategori yang ingin direset: ";
    cin >> subKategori;

    // Cari node dengan kategori dan subkategori yang sesuai
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            for (auto& subNode : node->children) {
                if (subNode->subKategori == subKategori) {
                    // Hapus semua item pada subkategori yang dimaksud
                    subNode->items.clear();
                    cout << "Subkategori berhasil direset!\n";
                    return;
                }
            }
            cout << "Subkategori tidak ditemukan!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Hapus subkategori
void deleteSubkategori(menuNode*& root, const string& kategori, const string& subKategori) {
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            for (auto it = node->children.begin(); it != node->children.end(); ++it) {
                if ((*it)->subKategori == subKategori) {
                    delete *it;
                    node->children.erase(it);
                    cout << "Subkategori berhasil dihapus!\n";
                    return;
                }
            }
            cout << "Subkategori tidak ditemukan!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Fungsi untuk menambahkan item baru
void addItem(menuNode* node) {
    string namaItem, kategori, subKategori;
    float harga;
    int stok;

    cout << "Masukkan nama item menu : ";
    cin >> namaItem;
    cout << "Masukkan harga : ";
    cin >> harga;
    cout << "Masukkan stok : ";
    cin >> stok;
    cout << "Masukkan ke kategori : ";
    cin >> kategori;
    cout << "Masukkan ke subkategori : ";
    cin >> subKategori;

    itemMenu newItemMenu{namaItem, harga, stok};
    addMenu(node, kategori, subKategori, newItemMenu);
}

// Fungsi untuk menghapus item
void deleteItem(menuNode*& root) {
    string kategori, subKategori, itemName;
    cout << "Masukkan nama kategori: ";
    cin >> kategori;
    cout << "Masukkan nama subkategori: ";
    cin >> subKategori;
    cout << "Masukkan nama item yang ingin dihapus: ";
    cin >> itemName;

    // Cari node dengan kategori, subkategori, dan item yang sesuai
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            for (auto& subNode : node->children) {
                if (subNode->subKategori == subKategori) {
                    for (auto it = subNode->items.begin(); it != subNode->items.end(); ++it) {
                        if (it->namaMenu == itemName) {
                            subNode->items.erase(it);
                            cout << "Item berhasil dihapus!\n";
                            return;
                        }
                    }
                    cout << "Item tidak ditemukan!\n";
                    return;
                }
            }
            cout << "Subkategori tidak ditemukan!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Fungsi untuk mencari item
void searchItem(menuNode* root) {
    string kategori, subKategori, itemName;
    cout << "Masukkan nama kategori: ";
    cin >> kategori;
    cout << "Masukkan nama subkategori: ";
    cin >> subKategori;
    cout << "Masukkan nama item yang ingin dicari: ";
    cin >> itemName;

    // Cari node dengan kategori, subkategori, dan item yang sesuai
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            for (auto& subNode : node->children) {
                if (subNode->subKategori == subKategori) {
                    for (auto& item : subNode->items) {
                        if (item.namaMenu == itemName) {
                            cout << "Item ditemukan!\n";
                            return;
                        }
                    }
                    cout << "Item tidak ditemukan!\n";
                    return;
                }
            }
            cout << "Subkategori tidak ditemukan!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Fungsi untuk mereset item (menghapus semua item pada kategori dan subkategori)
void resetItem(menuNode*& root) {
    string kategori, subKategori;
    cout << "Masukkan nama kategori: ";
    cin >> kategori;
    cout << "Masukkan nama subkategori: ";
    cin >> subKategori;

    // Cari node dengan kategori dan subkategori yang sesuai
    for (auto& node : root->children) {
        if (node->kategori == kategori) {
            for (auto& subNode : node->children) {
                if (subNode->subKategori == subKategori) {
                    // Hapus semua item pada subkategori yang dimaksud
                    subNode->items.clear();
                    cout << "Item berhasil direset!\n";
                    return;
                }
            }
            cout << "Subkategori tidak ditemukan!\n";
            return;
        }
    }
    cout << "Kategori tidak ditemukan!\n";
}

// Fungsi untuk mengupdate harga item
void updateHargaItem(menuNode* root) {
    string kategori, subKategori, itemName;
    float newPrice;

    cout << "Masukkan nama kategori: ";
    cin >> kategori;
    cout << "Masukkan nama subkategori: ";
    cin >> subKategori;
    cout << "Masukkan nama item yang ingin diupdate harganya: ";
    cin >> itemName;

    cout << "Masukkan harga baru: ";
    cin >> newPrice;

    // Panggil fungsi updateHargaItem dengan parameter yang sesuai
    updateHargaItem(root, kategori, subKategori, itemName, newPrice);
}

// Fungsi untuk mengupdate harga item (overload)
void updateHargaItem(menuNode* node, const string& kategori, const string& subKategori, const string& itemName, float newPrice) {
    if (node != nullptr) {
        if (node->kategori == kategori && node->subKategori == subKategori) {
            // Cari item berdasarkan nama
            for (auto& item : node->items) {
                if (item.namaMenu == itemName) {
                    item.harga = newPrice;
                    cout << "Harga item berhasil diupdate!\n";
                    return;
                }
            }
            cout << "Item tidak ditemukan!\n";
        }

        // Mencari di anak-anak node
        for (auto& child : node->children) {
            updateHargaItem(child, kategori, subKategori, itemName, newPrice);
        }
    } else {
        cout << "Kategori atau subkategori tidak ditemukan!\n";
    }
}

// Mencari di anak-anak node
        for (auto& child : node->children) {
            updateHargaItem(child, kategori, subKategori, itemName, newPrice);
        }
    } else {
        cout << "Kategori atau subkategori tidak ditemukan!\n";
    }
}

// Fungsi untuk mengupdate stok item
void updateStokItem(menuNode* node, const string& kategori, const string& subKategori, const string& itemName, int newStok) {
    if (node != nullptr) {
        if (node->kategori == kategori && node->subKategori == subKategori) {
            // Cari item berdasarkan nama
            for (auto& item : node->items) {
                if (item.namaMenu == itemName) {
                    item.stok = newStok;
                    cout << "Stok item berhasil diupdate!\n";
                    return;
                }
            }
            cout << "Item tidak ditemukan!\n";
        }

        // Mencari di anak-anak node
        for (auto& child : node->children) {
            updateStokItem(child, kategori, subKategori, itemName, newStok);
        }
    } else {
        cout << "Kategori atau subkategori tidak ditemukan!\n";
    }
}

// menampilkan menu
void viewMenu(menuNode* node){
    cout << node->kategori << endl;
  if(node != nullptr){
    
    cout << "  " << node->subKategori << ": \n";
    for(const auto& item : node->items){
      cout << "   - " << item.namaMenu << " (Rp" << item.harga << ") - Stok : " << item.stok << endl;
    }
    for(const auto& child : node->children){
      viewMenu(child);
    }
  }
}

// Menambahkan event baru
void addEvent(const string& namaEvent, const string& tanggal, const string& keterangan) {
    eventNode* newEvent = new eventNode{{namaEvent, tanggal, keterangan}, headEvent};
    headEvent = newEvent;
    cout << "Event berhasil ditambahkan!\n";
}

// Menghapus event berdasarkan nama
void deleteEvent(const string& namaEvent) {
    eventNode* prev = nullptr;
    eventNode* current = headEvent;

    while (current != nullptr && current->data.namaEvent != namaEvent) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev != nullptr) {
            prev->next = current->next;
        }
        else {
            headEvent = current->next;
        }

        delete current;
        cout << "Event berhasil dihapus!\n";
    }
    else {
        cout << "Event tidak ditemukan!\n";
    }
}

// Menampilkan daftar event
void viewEvent() {
    if (headEvent != nullptr) {
        cout << "Daftar Event:\n";
        eventNode* current = headEvent;
        while (current != nullptr) {
            cout << "- " << current->data.namaEvent << " (" << current->data.tanggal << "): " << current->data.keterangan << endl;
            current = current->next;
        }
    }
    else {
        cout << "Tidak ada event.\n";
    }
}

// Menampilkan menu
void viewMenu(menuNode* node) {
    cout << node->kategori << endl;
    if (node != nullptr) {

        cout << "  " << node->subKategori << ": \n";
        for (const auto& item : node->items) {
            cout << "   - " << item.namaMenu << " (Rp" << item.harga << ") - Stok : " << item.stok << endl;
        }
        for (const auto& child : node->children) {
            viewMenu(child);
        }
    }
}


int main(){
    menuNode* menuTree = dataMenu();
    int userInput;
    do{
        cout << "UpperEast Kafe" << endl;
        cout << "========================" << endl;
        cout << "1. View Menu" << endl;
        cout << "2. View event" << endl;
        cout << "3. Add event" << endl;
        cout << "4. Add kategori" << endl;
        cout << "5. Add subkategori" << endl;
        cout << "6. Add item" << endl;
        cout << "7. Add stok item" << endl;
        cout << "8. Delete event" << endl;
        cout << "9. Delete kategori" << endl;
        cout << "10. Delete subkategori" << endl;
        cout << "11. Delete item" << endl;
        cout << "12. Update harga item" << endl;
        cout << "13. Update stok item" << endl;
        cout << "14. Search kategori" << endl;
        cout << "15. Search subkategori" << endl;
        cout << "16. Search item" << endl;
        cout << "17. Reset kategori" << endl;
        cout << "18. Reset subkategori" << endl;
        cout << "19. Reset item" << endl;
        cout << "20. View bahan baku" << endl;
        cout << "21. Add stok bahan baku" << endl;
        cout << "0. Exit" << endl;
        cout << "========================" << endl;

        cout << "Input: ";
        cin >> userInput;
        getchar();

        switch (userInput) {
            case 1:
                cout << "Struktur Menu:" << endl;
                viewMenuStructure(menuTree);
                cout << "\nDaftar Menu:" << endl;
                viewFlatMenu(menuTree);
                system("pause");
                break;
			case 2:
                viewEvent();
                system("pause");
                break;
 			case 3:
                string namaEvent, tanggal, keterangan;
                cout << "Masukkan nama event: ";
                cin >> namaEvent;
                cout << "Masukkan tanggal event: ";
                cin >> tanggal;
                cout << "Masukkan keterangan event: ";
                cin.ignore();
                getline(cin, keterangan);

                addEvent(namaEvent, tanggal, keterangan);
                system("pause");
                break;
            case 4:
                addKategori(menuTree);
                system("pause");
                break;
            case 5:
                addSubkategori(menuTree);
                system("pause");
                break;
            case 6:
                addItem(menuTree);
                system("pause");
                break;
            case 7:
                string itemName;
                cout << "Masukkan nama item yang ingin ditambahkan stok: ";
                cin >> itemName;
                addStokitem(menuTree, itemName);
                system("pause");
                break;

//             deleteEvent(&headStok);
    //             system("pause");
    //             break;
     		case 9:
                string kategori;
                out << "Masukkan nama kategori yang ingin dihapus: ";
                cin >> kategori;
                deleteKategori(menuTree, kategori);
                system("pause");
                break;
    		case 10:
                deleteSubkategori(menuTree);
                system("pause");
                break;
    		case 11:
                deleteItem(menuTree);
                system("pause");
                break;
   			 case 12:
                updateHargaItem(menuTree);
                system("pause");
                break;
    //          case 10:
    // //             updatestokItem(&headStok);
    // //             system("pause");
    // //             break;
    		case 14:
                    string kategori;
                    cout << "Masukkan nama kategori yang ingin dicari: ";
                    cin >> kategori;
                    searchKategori(menuTree, kategori);
                    system("pause");
                    break;
   			case 15:
                searchSubkategori(menuTree);
                system("pause");
                break;
    		case 16:
                searchItem(menuTree);
                system("pause");
                break;
    		case 17:
                    string kategori;
                    cout << "Masukkan nama kategori yang ingin direset: ";
                    cin >> kategori;
                    resetKategori(menuTree, kategori);
                    system("pause");
                    break;
    		case 18:
                resetSubkategori(menuTree);
                system("pause");
                break;
   			case 19:
                resetItem(menuTree);
                system("pause");
                break;
    //          case 10:
    // //             viewBahanbaku(&headStok);
    // //             system("pause");
    // //             break;
    //          case 10:
    // //             addBahanbaku(&headStok);
    // //             system("pause");
    // //             break;
            case 0:
                exit(EXIT_SUCCESS);
                cout << "See you" << endl;
                break;
            default :
                cout << "Invalid Input!" << endl;
                break;
        
        }
    } while (userInput != 0);
    

  // bersihkan memori
  delete menuTree;

  return 0;
}
