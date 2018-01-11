// Translation_module_UnitTest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "CG_PD_Translation_module.h"
//#include "windows.h"

//=========================================================================

TEST(CGTranslation, LanguageTW) {
	CG_Translation cgt("../../../Translation_module/MOFile", "zh_TW");
	//CG_Translation cgt("../../../Translation_module/MOFile", "zh_TW");
	//Translation.setLocale("../../../Translation_module/MOFile");
	//Translation.setMOFilePath("zh_TW");
	//cout << "Path = " << Translation.getSetLocale().c_str() << endl;
	//cout << "Language = " << Translation.getMOFilePath().c_str() << endl;

	//cout << "Language = " << Translation.getTranslation(__(L"Hello, world")).c_str() << endl;
	wstring Text = L"Hello, world";

	//wcout << L"Language = " << cgt.getTranslation(Text).c_str() << endl;
	//MessageBoxW(NULL, cgt.getTranslation(Text.c_str()).c_str(), NULL, 0);

	wstring t = cgt.getTranslation(Text).c_str();

	wstring tt = L"你好世界";
	EXPECT_STREQ(tt.c_str(), t.c_str());

	//cout << "Language = " << cgt.getTranslation(__(L"Hello, world")).c_str() << endl;
	//EXPECT_EQ(false, flag);
	//wstring Text = L"Hello, world";
	//string a = cgt.getTranslation(Text).c_str();
	//cout << "Language = " << cgt.getTranslation(__(Text)).c_str() << endl;

}

TEST(CGTranslation, LanguageJP) {
	CG_Translation cgt("../../../Translation_module/MOFile", "ja_JP");
	wstring Text = L"Hello, world";
	wstring t = cgt.getTranslation(Text).c_str();
	wstring tt = L"ハローワールド";
	EXPECT_STREQ(tt.c_str(), t.c_str());
}

TEST(CGTranslation, LanguageNull) {
	CG_Translation cgt("../../../Translation_module/MOFile", "ja_JP");
	wstring Text = L"";
	wstring t = cgt.getTranslation(Text).c_str();
	wstring tt;
	EXPECT_STREQ(tt.c_str(), t.c_str());
}

TEST(CGTranslation, LanguageWrongPath) {
	CG_Translation cgt("../../../Translation_module/MOFiles", "ja_JP");
	wstring Text = L"Hello, world";
	wstring t = cgt.getTranslation(Text).c_str();
	EXPECT_STREQ(Text.c_str(), t.c_str());
}

TEST(CGTranslation, LanguageWrongLocale) {
	CG_Translation cgt("../../../Translation_module/MOFile", "ja_JPP");
	wstring Text = L"Hello, world";
	wstring t = cgt.getTranslation(Text).c_str();
	EXPECT_STREQ(Text.c_str(), t.c_str());
}

TEST(CGTranslation, LanguageNoTranslation) {
	CG_Translation cgt("../../../Translation_module/MOFile", "ja_JP");
	wstring Text = L"Wassup";
	wstring t = cgt.getTranslation(Text).c_str();
	EXPECT_STREQ(Text.c_str(), t.c_str());
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

