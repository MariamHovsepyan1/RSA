#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

void getTwoRandomPrimes(int& prime1, int& prime2)
{
    int primes[70] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                      31, 37, 41, 43, 47, 53, 59, 61, 67,
                      71, 73, 79, 83, 89, 97, 101, 103,
                      107, 109, 113, 127, 131, 137, 139,
                      149, 151, 157, 163, 167, 173, 179,
                      181, 191, 193, 197, 199, 211, 223,
                      227, 229, 233, 239, 241, 251, 257,
                      263, 269, 271, 277, 281, 283, 293,
                      307, 311, 313, 317, 331, 337, 347, 349 };

    srand(time(0));
    int i1, i2;
    i1 = rand() % 70;
    do{
        i2 = rand() % 70;
    }while(i1 == i2);

    prime1 = primes[i1];
    prime2 = primes[i2];

    cout << "prime1 = " << prime1 << endl;
    cout << "prime2 = " << prime2 << endl;
}

int GCD(int a, int b)
{
    int temp;

    while(b)
    {
        temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}

void generateKeys(int& n, int& e, int& d)
{
    int prime1, prime2;
    int phi;

    getTwoRandomPrimes(prime1, prime2);

    n = prime1 * prime2;
    phi = (prime1 - 1) * (prime2 - 1);

    e = 2;
    while(GCD(e, phi) != 1)
        ++e;

    // d = (k*Φ(n) + 1) / e for some integer k
    d = 2;
    while((d * e) % phi != 1)
        ++d;

    cout << "n = " << n << endl;
    cout << "e = " << e << endl;
    cout << "d = " << d << endl;
}

long encryptChar(char ch, int n, int e)
{
    int c = (int)ch;
    long encryptedChar = 1;
    while(e--)
    {
        encryptedChar *= c;
        encryptedChar %= n;
    }
    return encryptedChar;
}

char decryptChar(long c, int n, int d)
{
    long decryptedChar = 1;
    while(d--)
    {
        decryptedChar *= c;
        decryptedChar %= n;
    }
    return (char)decryptedChar;
}

vector<long> encrypt(string message, int n, int e)
{
    vector<long> result;
    for(char& ch : message)
        result.push_back(encryptChar(ch, n, e));
    return result;
}

string decrypt(vector<long> encryptedMessage, int n, int d)
{
    string result;
    for(long& num : encryptedMessage)
        result += decryptChar(num, n, d);
    return result;
}

string vectorToString(vector<long> vec)
{
    string result;
    for(long& num : vec)
        result += to_string(num) += " ";
    return result;
}

int main()
{
    int n, e, d;
    generateKeys(n, e, d);

    string message { "This is my message." };
    cout << "\nThe message:\n" << message << endl;

    vector<long> encryptedMessage = encrypt(message, n, e);
    cout << "\nEncrypted message:\n" << vectorToString(encryptedMessage) << endl;

    message = decrypt(encryptedMessage, n, d);
    cout << "\nDecrypted message:\n" << message << endl;
}