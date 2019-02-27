#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <stdexcept>

#include "MyString.h"
#include "set.h"

#include "memtrace.h"

/// Dinamikus String
/// MyString objektumokat t�rol l�ncolt list�ban
class MyList {

    /// MyList-ben t�rolt ListaElem
    struct ListaElem {

        /// ListaElem-ben t�rolt MyString
        MyString adat;

        /// Pointer a k�vetkez� ListaElem-re
        ListaElem *kov;

        /// ListaElem konstruktora
        ListaElem(ListaElem *p = NULL): kov(p) {}
    };

    /// Pointer az els� ListaElem-re
    ListaElem *eleje;

    /// MyList-ben t�rolt MyString-ek sz�ma
    unsigned int meret;

    /// MyList hossza
    unsigned int hossz;

    /// T�rolja, hogy �res-e a MyList
    bool ures;

public:

    /// MyList iter�tora
    class iterator {

        /// Pointert t�rol ListaElem-re
        ListaElem *elem;

    public:

        /// Iter�tor konstruktora: Elt�rolja a param�terk�nt adott pointert
        /// @param p - ListaElem pointer
        iterator(ListaElem *p = NULL): elem(p) {}

        /// MyList k�vetkez� elem�re l�p (pre-inkremens)
        iterator& operator++() {
            if (elem != NULL)
                elem = elem->kov;

            return *this;
        }

        /// MyList k�vetkez� elem�re l�p (post-inkremens)
        iterator operator++(int) {
            iterator masolat = *this;
            ++(*this);

            return masolat;
        }

        /// �sszehasonl�tja (egyenl�) a param�terk�nt adott iter�torral
        bool operator==(iterator rhs) { return elem==rhs.elem; }

        /// �sszehasonl�tja (nem egyenl�) a param�terk�nt adott iter�torral
        bool operator!=(iterator rhs) { return elem!=rhs.elem; }

        /// Iter�tor indirekci�ja (*)
        /// @return MyString referenci�t ad vissza
        MyString& operator*() {
            if (elem != NULL)
                return elem->adat;
            else
                throw std::out_of_range("Hibas indirekcio");
        }

        /// Iter�tor indirekci�ja (->)
        /// @return MyString pointert ad vissza
        MyString* operator->() {
            if (elem != NULL)
                return &(elem->adat);
            else
                throw std::out_of_range("Hibas indirekcio");
        }
    };

    /// Iter�tort ad vissza a MyList elej�re
    iterator begin() const { return iterator(eleje); }

    /// Iter�tort ad vissza a MyList v�g�re
    iterator end() const { return iterator(NULL); }

    /// Param�ter n�lk�l h�vhat� konstruktor
    /// �res MyList-et hoz l�tre
    MyList(): meret(0), hossz(0), ures(true) { eleje = new ListaElem; }

    /// Konstruktor: MyList-et hoz l�tre karaktert�mbb�l
    /// @param str - karaktert�mb
    MyList(const char *str);

    /// Visszaadja a MyList-ben t�rolt MyString-ek sz�m�t
    unsigned int getMeret() const { return meret; }

    /// Visszaadja a MyList hossz�t
    unsigned int getHossz() const { return hossz; }

    /// Visszaadja, hogy �res-e a MyList
    bool isUres() const { return ures; }

    /// MyList-be besz�r MyString-et
    /// @param str - MyString
    MyList& beszur(MyString str);

    /// MyList-be besz�r karaktert�mb�t MyString-k�nt
    /// @param str - karaktert�mb
    void beszur(const char *str) { beszur(MyString(str)); }

    /// MyList-be besz�r karaktert MyString-k�nt
    /// @param c - karakter
    void beszur(const char c) { beszur(MyString(c)); }

    /// MyList-b�l kit�rli a MyString-eket
    /// �res MyList-et kapunk vissza
    MyList& urit();

    /// Amennyiben a MyList-ben vannak olyan MyString-ek, amelyek nincsenek felt�ltve teljesen
    /// �s az nem az MyString, akkor �trendezi a karaktereket, hogy ne legyenek �res helyek a MyString-ekben
    MyList& atrendez();

    /// MyList-et indexelve visszaad egy karaktert
    /// Kisz�molja, hogy melyik MyString h�nyadik karaktere a keresett
    /// @param idx - index
    /// @return referenci�t ad vissza a karakterre
    char& operator[](unsigned int idx) const;


    /// Megl�v� MyList-et �rja fel�l MyList-tel
    /// @param rhs - MyList
    /// @return megl�v� MyList-et adja vissza fel�l�rva
    MyList& operator=(const MyList &rhs);

    /// Megl�v� MyList-et �rja fel�l karaktert�mbbel
    /// @param str - karaktert�mb
    /// @return megl�v� MyList-et adja vissza fel�l�rva
    MyList& operator=(const char *str);

    /// Megl�v� MyList-hez f�z MyList-et
    /// @param rhs - MyList
    /// @return megl�v� MyList-et adja vissza hozz�f�zve
    MyList& operator+=(const MyList &rhs);

    /// Megl�v� MyList-hez f�z karaktert�mb�t
    /// @param str - karaktert�mb
    /// @return megl�v� MyList-et adja vissza hozz�f�zve
    MyList& operator+=(const char *str);

    /// Megl�v� MyList-hez f�z MyList-et
    /// @param rhs - MyList
    /// @return �j �sszeg MyList-et ad vissza
    MyList operator+(const MyList &rhs);

    /// Megl�v� MyList-hez f�z karaktert�mb�t
    /// @param str - karaktert�mb
    /// @return �j �sszeg MyList-et ad vissza
    MyList operator+(const char *str);

    /// Megl�v� MyList tartalm�t t�bbsz�r�zi meg
    /// @param n - szorz�
    /// @return megl�v� MyList-et adja vissza referenciak�nt megszorozva
    MyList& operator*=(int n);

    /// Megl�v� MyList tartalm�t t�bbsz�r�zi meg
    /// @param n - szorz�
    /// @return �j szorzat MyList-et ad vissza
    MyList operator*(int n);


    /// �sszehasonl�tja (egyenl�) a param�terk�nt adott MyList-tel
    /// @param rhs - MyList
    bool operator==(const MyList &rhs);

    /// �sszehasonl�tja (egyenl�) a param�terk�nt adott karaktert�mbbel
    /// @param str - karaktert�mb
    bool operator==(const char *str);

    /// �sszehasonl�tja (nem egyenl�) a param�terk�nt adott MyList-tel
    /// @param rhs - MyList
    bool operator!=(const MyList &rhs);

    /// �sszehasonl�tja (nem egyenl�) a param�terk�nt adott karaktert�mbbel
    /// @param str - karaktert�mb
    bool operator!=(const char *str);

    /// �sszehasonl�tja (kisebb) a param�terk�nt adott MyList-tel
    /// @param rhs - MyList
    bool operator<(const MyList &rhs);

    /// �sszehasonl�tja (kisebb) a param�terk�nt adott karaktert�mbbel
    /// @param str - karaktert�mb
    bool operator<(const char *str);

    /// �sszehasonl�tja (nagyobb) a param�terk�nt adott MyList-tel
    /// @param rhs - MyList
    bool operator>(const MyList &rhs);

    /// �sszehasonl�tja (nagyobb) a param�terk�nt adott karaktert�mbbel
    /// @param str - karaktert�mb
    bool operator>(const char *str);

    /// �sszehasonl�tja (kisebb-egyenl�) a param�terk�nt adott MyList-tel
    /// @param rhs - MyList
    bool operator<=(const MyList &rhs);

    /// �sszehasonl�tja (kisebb-egyenl�) a param�terk�nt adott karaktert�mbbel
    /// @param str - karaktert�mb
    bool operator<=(const char *str);

    /// �sszehasonl�tja (nagyobb-egyenl�) a param�terk�nt adott MyList-tel
    /// @param rhs - MyList
    bool operator>=(const MyList &rhs);

    /// �sszehasonl�tja (nagyobb-egyenl�) a param�terk�nt adott karaktert�mbbel
    /// @param str - karaktert�mb
    bool operator>=(const char *str);


    /// M�sol�konstruktor
    MyList(const MyList &li);

    /// Destruktor felszabad�tja a listaelemeket
    ~MyList();

};

/// Szabv�nyos kimenetre ki�rja a MyList tartalm�t
std::ostream& operator<<(std::ostream &os, MyList &li);

#endif // MYLIST_H
