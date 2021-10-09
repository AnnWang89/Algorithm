#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;
int times_2 = 0;
int times_divide = 0;
int times_mult = 0;
string remove_zero(string num)
{
    int len = num.size();
    for (int i = 0; i < len; i++)
    {
        if (num[0] == '0')
        {
            num = num.substr(1, num.size());
        }
        else
            return num;
    }
    return "0";
}
string plusnum(string num1, string num2)
{
    int maxlen = max(num1.size(), num2.size());
    int c = 0;
    int num1_n = 0;
    int num2_n = 0;
    int plus_n = 0;
    string plus_num = "";
    for (int i = 0; i < maxlen; i++)
    {
        if (i >= num1.size())
        {
            num1_n = 0;
        }
        else
        {
            num1_n = num1[num1.size() - 1 - i] - '0';
        }
        if (i >= num2.size())
        {
            num2_n = 0;
        }
        else
        {
            num2_n = num2[num2.size() - 1 - i] - '0';
        }
        plus_n = num1_n + num2_n + c;
        c = plus_n / 10;
        plus_n = plus_n % 10;
        plus_num = to_string(plus_n) + plus_num;
    }
    plus_num = (c == 0 ? "" : "1") + plus_num;
    return plus_num;
}
string subnum(string num1, string num2)
{
    int maxlen = max(num1.size(), num2.size());
    int c = 0;
    int num1_n = 0;
    int num2_n = 0;
    int sub_n = 0;
    string sub_num = "";
    for (int i = 0; i < maxlen; i++)
    {
        if (i >= num1.size())
        {
            num1_n = 0;
        }
        else
        {
            num1_n = num1[num1.size() - 1 - i] - '0';
        }
        if (i >= num2.size())
        {
            num2_n = 0;
        }
        else
        {
            num2_n = num2[num2.size() - 1 - i] - '0';
        }
        num1_n -= c;
        if (num2_n > num1_n)
        {
            num1_n = 10 + num1_n;
            c = 1;
        }
        else
        {
            c = 0;
        }
        sub_n = num1_n - num2_n;
        sub_num = to_string(sub_n) + sub_num;
    }
    return sub_num;
}
string paddingzero(string *num, int len, bool pre)
{
    for (int i = 0; i < len; i++)
    {
        if (pre)
            *num = "0" + *num;

        else
            *num = *num + "0";
    }
    return *num;
}
string karatsuba(string num1, string num2)
{
    if (num1.size() < num2.size())
    {
        string tmp = num1;
        num1 = num2;
        num2 = tmp;
    }
    if (min(num1.size(), num2.size()) <= 1)
    {
        times_2 = times_2 + 1;
        return to_string(stoi(num1) * stoi(num2));
    }
    int maxlen = max(num1.size(), num2.size());
    paddingzero(&num1, maxlen - num1.size(), 1);
    paddingzero(&num2, maxlen - num2.size(), 1);
    int maxlen_2 = maxlen / 2;
    string x = num1.substr(0, maxlen - maxlen_2);
    string y = num1.substr(maxlen - maxlen_2, maxlen);
    string w = num2.substr(0, maxlen - maxlen_2);
    string z = num2.substr(maxlen - maxlen_2, maxlen);
    string xw = karatsuba(x, w);
    string yz = karatsuba(y, z);
    string plus_xw_yz = subnum(subnum(karatsuba(plusnum(x, y), plusnum(w, z)), xw), yz);
    paddingzero(&xw, maxlen_2 * 2, 0);
    paddingzero(&plus_xw_yz, maxlen_2, 0);
    string final_num = plusnum(plusnum(xw, yz), plus_xw_yz);
    return final_num;
}
string dynamic_karatsuba(int divide, string num1, string num2)
{
    if (num1.size() < num2.size())
    {
        string tmp = num1;
        num1 = num2;
        num2 = tmp;
    }
    int maxlen = max(num1.size(), num2.size());
    if (maxlen <= 1)
    {
        times_divide = times_divide + 1;
        return to_string(stoi(num1) * stoi(num2));
    }
    else if (maxlen < divide)
    {
        divide = 2;
    }
    paddingzero(&num1, maxlen - num1.size(), 1);
    paddingzero(&num2, maxlen - num2.size(), 1);
    vector<string> part_multiplication;
    vector<string> sub_num1;
    vector<string> sub_num2;
    int maxlen_divide = maxlen / divide;
    int last_len = (maxlen - maxlen_divide * divide);

    for (int i = 0; i < divide; i++)
    {
        if (i == 0 && last_len != 0)
        {
            string tmp1 = num1.substr(0, last_len + maxlen_divide);
            string tmp2 = num2.substr(0, last_len + maxlen_divide);
            sub_num1.push_back(tmp1);
            sub_num2.push_back(tmp2);
        }
        else
        {
            string tmp1 = num1.substr(last_len + maxlen_divide * i, maxlen_divide);
            string tmp2 = num2.substr(last_len + maxlen_divide * i, maxlen_divide);
            sub_num1.push_back(tmp1);
            sub_num2.push_back(tmp2);
        }
    }
    int terms = sub_num1.size();
    for (int i = 0; i < terms; i++)
    {
        string tmp = dynamic_karatsuba(divide, sub_num1[i], sub_num2[i]);
        part_multiplication.push_back(tmp);
    }
    vector<string> part_plus;
    for (int i = 0; i < terms - 1; i++)
    {
        for (int j = i + 1; j < terms; j++)
        {
            string plus_num1 = sub_num1[i];
            string plus_num2 = sub_num2[i];
            plus_num1 = plusnum(sub_num1[i], sub_num1[j]);
            plus_num2 = plusnum(sub_num2[i], sub_num2[j]);
            string multiplication_plus = dynamic_karatsuba(divide, plus_num1, plus_num2);
            multiplication_plus = subnum(subnum(multiplication_plus, part_multiplication[i]), part_multiplication[j]);
            int pz = part_multiplication.size();
            int padd = (part_multiplication.size() - i - 1);
            padd = padd + (part_multiplication.size() - j - 1);
            paddingzero(&multiplication_plus, ((terms - i - 1) + (terms - j - 1)) * maxlen_divide, 0);
            part_plus.push_back(multiplication_plus);
        }
    }
    for (int i = 0; i < terms; i++)
    {
        paddingzero(&part_multiplication[i], maxlen_divide * (terms - i - 1) * 2, 0);
    }
    string final_num = part_multiplication[0];
    for (int i = 1; i < terms; i++)
    {
        final_num = plusnum(final_num, part_multiplication[i]);
    }
    for (int i = 0; i < part_plus.size(); i++)
    {
        final_num = plusnum(final_num, part_plus[i]);
    }
    return final_num;
}
string multiplication(string num1, string num2)
{
    string final_num = "0";
    int maxlen = max(num1.size(), num2.size());
    paddingzero(&num1, maxlen - num1.size(), 1);
    paddingzero(&num2, maxlen - num2.size(), 1);
    for (int i = maxlen - 1; i >= 0; i--)
    {
        string plus_num = "";
        int c = 0;
        for (int j = maxlen - 1; j >= 0; j--)
        {
            times_mult = times_mult + 1;
            int mult = (num1[i] - '0') * (num2[j] - '0');
            mult = mult + c;
            c = mult / 10;
            mult = mult % 10;
            plus_num = to_string(mult) + plus_num;
        }
        paddingzero(&plus_num, (maxlen - i - 1), 0);
        final_num = plusnum(final_num, plus_num);
    }
    return final_num;
}
int main()
{
    string num1 = "";
    string num2 = "";
    string ans = "";
    int divide = 4;
    double start_time = 0.0;
    double end_time = 0.0;
    cout << "number1:";
    cin >> num1;
    cout << "number2:";
    cin >> num2;
    start_time = clock();
    ans = remove_zero(dynamic_karatsuba(divide, num1, num2));
    end_time = clock();
    cout << "divide " << divide << "  :" << ans << endl
         << (end_time - start_time) / CLOCKS_PER_SEC << endl
         << "times:" << times_divide << endl;

    start_time = clock();
    ans = remove_zero(karatsuba(num1, num2));
    end_time = clock();
    cout << "divide 2  :" << ans << endl
         << (end_time - start_time) / CLOCKS_PER_SEC << endl
         << "times:" << times_2 << endl;

    start_time = clock();
    ans = remove_zero(multiplication(num1, num2));
    end_time = clock();
    cout << "multiplication  :" << ans << endl
         << (end_time - start_time) / CLOCKS_PER_SEC << endl
         << "times:" << times_mult << endl;
    system("pause");
}
