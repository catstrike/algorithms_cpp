#include <algorithm>
#include <iostream>

using namespace std;

#define MOD2(x) (x & 1)

int minimumSwap(string s1, string s2) {
    int count = s1.size();

    if (count == 0 || count != s2.size()) {
        return -1;
    }

    int yx = 0;
    int xy = 0;

    for (int i = 0; i < count; i++) {
        if (s1[i] == 'x' && s2[i] == 'y') xy++;
        if (s1[i] == 'y' && s2[i] == 'x') yx++;
    }

    if (MOD2(MOD2(yx) + MOD2(xy)) == 1) return -1;

    return yx / 2 + MOD2(yx) + xy / 2 + MOD2(xy);
}

void test(string s1, string s2, int expected)
{
    int result = minimumSwap(s1, s2);
    string resultText = result == expected 
        ? "[+]"
        : "[-]";

    cout << resultText << " " << s1 << " : " << s2 << " -> " << result << ", expected " << expected << endl;
}

int main()
{
    test("xx", "yy", 1);
    test("xy", "yx", 2);
    test("xx", "xy", -1);
    test("xxyyxyxyxx", "xyyxyxxxyx", 4);

    return 0;
}