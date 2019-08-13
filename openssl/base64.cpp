#include <iostream>
#include <string>

std::string encode_base64(const std::string& d, bool base64url = false)
{
    const char alphabet_base64[] = "ABCDEFGH" "IJKLMNOP" "QRSTUVWX" "YZabcdef"
                                   "ghijklmn" "opqrstuv" "wxyz0123" "456789+/";
    const char alphabet_base64url[] = "ABCDEFGH" "IJKLMNOP" "QRSTUVWX" "YZabcdef"
                                      "ghijklmn" "opqrstuv" "wxyz0123" "456789-_";
    const char *const alphabet = base64url ? alphabet_base64url : alphabet_base64;
    const char padchar = '=';
    int padlen = 0;
 
    std::string tmp;
    tmp.resize((d.size() + 2) / 3 * 4);
 
    int i = 0;
    char *out = &tmp[0];
    while (i < d.size()) {
        // encode 3 bytes at a time
        int chunk = 0;
        chunk |= int((unsigned char)(d.data()[i++])) << 16;
        if (i == d.size()) {
            padlen = 2;
        } else {
            chunk |= int((unsigned char)(d.data()[i++])) << 8;
            if (i == d.size())
                padlen = 1;
            else
                chunk |= int((unsigned char)(d.data()[i++]));
        }
 
        int j = (chunk & 0x00fc0000) >> 18;
        int k = (chunk & 0x0003f000) >> 12;
        int l = (chunk & 0x00000fc0) >> 6;
        int m = (chunk & 0x0000003f);
        *out++ = alphabet[j];
        *out++ = alphabet[k];
 
        if (padlen > 1) {
            //if ((options & OmitTrailingEquals) == 0)
                *out++ = padchar;
        } else {
            *out++ = alphabet[l];
        }
        if (padlen > 0) {
            //if ((options & OmitTrailingEquals) == 0)
                *out++ = padchar;
        } else {
            *out++ = alphabet[m];
        }
    }
    //assert(/*(options & OmitTrailingEquals) ||*/ (out == tmp.size() + tmp.data()));
    //if (options & OmitTrailingEquals)
    //    tmp.truncate(out - tmp.data());
    return tmp;
}

std::string decode_base64(const std::string base64, bool base64url = false)
{
    unsigned int buf = 0;
    int nbits = 0;
    std::string tmp;
    tmp.resize((base64.size() * 3) / 4);
 
 
    int offset = 0;
    for (int i = 0; i < base64.size(); ++i) {
        int ch = base64.at(i);
        int d;
 
        if (ch >= 'A' && ch <= 'Z')
            d = ch - 'A';
        else if (ch >= 'a' && ch <= 'z')
            d = ch - 'a' + 26;
        else if (ch >= '0' && ch <= '9')
            d = ch - '0' + 52;
        else if (ch == '+' && (base64url) == 0)
            d = 62;
        else if (ch == '-' && (base64url) != 0)
            d = 62;
        else if (ch == '/' && (base64url) == 0)
            d = 63;
        else if (ch == '_' && (base64url) != 0)
            d = 63;
        else
            d = -1;
 
        if (d != -1) {
            buf = (buf << 6) | d;
            nbits += 6;
            if (nbits >= 8) {
                nbits -= 8;
                tmp[offset++] = buf >> nbits;
                buf &= (1 << nbits) - 1;
            }
        }
    }
 
    //tmp.truncate(offset);
    if (offset < tmp.size())
            tmp.resize(offset);
 
    return tmp;
}


int main(int argc, char const *argv[])
{
    std::string text = "https://www.baidu.com/s?ie=UTF-8&wd=%E9%98%BF%E8%90%A8%E5%BE%B7&tn=50000275_hao_pg";
    std::string str_d_base64    = encode_base64(text, false);
    std::string str_d_fromBase64= decode_base64(str_d_base64, false);
 
    std::cout << str_d_base64 <<std::endl;
    std::cout << str_d_fromBase64 <<std::endl;
    return 0;
}
