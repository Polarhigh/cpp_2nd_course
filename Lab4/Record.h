#ifndef _RECORD_H_
#define _RECORD_H_

#include <iostream>
#include <string>

class Record
{
	std::wstring m_Name;
	std::wstring m_Phone;

public:
	Record(const wchar_t* name, const wchar_t* phone) : m_Name(name), m_Phone(phone) { }
	Record(const std::wstring& name, const std::wstring& phone) : m_Name(name), m_Phone(phone) { }
	Record(const Record& record) : m_Name(record.m_Name), m_Phone(record.m_Phone) { }
	//~Record() { }

	Record& operator=(const Record& record)
	{
		m_Name = record.m_Name;
		m_Phone = record.m_Phone;

		return *this;
	}

	const std::wstring& GetName() const
	{
		return m_Name;
	}

	void SetName(const std::wstring& name)
	{
		m_Name = name;
	}

	const std::wstring& GetPhone() const
	{
		return m_Phone;
	}

	void SetPhone(const std::wstring& phone)
	{
		m_Phone = phone;
	}

	friend std::wostream& operator<<(std::wostream& os, const Record& rec);
};

std::wostream& operator<<(std::wostream& os, const Record& rec)
{
	os << L"Name: " << rec.m_Name << L"\tPhone: " << rec.m_Phone;
	return os;
}

#endif //_RECORD_H_