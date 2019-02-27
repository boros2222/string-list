#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>

#include "set.h"

#include "memtrace.h"

/// Fix méretû string, ami karaktertömböt tárol.
/// Méretét a set.h fájlból veszi
class MyString {

    /// Tárolt karaktertömb
    char str[tarolo_meret + 1];

    /// Tárolja, hogy a karaktertömb meddig van feltöltve
    unsigned int siz;

    /// Tárolja, hogy a karaktertömbben mennyi üres hely van még
    unsigned int rem;

public:

    /// Paraméter nélkül hívható konstruktor
    /// Üres MyString-et hoz létre
    MyString(): siz(0), rem(tarolo_meret) { str[0] = '\0'; }

    /// Paraméterként adott karaktertömbbõl MyString-et csinál
    /// @param s - karaktertömb
    MyString(const char *s);

    /// Paraméterként adott karaktertömbbõl MyString-et csinál
    /// szintén paraméterként adott kezdõponttól
    /// @param s - karaktertömb
    /// @param first - kezdõpont indexe
    MyString(const char *s, unsigned int first);

    /// Paraméterként adott karakterbõl MyString-et csinál
    /// @param c - karakter
    MyString(const char c);

    /// Másolókonstruktor
    MyString(const MyString &s);

    /// Visszaadja a MyString-ben tárolt karaktertömb címét
    const char* getStr() const { return str; }

    /// Visszaadja, hogy meddig van feltöltve a MyString
    unsigned int getSiz() const { return siz; }

    /// Visszaadja, hogy mennyi üres hely van még a MyString-ben
    unsigned int getRem() const { return rem; }

    /// Meglévõ MyString-et felülírja a paraméterként adott karakterrel
    /// @param c - karakter
    MyString& operator=(const char c);

    /// Meglévõ MyString-et felülírja a paraméterként adott karaktertömbbel
    /// @param s - karaktertömb
    MyString& operator=(const char *s);

    /// Meglévõ MyString-et felülírja a paraméterként adott MyString-gel
    MyString& operator=(const MyString &s);

    /// MyString-et indexelve visszaadja a benne tárolt karaktertömb egy karakterét
    /// @param idx - index
    /// @return referenciát ad vissza a karakterre
    char& operator[](unsigned int idx);

    /// Meglévõ MyString-hez füz karaktert
    /// @param c - karakter
    /// @return új összeg MyString-et ad vissza
    MyString operator+(const char c);

    /// Meglévõ MyString-hez füz karaktertömböt
    /// @param s - karaktertömb
    /// @return új összeg MyString-et ad vissza
    MyString operator+(const char *s);

    /// Meglévõ MyString-hez füz MyString-et
    /// @param s - MyString
    /// @return új összeg MyString-et ad vissza
    MyString operator+(const MyString s);

    /// Meglévõ MyString tartalmát többszörözi meg
    /// @param n - szorzó
    /// @return új szorzat MyString-et ad vissza
    MyString operator*(int n);
};

/// Szabványos kimenetre kiírja a MyString tartalmát
std::ostream& operator<<(std::ostream &os, MyString &s);

#endif // MYSTRING_H
