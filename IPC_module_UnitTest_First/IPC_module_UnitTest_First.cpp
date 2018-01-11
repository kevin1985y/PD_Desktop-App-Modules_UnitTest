// IPC_module_UnitTest.cpp : 定義主控台應用程式的進入點。

#include "stdafx.h"
#include "gtest/gtest.h"
#include "CG_PD_IPC.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include "CG_PD_Base64.h"
#include < windows.h >

NamaPipe Named_Pipe("P1", 100, 300);
NamaPipe Named_Pipe2("P2", 50, 70);
string shmName = "Mem1";
SharedMemory Shared_Memory(shmName, 300);
string shmNameNonCreate = "SM1";
SharedMemory Shared_Memory2(shmNameNonCreate, 300);
//=========================================================================

TEST(Named_Pipe, CheckPipeAvailableTrue) {
	bool CheckPipe = Named_Pipe.checkPipeRecieveAvailable();
	EXPECT_EQ(true, CheckPipe);
}

TEST(Named_Pipe, GetName) {
	string Name = Named_Pipe.getName();
	EXPECT_STREQ("P1", Name.c_str());
}

TEST(Named_Pipe, GetName2) {
	string Name = Named_Pipe2.getName();
	EXPECT_STREQ("P2", Name.c_str());
}

TEST(Named_Pipe, GetMaxLength) {
	size_t MaxLen = Named_Pipe.getMaxLength();
	EXPECT_EQ(300, MaxLen);
}

TEST(Named_Pipe, GetMaxLength2) {
	size_t MaxLen = Named_Pipe2.getMaxLength();
	EXPECT_EQ(70, MaxLen);
}

TEST(Named_Pipe, GetPipeSize) {
	size_t PipeSize = Named_Pipe.getPipeSize();
	EXPECT_EQ(100, PipeSize);
}

TEST(Named_Pipe, GetPipeSize2) {
	size_t PipeSize = Named_Pipe2.getPipeSize();
	EXPECT_EQ(50, PipeSize);
}


TEST(Named_Pipe, ReceiveVec) {
	vector<unsigned char> vec;
	printf("Start~~ReceiveVec\n");

	bool flag = Named_Pipe.receive(vec);

	CG_PD_Base64 b64;
	string s;
	b64.encode(vec, s);
	//printf("vec ~ str: %s\n", s.c_str());

	EXPECT_EQ(true, flag);
	EXPECT_STREQ("/789abcd+w==", s.c_str());
}

TEST(Named_Pipe, ReceiveStr) {
	string s;
	bool flag = Named_Pipe.receive(s);
	//printf("s: %s\n", s);
	EXPECT_EQ(true, flag);
	EXPECT_STREQ("StrMsg", s.c_str());
}

TEST(Shared_Memory, Create) {
	bool Create = SharedMemory::create(shmName, 111);
	EXPECT_TRUE(Create);
}

TEST(Shared_Memory, GetName) {
	string Name = Shared_Memory.getName();
	EXPECT_STREQ(shmName.c_str(), Name.c_str());
}

TEST(Shared_Memory, GetSize) {
	size_t MaxLen = Shared_Memory.getMaxLength();
	EXPECT_EQ(300, MaxLen);
}

TEST(Shared_Memory, WriteVec) {
	vector<unsigned char> vec = { 0xff, 0xbf, 0x3d, 0x69, 0xb7, 0x1d, 0xfb };
	bool flag = Shared_Memory.write(20, vec);
	EXPECT_EQ(true, flag);
}

TEST(Shared_Memory, WriteChar) {
	char c = 'f';
	bool flag = Shared_Memory.write(40, &c, 1);
	EXPECT_EQ(true, flag);
}

TEST(Shared_Memory, WriteOverSize) {
	char c = 'f';
	bool flag = Shared_Memory.write(301, &c, 1);
	EXPECT_EQ(false, flag);
}

TEST(Shared_Memory, WriteNon) {
	vector<unsigned char> vec = { 0xff, 0xbf, 0x3d, 0x69, 0xb7, 0x1d, 0xfb };
	bool flag = Shared_Memory2.write(20, vec);
	EXPECT_EQ(false, flag);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}