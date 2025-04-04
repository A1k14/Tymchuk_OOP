#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <unordered_map>

using namespace std;

class DomainIpMap {
private:
    unordered_map<string, string> domainToIp;
    unordered_map<string, string> ipToDomain;

public:
    DomainIpMap() {}

    ~DomainIpMap() {}

    DomainIpMap(int size, const string* domains, const string* ips) {
        if (domains == nullptr || ips == nullptr || size <= 0) {
            return;
        }
        domainToIp.reserve(size);
        ipToDomain.reserve(size);
        for (int i = 0; i < size; ++i) {
            AddMapping(domains[i], ips[i]);
        }
    }

    void AddMapping(const string& domain, const string& ip) {
        if (domain.empty() || ip.empty()) {
            return;
        }
        domainToIp[domain] = ip;
        ipToDomain[ip] = domain;
    }

    void PrintTable() const {
        cout << "\n--- Domain <-> IP Table ---" << endl;
        if (domainToIp.empty()) {
            cout << "  (empty)" << endl;
            cout << "-----------------------------" << endl;
            return;
        }
        cout << "Domain Name         \tIP Address" << endl;
        cout << "---------------------\t--------------" << endl;
        for (const auto& pair : domainToIp) {
            const string& domain = pair.first;
            const string& ip = pair.second;
            cout << domain;
            if (domain.length() < 8) {
                cout << "\t\t\t";
            }
            else if (domain.length() < 16) {
                cout << "\t\t";
            }
            else {
                cout << "\t";
            }
            cout << ip << endl;
        }
        cout << "-----------------------------" << endl;
    }

    string operator[](const string& domain) const {
        try {
            return domainToIp.at(domain);
        }
        catch (const std::out_of_range& oor) {
            throw std::out_of_range("Domain not found: " + domain);
        }
    }

    string getDomainByIp(const string& ip) const {
        try {
            return ipToDomain.at(ip);
        }
        catch (const std::out_of_range& oor) {
            throw std::out_of_range("IP address not found: " + ip);
        }
    }

    string operator()(const string& domain) const {
        return (*this)[domain];
    }

    size_t size() const {
        return domainToIp.size();
    }

    friend ostream& operator<<(ostream& os, const DomainIpMap& dmap) {
        os << "DomainIpMap Contents (" << dmap.size() << " entries):" << endl;
        if (dmap.domainToIp.empty()) {
            os << "  (map is empty)" << endl;
        }
        else {
            for (const auto& pair : dmap.domainToIp) {
                os << "  " << pair.first << " -> " << pair.second << endl;
            }
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
                is.clear();
                is.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            return is;
        }
        is.ignore(numeric_limits<streamsize>::max(), '\n');

        dmap.domainToIp.clear();
        dmap.ipToDomain.clear();

        if (count == 0) return is;

        dmap.domainToIp.reserve(count);
        dmap.ipToDomain.reserve(count);

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

            dmap.AddMapping(domain, ip);
        }
        return is;
    }
};


int main() {
    srand(time(0));

    cout << "--- Begin Domain/IP Mapping Program ---" << endl;

    DomainIpMap dnsCache;

    cout << "\nChoose initial data entry mode:\n";
    cout << "1 - Enter data manually\n";
    cout << "2 - Use predefined dataset\n";
    cout << "Your choice: ";
    int choice;

    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1) {
        cout << "\n--- Manual Entry Mode ---" << endl;
        if (!(cin >> dnsCache)) {
            cerr << "Exiting program due to initial data entry error." << endl;
            return 1;
        }
        cout << "Initial data entered successfully." << endl;

    }
    else {
        cout << "\n--- Predefined Data Mode ---" << endl;
        const int N = 5;
        string domains[N] = { "google.com", "example.com", "test.org", "local.dev", "google.com" };
        string ips[N] = { "172.217.160.142", "93.184.216.34", "192.0.2.1", "127.0.0.1", "216.58.214.206" };

        for (int i = 0; i < N; ++i) {
            dnsCache.AddMapping(domains[i], ips[i]);
        }
        cout << "Used " << dnsCache.size() << " predefined entries (duplicates might overwrite)." << endl;
    }

    cout << "\n--- Initial Table ---" << endl;
    dnsCache.PrintTable();

    string userInput;
    while (true) {
        cout << "\nEnter domain, IP, 'print', 'add', or 'exit': ";
        if (!getline(cin, userInput)) {
            cerr << "\nInput error. Exiting." << endl;
            break;
        }

        if (userInput == "exit") {
            break;
        }
        else if (userInput == "print") {
            dnsCache.PrintTable();
        }
        else if (userInput == "add") {
            string newDomain, newIp;
            cout << "Enter new domain: ";
            if (!getline(cin, newDomain) || newDomain.empty()) {
                cerr << "Invalid or empty domain input. Skipping add." << endl;
                continue;
            }
            cout << "Enter new IP: ";
            if (!getline(cin, newIp) || newIp.empty()) {
                cerr << "Invalid or empty IP input. Skipping add." << endl;
                continue;
            }
            dnsCache.AddMapping(newDomain, newIp);
            cout << "Mapping added/updated for '" << newDomain << "'." << endl;
        }
        else if (userInput.empty()) {
            continue;
        }
        else {
            bool found = false;
            try {
                string foundIp = dnsCache[userInput];
                cout << "  -> Found IP: " << foundIp << endl;
                found = true;
            }
            catch (const std::out_of_range&) {
                try {
                    string foundDomain = dnsCache.getDomainByIp(userInput);
                    cout << "  -> Found Domain: " << foundDomain << endl;
                    found = true;
                }
                catch (const std::out_of_range&) {
                }
            }

            if (!found) {
                cout << "  -> '" << userInput << "' not found as a known domain or IP." << endl;
            }
        }
    }

    cout << "\nExiting program. Goodbye!" << endl;

    return 0;
}