#include <crypto++/sha.h>
#include <crypto++/files.h>
using CryptoPP::FileSource;
using CryptoPP::FileSink;
#include <crypto++/base64.h>

#include <crypto++/filters.h>
using CryptoPP::StringSink;


std::string SHA256HashString(std::string aString){
    std::string digest;
    CryptoPP::SHA256 hash;

    CryptoPP::StringSource foo(aString, true,
    new CryptoPP::HashFilter(hash,
      new CryptoPP::Base64Encoder (
         new CryptoPP::StringSink(digest))));

    return digest;
}