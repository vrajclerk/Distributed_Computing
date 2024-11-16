# Socket Functions

## 1. inet_pton() (Presentation to Numeric)
**Purpose:** Converts an IP address from its text (presentation) form to its numeric (binary) form.

**Prototype:**
```c
int inet_pton(int af, const char *src, void *dst);
```

**Parameters:**
- `af`: Address family (AF_INET for IPv4, AF_INET6 for IPv6).
- `src`: The source address in string format (e.g., "192.168.1.1").
- `dst`: A pointer to a structure (usually `struct in_addr` for IPv4 or `struct in6_addr` for IPv6) to store the converted address.

**Returns:**
- `1` on successful conversion.
- `0` if the address is not valid for the specified address family.
- `-1` on error, and `errno` is set appropriately.

**Example:**
```c
struct in_addr addr;
if (inet_pton(AF_INET, "192.168.1.1", &addr) <= 0) {
    perror("inet_pton failed");
}
```

## 2. inet_ntop() (Numeric to Presentation)
**Purpose:** Converts an IP address from its binary (numeric) form to its text (presentation) form.

**Prototype:**
```c
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
```

**Parameters:**
- `af`: Address family (AF_INET for IPv4, AF_INET6 for IPv6).
- `src`: A pointer to a structure (usually `struct in_addr` for IPv4 or `struct in6_addr` for IPv6) containing the binary address.
- `dst`: The destination buffer to store the converted string.
- `size`: Size of the destination buffer.

**Returns:**
- A pointer to the `dst` buffer on success.
- `NULL` on error, and `errno` is set appropriately.

**Example:**
```c
char str[INET_ADDRSTRLEN];
struct in_addr addr;
inet_pton(AF_INET, "192.168.1.1", &addr);  // Convert text to binary first
if (inet_ntop(AF_INET, &addr, str, INET_ADDRSTRLEN) == NULL) {
    perror("inet_ntop failed");
}
printf("IP Address: %s\n", str);
```

## 3. htonl() and htons() (Host to Network Byte Order)
**Purpose:** Converts values from host byte order to network byte order.

**Prototype:**
```c
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
```

**Parameters:**
- `hostlong`: A 32-bit integer to convert (for `htonl()`).
- `hostshort`: A 16-bit integer to convert (for `htons()`).

**Returns:**
- The converted value in network byte order.

**Example:**
```c
uint32_t host_value = 12345;
uint32_t network_value = htonl(host_value);
```

## 4. ntohl() and ntohs() (Network to Host Byte Order)
**Purpose:** Converts values from network byte order to host byte order.

**Prototype:**
```c
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```

**Parameters:**
- `netlong`: A 32-bit value in network byte order.
- `netshort`: A 16-bit value in network byte order.

**Returns:**
- The converted value in host byte order.

**Example:**
```c
uint32_t network_value = 12345;
uint32_t host_value = ntohl(network_value);
```

## Summary of Address Conversion Functions
- `inet_pton()`: Text (string) to Binary (network).
- `inet_ntop()`: Binary (network) to Text (string).
- `htonl()` / `htons()`: Host to Network byte order.
- `ntohl()` / `ntohs()`: Network to Host byte order.

These functions are essential when working with network addresses in socket programming, ensuring the correct format for address manipulation and transmission.

## inet_aton() and inet_ntoa()
The functions `inet_aton()` and `inet_ntoa()` are older and simpler address conversion functions used in Unix-based systems for converting IPv4 addresses between string (text) and binary forms. Unlike the newer `inet_pton()` and `inet_ntop()`, these functions only work with IPv4 addresses.

### 1. inet_aton() (ASCII to Network)
**Purpose:** Converts an IPv4 address from its text (string) form to its binary (network) form.

**Prototype:**
```c
int inet_aton(const char *cp, struct in_addr *inp);
```

**Parameters:**
- `cp`: A string representing the IPv4 address (e.g., "192.168.1.1").
- `inp`: A pointer to a `struct in_addr` where the converted binary address will be stored.

**Returns:**
- `1` if the address is valid and successfully converted.
- `0` if the address is invalid.

**Example:**
```c
struct in_addr addr;
if (inet_aton("192.168.1.1", &addr)) {
    // Success: address is now in binary form in addr
} else {
    // Invalid address
}
```

### 2. inet_ntoa() (Network to ASCII)
**Purpose:** Converts an IPv4 address from its binary (network) form to its text (string) form.

**Prototype:**
```c
char *inet_ntoa(struct in_addr in);
```

**Parameters:**
- `in`: A `struct in_addr` containing the binary IPv4 address.

**Returns:** A pointer to a statically allocated string containing the converted IPv4 address in dotted-decimal notation (e.g., "192.168.1.1").

**Note:** Since the returned string is stored in a static buffer, subsequent calls to `inet_ntoa()` will overwrite the previous result.

**Example:**
```c
struct in_addr addr;
inet_aton("192.168.1.1", &addr);  // Convert text to binary
printf("IP Address: %s\n", inet_ntoa(addr));  // Convert binary to text
```

## Key Differences Between inet_aton/inet_ntoa and inet_pton/inet_ntop
### Protocol Support:
- `inet_aton()` and `inet_ntoa()` only support IPv4 addresses.
- `inet_pton()` and `inet_ntop()` support both IPv4 and IPv6 addresses.

### Thread-Safety:
- `inet_ntoa()` is not thread-safe because it returns a pointer to a statically allocated buffer, which can be overwritten by subsequent calls.
- `inet_pton()` and `inet_ntop()` are thread-safe, as they require you to pass in your own buffer.

### Error Handling:
- `inet_pton()` and `inet_ntop()` provide better error handling (with clear return values).
- `inet_aton()` and `inet_ntoa()` are simpler but more limited in their functionality.

## Summary:
- `inet_aton()`: Converts IPv4 addresses from text (ASCII) to binary (network).
- `inet_ntoa()`: Converts IPv4 addresses from binary (network) to text (ASCII).

These are older and IPv4-specific, whereas `inet_pton()` and `inet_ntop()` are more modern, versatile, and support both IPv4 and IPv6.
