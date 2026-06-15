#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
class URLShortener {
private:
    const string base_url = "abcdefghijklmnopqrstuvwxyz0123456789";
    unordered_map<string, string> shortToLong;
    unordered_map<string, string> longToShort;
    long long counter;
    string domain;
    string encode(long long id) {
        if (id == 0) {
            return "a";
        }
        string short_url = "";
        while (id > 0) {
            short_url += base_url[id % 36];
            id /= 36;
        }
        reverse(short_url.begin(), short_url.end());
        return short_url;
    }
public:
    URLShortener(string customDomain = "tiny.lk/") {
        counter = 100000;
        domain = customDomain;
    }
    string shortenURL(string longURL) {
        if (longToShort.find(longURL) != longToShort.end()) {
            return domain + longToShort[longURL];
        }
        string shortCode = encode(counter);
        counter++; 
        shortToLong[shortCode] = longURL;
        longToShort[longURL] = shortCode;
        return domain + shortCode;
    }
    string redirectURL(string shortURL) {
        size_t lastSlash = shortURL.find_last_of('/');
        string shortCode = (lastSlash == string::npos) ? shortURL : shortURL.substr(lastSlash + 1);
        if (shortToLong.find(shortCode) != shortToLong.end()) {
            return shortToLong[shortCode];
        }
        return "Error: 404 Not Found";
    }
};
int main() {
    URLShortener urlShortener;
    string longURL1 = "https://www.example.com/some/very/long/url";
    string longURL2 = "https://www.anotherexample.com/different/long/url";
    string shortURL1 = urlShortener.shortenURL(longURL1);
    string shortURL2 = urlShortener.shortenURL(longURL2);
    cout << "Shortened URL 1: " << shortURL1 << endl;
    cout << "Shortened URL 2: " << shortURL2 << endl;
    cout << "Redirecting " << shortURL1 << " to " << urlShortener.redirectURL(shortURL1) << endl;
    cout << "Redirecting " << shortURL2 << " to " << urlShortener.redirectURL(shortURL2) << endl;
    return 0;
}