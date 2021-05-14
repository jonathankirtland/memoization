// goldRabbits.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class BigInt
{
public:

	//constructors
	BigInt(string s);
	BigInt(int i);
	BigInt(const BigInt& bi);
	BigInt() { digits.clear(); digits.push_back('0'); }
	~BigInt();

	//prints out the number in full
	void print();

	//returns a string version of the number
	string toString() const;

	//operator overloads
	BigInt operator++(int);
	const BigInt operator+(const BigInt& b) const;
	const BigInt operator-(const BigInt& b) const;
	BigInt& operator+=(const BigInt& b);
	BigInt& operator -=(const BigInt& b);
	void operator=(const BigInt& b);
	friend ostream& operator<<(ostream& os, const BigInt& b);
	bool operator ==(const BigInt& second) const;
	bool operator<=(const BigInt& b) const;
	bool operator<(const BigInt& b) const;
	bool operator>(const BigInt& b) const;

private:
	vector<char> digits;
};
int goldRabbits(int n);
BigInt goldRabbits(BigInt b);

void pause()
{
	cout << "\npress enter to continue";
	getchar();
}
int main()
{
	BigInt B1("123456789123456789123456789123456789");
	BigInt B2(B1);
	BigInt MAX(INT_MAX);
	cout << "B1:" << B1 << "\nB2:" << B2 << "\nMAX:" << MAX << endl;
	pause();
	cout << "\nB1:";
	B1.print();
	cout << endl;
	pause();

	for (BigInt i = 0; i <= 3000; i++)	// uncomment this
	//for (int i = 0; i <= 3000; i++)		// comment this out
	{
		if (i < 8)
		{
			cout << "\ngoldRabbits(" << i << ") = " << goldRabbits(i);
		}
		else if (i > 55 && i < 67)
		{
			cout << "\ngoldRabbits(" << i << ") = " << goldRabbits(i);
		}
		else if (i > 2993)
		{
			cout << "\ngoldRabbits(" << i << ") = " << goldRabbits(i);
		}
	}
	pause();

	cout << "\nThis is the value of goldRabbits(3000)\n\n";
	BigInt gR3000 = goldRabbits(BigInt(3000));
	gR3000.print();

	pause();

	int n = 500;
	try {
		cout << "The value of goldRabbits(n) is:" << goldRabbits(n) << endl;
	}
	catch (string error)
	{
		cout << error << endl;
		cout << "Transitioning to BigInt\n";
		cout << goldRabbits(BigInt(n));
	}

	pause();
}

/*
copy constructor for bigint
*/
BigInt::BigInt(const BigInt& b)
{
	for (auto it = b.digits.begin(); it != b.digits.end(); it++)
	{
		digits.push_back(*it);
	}
}

/*
string constructor for bigint
*/
BigInt::BigInt(string s)
{
	for (auto it = s.begin(); it != s.end(); it++)
	{
		digits.push_back(*it);
	}
}

/*
outputs the entire bigint number
*/
void BigInt::print()
{
	for (vector<char>::iterator it = digits.begin(); it != digits.end(); it++)
	{
		cout << *it;
	}
}

/*
destructor
*/
BigInt::~BigInt()
{
	digits.clear();
}

/*
integer constructor for bigint
*/
BigInt::BigInt(int i)
{
	string temp = to_string(i);
	for (auto it = temp.begin(); it != temp.end(); it++)
	{
		digits.push_back(*it);
	}
}

/*
returns a string representing the number bigint represents
*/
string BigInt::toString() const
{
	string str = "";
	for (auto it = digits.begin(); it != digits.end(); it++)
	{
		str.push_back(*it);
	}
	return str;
}

/*
ostream operator overload
prints out number in scientific notation if there are more than 12 digits
*/
ostream& operator<<(ostream& os, const BigInt& b)
{
	if (b.digits.size() > 12)
	{
		string stringy = "";
		stringy.push_back(b.digits[0]);
		stringy.push_back('.');

		for (int i = 1; i < 11; i++)
		{
			if (b.digits.size() > 100 && i == 10)
			{
				i++;
			}
			else
			{
				stringy.push_back(b.digits[i]);
			}
		}
		stringy.push_back('e');

		stringy = stringy + to_string(b.digits.size());
		os << stringy;
	}
	else
	{
		os << b.toString();
	}
	return os;
}

/*
post fix operator overload
*/
BigInt BigInt::operator++(int)
{
	BigInt temp = *this;
	*this = *this + BigInt(1);
	return temp;
}

/*
greater than overload
*/
bool BigInt::operator>(const BigInt& b) const
{
	if (this->digits.size() > b.digits.size())
		return true;
	if (this->digits.size() < b.digits.size())
		return false;
	return toString() > b.toString();
}
/*
less than or equal to operator overload
*/
bool BigInt::operator<=(const BigInt& b) const
{
	return (*this == b || *this < b);
}

/*
assignment operator overload
*/
void BigInt:: operator=(const BigInt& b)
{
	digits.clear();
	for (auto it = b.digits.begin(); it != b.digits.end(); it++)
	{
		digits.push_back(*it);
	}
}

/*
less than operator overload
*/
bool BigInt::operator<(const BigInt& b) const
{
	if (this->digits.size() > b.digits.size())
		return false;
	if (this->digits.size() < b.digits.size())
		return true;
	return toString() < b.toString();
}

/*
add and assign operator overload
*/
BigInt& BigInt::operator+=(const BigInt& b)
{
	*this = *this + b;
	return *this;
}

/*
subtract and assign operator overload
*/
BigInt& BigInt::operator-=(const BigInt& b)
{
	*this = *this - b;
	return *this;
}
/*
subtraction operator overload
*/
BigInt const BigInt::operator-(const BigInt& b) const
{
	string a1 = toString(), b1 = b.toString();
	int n1 = a1.length(), n2 = b1.length();
	string res = "";

	// traverse them back to front
	reverse(a1.begin(), a1.end());
	reverse(b1.begin(), b1.end());

	int carry = 0;

	//calculate the differences for the digits that are the same
	for (int i = 0; i < n2; i++)
	{
		int sub = ((a1[i] - '0') - (b1[i] - '0') - carry);

		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		res.push_back(sub + '0');
	}

	//for the rest of the digits
	for (int i = n2; i < n1; i++)
	{
		int sub = ((a1[i] - '0') - carry);

		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}

		res.push_back(sub + '0');
	}
	reverse(res.begin(), res.end());

	//find the zeroes and make them go away
	res.erase(0, res.find_first_not_of('0'));

	return { res };
}

/*
addition operator overload
*/
BigInt const BigInt::operator+(const BigInt& b) const
{
	vector<char> a1, b1;
	int add;

	//make sure a1 is the vector with more numbers if there is one
	if (digits.size() > b.digits.size())
	{
		a1 = b.digits;
		b1 = digits;
	}
	else
	{
		a1 = digits;
		b1 = b.digits;
	}

	string result = "";

	int length1 = a1.size(), length2 = b1.size();
	int gap = length2 - length1;
	int carry = 0;

	//add the terms that are similar
	for (int i = length1 - 1; i >= 0; i--)
	{
		add = (a1[i] - '0') + (b1[i + gap] - '0') + carry;
		result.push_back(add % 10 + '0');
		carry = add / 10;
	}

	// add the rest of the terms
	for (int i = gap - 1; i >= 0; i--)
	{
		add = ((b1[i] - '0') + carry);
		result.push_back(add % 10 + '0');
		carry = add / 10;
	}
	if (carry > 0)
	{
		result.push_back(carry + '0');
	}

	reverse(result.begin(), result.end());

	return { result };
}

bool BigInt::operator==(const BigInt& b) const
{
	return (this->digits == b.digits);
}

/*
int representation of the goldrabbits (fibo) function that throws an error on overflow
*/
int goldRabbits(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}

	int fib = goldRabbits(n - 1) + goldRabbits(n - 2);

	//check for overflow
	if (fib < 0)
	{
		string error = to_string(n);
		throw string("Overflow Error at goldRabbits(" + error + ")");
	}
	return fib;
}

/*
bigint representation of the goldrabbits (fibo) function that will never overflow
*/
BigInt goldRabbits(BigInt b)
{
	static map<BigInt, BigInt> nums;

	//base case
	if (b < 2)
	{
		return { 1 };
	}

	//dynamically check created map
	map<BigInt, BigInt>::iterator it = nums.find(b);
	if (it != nums.end())
		return nums[b];

	//add recursive value to map
	nums[b] = (goldRabbits(b - 1) + goldRabbits(b - 2));

	//return the element in the map
	return nums[b];
}