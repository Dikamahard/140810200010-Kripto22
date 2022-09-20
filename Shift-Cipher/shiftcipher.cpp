/*
Rizky Mahardika - 140810200010
19-9-2022
Shift Cipher
*/


#include <iostream>
#include<windows.h>
using namespace std;


string encrypt(string text, int key) {
    string encrypted;

    for(int i=0; i< text.length(); i++) {
        int indexEncrypted;

        if((int)text[i] == 32) {
            indexEncrypted = (int)text[i];
        }else if((int)text[i] >= 97 && (int)text[i] <= 122) {  // alfabet kecil
            indexEncrypted = (int)text[i] + key;
            if(indexEncrypted > 122) {
                indexEncrypted -= 26;
            }
        }else if((int)text[i] >= 65 && (int)text[i] <= 90) {  // alfabet kapital
            indexEncrypted = (int)text[i] + key;
            if(indexEncrypted > 90) {
                indexEncrypted -= 26;
            }
        }

        

        encrypted += (char)indexEncrypted;
    }

    return encrypted;
}

string decrypt(string text, int key) {
    string decrypted;

    for(int i=0; i< text.length(); i++) {
        int indexDecrypted;

        if((int)text[i] == 32) {
            indexDecrypted = (int)text[i];
        }else if((int)text[i] >= 97 && (int)text[i] <= 122) {  //(huruf kecil)
            indexDecrypted = (int)text[i] - key;
            if(indexDecrypted < 97) {
                indexDecrypted += 26;
            }
        }else if((int)text[i] >= 65 && (int)text[i] <= 90) {  //(huruf kapital)
            indexDecrypted = (int)text[i] - key;
            if(indexDecrypted < 65) {
                indexDecrypted += 26;
            }
        }

        

        decrypted += (char)indexDecrypted;
    }

    return decrypted;
}

int main() {
    string text;
    int key;

    cout << "\nMasukkan text : ";
    getline(cin, text);

    cout << "\nMasukkan kunci : ";
    cin >> key;

    cout << "\n>> Encrypted Text : ";
    cout << encrypt(text, key) << endl;

    cout << "\n>> Decrypted Text : ";
    cout << decrypt(encrypt(text, key), key) << endl;

  
}