# URL Shortener (C++)

A simple in-memory URL shortener implemented in C++. It converts long URLs into short, unique codes (encoded in base36) and supports redirecting from a short URL back to its original long URL.

## Features

- **Shorten URLs**: Generates a short alphanumeric code for any given long URL.
- **Avoid duplicates**: If a URL has already been shortened, the existing short code is returned instead of generating a new one.
- **Redirect**: Given a short URL (or just its code), retrieves the original long URL.
- **Custom domain**: Supports a configurable prefix/domain for generated short URLs (defaults to `tiny.lk/`).

## How It Works

1. **Encoding**: Each URL is assigned a unique numeric ID (starting from `100000`), which is converted into a base36 string (`a-z`, `0-9`) using the `encode()` function.
2. **Storage**:
   - `shortToLong`: maps short codes to original long URLs (used for redirection).
   - `longToShort`: maps long URLs to short codes (used to avoid duplicate entries).
3. **Shortening** (`shortenURL`):
   - If the long URL was previously shortened, returns the existing short URL.
   - Otherwise, generates a new code, increments the counter, stores the mapping, and returns the new short URL.
4. **Redirecting** (`redirectURL`):
   - Extracts the short code from the given URL (everything after the last `/`).
   - Looks up the code in `shortToLong` and returns the original URL, or `"Error: 404 Not Found"` if not found.

## Requirements

- A C++ compiler supporting C++11 or later (e.g., `g++`).

## Build & Run

```bash
g++ -std=c++11 -o url_shortener url_shortener.cpp
./url_shortener
```

## Example Output

```
Shortened URL 1: tiny.lk/2bi8j
Shortened URL 2: tiny.lk/2bi8k
Redirecting tiny.lk/2bi8j to https://www.example.com/some/very/long/url
Redirecting tiny.lk/2bi8k to https://www.anotherexample.com/different/long/url
```

> Note: Actual short codes depend on the base36 encoding of the internal counter value, which starts at `100000`.

## Usage Example

```cpp
URLShortener urlShortener;

// Create a short URL
string shortURL = urlShortener.shortenURL("https://www.example.com/some/very/long/url");

// Resolve a short URL back to the original
string original = urlShortener.redirectURL(shortURL);
```

You can also pass a custom domain when constructing the shortener:

```cpp
URLShortener urlShortener("short.io/");
```

## Limitations

- **In-memory only**: All mappings are stored in memory (`unordered_map`) and are lost when the program exits. There is no persistence (database/file storage).
- **Not thread-safe**: Concurrent access to `shortenURL`/`redirectURL` from multiple threads is not safe without additional synchronization.
- **No URL validation**: The input URL is not checked for validity or format.
- **Single counter**: The counter starts at `100000` and increments sequentially; in a distributed setup this would need a shared/synchronized ID generator.

## Possible Improvements

- Persist mappings to a file or database.
- Add input validation for URLs.
- Support custom/user-defined short codes (vanity URLs).
- Add expiration dates for shortened URLs.
- Make the class thread-safe for concurrent use.
