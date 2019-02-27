#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>

#include "set.h"

#include "memtrace.h"

/// Fix m�ret� string, ami karaktert�mb�t t�rol.
/// M�ret�t a set.h f�jlb�l veszi
class MyString {

    /// T�rolt karaktert�mb
    char str[tarolo_meret + 1];

    /// T�rolja, hogy a karaktert�mb meddig van felt�ltve
    unsigned int siz;

    /// T�rolja, hogy a karaktert�mbben mennyi �res hely van m�g
    unsigned int rem;

public:

    /// Param�ter n�lk�l h�vhat� konstruktor
    /// �res MyString-et hoz l�tre
    MyString(): siz(0), rem(tarolo_meret) { str[0] = '\0'; }

    /// Param�terk�nt adott karaktert�mbb�l MyString-et csin�l
    /// @param s - karaktert�mb
    MyString(const char *s);

    /// Param�terk�nt adott karaktert�mbb�l MyString-et csin�l
    /// szint�n param�terk�nt adott kezd�pontt�l
    /// @param s - karaktert�mb
    /// @param first - kezd�pont indexe
    MyString(const char *s, unsigned int first);

    /// Param�terk�nt adott karakterb�l MyString-et csin�l
    /// @param c - karakter
    MyString(const char c);

    /// M�sol�konstruktor
    MyString(const MyString &s);

    /// Visszaadja a MyString-ben t�rolt karaktert�mb c�m�t
    const char* getStr() const { return str; }

    /// Visszaadja, hogy meddig van felt�ltve a MyString
    unsigned int getSiz() const { return siz; }

    /// Visszaadja, hogy mennyi �res hely van m�g a MyString-ben
    unsigned int getRem() const { return rem; }

    /// Megl�v� MyString-et fel�l�rja a param�terk�nt adott karakterrel
    /// @param c - karakter
    MyString& operator=(const char c);

    /// Megl�v� MyString-et fel�l�rja a param�terk�nt adott karaktert�mbbel
    /// @param s - karaktert�mb
    MyString& operator=(const char *s);

    /// Megl�v� MyString-et fel�l�rja a param�terk�nt adott MyString-gel
    MyString& operator=(const MyString &s);

    /// MyString-et indexelve visszaadja a benne t�rolt karaktert�mb egy karakter�t
    /// @param idx - index
    /// @return referenci�t ad vissza a karakterre
    char& operator[](unsigned int idx);

    /// Megl�v� MyString-hez f�z karaktert
    /// @param c - karakter
    /// @return �j �sszeg MyString-et ad vissza
    MyString operator+(const char c);

    /// Megl�v� MyString-hez f�z karaktert�mb�t
    /// @param s - karaktert�mb
    /// @return �j �sszeg MyString-et ad vissza
    MyString operator+(const char *s);

    /// Megl�v� MyString-hez f�z MyString-et
    /// @param s - MyString
    /// @return �j �sszeg MyString-et ad vissza
    MyString operator+(const MyString s);

    /// Megl�v� MyString tartalm�t t�bbsz�r�zi meg
    /// @param n - szorz�
    /// @return �j szorzat MyString-et ad vissza
    MyString operator*(int n);
};

/// Szabv�nyos kimenetre ki�rja a MyString tartalm�t
std::ostream& operator<<(std::ostream &os, MyString &s);

#endif // MYSTRING_H
