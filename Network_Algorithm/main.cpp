#include "MyHash.h"
#include<iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
	MyHashClass myhash;
	HashData data;
	system_clock::time_point start = system_clock::now();
	for (size_t i = 0; i < 200000; i++)
	{
		myhash.Input(i, data);
	}
	system_clock::time_point end = system_clock::now();
	nanoseconds nano = end - start;
	nanoseconds nsec = duration_cast<nanoseconds>(nano);
	milliseconds msec = duration_cast<milliseconds>(nano);
	seconds sec = duration_cast<seconds>(nano);


	cout << "\tInput(199998)=================== " << endl;
	cout << "경과시간(초 ns) : " << nsec.count() << endl;
	cout << "경과시간(초 ms) : " << msec.count() << endl;
	cout << "경과시간(초 s) : " << sec.count() << endl;

	std::cout << "All crash Hash : " << myhash.m_CrashCount << std::endl;
	//input=================================================

	data.data = "TestFindData";
	myhash.Input("myHash",data);

	//find=================================================
	start = system_clock::now();
	HashData result = myhash.Find("myHash");
	end = system_clock::now();
	nano = end - start;
	nsec = duration_cast<nanoseconds>(nano);
	msec = duration_cast<milliseconds>(nano);
	sec = duration_cast<seconds>(nano);
	cout << "\Find_========================== " << endl;
	cout << "경과시간(초 ns) : " << nsec.count() << endl;
	cout << "경과시간(초 ms) : " << msec.count() << endl;
	cout << "경과시간(초 s) : " << sec.count() << endl;

	cout << result.data << std::endl;

	return 0;
}