#include "BencodeReader.hpp"

BencodeReader::BencodeReader()
{
}

std::unique_ptr<BenValues> BencodeReader::decodeFile(std::istream& inStream) const
{
    int i = inStream.peek();
    switch (i)
    {
    case 'd':
        return decodeDict(inStream);
        break;
    case 'i':
        return decodeInteger(inStream);
        break;
    case 'l':
        return decodeList(inStream);
        break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
        return decodeString(inStream);
    case '\n':
        inStream.get();
        return decodeFile(inStream);
    default:
        char ch = i;
        std::cout << "Item = " << ch << std::endl;
        throw std::runtime_error("Invalid Item!");
    }
}

std::unique_ptr<BenString> BencodeReader::decodeString(std::istream& inStream) const
{
    std::string::size_type length = GetStringLength(inStream);
    std::string sRet(length, char());
    
    inStream.read(&sRet[0], length);
    std::string::size_type readLength = inStream.gcount();
    if (length != readLength)
    {
        throw std::runtime_error("String length mismatch");
    }
    return std::unique_ptr<BenString>(new BenString(sRet));
}

std::unique_ptr<BenDict> BencodeReader::decodeDict(std::istream& inStream) const
{
    //! Read 'd'
    
    inStream.get();
    std::unique_ptr<BenDict> dict(new BenDict());
    while (inStream && inStream.peek() != 'e')
    {
        std::shared_ptr<BenValues> key = decodeFile(inStream);
        std::shared_ptr<BenString> sKey = std::dynamic_pointer_cast<BenString>(key);
        if (!sKey)
        {
            throw std::runtime_error("Invalid key in map!");
        }
        std::shared_ptr<BenValues> value = decodeFile(inStream);
        (*dict)[sKey] = value;
    }
    //! Read 'e'
    inStream.get();
    return dict;
}

std::unique_ptr<BenList> BencodeReader::decodeList(std::istream& inStream) const
{
    //! Read 'l'
    inStream.get();
    std::unique_ptr<BenList> uItemList(new BenList());
    while (inStream.peek() != 'e')
    {
        auto sItem = decodeFile(inStream);
        uItemList->push_back(move(sItem));
    }
    if ((inStream.peek() == std::char_traits<char>::eof()))
    {
        throw std::runtime_error("invalid list");
    }
    //! Read 'e'
    inStream.get();
    return uItemList;
}

std::unique_ptr<BenInt> BencodeReader::decodeInteger(std::istream& inStream) const
{
    inStream.get();
    std::string sValue;
    while (inStream.peek() != 'e')
    {
        sValue += inStream.get();
    }
    if ((inStream.peek() == std::char_traits<char>::eof()))
    {
        std::cout << sValue << std::endl;
        throw std::runtime_error("invalid integer");
    }
    //! Read 'e'
    inStream.get();
    BenInt::ValueType iVal = std::stoll(sValue, nullptr);
    return std::unique_ptr<BenInt>(new BenInt(iVal));
}

std::string::size_type BencodeReader::GetStringLength(std::istream& inStream) const
{
    std::string sNum;
    while ((inStream.peek() != std::char_traits<char>::eof()) && (inStream.peek() != ':') )
    {
        sNum += inStream.get();
    }

    std::string::size_type length = std::stoi(sNum, NULL);
    if (inStream.get() != ':')
    {
        throw std::runtime_error("string length is invalid");
    }
    return length;
}
