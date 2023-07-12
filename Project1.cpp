#include<iostream>
#include<stdio.h>
using namespace std;

void printBin(char bin[]) {
    for (int i = 0; i < 8; i++) {
        cout << bin[i];
        if (i == 3) cout << " ";
    }
    cout << endl;
}

void copyBin(char bin[], char res[]) {
    for (int i = 0; i < 8; i++)
        res[i] = bin[i];
}

void DecimalToBinary(char bin[]) {
    int num;
    cin >> num;

    for (int i = 0; i < 8; i++) 
        bin[i] = (num >> 7 - i) & 1 ? '1' : '0';
}

bool addBin(char bin1[], char bin2[], char res[]) {
    bool carry = false;

    for (int i = 7; i >= 0; i--) {
        char temp = bin1[i];
        ((bin1[i] ^ bin2[i]) ^ carry) ? res[i] = '1' : res[i] = '0';

        if ((temp == '1' && bin2[i] == '1') ||
            (temp == '1' && carry) ||
            (bin2[i] == '1' && carry)) carry = true;
        else carry = false;
    }

    return carry;
}

void negBin(char bin[]) {
    char temp[] = "00000000", one[] = "00000001";
    for (int i = 0; i < 8; i++)
        bin[i] == '1' ? temp[i] = '0' : temp[i] = '1';
    addBin(temp, one, bin);
}

void subBin(char bin1[], char bin2[], char res[]) {
    char one[] = "00000001";
    char temp[8];

    copyBin(bin2, temp);
    negBin(temp);
    addBin(bin1, temp, res);
}

int BinaryToDecimal(char bin[]) {
    int num = 0;
    bool neg = false;

    if (bin[0] == '1') {
        negBin(bin);
        neg = true;
    }
    for (int i = 0; i < 8; i++)
        (bin[7 - i] == '1') ?
        num = (1 << i) | num : num = ~(1 << i) & num;
    return neg ? -num : num;
}

void shiftRight(char a[], char b[], char& q) {
    q = b[7];
    for (int i = 7; i >= 0; i--)
        b[i] = b[i - 1];
    b[0] = a[7];
    for (int i = 7; i >= 0; i--)
        a[i] = a[i - 1];
    a[0] = a[1];
}

void shiftLeft(char a[], char b[]) {
    char temp = b[0];
    for (int i = 0; i < 7; i++)
        b[i] = b[i + 1];
    b[7] = '0';
    for (int i = 0; i < 7; i++)
        a[i] = a[i + 1];
    a[7] = temp;
}

void mulBin(char bin1[], char bin2[], char res[]) {
    char q[9], m[8], temp[]="0000000000000000", a[] = "00000000";
    copyBin(bin1, q);
    copyBin(bin2, m);

    q[8] = '0';
    int k = 8;
    while (k > 0) {
        if (q[7] == '1' && q[8] == '0')
            subBin(a, m, a);
        else if (q[7] == '0' && q[8] == '1')
            addBin(a, m, a);

        shiftRight(a, q, q[8]);
        k--;
    }
    copyBin(q, res);
}

bool checkZero(char bin[]) {
    for(int i = 0; i < 8; i++) {
        if(bin[i] != '0') return false;
    }
    return true;
}

void divBin(char bin1[], char bin2[], char res[]) {
    if(checkZero(bin2)) {
        cout << "Can't be divided by zero!" << endl;
        return;
    }
    char q[8], m[8], a[9] = "00000000";
    char* temp = &q[7];
    copyBin(bin1, q);
    copyBin(bin2, m);
    
    int i = 0;
    while (i < 8) {
        if (q[i] == '1') break;
        i++;
    }

    if (q[0] == '1')
        negBin(q);
    if (m[0] == '1')
        negBin(m);

    int k = 8;
    while (k > 0) {
        shiftLeft(a, q);
        subBin(a, m, a);
        if (a[0] == '1') {
            addBin(a, m, a);
            *temp = '0';
        }
        else *temp = '1';

        k--;
    }
    if (bin1[0] ^ bin2[0]) negBin(q);
    copyBin(q, res);
}

void modBin(char bin1[], char bin2[], char res[]) {
    if(checkZero(bin2)) {
        cout << "Can't be divided by zero!" << endl;
        return;
    }
    char q[8], m[8], a[9] = "00000000";
    char* temp = &q[7];
    copyBin(bin1, q);
    copyBin(bin2, m);

    int i = 0;
    while (i < 8) {
        if (q[i] == '1') break;
        i++;
    }

    if (q[0] == '1')
        negBin(q);
    if (m[0] == '1')
        negBin(m);

    int k = 8;
    while (k > 0) {
        shiftLeft(a, q);
        subBin(a, m, a);
        if (a[0] == '1') {
            addBin(a, m, a);
            *temp = '0';
        }
        else *temp = '1';

        k--;
    }
    copyBin(a, res);
}

int main(){
    char bin1[8], bin2[8], res[] = "00000000";

    //Input decimal
    cout << "Input A (Decimal): ";
    DecimalToBinary(bin1);
    cout << "Input B (Decimal): ";
    DecimalToBinary(bin2);

    //Output binary
    cout << "A (Binary): ";
    printBin(bin1);
    cout << "B (Binary): ";
    printBin(bin2);

    //Addition
    addBin(bin1, bin2, res);
    cout << "A + B (Binary): ";
    printBin(res);
    cout << "A + B (Decimal): ";
    cout << BinaryToDecimal(res) << endl;

    //Subtraction
    subBin(bin1, bin2, res);
    cout << "A - B (Binary): ";
    printBin(res);
    cout << "A - B (Decimal): ";
    cout << BinaryToDecimal(res) << endl;

    //Multiplication
    for (int i = 0; i < 8; i++) res[i] = '0';
    mulBin(bin1, bin2, res);
    cout << "A * B (Binary): ";
    printBin(res);
    cout << "A * B (Decimal): ";
    cout << BinaryToDecimal(res) << endl;

    //Division
    for (int i = 0; i < 8; i++) res[i] = '0';
    divBin(bin1, bin2, res);
    cout << "A / B (Binary): ";
    printBin(res);
    cout << "A / B (Decimal): ";
    cout << BinaryToDecimal(res) << endl;

    //Modulo
    for (int i = 0; i < 8; i++) res[i] = '0';
    modBin(bin1, bin2, res);
    cout << "A % B (Binary): ";
    printBin(res);
    cout << "A % B (Decimal): ";
    cout << BinaryToDecimal(res) << endl;

    return 0;
}