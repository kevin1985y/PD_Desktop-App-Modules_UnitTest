// Config_module_UnitTest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "CG_Config_module.h"

//=========================================================================
//CG_Config Config;
CG_Config ConfigIni(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Config_module_UnitTest\\KevinTest.ini", CG_Config::ConfigType::ini);
wstring SecName = L"UnitTest";
CG_Config ConfigRegedit(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\ChangingTec\\KevinRegistry", CG_Config::ConfigType::registry);

TEST(CGConfig, ConfigTypeIniInt) {
	//CG_Config Config(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Config_module_UnitTest\\KevinTest.ini", CG_Config::ConfigType::ini);
	//Config.selectConfigType(CG_Config::ConfigType::ini);
	//wstring Path = L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Config_module_UnitTest\\KevinTest.ini";
	//Config.setPath(Path);

	int intVal;
	int i = 111;
	ConfigIni.setSector(SecName);
	ConfigIni.setValue(L"ID", i);
	ConfigIni.getValue(L"ID", intVal);

	EXPECT_EQ(i, intVal);
}

TEST(CGConfig, ConfigTypeIniSetIntNullKey) {
	int i = 111;
	ConfigIni.setSector(SecName);

	bool flag = ConfigIni.setValue(L"", i);;
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;

	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniGetIntNullKey) {
	int intVal;
	ConfigIni.setSector(SecName);

	bool flag = ConfigIni.getValue(L"", intVal);;
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;

	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniInt64) {
	//long long LonglongVal;
	__int64 int64 = 222;
	__int64 int64Val;
	ConfigIni.setSector(SecName);
	ConfigIni.setValue(L"ID2", int64);
	ConfigIni.getValue(L"ID2", int64Val);

	EXPECT_EQ(int64, int64Val);
}

TEST(CGConfig, ConfigTypeIniSetInt64NullKey) {
	__int64 int64 = 222;
	ConfigIni.setSector(SecName);
	bool flag = ConfigIni.setValue(L"", int64);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniGetInt64NullKey) {
	__int64 int64Val;
	ConfigIni.setSector(SecName);
	bool flag = ConfigIni.getValue(L"", int64Val);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniVec) {
	vector<unsigned char> vec = { 0xab, 0xff, 0xce };
	//vec.resize(vec.size());

	vector<unsigned char> VecVal;
	ConfigIni.setSector(SecName);
	ConfigIni.setValue(L"ID3", vec);

	ConfigIni.getValue(L"ID3", VecVal);
	//string s;
	//convert.binary2HexString(vec, s);

	//EXPECT_STREQ("222", s.c_str());
	EXPECT_EQ(vec, VecVal);
}

TEST(CGConfig, ConfigTypeIniSetVecNullValue) {
	vector<unsigned char> vec = {};
	ConfigIni.setSector(SecName);
	bool flag = ConfigIni.setValue(L"ID88", vec);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(true, flag);
}

TEST(CGConfig, ConfigTypeIniSetVecNullKey) {
	vector<unsigned char> vec = { 0xab, 0xff, 0xce };
	ConfigIni.setSector(SecName);
	bool flag = ConfigIni.setValue(L"", vec);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniGetVecNullKey) {
	vector<unsigned char> VecVal;
	ConfigIni.setSector(SecName);
	bool flag = ConfigIni.getValue(L"", VecVal);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniWstring) {
	ConfigIni.setSector(SecName);
	wstring ws = L"555";
	ConfigIni.setValue(L"ID5", ws);
	wstring wsVal;
	ConfigIni.getValue(L"ID5", wsVal);

	EXPECT_EQ(ws, wsVal);
}

TEST(CGConfig, ConfigTypeIniSetWstringNullValue) {
	ConfigIni.setSector(SecName);
	wstring ws = L"";
	bool flag = ConfigIni.setValue(L"ID99", ws);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(true, flag);
}

TEST(CGConfig, ConfigTypeIniSetWstringNullKey) {
	ConfigIni.setSector(SecName);
	wstring ws = L"555";
	bool flag = ConfigIni.setValue(L"", ws);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniGetWstringNullKey) {
	ConfigIni.setSector(SecName);
	wstring wsVal;
	bool flag = ConfigIni.getValue(L"", wsVal);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniBool) {
	ConfigIni.setSector(SecName);
	bool b = true;
	ConfigIni.setValue(L"ID6", b);
	bool bVal;
	ConfigIni.getValue(L"ID6", bVal);

	EXPECT_EQ(b, bVal);
}

TEST(CGConfig, ConfigTypeIniSetBoolNullKey) {
	ConfigIni.setSector(SecName);
	bool b = true;
	bool flag = ConfigIni.setValue(L"", b);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniGetBoolNullKey) {
	ConfigIni.setSector(SecName);
	bool bVal;
	bool flag = ConfigIni.getValue(L"", bVal);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(false, flag);
}

TEST(CGConfig, ConfigTypeIniSector) {
	int intVal;
	int i = 111;
	ConfigIni.setSector(L"UnitTest2");
	ConfigIni.setValue(L"ID", i);
	ConfigIni.getValue(L"ID", intVal);

	EXPECT_EQ(i, intVal);
}

TEST(CGConfig, ConfigTypeIniRemoveKey) {
	ConfigIni.setSector(SecName);
	ConfigIni.removeKey(L"ID5");
	wstring wsVal;
	ConfigIni.getValue(L"ID5", wsVal);

	EXPECT_EQ(L"", wsVal);
}

TEST(CGConfig, ConfigTypeRegeditAdmin) {
	int intVal;
	int i = 111;
	ConfigIni.setSector(SecName);

	bool flag = ConfigRegedit.setValue(L"", i);;
	cout << ConfigRegedit.getErrorMessage() << endl;

	EXPECT_EQ(true, flag);
}

TEST(CGConfig, ConfigTypeRegeditInt) {
	int intVal;
	int i = 111;
	ConfigRegedit.setValue(L"ID", i);
	ConfigRegedit.getValue(L"ID", intVal);

	EXPECT_EQ(i, intVal);
}

TEST(CGConfig, ConfigTypeRegeditInt64) {
	__int64 int64 = 222;
	__int64 int64Val;
	ConfigRegedit.setSector(SecName);
	ConfigRegedit.setValue(L"ID2", int64);
	ConfigRegedit.getValue(L"ID2", int64Val);

	EXPECT_EQ(int64, int64Val);
}

TEST(CGConfig, ConfigTypeRegeditVec) {
	vector<unsigned char> vec = { 0xab, 0xff, 0xce };
	vector<unsigned char> VecVal, vec2;
	ConfigRegedit.setValue(L"ID3", vec);
	ConfigRegedit.getValue(L"ID3", VecVal);

	EXPECT_EQ(vec, VecVal);
}

TEST(CGConfig, ConfigTypeRegeditVecNull) {
	vector<unsigned char> vec = {};

	bool flag = ConfigRegedit.setValue(L"ID3", vec);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(true, flag);

}

TEST(CGConfig, ConfigTypeRegeditWstring) {
	ConfigRegedit.setSector(SecName);
	wstring ws = L"555";
	ConfigRegedit.setValue(L"ID5", ws);
	wstring wsVal;
	ConfigRegedit.getValue(L"ID5", wsVal);

	EXPECT_EQ(ws, wsVal);
}

TEST(CGConfig, ConfigTypeRegeditWstringNull) {
	ConfigRegedit.setSector(SecName);
	wstring ws = L"";

	bool flag = ConfigRegedit.setValue(L"ID5", ws);
	cout << "catch exception: " << ConfigIni.getErrorMessage() << endl;
	EXPECT_EQ(true, flag);
}

TEST(CGConfig, ConfigTypeRegeditBool) {
	ConfigRegedit.setSector(SecName);
	bool b = true;
	ConfigRegedit.setValue(L"ID6", b);
	bool bVal;
	ConfigRegedit.getValue(L"ID6", bVal);

	EXPECT_EQ(b, bVal);
}

TEST(CGConfig, ConfigTypeRegeditRemoveKey) {
	ConfigRegedit.removeKey(L"ID5");
	wstring wsVal;
	ConfigRegedit.getValue(L"ID5", wsVal);

	EXPECT_EQ(L"", wsVal);
}

TEST(CGConfig, ConfigTypeRegeditRemovePath) {
	bool flag = false;
	try {
		ConfigRegedit.removePath();
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
