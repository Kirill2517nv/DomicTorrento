#ifndef DECODE_HXX
#define DECODE_HXX
#include <memory>
#include <iostream>
#include "Values.hpp"


class BencodeReader {
public:
    BencodeReader();
    std::unique_ptr<BenValues> decodeFile(std::istream&) const;

private:
    std::unique_ptr<BenString> decodeString(std::istream&) const;
    std::unique_ptr<BenDict> decodeDict(std::istream&) const;
    std::unique_ptr<BenList> decodeList(std::istream&) const;
    std::unique_ptr<BenInt> decodeInteger(std::istream& inStream) const;
    std::string::size_type GetStringLength(std::istream& inStream) const;
};
#endif /* DECODE_HXX */