// WinRelated_module_UnitTest.cpp : 定義主控台應用程式的進入點。

#include "stdafx.h"
#include "gtest/gtest.h"
#include "WindowsRelated.h"
#include <fstream>
#include <string>
#include <locale.h> 
#include <stdlib.h> 
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
Windows_Related Win_Related;
//=========================================================================
wstring username;
Windows_Related::DomainName domain;
string OpenFile(int row);
wstring OpenTxt(int row);

string OpenFile(int row) {
	fstream File;
	//wstring FileName = L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\WinRelated_module_UnitTest\\WinRelated.txt";
	wstring FileName = L"C:\\Users\\Administrator\\Downloads\\WinRelated.txt";
	//wstring FileName = L"C:\\Users\\kevinlin\\Downloads\\WinRelated.txt";
	char Buffer[1000];
	string level[1000];

	File.open(FileName, ios::in);
	if (!File) {
		printf("The System Cannot Find the File.\n");
		exit(0);
	}
	else {	
		int i = 0;
		while (!File.eof()) {
			//printf("i is %d \n", i);
			File.getline(Buffer, sizeof(Buffer));		
			//printf("Buffer is %s \n", Buffer);
			level[i] = Buffer;	
			//printf("level [%i] is %s \n", i, level[i]);
			i++;
		}
		//printf("level [%d] is %s \n", row, level[row]);
		File.close();
		return level[row];
	}
}

wstring OpenTxt(int row) {
	wifstream File;
	//wstring FileName = L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\WinRelated_module_UnitTest\\WinRelated.txt";
	wstring FileName = L"C:\\Users\\Administrator\\Downloads\\WinRelated.txt";
	//wstring FileName = L"C:\\Users\\kevinlin\\Downloads\\WinRelated.txt";
	wchar_t Buffer[1000];
	wstring level[1000];

	File.open(FileName, ios::in);
	if (!File) {
		printf("The System Cannot Find the File.\n");
		exit(0);
	}
	else {
		int i = 0;
		while (!File.eof()) {
			//printf("i is %d \n", i);
			File.getline(Buffer, sizeof(Buffer));
			//printf("Buffer is %s \n", Buffer);
			level[i] = Buffer;
			//printf("level [%i] is %s \n", i, level[i]);
			i++;
		}
		//printf("level [%d] is %s \n", row, level[row]);
		File.close();
		return level[row];
	}
}

TEST(Windows_Related, GetCurrentUser) {
	/*string str = OpenFile(0);
	unsigned len = str.size() * 2;
	setlocale(LC_CTYPE, "");     
	wchar_t *p = new wchar_t[len];
	mbstowcs(p, str.c_str(), len);
	wstring FileUserName(p);
	delete[] p;*/

	wstring FileUserName = OpenTxt(0);

	//printf("File-Username is %ls\n", FileUserName.c_str());

	Win_Related.GetCurrentDomainAndUser(username, domain);
	//printf("Username is %ls\n", username.c_str());	
	EXPECT_STREQ(FileUserName.c_str(), username.c_str());
}

TEST(Windows_Related, GetCurrentDnsDomainName) {
	wstring FileDns = OpenTxt(1);;

	Win_Related.GetCurrentDomainAndUser(username, domain);
	//printf("DnsDomainName is %ls\n", domain.DnsDomainName.c_str());
	EXPECT_STREQ(FileDns.c_str(), domain.DnsDomainName.c_str());
}

TEST(Windows_Related, GetCurrentNetbiosDomainName) {
	wstring FileNetbios = OpenTxt(2);

	Win_Related.GetCurrentDomainAndUser(username, domain);
	//printf("NetbiosDomainName is %ls\n", domain.NetbiosDomainName.c_str());
	EXPECT_STREQ(FileNetbios.c_str(), domain.NetbiosDomainName.c_str());
}

TEST(Windows_Related, GetLocalComputerName) {
	wstring FileComputerName = OpenTxt(3);
	wstring name;
	Win_Related.GetLocalComputerName(name);
	//printf("ComputerName is %ls\n", name.c_str());
	EXPECT_STREQ(FileComputerName.c_str(), name.c_str());
}

TEST(Windows_Related, GetDnsDomainNameList) {
	vector<Windows_Related::DomainName> domainlist;
	//vector<Windows_Related::DomainName> Vec = { };

	Win_Related.GetDomainNameList(domainlist);
	int i;
	for (i = 0; i < domainlist.size(); i++) {
		//printf("domain is %ls\n", domainlist[i].DnsDomainName.c_str());
		//printf("i is %d\n", i);

		wstring FileDomainNameList = OpenTxt(4 + i);

		EXPECT_STREQ(FileDomainNameList.c_str(), domainlist[i].DnsDomainName.c_str());
	}
}

TEST(Windows_Related, GetNetbiosDomainNameList) {
	vector<Windows_Related::DomainName> domainlist;
	//vector<Windows_Related::DomainName> Vec = {};

	Win_Related.GetDomainNameList(domainlist);
	int i;
	for (i = 0; i < domainlist.size(); i++) {
		//printf("domain is %ls\n", domainlist[i].NetbiosDomainName.c_str());
		//printf("i is %d\n", i);

		wstring NetbiosNameList = OpenTxt(6 + i);

		EXPECT_STREQ(NetbiosNameList.c_str(), domainlist[i].NetbiosDomainName.c_str());
	}
}

TEST(Windows_Related, GetHardwareProfileId) {
	wstring FileProfileId = OpenTxt(8);
	wstring ProfileId;
	Win_Related.GetHardwareProfileId(ProfileId);
	//printf("ProfileId is %ls\n", ProfileId.c_str());
	EXPECT_STREQ(FileProfileId.c_str(), ProfileId.c_str());
}

TEST(Windows_Related, GetLocalUserAccountList) {
	vector<wstring> AccountList;
	vector<wstring> Vec = {};
	Win_Related.GetLocalUserAccountList(AccountList);
	int i;
	for (i = 0; i < AccountList.size(); i++) {
		//printf("ProfileId is %ls\n", AccountList[i].c_str());
		//printf("i is %d\n", i);

		wstring FileProfileId = OpenTxt(9 + i);
		//printf("FileProfileId is %ls\n", FileProfileId.c_str());
		EXPECT_STREQ(FileProfileId.c_str(), AccountList[i].c_str());
	}
}

TEST(Windows_Related, UserLogonTest) {
	bool result;
	//Win_Related.UserLogonTest(L"",L"Kevin-PC", L"changingtec", result);
	Win_Related.UserLogonTest(L"", L"Administrator", L"4rfv$RFV", result);
	//printf("Logon is %d\n", result);
	EXPECT_EQ(true, result);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}