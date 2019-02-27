#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <stdexcept>

#include "MyString.h"
#include "set.h"

#include "memtrace.h"

/// Dinamikus String
/// MyString objektumokat tárol láncolt listában
class MyList {

    /// MyList-ben tárolt ListaElem
    struct ListaElem {

        /// ListaElem-ben tárolt MyString
        MyString adat;

        /// Pointer a következö ListaElem-re
        ListaElem *kov;

        /// ListaElem konstruktora
        ListaElem(ListaElem *p = NULL): kov(p) {}
    };

    /// Pointer az elsö ListaElem-re
    ListaElem *eleje;

    /// MyList-ben tárolt MyString-ek száma
    unsigned int meret;

    /// MyList hossza
    unsigned int hossz;

    /// Tárolja, hogy üres-e a MyList
    bool ures;

public:

    /// MyList iterátora
    class iterator {

        /// Pointert tárol ListaElem-re
        ListaElem *elem;

    public:

        /// Iterátor konstruktora: Eltárolja a paraméterként adott pointert
        /// @param p - ListaElem pointer
        iterator(ListaElem *p = NULL): elem(p) {}

        /// MyList következö elemére lép (pre-inkremens)
        iterator& operator++() {
            if (elem != NULL)
                elem = elem->kov;

            return *this;
        }

        /// MyList következö elemére lép (post-inkremens)
        iterator operator++(int) {
            iterator masolat = *this;
            ++(*this);

            return masolat;
        }

        /// Összehasonlítja (egyenlö) a paraméterként adott iterátorral
        bool operator==(iterator rhs) { return elem==rhs.elem; }

        /// Összehasonlítja (nem egyenlö) a paraméterként adott iterátorral
        bool operator!=(iterator rhs) { return elem!=rhs.elem; }

        /// Iterátor indirekciója (*)
        /// @return MyString referenciát ad vissza
        MyString& operator*() {
            if (elem != NULL)
                return elem->adat;
            else
                throw std::out_of_range("Hibas indirekcio");
        }

        /// Iterátor indirekciója (->)
        /// @return MyString pointert ad vissza
        MyString* operator->() {
            if (elem != NULL)
                return &(elem->adat);
            else
                throw std::out_of_range("Hibas indirekcio");
        }
    };

    /// Iterátort ad vissza a MyList elejére
    iterator begin() const { return iterator(eleje); }

    /// Iterátort ad vissza a MyList végére
    iterator end() const { return iterator(NULL); }

    /// Paraméter nélkül hívható konstruktor
    /// Üres MyList-et hoz létre
    MyList(): meret(0), hossz(0), ures(true) { eleje = new ListaElem; }

    /// Konstruktor: MyList-et hoz létre karaktertömbböl
    /// @param str - karaktertömb
    MyList(const char *str);

    /// Visszaadja a MyList-ben tárolt MyString-ek számát
    unsigned int getMeret() const { return meret; }

    /// Visszaadja a MyList hosszát
    unsigned int getHossz() const { return hossz; }

    /// Visszaadja, hogy üres-e a MyList
    bool isUres() const { return ures; }

    /// MyList-be beszúr MyString-et
    /// @param str - MyString
    MyList& beszur(MyString str);

    /// MyList-be beszúr karaktertömböt MyString-ként
    /// @param str - karaktertömb
    void beszur(const char *str) { beszur(MyString(str)); }

    /// MyList-be beszúr karaktert MyString-ként
    /// @param c - karakter
    void beszur(const char c) { beszur(MyString(c)); }

    /// MyList-böl kitörli a MyString-eket
    /// Üres MyList-et kapunk vissza
    MyList& urit();

    /// Amennyiben a MyList-ben vannak olyan MyString-ek, amelyek nincsenek feltöltve teljesen
    /// és az nem az MyString, akkor átrendezi a karaktereket, hogy ne legyenek üres helyek a MyString-ekben
    MyList& atrendez();

    /// MyList-et indexelve visszaad egy karaktert
    /// Kiszámolja, hogy melyik MyString hányadik karaktere a keresett
    /// @param idx - index
    /// @return referenciát ad vissza a karakterre
    char& operator[](unsigned int idx) const;


    /// Meglévõ MyList-et írja felül MyList-tel
    /// @param rhs - MyList
    /// @return meglévö MyList-et adja vissza felülírva
    MyList& operator=(const MyList &rhs);

    /// Meglévõ MyList-et írja felül karaktertömbbel
    /// @param str - karaktertömb
    /// @return meglévö MyList-et adja vissza felülírva
    MyList& operator=(const char *str);

    /// Meglévõ MyList-hez füz MyList-et
    /// @param rhs - MyList
    /// @return meglévö MyList-et adja vissza hozzáfüzve
    MyList& operator+=(const MyList &rhs);

    /// Meglévõ MyList-hez füz karaktertömböt
    /// @param str - karaktertömb
    /// @return meglévö MyList-et adja vissza hozzáfüzve
    MyList& operator+=(const char *str);

    /// Meglévõ MyList-hez füz MyList-et
    /// @param rhs - MyList
    /// @return új összeg MyList-et ad vissza
    MyList operator+(const MyList &rhs);

    /// Meglévõ MyList-hez füz karaktertömböt
    /// @param str - karaktertömb
    /// @return új összeg MyList-et ad vissza
    MyList operator+(const char *str);

    /// Meglévõ MyList tartalmát többszörözi meg
    /// @param n - szorzó
    /// @return meglévö MyList-et adja vissza referenciaként megszorozva
    MyList& operator*=(int n);

    /// Meglévõ MyList tartalmát többszörözi meg
    /// @param n - szorzó
    /// @return új szorzat MyList-et ad vissza
    MyList operator*(int n);


    /// Összehasonlítja (egyenlö) a paraméterként adott MyList-tel
    /// @param rhs - MyList
    bool operator==(const MyList &rhs);

    /// Összehasonlítja (egyenlö) a paraméterként adott karaktertömbbel
    /// @param str - karaktertömb
    bool operator==(const char *str);

    /// Összehasonlítja (nem egyenlö) a paraméterként adott MyList-tel
    /// @param rhs - MyList
    bool operator!=(const MyList &rhs);

    /// Összehasonlítja (nem egyenlö) a paraméterként adott karaktertömbbel
    /// @param str - karaktertömb
    bool operator!=(const char *str);

    /// Összehasonlítja (kisebb) a paraméterként adott MyList-tel
    /// @param rhs - MyList
    bool operator<(const MyList &rhs);

    /// Összehasonlítja (kisebb) a paraméterként adott karaktertömbbel
    /// @param str - karaktertömb
    bool operator<(const char *str);

    /// Összehasonlítja (nagyobb) a paraméterként adott MyList-tel
    /// @param rhs - MyList
    bool operator>(const MyList &rhs);

    /// Összehasonlítja (nagyobb) a paraméterként adott karaktertömbbel
    /// @param str - karaktertömb
    bool operator>(const char *str);

    /// Összehasonlítja (kisebb-egyenlö) a paraméterként adott MyList-tel
    /// @param rhs - MyList
    bool operator<=(const MyList &rhs);

    /// Összehasonlítja (kisebb-egyenlö) a paraméterként adott karaktertömbbel
    /// @param str - karaktertömb
    bool operator<=(const char *str);

    /// Összehasonlítja (nagyobb-egyenlö) a paraméterként adott MyList-tel
    /// @param rhs - MyList
    bool operator>=(const MyList &rhs);

    /// Összehasonlítja (nagyobb-egyenlö) a paraméterként adott karaktertömbbel
    /// @param str - karaktertömb
    bool operator>=(const char *str);


    /// Másolókonstruktor
    MyList(const MyList &li);

    /// Destruktor felszabadítja a listaelemeket
    ~MyList();

};

/// Szabványos kimenetre kiírja a MyList tartalmát
std::ostream& operator<<(std::ostream &os, MyList &li);

#endif // MYLIST_H
