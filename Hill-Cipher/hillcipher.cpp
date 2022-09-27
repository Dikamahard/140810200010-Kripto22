#include<iostream>
#include<string>
#include<windows.h>
#include<stdlib.h>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

string removeSpaces(string str);
int inversedKey[2][2];
void inverseKey(int key[2][2]);
string Encrypt(string plainText, int key[2][2]);
string Decrypt(string cipher, int key[2][2]);
int gcd(int m, int n);
int findInverse(int m, int n);
void findKey();

int main(){
    cout << "==============================\n";
	cout << "-----> Hill Cipher(2x2) <-----\n";
    cout << "==============================\n";


	bool menu = true;
	int key[2][2];

	string plainteks,cipher;
	int pil;

	while(menu){
		cout << "\nMenu : " << endl;
		cout << "1. Enkripsi" << endl;
		cout << "2. Dekripsi" << endl;
		cout << "3. Cari Key" << endl;
		cout << "4. Keluar" << endl;
		cout << "Pilih : "; cin >> pil;
		switch(pil){
			case 1:
            	cout << "== ENKRIPSI ==\n";
            	cout << "\nMasukkan matriks key 2x2 :\n";
                for(int a = 0; a < 2; a++){
                    for(int b = 0; b < 2; b++){
                        cout << "key[" << a << "][" << b << "] = ";
                        cin >> key[a][b];
                    }
                }
				cout << "\nInput Plainteks: ";
				cin.ignore();
				getline(cin,plainteks);
				plainteks = removeSpaces(plainteks); 
				transform(plainteks.begin(), plainteks.end(), plainteks.begin(), ::toupper);
				cout << "Cipherteks : " << Encrypt(plainteks,key) << endl << endl;
				break;
			case 2:
            	cout << "== DEKRIPSI ==\n";
            	cout << "Masukkan matriks key 2x2 :\n";
                for(int a = 0; a < 2; a++){
                    for(int b = 0; b < 2; b++){
                        cout << "key[" << a << "][" << b << "] = ";
                        cin >> key[a][b];
                    }
                }
				cout << "\nInput Cipherteks: ";
				cin.ignore();
				getline(cin,cipher);
				cipher = removeSpaces(cipher);
				transform(cipher.begin(), cipher.end(), cipher.begin(), ::toupper); 
				cout << "Plainteks : " << Decrypt(cipher,key) <<endl<<endl;
				break;
			case 3:
				cout << "== CARI KUNCI ==\n";
				cout<<endl;
				findKey();
    
				break;
			default:
				cout << "\nERROR 404" <<endl;
				break;
		}
	}
		
		

}



string removeSpaces(string str){ 
    int count = 0; 
    for (int i = 0; str[i]; i++) 
        if (str[i] == ' ') 
            str[i] = 'X';
	return str; 
} 

void inverseKey(int key[2][2]) {
	int tempKey[2][2];
	tempKey[0][0]=(int)(key[1][1]);
	tempKey[0][1]=(int)((-1) * key[0][1]);
	tempKey[1][0]=(int)((-1) * key[1][0]);
	tempKey[1][1]=(int)(key[0][0]);
	int determinant = (key[0][0]*key[1][1]) - (key[0][1]*key[1][0]);
	int determinantInverse = 0;
    int flag = 0;
    
    for (int i = 0; i < 26; i++){
        flag = (determinant * i) % 26;
        if (flag < 0){
        	flag = flag + 26;
		}
        if (flag == 1){
            determinantInverse = i;
        }
    }
	for(int i=0 ; i<2 ; i++)
		for(int j=0 ; j<2 ; j++){
			if ( tempKey[i][j] < 0 ) {
				int tempNumber = tempKey[i][j]*determinantInverse;
			    inversedKey[i][j] = ((tempNumber%26) + 26)%26;
			}
			else{
				inversedKey[i][j] = (tempKey[i][j]*determinantInverse%26);
			}
		}
}

string Encrypt(string plainText, int key[2][2]) {
	string cipher = "";
	int stringLength = plainText.length();
	if (plainText.length()%2==1)
		stringLength += 1;
	char matrixPlainText[2][stringLength];
	int count=0;
	for(int i=0; i<stringLength/2;i++)
		for(int j=0;j<2;j++){
			if(matrixPlainText[j][i] == 32){
				break;
			}
			matrixPlainText[j][i] = plainText[count];
			count++;
		}
	for(int i = 0; i < stringLength/2; i++){
   		for(int j = 0; j < 2; j++){
   			int tempCipher=0;
   			for(int k = 0; k < 2; k++){
   				int l = key[j][k] * (matrixPlainText[k][i]%65);
   				tempCipher += l;	
			}
			tempCipher = (tempCipher%26) +65;
			cipher += (char)tempCipher;	
		   }
	}
	return cipher;
}

string Decrypt(string cipher, int key[2][2]) {
	string plainText = "";
	int stringLength = cipher.length();
	if (plainText.length()%2==1)
		stringLength = cipher.length()+1;
   	inverseKey(key);
   	char matrixCipher[2][stringLength/2];
	int count=0;
	for(int i=0; i<stringLength/2;i++)
		for(int j=0;j<2;j++){
			matrixCipher[j][i] = cipher[count];
			count++;
		}
	
	for(int i = 0; i < cipher.length()/2; i++){
   		for(int j = 0; j < 2; j++){
   			int tempPlain=0;
   			for(int k = 0; k < 2; k++){
   				int l = inversedKey[j][k] * (matrixCipher[k][i]%65);
   				tempPlain += l;
			   }
			tempPlain = (tempPlain%26) +65;
			plainText += (char)tempPlain;	
		   }
	}
	return plainText;
}

int gcd(int m, int n){
	if (n > m)
		swap(m,n);
	
	do{
		int temp = m % n;
		m = n;
		n = temp;
	} while (n != 0);
	
	return m;
}

int findInverse(int m, int n){
	int t0 = 0,t1 = 1,inverse,q,r,b = m;
	while(r != 1){
		q = m/n;
		r = m%n;
		inverse = t0 - q * t1;
		if(inverse < 0){
			inverse = b - (abs(inverse)%b);
		}else{
			inverse %= b;
		}
		t0 = t1;
		t1 = inverse;
		m = n;
		n = r;	
	}
	return inverse;
}

void findKey(){
	//declaration
	string plainteks,cipherteks;
	int key[2][2],det,determinantInverse,adj[2][2],plainteksInv[2][2],matrixPlainText[2][2],matrixCipher[2][2],counter;
	int p,c;
	int transpose[2][2];
	
	//plaintext input
	cout << "Input Plainteks : ";
	cin.ignore();
	getline(cin,plainteks);
	
	//plaintext to matrix
	counter = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			p = toupper(plainteks[counter]) - 65;
			matrixPlainText[i][j] = p;
			counter++;
		}
	}
	
	//ciphertext input
	cout << "Input Cipherteks : ";
	getline(cin,cipherteks);
	
	//ciphertext to matrix
	counter = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			c = toupper(cipherteks[counter]) - 65;
			matrixCipher[i][j] = c;
			counter++;
		}
	}
	
	// determinan
	det = (matrixPlainText[0][0] * matrixPlainText[1][1]) - (matrixPlainText[0][1] * matrixPlainText[1][0]);
	if(gcd(det,26)==1){
		// inverse dari determinan mod 26
		determinantInverse = findInverse(26,det);
		
		//menghitung adjoin
		adj[0][0] = matrixPlainText[1][1];
		adj[0][1] = (-1)*matrixPlainText[0][1];
		adj[1][0] = (-1)*matrixPlainText[1][0];
		adj[1][1] = matrixPlainText[0][0];
		
		//menghitung matriks inverse dari plainteks
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				plainteksInv[i][j] = determinantInverse * adj[i][j];
				if(plainteksInv[i][j] < 0){
					plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j])%26); 
				}else{
					plainteksInv[i][j] = plainteksInv[i][j];
					plainteksInv[i][j] = plainteksInv[i][j] % 26;
				}
			} 
		}
		
		//Search key
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				key [i][j] = 0;
				for(int k = 0; k < 2; k++){
					key [i][j] += (plainteksInv[i][k] * matrixCipher[k][j]);
				}
				key [i][j] %= 26;
			}
		}
		

		for (int i = 0; i < 2; i++){
    	for (int j = 0; j < 2; j++){
      		transpose[j][i] = key[i][j];
    		}
  		}
  	
	    for(int i = 0; i < 2; i++){
	        for (int j = 0; j < 2; j++){
	            cout << (transpose[i][j]) << "\t";
	        }
	        cout <<endl;
	    } 	 	
	}else{
		cout << "Error 404 " <<endl;
		cout << "Key not found" <<endl<<endl;
	}
	system("pause");
	system("cls");
}