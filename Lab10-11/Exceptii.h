#pragma once
#include <string>

using std::string;

class RepoException
{
private:
	string message;
public:
	RepoException(string msg) :message{ msg } {}

	string getMessage()const
	{
		return this->message;
	}
};

class ValidException
{
private:
	string message;
public:
	ValidException(string msg) :message{ msg } {}

	string getMessage()const
	{
		return this->message;
	}
};