#include <iostream>
#include <climits>
#include <string>
using namespace std;

class BigInteger
{
public:
    string data;
    bool ispositive;

    BigInteger(long long int data)
    {
        if (data >= 0)
        {
            this->ispositive = true;
            this->data = to_string(data);
        }
        else
        {
            this->ispositive = false;
            this->data = to_string(-data);
        }
    }

    BigInteger(string data)
    {
        this->data = "";
        int i = 0;
        if (data[i] == '-')
        {
            this->ispositive = false;
            i++;
        }
        else
            this->ispositive = true;
        while (data[i] == '0')
            i++;
        for (int j = i; j < data.size(); j++)
            this->data += data[j];
        if (this->data.size() == 0)
        {
            this->data = "0";
            this->ispositive = true;
        }
    }

    bool operator==(const BigInteger &b)
    {
        if (!(this->ispositive == b.ispositive))
            return false;
        else if (!(this->data.size() == b.data.size()))
            return false;
        else
            for (int i = 0; i < this->data.size(); i++)
                if (this->data[i] != b.data[i])
                    return false;
        return true;
    }

    bool operator>(const BigInteger &b)
    {
        if (this->ispositive && !b.ispositive)
            return true;
        else if (!this->ispositive && b.ispositive)
            return false;
        //if both positive
        else if (this->ispositive && b.ispositive)
        {
            if (this->data.size() > b.data.size())
                return true;
            else if (this->data.size() == b.data.size())
            {
                for (int i = 0; i < this->data.size();)
                {
                    //if all digits till here are equal and this one's greater then true
                    if (this->data[i] > b.data[i])
                        return true;
                    // if b's digit is greater now then false
                    else if (this->data[i] < b.data[i])
                        return false;
                    // if both digit same then increment
                    else
                        i++;
                }
                //if all digits same then false since they are equal
                return false;
            }
            else
                return false;
        }
        // if both negative
        else if (!this->ispositive && !b.ispositive)
        {
            if (this->data.size() < b.data.size())
                return true;
            else if (this->data.size() == b.data.size())
            {
                for (int i = 0; i < this->data.size();)
                    if (this->data[i] < b.data[i])
                        return true;
                    else if (this->data[i] > b.data[i])
                        return false;
                    else
                        i++;
                return false;
            }
            else
                return true;
        }
        return false;
    }

    bool operator>=(const BigInteger &b)
    {
        return (*this > b) || (*this == b);
    }

    bool operator<(const BigInteger &b)
    {
        return !(*this >= b);
    }

    bool operator<=(const BigInteger &b)
    {
        return !(*this > b);
    }

    BigInteger operator+(BigInteger &b)
    {
        BigInteger result(0);
        result.data = "";
        //get the bigger and smaller of the two
        BigInteger *bigger, *smaller;
        if (*this >= b)
        {
            bigger = this;
            smaller = &b;
        }
        else
        {
            bigger = &b;
            smaller = this;
        }

        int balance = 0;
        int i = 0;
        for (; i < smaller->data.size(); i++)
        {
            int d1 = bigger->data[bigger->data.size() - 1 - i] - '0';
            int d2 = smaller->data[smaller->data.size() - 1 - i] - '0';
            int sum = d1 + d2 + balance;
            balance = sum / 10;
            sum %= 10;
            result.data = char(sum + '0') + result.data;
        }

        for (int j = i; j < bigger->data.size(); j++)
        {
            int d = bigger->data[bigger->data.size() - 1 - j] - '0';
            int sum = d + balance;
            balance = sum / 10;
            sum %= 10;
            result.data = char(sum + '0') + result.data;
        }

        if (balance > 0)
            result.data = char(balance + '0') + result.data;

        if (!this->ispositive && !b.ispositive)
            result.ispositive = false;
        return BigInteger(result.data);
    }

    BigInteger operator+(long long int b)
    {
        BigInteger temp(b);
        return *this + temp;
    }

    BigInteger operator*(BigInteger &b)
    {
        BigInteger result(0);
        // go through b in outside loop
        for (int i = b.data.size() - 1; i >= 0; i--)
        {
            int multcarry = 0;
            int d2 = b.data[i] - '0';
            BigInteger tempresult(0);
            tempresult.data = "";
            for (int j = i + 1; j < b.data.size(); j++)
            {
                tempresult.data += '0';
            }
            // go through this in inside loop
            for (int j = this->data.size() - 1; j >= 0; j--)
            {
                int d1 = this->data[j] - '0';
                int tempmult = d1 * d2 + multcarry;
                multcarry = tempmult / 10;
                tempmult %= 10;
                tempresult.data = char(tempmult + '0') + tempresult.data;
            }
            if (multcarry > 0)
            {
                tempresult.data = char(multcarry + '0') + tempresult.data;
            }
            result = result + tempresult;
        }
        if (this->ispositive != b.ispositive)
            result.ispositive = false;
        return BigInteger(result.data);
    }

    BigInteger operator*(long long int b)
    {
        BigInteger temp(b);
        return *this * temp;
    }

    BigInteger operator-(long long int b)
    {
        BigInteger temp(b);
        return *this - temp;
    }

    BigInteger operator-(BigInteger &b)
    {
        if (this->ispositive && !b.ispositive)
        {
            b.ispositive = true;
            BigInteger result = *this + b;
            b.ispositive = false;
            return result;
        }
        else if (!(this->ispositive) && b.ispositive)
        {
            b.ispositive = false;
            BigInteger result = *this + b;
            b.ispositive = true;
            return result;
        }
        BigInteger result(0);
        result.data = "";

        int carry = 0;
        int i = 0;
        for (; i < b.data.size(); i++)
        {
            int d1 = this->data[this->data.size() - 1 - i] - '0';
            int d2 = b.data[b.data.size() - 1 - i] - '0';
            int sum = d1 - d2 - carry;
            if (sum < 0)
            {
                carry = 1;
                sum = 10 + sum;
            }
            else
                carry = 0;
            result.data = char(sum + '0') + result.data;
        }

        for (int j = i; j < this->data.size(); j++)
        {
            int d = this->data[this->data.size() - 1 - j] - '0';
            int sum = d - carry;
            if (sum < 0)
            {
                carry = 1;
                sum = 10 + sum;
            }
            else
                carry = 0;
            result.data = char(sum + '0') + result.data;
        }

        return BigInteger(result);
    }

    BigInteger operator<<(int n)
    {
        BigInteger result(this->data);
        for (int i = 1; i <= n; i++)
            result = result * 2;
        return result;
    }

    BigInteger operator>>(int n)
    {
        BigInteger result(this->data);
        for (int i = 1; i <= n; i++)
        {
            int balance = 0;
            BigInteger tempresult(0);
            tempresult.data = "";
            for (int j = 0; j < result.data.size(); j++)
            {
                int digit = result.data[j] - '0';
                int divires = (10 * balance + digit) / 2;
                if ((10 * balance + digit) & 1)
                    balance = 1;
                else
                    balance = 0;
                tempresult.data = tempresult.data + char(divires + '0');
            }
            result.data = tempresult.data;
        }
        return BigInteger(result.data);
    }

    BigInteger operator%(BigInteger &b)
    {
        if (*this < b)
            return *this;
        if (*this == b)
            return BigInteger("0");

        // Newton Raphson division
        // for each new digit find the quotient which brings b*quotient closest to dividend
        BigInteger result(0);
        result.data = "";
        for (int i = 0; i < this->data.size(); i++)
        {
            result.data = result.data + this->data[i];
            result.data = BigInteger(result.data).data;

            long long int quotient = 0;
            long long int lowerbound = 0;
            long long int upperbound = LLONG_MAX;

            if (result < b)
            {
                quotient = 0;
            }
            else
                while (lowerbound <= upperbound)
                {
                    long long int mid = lowerbound + ((upperbound - lowerbound) >> 1);
                    if (BigInteger(mid) * b > result)
                    {
                        quotient = mid;
                        upperbound = mid - 1;
                    }
                    else
                    {
                        quotient = mid;
                        lowerbound = mid + 1;
                    }
                }

            if ((b * quotient) == result)
            {
                result.data = "0";
            }
            else if ((b * quotient) > result)
            {
                BigInteger temp((b * (quotient - 1)).data);
                result = result - temp;
            }
            else if ((b * quotient) < result)
            {
                BigInteger temp((b * (quotient)).data);
                result = result - temp;
            }
        }

        return BigInteger(result.data);
    }

    BigInteger operator%(long long int b)
    {
        BigInteger temp(b);
        return *this % temp;
    }
};

ostream &operator<<(ostream &out, const BigInteger &b)
{
    if (!b.ispositive)
    {
        out << "-";
    }
    out << b.data;
    return out;
}

BigInteger gcd(BigInteger &a, BigInteger &b)
{
    BigInteger *bigger;
    BigInteger *smaller;

    BigInteger copya(a.data);
    BigInteger copyb(b.data);

    if (copya > copyb)
    {
        bigger = &copya;
        smaller = &copyb;
    }
    else
    {
        bigger = &copyb;
        smaller = &copya;
    }

    while (*smaller > 0)
    {
        BigInteger r((*bigger % *smaller).data);
        *bigger = *smaller;
        *smaller = r;
    }

    return *bigger;
}

BigInteger factorial(BigInteger b)
{
    BigInteger result(1);

    for (BigInteger i(2); i <= b; i = i + 1)
        result = result * i;

    return result;
}

BigInteger factorial(long long int b)
{
    BigInteger temp(b);
    return factorial(temp);
}

BigInteger fastExpUtil(BigInteger a, BigInteger b)
{
    if (b == 0)
    {
        return BigInteger(1);
    }
    if (b == 1)
    {
        return a;
    }
    else
    {
        BigInteger c((b >> 1).data);
        int d = b.data[b.data.size() - 1] - '0';
        BigInteger smallerres = fastExpUtil(a, c);
        if (d & 1)
            return (smallerres * smallerres) * a;
        else
            return (smallerres * smallerres);
    }
}

BigInteger fastExp(BigInteger &a, BigInteger &b)
{
    BigInteger result(0);
    result = fastExpUtil(a, b);
    int lastdigit = b.data[b.data.size() - 1] - '0';
    if (!a.ispositive && (lastdigit & 1))
    {
        result.ispositive = false;
    }
    return result;
}

BigInteger fastExp(long long int a, long long int b)
{
    BigInteger ba(a);
    BigInteger bb(b);
    return fastExp(ba, bb);
}

BigInteger fastExp(BigInteger &a, long long int b)
{
    BigInteger bb(b);
    return fastExp(a, bb);
}

int main()
{
    int Q;
    cin >> Q;
    while (Q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            //exponentiation
            string a, b;
            cin >> a;
            cin >> b;
            BigInteger A(a);
            BigInteger B(b);
            BigInteger res(0);
            res = fastExp(A, B);
            cout << res << endl;
        }
        else if (type == 2)
        {
            //gcd
            string a, b;
            cin >> a;
            cin >> b;
            BigInteger A(a);
            BigInteger B(b);
            BigInteger res(0);
            res = gcd(A, B);
            cout << res << endl;
        }
        else
        {
            string a;
            cin >> a;
            BigInteger A(a);
            cout << factorial(A) << endl;
        }
    }
}