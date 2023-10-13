#ifndef ITEMS_HXX
#define ITEMS_HXX
#include <map>
#include <list>
#include <string>
#include <memory>
#include "PrettyPrinter.hpp"


class PrintPretty;


class BenValues 
{
public:
	BenValues() {}
	virtual ~BenValues() = default;
	virtual void accept(PrintPretty*) = 0;
    virtual bool IsInt() const { return false; }
    virtual bool IsStr() const { return false; }
    virtual bool IsLst() const { return false; }
    virtual bool IsDct() const { return false; }
    virtual int GetInt() const { return 0; }
    virtual std::string GetStr() const { return ""; }
    bool operator==(const BenValues& other);
}; 

class BenList : public BenValues
{
    using ValueType = std::list<std::shared_ptr<BenValues> >;
public:
    BenList();
    ~BenList() {}
    void push_back(const std::shared_ptr<BenValues>& value);
    using iterator = ValueType::iterator;
    using const_iterator = ValueType::const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    virtual void accept(PrintPretty*) override;
    virtual bool IsLst() const override { return true; }
    

private:
    ValueType BenList_;
};


class BenString : public BenValues
{
    using ValueType = std::string;
public:
    BenString();
    ~BenString() {}
    BenString(ValueType&);
    virtual void accept(PrintPretty*) override;
    virtual bool IsStr() const override { return true; }
    ValueType GetValue() const;
    virtual std::string GetStr() const override;
private:
    ValueType value_;
};

struct mycomp {
    bool operator()(std::shared_ptr<BenString> l, std::shared_ptr<BenString> r) const {
        return l->GetValue() < r->GetValue();
    }
};

class BenDict : public BenValues
{
    using ValueType = std::map<std::shared_ptr<BenString>,
        std::shared_ptr<BenValues>,
        mycomp>;
public:
    using iterator = ValueType::iterator;
    using const_iterator = ValueType::const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    virtual void accept(PrintPretty*) override;
    virtual bool IsDct() const override { return true; }
    using key_type = ValueType::key_type;

    using mapped_type = ValueType::mapped_type;

    BenDict();

    ~BenDict() {}


    mapped_type& operator[](const key_type& key);
    
private:
    ValueType value_;
};


class BenInt : public BenValues
{
public:
    using ValueType = long long;
    virtual void accept(PrintPretty*) override;
    virtual bool IsInt() const override { return true; }
    BenInt(ValueType&);
    ~BenInt() {}
    ValueType GetValue() const;
    virtual int GetInt() const override;
private:
    ValueType value_;
};
#endif