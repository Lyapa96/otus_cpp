#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>

using namespace std;

class IpAddr 
{
public:
    IpAddr(vector<string> stringIp){
        first_byte = stoi(stringIp.at(0));
        second_byte = stoi(stringIp.at(1));
        third_byte = stoi(stringIp.at(2));
        forth_byte = stoi(stringIp.at(3));
    }

    int first_byte;
    int second_byte;
    int third_byte;
    int forth_byte;
};

ostream& operator<<(ostream& stream, const IpAddr& ipAddr)
{
    stream << ipAddr.first_byte << "."
        << ipAddr.second_byte << "."
        << ipAddr.third_byte << "."
        << ipAddr.forth_byte;
    return stream;
}

bool operator<(const IpAddr& lhs, const IpAddr& rhs)
{
    return tie(lhs.first_byte, lhs.second_byte, lhs.third_byte, lhs.forth_byte) 
    < tie(rhs.first_byte, rhs.second_byte, rhs.third_byte, rhs.forth_byte);
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
vector<string> split(const string& str, char d)
{
    vector<string> r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


void print(const vector<IpAddr> ipAddrs, const function<bool(IpAddr)>& filter)
{
    for (const auto& ipAddr : ipAddrs)
    {
        if (filter(ipAddr))
            cout << ipAddr << endl;
    }
}


int main(int argc, char const *argv[])
{
    try
    {
        vector<IpAddr> ip_pool;
        for(string line; getline(cin, line);)
        {
            vector<string> v = split(line, '\t');
            IpAddr ipAddr(split(v.at(0), '.'));
            ip_pool.push_back(ipAddr);
        }

        sort(ip_pool.rbegin(), ip_pool.rend());

        print(ip_pool, [](IpAddr ipAddr) {return true;});
        print(ip_pool, [](IpAddr ipAddr) {return ipAddr.first_byte == 1;});
        print(ip_pool, [](IpAddr ipAddr) {return ipAddr.first_byte == 46 && ipAddr.second_byte == 70;});
        print(ip_pool, [](IpAddr ipAddr) {return ipAddr.first_byte == 46 || ipAddr.second_byte == 46 || ipAddr.third_byte == 46 || ipAddr.forth_byte == 46;});
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
