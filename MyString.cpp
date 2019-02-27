#include <iostream>
#include <stdexcept>
#include <cstring>

#include "set.h"
#include "MyString.h"

#include "memtrace.h"

MyString::MyString(const char *s) {
    if (strlen(s) <= tarolo_meret) {
        strcpy(str, s);
        siz = strlen(s);
        rem = tarolo_meret - siz;
    }
    else {
        for (unsigned int i = 0; i < tarolo_meret; ++i)
            str[i] = s[i];
        str[tarolo_meret] = '\0';
        siz = tarolo_meret;
        rem = 0;
    }
}

MyString::MyString(const char *s, unsigned int first) {
    if (first >= strlen(s))
        throw std::out_of_range("Hibas kezdopont");
    else if ((strlen(s) - first) < tarolo_meret) {
        unsigned int i;
        for(i = first; i < strlen(s); ++i)
            str[i-first] = s[i];
        str[i-first] = '\0';
    }
    else {
        unsigned int i;
        for(i = first; i < (first + tarolo_meret); ++i)
            str[i-first] = s[i];
        str[i-first] = '\0';
    }

    siz = strlen(str);
    rem = tarolo_meret - siz;
}

MyString::MyString(const char c) {
    str[0] = c;
    str[1] = '\0';
    siz = 1;
    rem = tarolo_meret - siz;
}

MyString::MyString(const MyString &s) {
    strcpy(str, s.getStr());
    siz = s.getSiz();
    rem = s.getRem();
}

MyString& MyString::operator=(const char c) {
    str[0] = c;
    str[1] = '\0';
    siz = 1;
    rem = tarolo_meret - siz;

    return *this;
}

MyString& MyString::operator=(const char *s) {
    if (strlen(s) <= tarolo_meret) {
        strcpy(str, s);
        siz = strlen(s);
        rem = tarolo_meret - siz;
    }
    else {
        for (unsigned int i=0; i<tarolo_meret; ++i)
            str[i] = s[i];
        str[tarolo_meret] = '\0';
        siz = tarolo_meret;
        rem = 0;
    }

    return *this;
}

MyString& MyString::operator=(const MyString &s) {
    strcpy(str, s.getStr());
    siz = s.getSiz();
    rem = s.getRem();

    return *this;
}

char& MyString::operator[](unsigned int idx) {
    if (idx >= siz)
        throw std::out_of_range("String tulindexeles"); //return str[siz-1];
    else
        return str[idx];
}

MyString MyString::operator+(const char c) {
    if (rem <= 0) return MyString(str);
    else {
        char temp[siz + 2];
        strcpy(temp, str);
        temp[siz] = c;
        temp[siz+1] = '\0';

        return MyString(temp);
    }
}

MyString MyString::operator+(const char *s) {
    if (rem <= 0) return MyString(str);
    else {
        char temp[siz + strlen(s) + 1];
        strcpy(temp, str);
        strcat(temp, s);

        return MyString(temp);
    }
}

MyString MyString::operator+(const MyString s) {
    if (rem <= 0) return MyString(str);
    else {
        char temp[siz + s.getSiz() + 1];
        strcpy(temp, str);
        strcat(temp, s.getStr());

        return MyString(temp);
    }
}

MyString MyString::operator*(int n) {
    if (rem <= 0 || n <= 1) return MyString(str);
    else {
        MyString temp = str;
        MyString szorzat;
        for (int i = 1; i <= n; ++i)
            szorzat = szorzat + temp;

        return MyString(szorzat);
    }
}

std::ostream& operator<<(std::ostream &os, MyString &s) {
    os << s.getStr();

    return os;
}
