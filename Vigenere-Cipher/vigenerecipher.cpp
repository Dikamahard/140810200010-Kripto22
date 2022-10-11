/*
Rizky Mahardika - 140810200010
11-10-2022
Vigenere Cipher
*/

#include <iostream>
#include<windows.h>
using namespace std;
#define ma_mod(a,n) ((a%n)+n)%n


string encrypt(string plainText, string extendedKey) {
    string encryptedText;

    for(int i=0; i<plainText.size(); i++) {
        int indexEncrypted;

        indexEncrypted = (((int)plainText[i] + (int)extendedKey[i]) % 97) % 26;
        encryptedText += (char)indexEncrypted + 97;  
    }

    return encryptedText;
}

string decrypt(string encryptedText, string extendedKey) {
    string decryptedText;

    for(int i=0; i<encryptedText.size(); i++) {
        int indexDecrypted;

        indexDecrypted = ma_mod((int)encryptedText[i] - (int)extendedKey[i], 26);
        decryptedText += (char)indexDecrypted + 97;
    }

    return decryptedText;
}


int main() {
    string key;
    string plainText;
    string extendedKey;
    int loopKey = 0;

    cout << "Key : ";
    cin >> key;
    cout << "Plain Text : ";
    cin >> plainText;

    for(int i=0; i<plainText.size(); i++) {
        if(loopKey % key.size() == 0) {
            loopKey = 0;
        } 
        extendedKey += key[loopKey];
        loopKey++;
        
    }
    cout << "Extended Key : " << extendedKey;

    // Encryption
    cout << "\nCipher Text : " << encrypt(plainText, extendedKey);

    // Decryption
    cout << "\nDecrypted Text : " << decrypt(encrypt(plainText, extendedKey), extendedKey);


}