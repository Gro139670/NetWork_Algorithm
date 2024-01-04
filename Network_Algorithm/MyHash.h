#pragma once
#include <iostream>
#include <array>
#include <Windows.h>
#include <string>
#include <type_traits>
#include <vector>
#include <cmath>

union Hash
{
	//BYTE _1;
	//BYTE _2;
	//BYTE _3;
	//BYTE _4;
	//BYTE _5;
	//BYTE _6;
	//BYTE _7;
	//BYTE _8;
	BYTE hash[8];
	ULONGLONG _data;

};

struct HashData
{
	std::string data;
};

class MyHashClass
{
public:
	MyHashClass() { m_HashBuffer.resize(200010); }

	template<typename T>
	bool Input(T _input, HashData& _data)
	{
		if (std::is_class_v<T>)
		{
			std::cout << "AddData Error : Bad Data\n";
			return false;
		}
		std::string data = std::to_string(_input);
		return GetHash(data.c_str(), _data);
	}

	bool Input(const char* _input, HashData& _data)
	{
		return GetHash(_input, _data);
	}

	bool Input(std::string _input, HashData& _data)
	{
		return GetHash(_input.c_str(), _data);
	}

private:
	bool GetHash(const char* _data, HashData& _inputData)
	{

		if (_data == nullptr)
		{
			std::cout << "AddData Error : Bad Data\n";
			return false;
		}
		Hash hash;
		for (size_t i = 0; i < 8; i++)
		{
			hash.hash[i] = _data[0] << i;
		}

		size_t size = strlen(_data) > 4 ? strlen(_data) : 4;

		for (size_t i = 0; i < size; i++)
		{
			hash._data = hash._data << 2;
			hash._data *= _data[i];
			//hash._data *= hash._data;

		}
		Hash resultHash[2];
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				if (j & 1)
				{
					resultHash[j].hash[i] = (hash.hash[i] & 0x0f) * hash.hash[i];
				}
				else
				{
					resultHash[j].hash[i] = ((hash.hash[i] & 0xf0) >> 4) * hash.hash[i];
				}
			}
		}

		char result[17];
		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				result[(i * j) + j] = 48 + resultHash[i].hash[j] % 122;
			}
		}
		result[16] = '\0';
		unsigned int res = 0;
		for (size_t i = 0; i < 16; i++)
		{
			res += result[i];
		}
		unsigned int add = 1;
		res %= 200000;
		while (m_HashBuffer[res].first.empty() == false)
		{
			res = ((res * hash._data) + add) % 200000;

			add++;
			m_CrashCount++;
		}
		//if (m_HashBuffer[res].first.empty() == true)
		{
			m_HashBuffer[res].first = _data;
			m_HashBuffer[res].second = _inputData;
			std::cout <<"Input : " << _data << " _ " << result << "\n";
		}

		return true;

	}

public:
	HashData Find(const char* _data)
	{
		if (_data == nullptr)
		{
			std::cout << "AddData Error : Bad Data\n";
			return HashData();
		}
		Hash hash;
		for (size_t i = 0; i < 8; i++)
		{
			hash.hash[i] = _data[0] << i;
		}

		size_t size = strlen(_data) > 4 ? strlen(_data) : 4;

		for (size_t i = 0; i < size; i++)
		{
			hash._data = hash._data << 2;
			hash._data *= _data[i];
			//hash._data *= hash._data;

		}
		Hash resultHash[2];
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				if (j & 1)
				{
					resultHash[j].hash[i] = (hash.hash[i] & 0x0f) * hash.hash[i];
				}
				else
				{
					resultHash[j].hash[i] = ((hash.hash[i] & 0xf0) >> 4) * hash.hash[i];
				}
			}
		}

		char result[17];
		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				result[(i * j) + j] = 48 + resultHash[i].hash[j] % 122;
			}
		}
		result[16] = '\n';
		unsigned int res = 0;
		for (size_t i = 0; i < 16; i++)
		{
			res += result[i];
		}
		unsigned int add = 1;
		int addCount = 0;

		res %= 200000;
		while (m_HashBuffer[res].first._Equal(_data) == false)
		{
			res = ((res * hash._data) + add) % 200000;

			add++;
			addCount++;
		}
		std::cout << "Find Count : " << addCount << std::endl;
		std::cout << "buffer index : " << res << std::endl;

		return m_HashBuffer[res].second;
	}
	

public:
	// 2byte
	std::vector<std::pair<std::string,HashData>> m_HashBuffer;
	ULONGLONG m_CrashCount = 0;
};

