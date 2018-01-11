// IPC_module_UnitTest.cpp : 定義主控台應用程式的進入點。

#include "stdafx.h"
#include "gtest/gtest.h"
#include "CG_PD_IPC.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include "CG_PD_Base64.h"
#include < windows.h >

NamaPipe Named_Pipe("P1", 300);
NamaPipe Named_Pipe2("P2", 70);
string shmName = "Mem1";
SharedMemory Shared_Memory(shmName, 300);
string shmNameNonCreate = "SM1";
SharedMemory Shared_Memory2(shmNameNonCreate, 300);
//=========================================================================

TEST(Named_Pipe, SendVec) {
	vector<unsigned char> vec = { 0xff, 0xbf, 0x3d, 0x69, 0xb7, 0x1d, 0xfb };
	bool flag = Named_Pipe.send(vec);
	EXPECT_EQ(true, flag);
}

TEST(Named_Pipe, SendStr) {
	bool flag = Named_Pipe.send("StrMsg");
	//Named_Pipe.send(".StrMsg2");
	EXPECT_EQ(true, flag);
}

TEST(Shared_Memory, ReadVec) {
	Sleep(10);
	size_t Size, Len;
	vector<unsigned char> vec;
	bool flag = Shared_Memory.read(20, 7, vec);

	CG_PD_Base64 b64;
	string s;
	b64.encode(vec, s);
	//printf("vec ~ str: %s\n", s.c_str());
	EXPECT_EQ(true, flag);
	EXPECT_STREQ("/789abcd+w==", s.c_str());
}

TEST(Shared_Memory, ReadChar) {
	size_t Size, Len;
	vector<unsigned char> vec;
	bool flag = Shared_Memory.read(40, 1, vec);

	CG_PD_Base64 b64;
	string s;
	b64.encode(vec, s);
	//printf("vec ~ str: %s\n", s.c_str());
	EXPECT_EQ(true, flag);
	EXPECT_STREQ("Zg==", s.c_str());
}

TEST(Shared_Memory, ReadOverSize) {
	size_t Size, Len;
	vector<unsigned char> vec;
	bool flag = Shared_Memory.read(301, 10, vec);
	EXPECT_EQ(false, flag);
}

TEST(Shared_Memory, ReadNon) {
	size_t Size, Len;
	vector<unsigned char> vec;
	bool flag = Shared_Memory2.read(20, 7, vec);

	CG_PD_Base64 b64;
	string s;
	b64.encode(vec, s);
	//printf("vec ~ str: %s\n", s.c_str());
	EXPECT_EQ(false, flag);
}
TEST(Named_Pipe, Remove) {
	Sleep(10);
	bool del = Named_Pipe.remove();
	bool flag = Named_Pipe.send("StrMsg");
	EXPECT_EQ(true, del);
	EXPECT_EQ(false, flag);
}

TEST(Shared_Memory, Remove) {
	bool del = Shared_Memory.remove();
	EXPECT_EQ(true, del);
}

TEST(Shared_Memory, RemoveNon) {
	bool del = Shared_Memory2.remove();
	EXPECT_EQ(false, del);
}

TEST(Shared_Memory, RemoveNon2) {
	bool del = Shared_Memory.remove("xyz");
	EXPECT_EQ(false, del);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}