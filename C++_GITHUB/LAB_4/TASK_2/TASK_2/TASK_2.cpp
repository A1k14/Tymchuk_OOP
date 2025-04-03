#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

class DomainIpMap {
private:
    vector<string> domainNames;
    vector<string> ipAddresses;

public:
    DomainIpMap() {}

    ~DomainIpMap() {}

    DomainIpMap(int size, const string* domains, const string* ips) {
        if (domains == nullptr || ips == nullptr || size <= 0) {
            cerr << "Warning: Invalid arguments passed to constructor. Map is empty." << endl;
            return;
        }
        domainNames.reserve(size);
        ipAddresses.reserve(size);
        for (int i = 0; i < size; ++i) {
            domainNames.push_back(domains[i]);
            ipAddresses.push_back(ips[i]);
        }
    }

    void AddMapping(const string& domain, const string& ip) {
        domainNames.push_back(domain);
        ipAddresses.push_back(ip);
    }

    void PrintTable() const {
        cout << "--- Domain <-> IP Table ---" << endl;
        if (domainNames.empty()) {
            cout << "  (empty)" << endl;
            return;
        }
        cout << "Domain Name         \tIP Address" << endl;
        cout << "---------------------\t--------------" << endl;
        for (size_t i = 0; i < domainNames.size(); ++i) {
            cout << domainNames[i] << "\t\t" << ipAddresses[i] << endl;
        }
        cout << "-----------------------------" << endl;
    }

    // Основний пошук: Домен -> IP
    string operator[](const string& domain) const {
        for (size_t i = 0; i < domainNames.size(); ++i) {
            if (domainNames[i] == domain) {
                return ipAddresses[i];
            }
        }
        throw std::out_of_range("Domain not found: " + domain);
    }

    // Метод для зворотного пошуку: IP -> Домен
    string getDomainByIp(const string& ip) const {
        for (size_t i = 0; i < ipAddresses.size(); ++i) {
            if (ipAddresses[i] == ip) {
                return domainNames[i];
            }
        }
        throw std::out_of_range("IP address not found: " + ip);
    }

    // Альтернативне звернення ТІЛЬКИ для Домен -> IP
    string operator()(const string& domain) const {
        return (*this)[domain]; // Викликає operator[]
    }

    // Метод для отримання розміру
    size_t size() const {
        return domainNames.size();
    }

    friend ostream& operator<<(ostream& os, const DomainIpMap& dmap) {
        os << "DomainIpMap Contents (" << dmap.size() << " entries):" << endl;
        for (size_t i = 0; i < dmap.domainNames.size(); ++i) {
            os << "  " << dmap.domainNames[i] << " -> " << dmap.ipAddresses[i] << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, DomainIpMap& dmap) {
        int count;
        if (&is == &cin) {
            cout << "Enter number of entries: ";
        }

        is >> count;
        if (!is || count < 0) {
            is.setstate(ios::failbit);
            if (&is == &cin) {
                cerr << "Error reading count or invalid count entered." << endl;
            }
            return is;
        }
        is.ignore(numeric_limits<streamsize>::max(), '\n');


        dmap.domainNames.clear();
        dmap.ipAddresses.clear();

        if (count == 0) return is;

        dmap.domainNames.reserve(count);
        dmap.ipAddresses.reserve(count);

        string domain, ip;
        for (int i = 0; i < count; ++i) {
            if (&is == &cin) { cout << "Enter domain name " << i + 1 << ": "; }
            if (!getline(is, domain)) {
                if (&is == &cin) { cerr << "Error reading domain name " << i + 1 << "." << endl; }
                is.setstate(ios::failbit); return is;
            }

            if (&is == &cin) { cout << "Enter IP address " << i + 1 << ": "; }
            if (!getline(is, ip)) {
                if (&is == &cin) { cerr << "Error reading IP address " << i + 1 << "." << endl; }
                is.setstate(ios::failbit); return is;
            }

            if (!domain.empty() && !ip.empty()) {
                dmap.AddMapping(domain, ip);
            }
            else {
                if (&is == &cin)
                    cerr << "Warning: Skipping empty domain or IP entry for item " << i + 1 << "." << endl;
            }
        }
        return is;
    }
};


int main() {
    cout << "--- Begin Domain/IP Test (with Exceptions) ---" << endl;

    const int N = 5;
    string domains[N] = { "google.com", "example.com", "test.org", "local.dev", "google.com" };
    string ips[N] = { "172.217.160.142", "93.184.216.34", "192.0.2.1", "127.0.0.1", "216.58.214.206" };

    DomainIpMap dnsCache(N, domains, ips);
    dnsCache.PrintTable();

    string domainToFind = "example.com";
    cout << "Test : string operator[](const string& domain) : Domain " << domainToFind;
    try {
        string foundIp = dnsCache[domainToFind];
        cout << " IP   " << foundIp << endl;
    }
    catch (const std::out_of_range& e) {
        cout << " - Error: " << e.what() << endl;
    }

    string ipToFind = "127.0.0.1";
    cout << "Test : string getDomainByIp(const string& ip) : IP " << ipToFind;
    try {
        string foundDomain = dnsCache.getDomainByIp(ipToFind);
        cout << " Domain " << foundDomain << endl;
    }
    catch (const std::out_of_range& e) {
        cout << " - Error: " << e.what() << endl;
    }

    string nonExistentDomain = "unknown.net";
    cout << "Test : string operator[](const string& domain) : Domain " << nonExistentDomain;
    try {
        string foundIp = dnsCache[nonExistentDomain];
        cout << " IP   '" << foundIp << "'" << endl;
    }
    catch (const std::out_of_range& e) {
        cout << " - Error correctly caught: " << e.what() << endl;
    }

    string domainForFuncCall = "test.org";
    cout << "Test : string operator()(const string& domain) : Domain " << domainForFuncCall;
    try {
        string foundIp = dnsCache(domainForFuncCall); // Використання () для Домен -> IP
        cout << " IP   " << foundIp << endl;
    }
    catch (const std::out_of_range& e) {
        cout << " - Error: " << e.what() << endl;
    }

    // Прибрано тест для operator() з IP, оскільки це перевантаження видалено
    string nonExistentIp = "192.168.1.1";
    cout << "Test : string getDomainByIp(const string& ip)  : IP " << nonExistentIp; // Тест тепер через getDomainByIp
    try {
        string foundDomain = dnsCache.getDomainByIp(nonExistentIp); // Використання getDomainByIp
        cout << " Domain " << foundDomain << endl;
    }
    catch (const std::out_of_range& e) {
        cout << " - Error correctly caught: " << e.what() << endl;
    }


    cout << "\nTesting output operator << :" << endl;
    cout << dnsCache;

    /*
    cout << "\nTesting input operator >> (enter 2 entries for test):" << endl;
    DomainIpMap newCache;
    if (cin >> newCache) {
       cout << "\nData entered via input operator:" << endl;
       cout << newCache;
    } else {
       cerr << "\nFailed to read data using input operator." << endl;
    }
    */

    cout << "\n--- End test ---" << endl;
    return 0;
}