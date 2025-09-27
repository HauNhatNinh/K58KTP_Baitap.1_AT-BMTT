#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ====== Caesar Cipher ======
string caesarEncrypt(const string &text, int key) {
    string res = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            res += char((c - base + key) % 26 + base);
        } else res += c;
    }
    return res;
}
string caesarDecrypt(const string &text, int key) {
    return caesarEncrypt(text, 26 - key % 26);
}

// ====== Affine Cipher ======
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}
string affineEncrypt(const string &text, int a, int b) {
    string res = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            res += char(((a * (c - base) + b) % 26) + base);
        } else res += c;
    }
    return res;
}
string affineDecrypt(const string &text, int a, int b) {
    string res = "";
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) return "Khong ton tai nghich dao a!";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int y = c - base;
            res += char((a_inv * (y - b + 26)) % 26 + base);
        } else res += c;
    }
    return res;
}

// ====== Hoán vị Cipher ======
string permutationEncrypt(const string &text, const vector<int> &key) {
    int n = key.size();
    string res = "";
    for (int i = 0; i < (int)text.size(); i += n) {
        string block = text.substr(i, n);
        if ((int)block.size() < n) block.append(n - block.size(), 'X');
        string newBlock = block;
        for (int j = 0; j < n; j++) newBlock[j] = block[key[j]];
        res += newBlock;
    }
    return res;
}
string permutationDecrypt(const string &text, const vector<int> &key) {
    int n = key.size();
    string res = "";
    vector<int> inv(n);
    for (int i = 0; i < n; i++) inv[key[i]] = i;
    for (int i = 0; i < (int)text.size(); i += n) {
        string block = text.substr(i, n);
        string newBlock = block;
        for (int j = 0; j < n; j++) newBlock[j] = block[inv[j]];
        res += newBlock;
    }
    return res;
}

// ====== Vigenere Cipher ======
string vigenereEncrypt(const string &text, const string &key) {
    string res = "";
    int m = key.size();
    for (int i = 0, j = 0; i < (int)text.size(); i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = tolower(key[j % m]) - 'a';
            res += char((c - base + k) % 26 + base);
            j++;
        } else res += c;
    }
    return res;
}
string vigenereDecrypt(const string &text, const string &key) {
    string res = "";
    int m = key.size();
    for (int i = 0, j = 0; i < (int)text.size(); i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = tolower(key[j % m]) - 'a';
            res += char((c - base - k + 26) % 26 + base);
            j++;
        } else res += c;
    }
    return res;
}

// ====== Playfair Cipher ======
vector<vector<char>> generateMatrix(const string &key) {
    string s = "";
    vector<int> exist(26, 0);
    for (char c : key) {
        c = tolower(c);
        if (c == 'j') c = 'i';
        if (isalpha(c) && !exist[c - 'a']) {
            exist[c - 'a'] = 1;
            s += c;
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') continue;
        if (!exist[c - 'a']) s += c;
    }
    vector<vector<char>> matrix(5, vector<char>(5));
    for (int i = 0; i < 25; i++) matrix[i / 5][i % 5] = s[i];
    return matrix;
}
pair<int,int> findPos(const vector<vector<char>> &mat, char c) {
    if (c == 'j') c = 'i';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (mat[i][j] == c) return {i,j};
    return {-1,-1};
}
string playfairEncrypt(const string &text, const string &key) {
    auto mat = generateMatrix(key);
    string res = "";
    string t = "";
    for (char c : text) if (isalpha(c)) t += tolower(c);
    for (int i = 0; i < (int)t.size(); i++) {
        char a = t[i];
        char b = (i+1 < (int)t.size() ? t[i+1] : 'x');
        if (a == b) b = 'x'; else i++;
        auto p1 = findPos(mat,a);
        auto p2 = findPos(mat,b);
        int r1=p1.first,c1=p1.second,r2=p2.first,c2=p2.second;
        if (r1 == r2) {
            res += mat[r1][(c1+1)%5];
            res += mat[r2][(c2+1)%5];
        } else if (c1 == c2) {
            res += mat[(r1+1)%5][c1];
            res += mat[(r2+1)%5][c2];
        } else {
            res += mat[r1][c2];
            res += mat[r2][c1];
        }
    }
    return res;
}
string playfairDecrypt(const string &text, const string &key) {
    auto mat = generateMatrix(key);
    string res = "";
    for (int i = 0; i < (int)text.size(); i += 2) {
        char a = text[i], b = text[i+1];
        auto p1 = findPos(mat,a);
        auto p2 = findPos(mat,b);
        int r1=p1.first,c1=p1.second,r2=p2.first,c2=p2.second;
        if (r1 == r2) {
            res += mat[r1][(c1+4)%5];
            res += mat[r2][(c2+4)%5];
        } else if (c1 == c2) {
            res += mat[(r1+4)%5][c1];
            res += mat[(r2+4)%5][c2];
        } else {
            res += mat[r1][c2];
            res += mat[r2][c1];
        }
    }
    return res;
}

// ====== Main Menu ======
int main() {
    while (true) {
        cout << "\n=== MENU MA HOA / GIAI MA ===\n";
        cout << "1. Caesar\n2. Affine\n3. Hoan vi\n4. Vigenere\n5. Playfair\n0. Thoat\n";
        cout << "Chon phuong phap: ";
        int choice; cin >> choice;
        if (choice == 0) break;

        cout << "1. Ma hoa\n2. Giai ma\nChon: ";
        int act; cin >> act;
        cin.ignore();

        string text, keyStr;
        int a,b;
        cout << "Nhap chuoi: ";
        getline(cin, text);

        string result;
        switch(choice) {
            case 1: { // Caesar
                int k; cout << "Nhap khoa k: "; cin >> k;
                result = (act==1) ? caesarEncrypt(text,k) : caesarDecrypt(text,k);
                break;
            }
            case 2: { // Affine
                cout << "Nhap khoa a (nguyen to cung 26): "; cin >> a;
                cout << "Nhap khoa b: "; cin >> b;
                result = (act==1) ? affineEncrypt(text,a,b) : affineDecrypt(text,a,b);
                break;
            }
            case 3: { // Hoan vi
                int n; cout << "Nhap do dai khoa n: "; cin >> n;
                vector<int> key(n);
                cout << "Nhap khoa hoan vi (0.." << n-1 << "): ";
                for (int i=0;i<n;i++) cin >> key[i];
                result = (act==1) ? permutationEncrypt(text,key) : permutationDecrypt(text,key);
                break;
            }
            case 4: { // Vigenere
                cout << "Nhap khoa chuoi: "; cin >> keyStr;
                result = (act==1) ? vigenereEncrypt(text,keyStr) : vigenereDecrypt(text,keyStr);
                break;
            }
            case 5: { // Playfair
                cout << "Nhap khoa chuoi: "; cin >> keyStr;
                result = (act==1) ? playfairEncrypt(text,keyStr) : playfairDecrypt(text,keyStr);
                break;
            }
            default: result = "Lua chon sai!";
        }

        cout << ">> Ket qua: " << result << "\n";
    }
    return 0;
}
