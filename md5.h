#ifndef MD5_H
#define MD5_H

// Hash the input string using MD5
// Places the result in output as a hex string
void md5String(const char *input, char *output);

// Hash the input string using MD5
// Places the result in output as raw bytes
void md5Bytes(const char *input, unsigned char *output);

#endif
