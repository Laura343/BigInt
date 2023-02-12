#include <BigInt/BigInt.h>

#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

namespace ACA
{

BigInt::BigInt(const string& s)
{
	for(int i=0;i<s.length();++i)
	{
		if(s[i]<'0' || s[i]>'9')
		{
			throw ("No valid number") ;
		}
	}
	int i=0;
	digits="";
	while(s[i]=='0' && i<s.length())
	{
		i++;
	}
	while(i<s.length())
	{
		digits.push_back(s[i]);
		i++;
	}
	if(digits=="")
	{
		digits="0";
	}
}

BigInt::BigInt(unsigned long long nr)
{
	digits="";
	while(nr)
	{
		digits.push_back(nr%10 + '0');
		nr/=10;
	}
	std::reverse(digits.begin(),digits.end());
}

BigInt::BigInt(const BigInt& other)
{
	digits = other.digits;
}

BigInt& BigInt::operator=(const BigInt& other)
{
    // Guard self assignment
    if (this == &other)
    {
        return *this;
    }
	digits = other.digits;
    return *this;
}

/*
BigInt& BigInt::operator=(BigInt other) noexcept
{
    // exchange resources between *this and other
    std::swap(digits, other.digits);
    return *this;
}
*/

bool operator==(const BigInt& lhs, const BigInt& rhs)
{
    return lhs.digits == rhs.digits;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const BigInt& lhs, const BigInt& rhs)
{
	int n=lhs.digits.length();
	int m=rhs.digits.length();
	if(n<m)
		return true;
	if(n>m)
		return false;
	for(int i=0;i<n;++i)
	{
		if(lhs.digits[i]<rhs.digits[i])
			return true;
		if(lhs.digits[i]>rhs.digits[i])
			return false;
	}
    return false;
}

bool operator>(const BigInt& lhs, const BigInt& rhs)
{
	return rhs < lhs;
}

bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs > rhs);
}

BigInt& BigInt::operator++()
{
	std::reverse(digits.begin(),digits.end());
	int i=0;
	while(digits[i]=='9' && i<digits.length())
	{
		digits[i]='0';
		i++;
	}
	if(i<digits.length())
		digits[i]++;
	else
		digits.push_back('1');
	std::reverse(digits.begin(),digits.end());
	
    return *this;
}

BigInt BigInt::operator++(int /* tmp */)
{
	BigInt old = *this;
	operator++(); // prefix increment
	return old;
}

BigInt& BigInt::operator--()
{
	if(digits[0]=='0' && digits.length()==1)
		throw ("Underflow");

	std::reverse(digits.begin(),digits.end());
	int i=0;
	while(digits[i]=='0')
	{
		digits[i]='9';
		i++;
	}
	digits[i]--;
	if(digits[digits.length()-1]=='0' && digits.length()>1)
	{
		digits.pop_back();
	}
	std::reverse(digits.begin(),digits.end());

    return *this;
}

BigInt BigInt::operator--(int /* tmp */)
{
	BigInt old = *this;
	operator--(); // prefix decrement
	return old;
}

BigInt& BigInt::operator+=(const BigInt& rhs)
{
	std::reverse(digits.begin(),digits.end());

	int n=digits.length(),m=rhs.digits.length();

	if(n<m)
		digits.append(m-n,'0');
	
	int j=m-1;
	int sum;
	int tmp=0;
	for(int i=0;i<digits.length();i++)
	{
		if(j>=0)
		{
			sum=digits[i]-'0'+rhs.digits[j]-'0'+tmp;
			digits[i]= sum%10 + '0';
			j--;
		}
		else 
		{
			sum=digits[i]-'0'+tmp;
			digits[i]=sum%10 + '0';
		}
		tmp=sum/10;
	}
	if(tmp!=0)
	{
		digits.push_back(tmp+'0');
	}
	std::reverse(digits.begin(),digits.end());
    return *this;
}

BigInt operator+(BigInt lhs, const BigInt& rhs)
{
	lhs += rhs;
	return lhs;
}

BigInt& BigInt::operator-=(const BigInt& rhs)
{
	if(*this<rhs)
	{
		throw ("This will give a negative value");
	}
	if(*this==rhs)
	{
		digits="0";
	}
	else
	{
	std::reverse(digits.begin(),digits.end());

	int j=rhs.digits.length()-1;
	int tmp=0;
	bool isPos;
	for(int i=0;i<digits.length();++i)
	{
		if(j>=0)
		{
			if((digits[i]-rhs.digits[j]-tmp)>=0)
			{   
				isPos=true;
				digits[i]=digits[i]-rhs.digits[j]-tmp+'0';
			}
			else 
			{
				isPos=false;
				digits[i]=digits[i]-rhs.digits[j]-tmp+10 +'0';
				isPos=false;
			}
			j--;
		}		
		else if((digits[i]-tmp)>='0')
		{
			isPos=true;
			digits[i]=digits[i]-tmp;
		}
		else
		{
			isPos=false;
			digits[i]=digits[i]-tmp+10;
		}
		tmp=isPos?0:1;
	}
	j=digits.length()-1;
	while(digits[j]=='0')
	{
		digits.pop_back();
		j--;
	}
	std::reverse(digits.begin(),digits.end());
	}
	
    return *this;
}

BigInt operator-(BigInt lhs, const BigInt& rhs)
{
	lhs -= rhs;
	return lhs;
}

BigInt& BigInt::operator*=(const BigInt& rhs)
{
	BigInt num("0");
	for(int i=0;i<rhs.digits.length();++i)
	{
		num+=mul(rhs.digits[i]);
		num.digits.push_back('0');		
	}
	num.digits.pop_back();
	*this=num;
    return *this;
}

BigInt BigInt::mul(char c) const
{
	std::string str=digits;
	std::reverse(str.begin(),str.end());
	int tmp=0;
	for(int i=0;i<digits.length();++i)
	{
		int t=(str[i]-'0')*(c-'0');
		str[i]=(t +tmp)%10 +'0';
		tmp=(t +tmp)/10;
	}
	if(tmp!=0)
	{
		str.push_back('0'+tmp);
	}
	std::reverse(str.begin(),str.end());
	BigInt num=str;
	return num;
}

BigInt operator*(BigInt lhs, const BigInt& rhs)
{
	lhs *= rhs;
	return lhs;
}

BigInt& BigInt::operator/=(const BigInt& rhs)
{
	if((*this)<rhs)
	{
		digits="0";
		return *this;
	}
	if(rhs.digits=="0")
	{
		throw std::logic_error("Divide by Zero");
	}
	BigInt tmp;
	std::string result;
	int count=0;
	for(int i=0;i<digits.length();++i)
	{
		if(tmp<rhs)
		{
			tmp.digits+=digits[i];
			result+='0';
		}
		else
		{
			count=0;
			while(tmp>=rhs)
			{
				tmp-=rhs;
				count++;
			}
			result+=to_string(count);
			tmp.digits+=digits[i];
		}
	}

	count=0;
	while(tmp>=rhs)
	{
		tmp-=rhs;
		count++;
	}
	result+=to_string(count);

	*this=result;
    return *this;
}

BigInt operator/(BigInt lhs, const BigInt& rhs)
{
	lhs /= rhs;
	return lhs;
}

BigInt& BigInt::operator%=(const BigInt& rhs)
{
	if((*this)<rhs)
	{
		return *this;
	}
	if(rhs.digits=="0")
	{
		throw ("Divide by Zero");
	}
	BigInt tmp;
	for(int i=0;i<digits.length();++i)
	{
		if(tmp<rhs)
		{
			tmp.digits+=digits[i];
		}
		else
		{
			while(tmp>=rhs)
			{
				tmp-=rhs;
			}
			tmp.digits+=digits[i];
		}
	}
	while(tmp>=rhs)
	{
		tmp-=rhs;
	}
	*this=tmp;
    return *this;
}

BigInt operator%(BigInt lhs, const BigInt& rhs)
{
	lhs %= rhs;
	return lhs;
}

BigInt& BigInt::operator^=(const BigInt& rhs)
{
	BigInt b=rhs;
	BigInt a=*this;
	digits="1";
	BigInt two("2");
	while(b.digits!="0")
	{
		if((b.digits[b.digits.length()-1]-'0')&1==1)
		{
			(*this)*=a;
		}
		a*=a;
		b/=two;
	}
    return *this;
}

BigInt operator^(BigInt lhs, const BigInt& rhs)
{
	lhs ^= rhs;
	return lhs;
}

istream& operator>>(istream& in, BigInt& a)
{
   std::string str;
   std::cin>>str;
   for(int i=0;i<str.length();++i)
   {
		if(str[i]<'0' || str[i]>'9')
		{
			throw("No valid input");
		}
   }
   a=str;
    return in;
}

ostream& operator<<(ostream& out, const BigInt& a)
{
	out << a.digits;
    return out;
}

} // namespace ACA