#include <iostream>

#include "MyList.h"
#include "MyString.h"

#include "memtrace.h"

MyList::MyList(const char *str): meret(0), hossz(0), ures(true) {
    eleje = new ListaElem;

    unsigned int darab = 0;

    if (strlen(str) % tarolo_meret == 0)
        darab = strlen(str) / tarolo_meret;
    else
        darab = strlen(str) / tarolo_meret + 1;

    for (unsigned int i = 0; i < darab; ++i)
        beszur(MyString(str, i*tarolo_meret));
}

MyList& MyList::beszur(MyString str) {
    ListaElem *iter;

    for(iter = eleje; iter->kov != NULL; iter = iter->kov) {}

    ListaElem *uj = new ListaElem;
    uj->adat = str;
    uj->kov = NULL;
    meret++;
    hossz += str.getSiz();

    if (iter == eleje && ures) {
        delete eleje;
        eleje = uj;
        ures = false;
    } else
        iter->kov = uj;

    return *this;
}

MyList& MyList::urit() {
    ListaElem *iter = eleje;
    ListaElem *temp = NULL;
    while(iter != NULL) {
        temp = iter->kov;
        delete iter;
        iter = temp;
    }

    eleje = new ListaElem;
    meret = 0;
    hossz = 0;
    ures = true;

    return *this;
}

MyList& MyList::atrendez() {
    char temp[hossz + 1];

    for(unsigned int i = 0; i < hossz; ++i)
        temp[i] = (*this)[i];
    temp[hossz] = '\0';

    return (*this = temp);
}

char& MyList::operator[](unsigned int idx) const {
    if (idx >= hossz)
        throw std::out_of_range("Lista tulindexeles");
    else {
        if (idx < (eleje->adat).getSiz())
            return (eleje->adat)[idx];

        else if (idx < ((eleje->adat).getSiz() + ((eleje->kov)->adat).getSiz()) )
            return ((eleje->kov)->adat)[idx - (eleje->adat).getSiz()];

        else {
            unsigned int elozo = (eleje->adat).getSiz();
            ListaElem *iter = eleje;
            while ((elozo + ((iter->kov)->adat).getSiz()) <= idx) {
                iter = iter->kov;
                elozo += (iter->adat).getSiz();
            }
            return ((iter->kov)->adat)[idx - elozo];
        }
    }
}

MyList& MyList::operator=(const MyList &rhs) {
    urit();

    if (!rhs.ures)
        for(iterator iter = rhs.begin(); iter != rhs.end(); ++iter) {
            MyString str = *iter;
            beszur(str);
        }

    return *this;
}

MyList& MyList::operator=(const char *str) {
    urit();

    if(strlen(str) > 0) {
        unsigned int darab = 0;

        if (strlen(str) % tarolo_meret == 0)
            darab = strlen(str) / tarolo_meret;
        else
            darab = strlen(str) / tarolo_meret + 1;

        for (unsigned int i = 0; i < darab; ++i)
            beszur(MyString(str, i*tarolo_meret));
    }

    return *this;
}

MyList& MyList::operator+=(const MyList &rhs) {
    if (!rhs.ures)
        for(iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
            beszur(*iter);

    return *this;
}

MyList& MyList::operator+=(const char *str) {
    if(strlen(str) > 0) {
        unsigned int darab = 0;

        if (strlen(str) % tarolo_meret == 0)
            darab = strlen(str) / tarolo_meret;
        else
            darab = strlen(str) / tarolo_meret + 1;

        for (unsigned int i = 0; i < darab; ++i)
            beszur(MyString(str, i*tarolo_meret));
    }

    return *this;
}

MyList MyList::operator+(const MyList &rhs) {
    MyList osszeg;

    if(!ures)
        for(iterator iter = begin(); iter != end(); ++iter)
            osszeg.beszur(*iter);

    if(!rhs.ures)
        for(iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
            osszeg.beszur(*iter);

    return osszeg;
}

MyList MyList::operator+(const char *str) {
    MyList osszeg;

    if(!ures)
        for(iterator iter = begin(); iter != end(); ++iter)
            osszeg.beszur(*iter);

    if(strlen(str) > 0) {
        unsigned int darab = 0;

        if (strlen(str) % tarolo_meret == 0)
            darab = strlen(str) / tarolo_meret;
        else
            darab = strlen(str) / tarolo_meret + 1;

        for (unsigned int i = 0; i < darab; ++i)
            osszeg.beszur(MyString(str, i*tarolo_meret));
    }

    return osszeg;
}

MyList& MyList::operator*=(int n) {
    if (n <= 1 || ures) return *this;
    else {
        MyList temp = *this;
        for (int i = 1; i < n; ++i)
            *this = *this + temp;

        return *this;
    }
}

MyList MyList::operator*(int n) {
    MyList szorzat;

    if (n <= 1 || ures) return (szorzat = *this);
    else {
        MyList temp = *this;
        MyList szorzat;
        for (int i = 1; i <= n; ++i)
            szorzat = szorzat + temp;

        return szorzat;
    }
}

bool MyList::operator==(const MyList &rhs) {
    if (hossz != rhs.hossz)
        return false;
    else
        for (unsigned int i = 0; i < hossz; ++i)
            if ((*this)[i] != rhs[i])
                return false;

    return true;
}

bool MyList::operator==(const char *str) {
    MyList temp;
    temp = str;

    return *this == temp;
}

bool MyList::operator!=(const MyList &rhs) {
    if (hossz != rhs.hossz)
        return true;
    else
        for (unsigned int i = 0; i < hossz; ++i)
            if ((*this)[i] != rhs[i])
                return true;

    return false;
}

bool MyList::operator!=(const char *str) {
    MyList temp;
    temp = str;

    return *this != temp;
}

bool MyList::operator<(const MyList &rhs) {
    char temp1[hossz + 1];
    for(unsigned int i = 0; i < hossz; ++i)
        temp1[i] = (*this)[i];
    temp1[hossz] = '\0';

    char temp2[rhs.hossz + 1];
    for(unsigned int i = 0; i < rhs.hossz; ++i)
        temp2[i] = rhs[i];
    temp2[rhs.hossz] = '\0';

    return strcmp(temp1, temp2) < 0;
}

bool MyList::operator<(const char *str) {
    char temp[hossz + 1];
    for(unsigned int i = 0; i < hossz; ++i)
        temp[i] = (*this)[i];
    temp[hossz] = '\0';

    return strcmp(temp, str) < 0;
}

bool MyList::operator>(const MyList &rhs) {
    char temp1[hossz + 1];
    for(unsigned int i = 0; i < hossz; ++i)
        temp1[i] = (*this)[i];
    temp1[hossz] = '\0';

    char temp2[rhs.hossz + 1];
    for(unsigned int i = 0; i < rhs.hossz; ++i)
            temp2[i] = rhs[i];
    temp2[rhs.hossz] = '\0';

    return strcmp(temp1, temp2) > 0;
}

bool MyList::operator>(const char *str) {
    char temp[hossz + 1];
    for(unsigned int i = 0; i < hossz; ++i)
        temp[i] = (*this)[i];
    temp[hossz] = '\0';

    return strcmp(temp, str) > 0;
}

bool MyList::operator<=(const MyList &rhs) {
    if (*this < rhs || *this == rhs)
        return true;
    else
        return false;
}

bool MyList::operator<=(const char *str) {
    if (*this < str || *this == str)
        return true;
    else
        return false;
}

bool MyList::operator>=(const MyList &rhs) {
    if (*this > rhs || *this == rhs)
        return true;
    else
        return false;
}

bool MyList::operator>=(const char *str) {
    if (*this > str || *this == str)
        return true;
    else
        return false;
}

MyList::MyList(const MyList &li): meret(0), hossz(0), ures(true) {
    eleje = new ListaElem;

    if (!li.ures)
        for(iterator iter = li.begin(); iter != li.end(); ++iter)
            beszur(*iter);
}

MyList::~MyList() {
    ListaElem *iter = eleje;
    ListaElem *temp = NULL;

    while(iter != NULL) {
        temp = iter->kov;
        delete iter;
        iter = temp;
    }
}

std::ostream& operator<<(std::ostream &os, MyList &li) {
    MyList::iterator iter;

    for(iter = li.begin(); iter != li.end(); ++iter) {
        os << *iter;
    }

    return os;
}
