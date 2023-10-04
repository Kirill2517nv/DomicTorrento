#include "Values.hpp"
#include <iostream>

BenList::BenList() : BenValues()
{
}

void BenList::push_back(const std::shared_ptr<BenValues>& value)
{
	BenList_.push_back(value);
}


BenList::iterator BenList::begin()
{
	return BenList_.begin();
}

BenList::iterator BenList::end()
{
	return BenList_.end();
}

BenList::const_iterator BenList::begin() const
{
	return BenList_.begin();
}

BenList::const_iterator BenList::end() const
{
	return BenList_.end();
}

BenList::const_iterator BenList::cbegin() const
{
	return BenList_.cbegin();
}

BenList::const_iterator BenList::cend() const
{
	return BenList_.cend();
}

void BenList::accept(PrintPretty* pVisitor)
{
	pVisitor->visit(this);
}

BenString::BenString() : BenValues()
{
}

BenString::BenString(ValueType& value) :
	BenValues(),
	value_(value)
{
}

void BenString::accept(PrintPretty* pVisitor)
{
	pVisitor->visit(this);
}

BenString::ValueType BenString::GetValue() const
{
	return value_;
}

std::string BenString::GetStr() const
{
	if (this->IsStr())
	{
	return value_;
	}
	else
	{
		throw std::runtime_error("Wrong string");
	}
}


BenDict::iterator BenDict::begin()
{
	return value_.begin();
}

BenDict::iterator BenDict::end()
{
	return value_.end();
}

BenDict::const_iterator BenDict::begin() const
{
	return value_.begin();
}

BenDict::const_iterator BenDict::end() const
{
	return value_.end();
}

BenDict::const_iterator BenDict::cbegin() const
{
	return value_.cbegin();
}

BenDict::const_iterator BenDict::cend() const
{
	return value_.cend();
}

void BenDict::accept(PrintPretty* pVisitor)
{
	pVisitor->visit(this);
}

BenDict::BenDict() : BenValues()
{
}

BenDict::mapped_type& BenDict::operator[](const key_type& key)
{
	return value_[key];
}


void BenInt::accept(PrintPretty* pVisitor)
{
	pVisitor->visit(this);
}

BenInt::BenInt(ValueType& value) : 
	BenValues(),
	value_(value)
{
}

BenInt::ValueType BenInt::GetValue() const
{
	return value_;
}

int BenInt::GetInt() const
{
	if (this->IsInt()) 
	{
		return value_;
	}
	else
	{
		throw std::runtime_error("invalid integer");
	}
}

bool BenValues::operator==(const BenValues& other)
{
	if (this->IsStr() && other.IsStr())
	{
		return (this->GetStr() == other.GetStr());
	}
	return false;
}
