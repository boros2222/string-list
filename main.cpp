#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "MyString.h"
#include "MyList.h"

#include "gtest_lite.h"
#include "memtrace.h"

using std::cout;
using std::cin;
using std::endl;


int main(int argc, char* argv[]) {

    /***********************
     * MyString tesztelése
     **********************/
    cout << endl << "==== [ MyString TESZTELESE ] ====" << endl;

    /// 1. teszt
    TEST(MyString, getStr) {
        EXPECT_STR_EQ("teszt", MyString("teszt").getStr());

        try {
            EXPECT_STR_EQ("szt", MyString("teszt", 2).getStr());
        } catch (std::exception &e) {
            cout << e.what() << endl;
        }

        MyString a("teszt");
        MyString b = a;
        EXPECT_STR_EQ("teszt", b.getStr());

        MyString c;
        c = a;
        EXPECT_STR_EQ("teszt", c.getStr());

        MyString d;
        d = "012345678901234567890123456789";
        EXPECT_STR_EQ("01234567890123456789", d.getStr());
    } END

    /// 2. teszt
    TEST(MyString, getSiz) {
        EXPECT_EQ(5, MyString("teszt").getSiz());
    } END

    /// 3. teszt
    TEST(MyString, getRem) {
        EXPECT_EQ(15, MyString("teszt").getRem());
    } END

    /// 4. teszt
    TEST(MyString, operator[]) {
        try {
            MyString a("teszt");
            char str[6];

            for (unsigned int i = 0; i < a.getSiz(); ++i)
                str[i] = a[i];
            str[5] = '\0';

            EXPECT_STR_EQ("teszt", str);
        } catch (std::exception &e) {
            cout << e.what() << endl;
        }
    } END

    /// 5. teszt
    TEST(MyString, operator+) {
        MyString a;
        a = a + 'a';
        EXPECT_STR_EQ("a", a.getStr());
        a = a + "bc";
        EXPECT_STR_EQ("abc", a.getStr());
        a = a + MyString("de");
        EXPECT_STR_EQ("abcde", a.getStr());
    } END

    /// 6. teszt
    TEST(MyString, operator*) {
        MyString a("teszt");
        a = a * 3;
        EXPECT_STR_EQ("teszttesztteszt", a.getStr());
    } END


    /**********************
     * MyList tesztelése
     *********************/
    cout << endl << "==== [ MyList TESZTELESE ] ====" << endl;

    /// 1. teszt
    TEST(MyList, getHossz) {
        EXPECT_EQ(5, MyList("teszt").getHossz());
    } END

    /// 2. teszt
    TEST(MyList, getMeret) {
        EXPECT_EQ(1, MyList("teszt").getMeret());
    } END

    /// 3. teszt
    TEST(MyList, isUres) {
        EXPECT_TRUE(MyList("").isUres());
        EXPECT_FALSE(MyList("teszt").isUres());
    } END

    /// 4. teszt
    TEST(MyList, beszur) {
        MyList a;
        a.beszur("teszt");
        std::ostringstream os;
        os << a;
        EXPECT_STR_EQ("teszt", os.str().c_str());
    } END

    /// 5. teszt
    TEST(MyList, urit) {
        MyList a("teszt");
        a.urit();

        std::ostringstream os;
        os << a;
        EXPECT_STR_EQ("", os.str().c_str());
    } END

    /// 6. teszt
    TEST(MyList, atrendez) {
        MyList a;
        a.beszur("teszt");
        a.beszur("teszt");
        EXPECT_EQ(2, a.getMeret());
        a.atrendez();
        EXPECT_EQ(1, a.getMeret());
    } END

    /// 7. teszt
    TEST(MyList, operator[]) {
        try {
            MyList a("teszt");
            char str[6];

            for (unsigned int i = 0; i < a.getHossz(); ++i)
                str[i] = a[i];
            str[5] = '\0';

            EXPECT_STR_EQ("teszt", str);
        } catch (std::exception &e) {
            cout << e.what() << endl;
        }
    } END

    /// 8. teszt
    TEST(MyList, operator=) {
        MyList a;
        a = "teszt";
        std::ostringstream os;
        os << a;
        EXPECT_STR_EQ("teszt", os.str().c_str());

        MyList b;
        b = MyList("teszt");
        std::ostringstream osb;
        osb << b;
        EXPECT_STR_EQ("teszt", osb.str().c_str());

        MyList c = b;
        std::ostringstream osc;
        osc << b;
        EXPECT_STR_EQ("teszt", osc.str().c_str());
    } END

    /// 9. teszt
    TEST(MyList, operator+=) {
        MyList a("teszt");
        a += "teszt";
        std::ostringstream os;
        os << a;
        EXPECT_STR_EQ("tesztteszt", os.str().c_str());

        MyList b("teszt");
        b += MyList("teszt");
        std::ostringstream osb;
        osb << b;
        EXPECT_STR_EQ("tesztteszt", os.str().c_str());
    } END

    /// 10. teszt
    TEST(MyList, operator+) {
        MyList a("teszt");
        a = a + "teszt";
        std::ostringstream os;
        os << a;
        EXPECT_STR_EQ("tesztteszt", os.str().c_str());

        MyList b("teszt");
        b = b + MyList("teszt");
        std::ostringstream osb;
        osb << b;
        EXPECT_STR_EQ("tesztteszt", os.str().c_str());
    } END

    /// 11. teszt
    TEST(MyList, operator*=) {
        MyList a("teszt");
        a *= 2;
        std::ostringstream os;
        os << a;
        EXPECT_STR_EQ("tesztteszt", os.str().c_str());
    } END

    /// 12. teszt
    TEST(MyList, operator*) {
        MyList a("teszt");
        a = a * 2;
        std::ostringstream os;
        os << a;
        EXPECT_STR_EQ("tesztteszt", os.str().c_str());
    } END

    /// 13. teszt
    TEST(MyList, operator==) {
        EXPECT_TRUE(MyList("teszt") == "teszt");
        EXPECT_TRUE(MyList("teszt") == MyList("teszt"));
        EXPECT_FALSE(MyList("teszt") == "abc");
        EXPECT_FALSE(MyList("teszt") == MyList("abc"));
    } END

    /// 14. teszt
    TEST(MyList, operator!=) {
        EXPECT_FALSE(MyList("teszt") != "teszt");
        EXPECT_FALSE(MyList("teszt") != MyList("teszt"));
        EXPECT_TRUE(MyList("teszt") != "abc");
        EXPECT_TRUE(MyList("teszt") != MyList("abc"));
    } END

    /// 15. teszt
    TEST(MyList, operator<) {
        EXPECT_TRUE(MyList("teszt") < "tesztteszt");
        EXPECT_TRUE(MyList("teszt") < MyList("tesztteszt"));
        EXPECT_FALSE(MyList("teszt") < "abc");
        EXPECT_FALSE(MyList("teszt") < MyList("abc"));
    } END

    /// 16. teszt
    TEST(MyList, operator>) {
        EXPECT_FALSE(MyList("teszt") > "tesztteszt");
        EXPECT_FALSE(MyList("teszt") > MyList("tesztteszt"));
        EXPECT_TRUE(MyList("teszt") > "abc");
        EXPECT_TRUE(MyList("teszt") > MyList("abc"));
    } END

    /// 17. teszt
    TEST(MyList, operator<=) {
        EXPECT_TRUE(MyList("teszt") <= "tesztteszt");
        EXPECT_TRUE(MyList("teszt") <= MyList("tesztteszt"));
        EXPECT_TRUE(MyList("teszt") <= "teszt");
        EXPECT_TRUE(MyList("teszt") <= MyList("teszt"));
        EXPECT_FALSE(MyList("teszt") <= "abc");
        EXPECT_FALSE(MyList("teszt") <= MyList("abc"));
    } END

    /// 18. teszt
    TEST(MyList, operator>=) {
        EXPECT_FALSE(MyList("teszt") >= "tesztteszt");
        EXPECT_FALSE(MyList("teszt") >= MyList("tesztteszt"));
        EXPECT_TRUE(MyList("teszt") >= "teszt");
        EXPECT_TRUE(MyList("teszt") >= MyList("teszt"));
        EXPECT_TRUE(MyList("teszt") >= "abc");
        EXPECT_TRUE(MyList("teszt") >= MyList("abc"));
    } END

    /// 19. teszt
    TEST(MyList, iterator) {
        try {
            MyList a;
            a.beszur("abc");
            a.beszur("def");
            a.beszur("ghi");

            MyList::iterator iter;

            iter = a.begin();
            EXPECT_STR_EQ("abc", (*iter).getStr());

            ++iter;
            EXPECT_STR_EQ("def", (*iter).getStr());

            ++iter;
            EXPECT_STR_EQ("ghi", (*iter).getStr());
        } catch (std::exception &e) {
            cout << e.what() << endl;
        }
    } END


    /*********************************
     * Paraméterként kapott stringek
     ********************************/
    MyList ltomb[argc];
    cout << endl << "==== [ PARAMETEREK ] ====" << endl;
    for(int i = 0; i < argc; ++i) {
        ltomb[i] = argv[i];
        cout << " (" << i << "). String tartalma:" << endl;
        cout << " " << ltomb[i] << endl;
        cout << " Tarolok szama: " << ltomb[i].getMeret() << endl;
        cout << " String hossza: " << ltomb[i].getHossz() << endl;
        if (i < argc - 1)
            cout << "=========================" << endl;
    }

    return 0;
}
