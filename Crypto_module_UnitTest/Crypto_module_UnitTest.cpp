// Crypto_module_UnitTest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "CG_PD_Base64.h"
#include "CG_PD_Converter.h"
#include "CG_PD_Crypto_AES.h"
#include "CG_PD_Crypto_PBKDF2.h"
#include "CG_PD_Crypto_RSA.h"
#include "CG_PD_Crypto_SHA.h"
#pragma warning(disable:4996)

//=========================================================================
CG_PD_Base64 b64;
//unique_ptr<CG_PD_Base64> mpb64;

TEST(CGPDBase64, Encode) {
	//mpb64 = make_unique<CG_PD_Base64>();
	//mpb64->encode();

	//string text = "kevin test123 !@#$&&**";
	vector<unsigned char> vec = { 0xff, 0xbf, 0x3d, 0x69, 0xb7, 0x1d, 0xfb };
	//vec.resize(text.length());
	vec.resize(vec.size());
	//vector<unsigned char> vec;

	//vec.resize(text.length());
		
	//memcpy(&vec[0], text.data(), vec.size());
	string s;
	
	b64.encode(vec, s);
	//printf("%s\n", s.c_str());
	//string last= s.substr(s.size()-2);
	EXPECT_STREQ("/789abcd+w==", s.c_str());
	//EXPECT_STREQ("a2V2aW4gdGVzdDEyMyAhQCMkJiYqKg==", s.c_str());
}

TEST(CGPDBase64, EncodeEmpty) {
	//string text = "testdata123123";
	vector<unsigned char> vec;
	//vec.resize(text.length());

	//memcpy(&vec[0], text.data(), vec.size());
	//string s="456";
	string s;
	b64.encode(vec, s);
	//printf("%s\n", s.c_str());
	EXPECT_STREQ("", s.c_str());
}

TEST(CGPDBase64, Decode) {
	string text = "a2V2aW4gdGVzdDEyMyAhQCMkJiYqKg==";
	vector<unsigned char> vec;
	//vec.resize(text.length());

	//memcpy(&vec[0], text.data(), vec.size());
	//string s;

	//bool rtn = b64.decode(text, vec);
	b64.decode(text, vec);
	//EXPECT_FALSE(rtn);
	//printf("%s\n", s.c_str());
	//string last= s.substr(s.size()-2);
	string s;
	for (int i = 0; i < vec.size();i++) {
		s.push_back(vec.at(i));
	}	
	//EXPECT_STREQ("kevin test123 !@#$&&**", s.data());
	//printf("%s\n", s.c_str());
	EXPECT_STREQ("kevin test123 !@#$&&**", s.c_str());
}

TEST(CGPDBase64, DecodeEmpty) {
	string text;
	vector<unsigned char> vec;
	//vec.resize(text.length());

	//memcpy(&vec[0], text.data(), vec.size());
	//string s;

	//bool rtn = b64.decode(text, vec);
	b64.decode(text, vec);
	//EXPECT_FALSE(rtn);
	//printf("%s\n", s.c_str());
	//string last= s.substr(s.size()-2);
	string s;
	for (int i = 0; i < vec.size(); i++) {
		s.push_back(vec.at(i));
	}

	//printf("%s\n", s.c_str());
	EXPECT_STREQ("", s.c_str());
}

TEST(CGPDBase64, EncodeURLSafe) {
	//string text = "";
	vector<unsigned char> vec = {0xff, 0xbf, 0x3d, 0x69, 0xb7, 0x1d, 0xfb};
	//vec.resize(text.length());
	vec.resize(vec.size());
	//memcpy(&vec[0], text.data(), vec.size());
	string s;

	b64.encode(vec, s, CG_PD_Base64::imp::urlSafe);

	//printf("%s\n", s.c_str());

	EXPECT_STREQ("_789abcd-w", s.c_str());
}

TEST(CGPDBase64, EncodeURLSafePad) {
	vector<unsigned char> vec = { 0xff, 0xbf, 0x3d, 0x69, 0xb7, 0x1d, 0xfb};
	vec.resize(vec.size());
	string s;

	b64.encode(vec, s, CG_PD_Base64::imp::urlSafe_pad);

	//printf("%s\n", s.c_str());

	EXPECT_STREQ("_789abcd-w==", s.c_str());
}

TEST(CGPDBase64, EncodeRegularExpression) {
	vector<unsigned char> vec = { 0xff, 0xbf, 0x3d, 0x69, 0xb7, 0x1d, 0xfb };
	vec.resize(vec.size());
	string s;

	b64.encode(vec, s, CG_PD_Base64::imp::regularExpression);

	//printf("%s\n", s.c_str());

	EXPECT_STREQ("-789abcd!w==", s.c_str());
}

TEST(CGPDBase64, DecodeURLSafe) {
	string text = "_789abcd-w";
	vector<unsigned char> vec;

	b64.decode(text, vec, CG_PD_Base64::imp::urlSafe);

	string s;
	for (int i = 0; i < vec.size(); i++) {
		s.push_back(vec.at(i));
	}
	//printf("%s\n", s.data());
	EXPECT_STREQ("\xFF\xBF=i\xB7\x1D\xFB", s.c_str());
}

TEST(CGPDBase64, DecodeURLSafePad) {
	string text = "_789abcd-w==";
	vector<unsigned char> vec;

	b64.decode(text, vec, CG_PD_Base64::imp::urlSafe_pad);

	string s;
	for (int i = 0; i < vec.size(); i++) {
		s.push_back(vec.at(i));
	}
	//printf("%s\n", s.data());
	EXPECT_STREQ("\xFF\xBF=i\xB7\x1D\xFB", s.c_str());
}

TEST(CGPDBase64, DecodeRegularExpression) {
	string text = "-789abcd!w==";
	vector<unsigned char> vec;

	b64.decode(text, vec, CG_PD_Base64::imp::regularExpression);

	string s;
	for (int i = 0; i < vec.size(); i++) {
		s.push_back(vec.at(i));
	}
	//printf("%s\n", s.data());
	EXPECT_STREQ("\xFF\xBF=i\xB7\x1D\xFB", s.c_str());
}
//=========================================================================
CG_PD_Converter convert;

TEST(CGPDConverter, HexString2Binary) {
	string text = "ABFF";
	vector<unsigned char> vec;
	convert.hexString2Binary(text, vec);

	string s;
	for (int i = 0; i < vec.size(); i++) {
		s.push_back(vec.at(i));
	}

	//printf("%s\n", s.c_str());
	EXPECT_STREQ("\xAB\xFF", s.c_str());
}

TEST(CGPDConverter, HexString2BinaryEmpty) {
	string text;
	vector<unsigned char> vec;
	convert.hexString2Binary(text, vec);

	string s;
	for (int i = 0; i < vec.size(); i++) {
		s.push_back(vec.at(i));
	}
	EXPECT_STREQ("", s.c_str());	
}

TEST(CGPDConverter, HexString2BinaryWrongLenth) {
	string text = "ABCFF";;
	vector<unsigned char> vec;
	bool flag = false;
	try {
		convert.hexString2Binary(text, vec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true,flag);
}

TEST(CGPDConverter, Binary2HexString) {
	vector<unsigned char> vec = { 0xab, 0xff };
	vec.resize(vec.size());
	string s;

	convert.binary2HexString(vec, s);
	//printf("%s\n", s.c_str());

	EXPECT_STREQ("ABFF", s.c_str());
}

TEST(CGPDConverter, Binary2HexStringEmpty) {
	vector<unsigned char> vec;
	string s;
	convert.binary2HexString(vec, s);
	EXPECT_STREQ("", s.c_str());
}

TEST(CGPDConverter, Binary2HexStringUppercase) {
	vector<unsigned char> vec = { 0xab, 0xff };
	vec.resize(vec.size());
	string s;

	convert.binary2HexString(vec, s, true);
	//printf("%s\n", s.c_str());

	EXPECT_STREQ("ABFF", s.c_str());
}

TEST(CGPDConverter, Binary2HexStringLowercase) {
	vector<unsigned char> vec = { 0xab, 0xff };
	vec.resize(vec.size());
	string s;

	convert.binary2HexString(vec, s, false);
	//printf("%s\n", s.c_str());

	EXPECT_STREQ("abff", s.c_str());
}

TEST(CGPDConverter, Utf8ToUtf16) {
	//string text = u8"汉汉";
	string text = u8"Kevin 林凱文!汉码¥ドル$달러";
	wstring data;
	convert.utf8_2utf16(text, data);
	string hexString;

	//vector<unsigned char> vec = { 0xFF, 0xFF, 0x6C, 0x49 };
	//cout << "utf8_2utf16 success" << endl;
	//cout << "utf8 str = ";
	//for (int i = 0; i < text.size(); i++) {
		;// printf("%02X", (unsigned char)text.at(i));
	//}
	//cout << endl << "utf16 wstr = ";

	for (int i = 0; i < data.size(); i++) {
		//printf("%02X", data.at(i));
		char c[4];
		sprintf(&c[0], "%04X", data.at(i));
		//sprintf_s(&c[0], 4 , "%04X", data.at(i));
		hexString.append(c);
	}
	//cout << endl;

	//EXPECT_EQ("6C496C49", hexString);
	EXPECT_STREQ("004B006500760069006E0020679751F1658700216C49780100A530C930EB0024B2ECB7EC", hexString.c_str());
}

TEST(CGPDConverter, Utf8ToUtf16Empty) {
	//string text = u8"汉汉";
	string text;
	wstring data;
	convert.utf8_2utf16(text, data);
	string hexString;

	for (int i = 0; i < data.size(); i++) {
		char c[4];
		sprintf(&c[0], "%04X", data.at(i));
		hexString.append(c);
	}
	EXPECT_STREQ("", hexString.c_str());
}

TEST(CGPDConverter, Utf16ToUtf8) {
	string text;
	wstring data = L"Kevin 林凱文!汉码¥ドル$달러";
	convert.utf16_2utf8(data, text);
	string hexString;

	//vector<unsigned char> vec = { 0xFF, 0xFF, 0x6C, 0x49 };
	//cout << "utf8_2utf16 success" << endl;
	//cout << "utf8 str = ";
	//for (int i = 0; i < text.size(); i++) {
	;// printf("%02X", (unsigned char)text.at(i));
	 //}
	 //cout << endl << "utf16 wstr = ";
	//cout << "data size = " << data.size() << ", text size = " << text.size() << endl;
	for (int i = 0; i < text.size(); i++) {
		//printf("%02X", (unsigned char)text.at(i));
		char c[3];
		sprintf(&c[0], "%02X", (unsigned char)text.at(i));
		//sprintf_s(&c[0], 4 , "%04X", data.at(i));
		c[2] = 0x00;
		hexString.append(c);
	}
	//cout << endl;
	//cout << "hex string = " << hexString << endl;
	EXPECT_STREQ("4B6576696E20E69E97E587B1E6968721E6B189E7A081C2A5E38389E383AB24EB8BACEB9FAC", hexString.data());
}

TEST(CGPDConverter, Utf16ToUtf8Empty) {
	string text;
	wstring data;
	convert.utf16_2utf8(data, text);
	string hexString;

	for (int i = 0; i < text.size(); i++) {
		char c[3];
		sprintf(&c[0], "%02X", (unsigned char)text.at(i));
		c[2] = 0x00;
		hexString.append(c);
	}
	EXPECT_STREQ("", hexString.data());
}

//=========================================================================
TEST(CGPDCryptoAES, EncryptECBString) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	//CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::ECB);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("A7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1A76F92B99011802440EFAF3539934B7B5", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptECBString2) {
	//Change Key
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("C556046C9C559013E5F3FD18662E335EC556046C9C559013E5F3FD18662E335EC556046C9C559013E5F3FD18662E335EC556046C9C559013E5F3FD18662E335EAD6147963ED92350315EC100667E1AEB", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptECBStringNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	AES.setPadding(false);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("A7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1A", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptECBHex) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("E971A54308FEB211E396E7698A1C2FD1E971A54308FEB211E396E7698A1C2FD176F92B99011802440EFAF3539934B7B5", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptECBHex2) {
	//Change Key
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("C831E4928B5820AF8E4C9BD42DD5E9BCC831E4928B5820AF8E4C9BD42DD5E9BCAD6147963ED92350315EC100667E1AEB", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptECBHexNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.setPadding(false);

	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("E971A54308FEB211E396E7698A1C2FD1E971A54308FEB211E396E7698A1C2FD1", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptECBEmpty) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("76F92B99011802440EFAF3539934B7B5", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptECBEmptyNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.setPadding(false);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, ECBKeyLength128) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, ECBKeyLength192) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, ECBKeyLength256) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, ECBNoKey) {
	string strkey = "";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}

	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, ECBWrongKeyLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, EncryptCBCString) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("D9D082B8F61BE0E7D7F6FF4C8FD8B89B48D1DA4D3429572BB5B474688DB10C1564129F71F149525F9409AE48E43C31FAAE815D037CAF334AA87F2DB88BD125E6CC4B5F827E7100525756C20B25696A98", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCString2) {
	//Change Key
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("491A3D7810B9729AC042A28B7BDA96B75925D01CA4BCA262BBBC841D49DF807AEB47EE8141ED8D0F65D31181572B2A144C768E7417C744D91CDBA64B868399B1FCDC1C6E53210D8450D05981E1ABA084", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCString3) {
	//Change IV
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	string  striv = "FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("149C26AE361875C974B10737EDCB78B497D1369A9CBB54918458FE2849E11EE2B7E754D88D73E7250037B64FA3C28CA324CD247EA119E7F34411C9C9933804198947F17D1CDA78D470E35DE57F65D6FC", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCStringNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("D9D082B8F61BE0E7D7F6FF4C8FD8B89B48D1DA4D3429572BB5B474688DB10C1564129F71F149525F9409AE48E43C31FAAE815D037CAF334AA87F2DB88BD125E6", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCHex) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	//vector<unsigned char> IV(16, 0x00);
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);
	
	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("70DB6635C2AF9E3713E3EAA051937C7B3250409C494874BC867CE19B9908CB0E59E9AAF2323F493E01456142348A81C8", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCHex2) {
	//Change Key
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("9847178BB46107ADB46BB347DB4AFBA9C668170B6EE05B8E8E65E5B93033F699ADF2FDC45474C84C7CAE257BD821EEFB", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCHex3) {
	//Change IV
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("FDDA9B776612B2F78D55649339798EBE2398F86A06E450290A97C50DD25E10F8B2084E4D043E4601DADF4586B4867255", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCHexNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("70DB6635C2AF9E3713E3EAA051937C7B3250409C494874BC867CE19B9908CB0E", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCEmpty) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	//vector<unsigned char> IV(16, 0x00);
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("A08FBF3BA23E5CCF1FEAE8BE39E65665", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCBCEmptyNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	//vector<unsigned char> IV(16, 0x00);
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, CBCNoKey) {
	string strkey = "";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, CBCWrongKeyLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, CBCKeyLength128) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, CBCKeyLength192) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, CBCKeyLength256) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, EncryptCBCNoIV) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	//AES.setIV(IV);
	bool flag = false;
	try {
		AES.encrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}

	//convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, EncryptCBCWrongIVLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "01234567";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	bool flag = false;
	try {
		AES.setIV(IV);
		AES.encrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, EncryptCFBString) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a";
	string outputstr;

	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("669C04FDFB085784E86C03D9A2C9D55653080A195F6B9C9D8755DC055F1EDF11", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBString2) {
	//Change Key
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "6bc1bee22e409f96e93d7e1173931";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("02FA1106322BDE5EC3CB9C647427FB10BB62166013B6F4185615FBFE56", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBString3) {
	//Change IV
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "6bc1bee22e409f96e93d7e1173931";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e1a";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("BA4A8775FAC69DDDB1BC4F3B3DA2F6FCB73733BA0B591F94B51A6A3400", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBStringNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "6bc1bee22e409f96e93d7e1173931";
	string outputstr;
	AES.setPadding(false);
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("669C04FDFB085784E86C03D9A2C9D55653080A195F6B9C9D8755DC055F", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBHex) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a6bc1bee22e409f96";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	vector<unsigned char> plainVec, outputVec;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, plainVec);

	AES.setIV(IV);
	AES.encrypt(plainVec, outputVec);
	//printf("%s\n", outputstr.c_str());
	convert.binary2HexString(outputVec, outputstr);
	EXPECT_STREQ("3B3FD92EB72DAD20333449F8E83CFB4A0D4A718290F09A35", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBHex2) {
	//Change Key
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a6bc1bee22e409f96";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	vector<unsigned char> plainVec, outputVec;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, plainVec);

	AES.setIV(IV);
	AES.encrypt(plainVec, outputVec);
	//printf("%s\n", outputstr.c_str());
	convert.binary2HexString(outputVec, outputstr);
	EXPECT_STREQ("5F59CCD57E0E24FA1893D6453ED2D50C453C7111C648AE3F", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBHex3) {
	//Change IV
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a6bc1bee22e409f96";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e1a";
	vector<unsigned char> IV;
	vector<unsigned char> plainVec, outputVec;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, plainVec);

	AES.setIV(IV);
	AES.encrypt(plainVec, outputVec);
	//printf("%s\n", outputstr.c_str());
	convert.binary2HexString(outputVec, outputstr);
	EXPECT_STREQ("E7E95AA6B6E367796AE4051A7757D8E076C9F4F5D3BA1A08", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBHexNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a6bc1bee22e409f96";
	string outputstr;
	AES.setPadding(false);
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	vector<unsigned char> plainVec, outputVec;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, plainVec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.encrypt(plainVec, outputVec);

	convert.binary2HexString(outputVec, outputstr);
	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("3B3FD92EB72DAD20333449F8E83CFB4A0D4A718290F09A35", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBEmpty) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptCFBEmptyNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "";
	string outputstr;
	AES.setPadding(false);
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, CFBNoKey) {
	string strkey = "";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, CFBWrongKeyLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, CFBKeyLength128) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, CFBKeyLength192) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, CFBKeyLength256) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, EncryptCFBNoIV) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	//AES.setIV(IV);
	bool flag = false;
	try {
		AES.encrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, EncryptCFBWrongIVLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "01234567";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	bool flag = false;
	try {
		AES.setIV(IV);
		AES.encrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, EncryptOFBString) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "6bc1bee22e409f96e93d7e1173931";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("669C04FDFB085784E86C03D9A2C9D556BC9DE9BE3FF712AE5CB80445B1", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBString2) {
	//Change Key
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "6bc1bee22e409f96e93d7e1173931";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("02FA1106322BDE5EC3CB9C647427FB10039DE84F529101ACC9D478AABE", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBString3) {
	//Change IV
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "6bc1bee22e409f96e93d7e1173931";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e1a";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("BA4A8775FAC69DDDB1BC4F3B3DA2F6FCF6DD9CD4D0BC11B8B2FA7DCB0B", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBStringNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "6bc1bee22e409f96e93d7e1173931";
	string outputstr;
	AES.setPadding(false);
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	AES.setIV(IV);
	AES.encrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("669C04FDFB085784E86C03D9A2C9D556BC9DE9BE3FF712AE5CB80445B1", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBHex) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a6bc1bee22e409f96";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	vector<unsigned char> plainVec, outputVec;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, plainVec);

	AES.setIV(IV);
	AES.encrypt(plainVec, outputVec);
	//printf("%s\n", outputstr.c_str());
	convert.binary2HexString(outputVec, outputstr);
	EXPECT_STREQ("3B3FD92EB72DAD20333449F8E83CFB4AB265643826D2BC09", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBHex2) {
	//Change Key
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a6bc1bee22e409f96";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	vector<unsigned char> plainVec, outputVec;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, plainVec);

	AES.setIV(IV);
	AES.encrypt(plainVec, outputVec);
	//printf("%s\n", outputstr.c_str());
	convert.binary2HexString(outputVec, outputstr);
	EXPECT_STREQ("5F59CCD57E0E24FA1893D6453ED2D50C0D6565C94BB4AF0B", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBHex3) {
	//Change IV
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a6bc1bee22e409f96";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e1a";
	vector<unsigned char> IV;
	vector<unsigned char> plainVec, outputVec;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, plainVec);

	AES.setIV(IV);
	AES.encrypt(plainVec, outputVec);
	//printf("%s\n", outputstr.c_str());
	convert.binary2HexString(outputVec, outputstr);
	EXPECT_STREQ("E7E95AA6B6E367796AE4051A7757D8E0F8251152C999BF1F", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBHexNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "6bc1bee22e409f96e93d7e117393172a6bc1bee22e409f96";
	string outputstr;
	AES.setPadding(false);
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	vector<unsigned char> plainVec, outputVec;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, plainVec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.encrypt(plainVec, outputVec);

	convert.binary2HexString(outputVec, outputstr);
	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("3B3FD92EB72DAD20333449F8E83CFB4AB265643826D2BC09", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBEmpty) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, EncryptOFBEmptyNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "";
	string outputstr;
	AES.setPadding(false);
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.encrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, OFBNoKey) {
	string strkey = "";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, OFBWrongKeyLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, OFBKeyLength128) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, OFBKeyLength192) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, OFBKeyLength256) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	bool flag = false;
	try {
		CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, EncryptOFBNoIV) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	//AES.setIV(IV);
	bool flag = false;
	try {
		AES.encrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, EncryptOFBWrongIVLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "01234567";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	bool flag = false;
	try {
		AES.setIV(IV);
		AES.encrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, DecryptECBString) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "A7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1A76F92B99011802440EFAF3539934B7B5";
	string outputstr;

	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptECBString2) {
	//Change Key
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "C556046C9C559013E5F3FD18662E335EC556046C9C559013E5F3FD18662E335EC556046C9C559013E5F3FD18662E335EC556046C9C559013E5F3FD18662E335EAD6147963ED92350315EC100667E1AEB";
	string outputstr;

	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptECBStringNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "A7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1AA7A71876DB0EE54380EA9D753AD98B1A";
	string outputstr;

	AES.setPadding(false);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptECBHex) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "E971A54308FEB211E396E7698A1C2FD1E971A54308FEB211E396E7698A1C2FD176F92B99011802440EFAF3539934B7B5";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptECBHex2) {
	//Change Key
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "C831E4928B5820AF8E4C9BD42DD5E9BCC831E4928B5820AF8E4C9BD42DD5E9BCAD6147963ED92350315EC100667E1AEB";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptECBHexNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "E971A54308FEB211E396E7698A1C2FD1E971A54308FEB211E396E7698A1C2FD1";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.setPadding(false);

	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptECBEmpty) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);
	bool flag = false;

	try {
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, DecryptECBEmptyNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key);
	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	AES.setPadding(false);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCString) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	string inputstr = "D9D082B8F61BE0E7D7F6FF4C8FD8B89B48D1DA4D3429572BB5B474688DB10C1564129F71F149525F9409AE48E43C31FAAE815D037CAF334AA87F2DB88BD125E6CC4B5F827E7100525756C20B25696A98";
	string outputstr;

	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCString2) {
	//Change Key
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	string inputstr = "491A3D7810B9729AC042A28B7BDA96B75925D01CA4BCA262BBBC841D49DF807AEB47EE8141ED8D0F65D31181572B2A144C768E7417C744D91CDBA64B868399B1FCDC1C6E53210D8450D05981E1ABA084";
	string outputstr;

	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCString3) {
	//Change IV
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	string inputstr = "149C26AE361875C974B10737EDCB78B497D1369A9CBB54918458FE2849E11EE2B7E754D88D73E7250037B64FA3C28CA324CD247EA119E7F34411C9C9933804198947F17D1CDA78D470E35DE57F65D6FC";
	string outputstr;

	string  striv = "FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCStringNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);
	string inputstr = "D9D082B8F61BE0E7D7F6FF4C8FD8B89B48D1DA4D3429572BB5B474688DB10C1564129F71F149525F9409AE48E43C31FAAE815D037CAF334AA87F2DB88BD125E6";
	string outputstr;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCHex) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "70DB6635C2AF9E3713E3EAA051937C7B3250409C494874BC867CE19B9908CB0E59E9AAF2323F493E01456142348A81C8";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	//vector<unsigned char> IV(16, 0x00);
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCHex2) {
	//Change Key
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "9847178BB46107ADB46BB347DB4AFBA9C668170B6EE05B8E8E65E5B93033F699ADF2FDC45474C84C7CAE257BD821EEFB";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCHex3) {
	//Change IV
	string strkey = "FDBECA9873216540FDBECA9873216540FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "FDDA9B776612B2F78D55649339798EBE2398F86A06E450290A97C50DD25E10F8B2084E4D043E4601DADF4586B4867255";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "FDBECA9873216540FDBECA9873216540";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCHexNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "70DB6635C2AF9E3713E3EAA051937C7B3250409C494874BC867CE19B9908CB0E";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCEmpty) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	bool flag = false;
	try {
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, DecryptCBCEmptyNoPadding) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCBCNoIV) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	//AES.setIV(IV);
	bool flag = false;
	bool kevin = true;
	try {
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, DecryptCBCWrongIVLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CBC);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "01234567";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	bool flag = false;
	try {
		AES.setIV(IV);
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, DecryptCFBString) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "669C04FDFB085784E86C03D9A2C9D55653080A195F6B9C9D8755DC055F1EDF11";
	string outputstr;

	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("6bc1bee22e409f96e93d7e117393172a", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBString2) {
	//Change Key
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "02FA1106322BDE5EC3CB9C647427FB10BB62166013B6F4185615FBFE56";
	string outputstr;

	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("6bc1bee22e409f96e93d7e1173931", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBString3) {
	//Change IV
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "BA4A8775FAC69DDDB1BC4F3B3DA2F6FCB73733BA0B591F94B51A6A3400";
	string outputstr;

	string  striv = "000102030405060708090a0b0c0d0e1a";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("6bc1bee22e409f96e93d7e1173931", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBStringNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);
	string inputstr = "669C04FDFB085784E86C03D9A2C9D55653080A195F6B9C9D8755DC055F";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("6bc1bee22e409f96e93d7e1173931", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBHex) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "3B3FD92EB72DAD20333449F8E83CFB4A0D4A718290F09A35";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	//vector<unsigned char> IV(16, 0x00);
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("6BC1BEE22E409F96E93D7E117393172A6BC1BEE22E409F96", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBHex2) {
	//Change Key
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "5F59CCD57E0E24FA1893D6453ED2D50C453C7111C648AE3F";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("6BC1BEE22E409F96E93D7E117393172A6BC1BEE22E409F96", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBHex3) {
	//Change IV
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "E7E95AA6B6E367796AE4051A7757D8E076C9F4F5D3BA1A08";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e1a";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("6BC1BEE22E409F96E93D7E117393172A6BC1BEE22E409F96", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBHexNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "3B3FD92EB72DAD20333449F8E83CFB4A0D4A718290F09A35";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("6BC1BEE22E409F96E93D7E117393172A6BC1BEE22E409F96", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBEmpty) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	bool flag = false;
	try {
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, DecryptCFBEmptyNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptCFBNoIV) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	//AES.setIV(IV);
	bool flag = false;
	bool kevin = true;
	try {
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, DecryptCFBWrongIVLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::CFB);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "01234567";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	bool flag = false;
	try {
		AES.setIV(IV);
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, DecryptOFBString) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "669C04FDFB085784E86C03D9A2C9D556BC9DE9BE3FF712AE5CB80445B1";
	string outputstr;

	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("6bc1bee22e409f96e93d7e1173931", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBString2) {
	//Change Key
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "02FA1106322BDE5EC3CB9C647427FB10039DE84F529101ACC9D478AABE";
	string outputstr;

	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("6bc1bee22e409f96e93d7e1173931", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBString3) {
	//Change IV
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "BA4A8775FAC69DDDB1BC4F3B3DA2F6FCF6DD9CD4D0BC11B8B2FA7DCB0B";
	string outputstr;

	string  striv = "000102030405060708090a0b0c0d0e1a";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);

	AES.setIV(IV);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("6bc1bee22e409f96e93d7e1173931", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBStringNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);
	string inputstr = "669C04FDFB085784E86C03D9A2C9D556BC9DE9BE3FF712AE5CB80445B1";
	string outputstr;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputstr, outputstr);
	//printf("%s\n", outputstr.c_str());
	EXPECT_STREQ("6bc1bee22e409f96e93d7e1173931", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBHex) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "3B3FD92EB72DAD20333449F8E83CFB4AB265643826D2BC09";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	//vector<unsigned char> IV(16, 0x00);
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("6BC1BEE22E409F96E93D7E117393172A6BC1BEE22E409F96", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBHex2) {
	//Change Key
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "5F59CCD57E0E24FA1893D6453ED2D50C0D6565C94BB4AF0B";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("6BC1BEE22E409F96E93D7E117393172A6BC1BEE22E409F96", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBHex3) {
	//Change IV
	string strkey = "2b7e151628aed2a6abf7158809cf4f2b";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "E7E95AA6B6E367796AE4051A7757D8E0F8251152C999BF1F";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e1a";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("6BC1BEE22E409F96E93D7E117393172A6BC1BEE22E409F96", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBHexNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "3B3FD92EB72DAD20333449F8E83CFB4AB265643826D2BC09";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("6BC1BEE22E409F96E93D7E117393172A6BC1BEE22E409F96", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBEmpty) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	bool flag = false;
	try {
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(false, flag);
}

TEST(CGPDCryptoAES, DecryptOFBEmptyNoPadding) {
	string strkey = "2b7e151628aed2a6abf7158809cf4f3c";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "000102030405060708090a0b0c0d0e0f";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	AES.setIV(IV);
	AES.setPadding(false);
	AES.decrypt(inputvec, outputvec);

	convert.binary2HexString(outputvec, outputstr);

	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

TEST(CGPDCryptoAES, DecryptOFBNoIV) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	//AES.setIV(IV);
	bool flag = false;
	bool kevin = true;
	try {
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoAES, DecryptOFBWrongIVLength) {
	string strkey = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	vector<unsigned char> key;
	convert.hexString2Binary(strkey, key);
	CG_PD_Crypto_AES AES(key, CG_PD_Crypto_AES::blockCipherMode::OFB);

	string inputstr = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	string  striv = "01234567";
	vector<unsigned char> IV;
	convert.hexString2Binary(striv, IV);
	convert.hexString2Binary(inputstr, inputvec);
	bool flag = false;
	try {
		AES.setIV(IV);
		AES.decrypt(inputvec, outputvec);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

//=========================================================================
CG_PD_Crypto_PBKDF2 PBKDF2;

TEST(CGPDCryptoPBKDF2, GetDerivedKey) {
	string salt = "B00F4D8CE0240FA83144354C09D6D86C";
	string password = "password";
	int iteration = 1000;
	int keylength = 32;
	vector<unsigned char> key;

	PBKDF2.getDerivedKey(salt, password, iteration, keylength, key);

	//printf("%s\n", key.data());

	string outputstr;
	convert.binary2HexString(key, outputstr);
	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("76146A931CDFC500846018EB049BE8781FCFD1B58EAFD9C4DC1324AE4C2AF9CB", outputstr.c_str());
}

TEST(CGPDCryptoPBKDF2, JSIteration) {
	string salt = "B00F4D8CE0240FA83144354C09D6D86C";
	string password = "password";
	int iteration = 100000;
	int keylength = 32;
	vector<unsigned char> key;

	PBKDF2.getDerivedKey(salt, password, iteration, keylength, key);

	//printf("%s\n", key.data());

	string outputstr;
	convert.binary2HexString(key, outputstr);
	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("1D9E1951C4E764995FC9858021A1FF50EC67C01595BBF68007ED3836347E376B", outputstr.c_str());
}

TEST(CGPDCryptoPBKDF2, MaxIteration) {
	string salt = "B00F4D8CE0240FA83144354C09D6D86C";
	string password = "password";
	int iteration = 100002;
	int keylength = 32;
	vector<unsigned char> key;

	PBKDF2.getDerivedKey(salt, password, iteration, keylength, key);

	//printf("%s\n", key.data());

	string outputstr;
	convert.binary2HexString(key, outputstr);
	//printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("C20652A2B9004D28E4C29401B3B301ECEDEACFF15309E5286C459A24B380248D", outputstr.c_str());
}

TEST(CGPDCryptoPBKDF2, WrongIteration) {
	string salt = "B00F4D8CE0240FA83144354C09D6D86C";
	string password = "password";
	int iteration = -1;
	int keylength = 32;
	vector<unsigned char> key;

	PBKDF2.getDerivedKey(salt, password, iteration, keylength, key);

	//printf("%s\n", key.data());

	string outputstr;
	convert.binary2HexString(key, outputstr);
	printf("%s\n", outputstr.c_str());

	EXPECT_STREQ("", outputstr.c_str());
}

//=========================================================================
CG_PD_Crypto_RSA RSA;

TEST(CGPDCryptoRSA, PubKey) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 512;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	EXPECT_STRNE("", pubKey.c_str());
}

TEST(CGPDCryptoRSA, PrivKey) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 512;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	EXPECT_STRNE("", privKey.c_str());
}

TEST(CGPDCryptoRSA, PubKeyNoPassword) {
	string pubKey, privKey;
	string password;
	int keylength = 512;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	EXPECT_STRNE("", pubKey.c_str());
}

TEST(CGPDCryptoRSA, PrivKeyNoPassword) {
	string pubKey, privKey;
	string password;
	int keylength = 512;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	EXPECT_STRNE("", privKey.c_str());
}

TEST(CGPDCryptoRSA, WrongKeyLength) {
	string pubKey, privKey;
	string password;
	int keylength = 5;
	bool flag = false;

	try {
		RSA.genRSAKey(pubKey, privKey, keylength, password);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);	
}

TEST(CGPDCryptoRSA, KeyLength512) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 512;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	EXPECT_STRNE("", pubKey.c_str());
}

TEST(CGPDCryptoRSA, KeyLength1024) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 1024;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	EXPECT_STRNE("", pubKey.c_str());
}

TEST(CGPDCryptoRSA, KeyLength2048) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 2048;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	EXPECT_STRNE("", pubKey.c_str());
}

TEST(CGPDCryptoRSA, KeyLength4096) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 4096;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	EXPECT_STRNE("", pubKey.c_str());
}

TEST(CGPDCryptoRSA, ImportKey) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 512;

	RSA.genRSAKey(pubKey, privKey, keylength, password);
	RSA.importKey(pubKey, privKey, password);
	EXPECT_STRNE("", pubKey.c_str());
}

TEST(CGPDCryptoRSA, ImportEmptyPubKey) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 512;

	//RSA.genRSAKey(pubKey, privKey, keylength, password);

	bool flag = false;
	try {
		RSA.importKey(pubKey, privKey, password);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

TEST(CGPDCryptoRSA, ImportEmptyPrivKey) {
	string pubKey, privKey;
	string password = "KevinLin";
	int keylength = 512;

	string privKey2;
	
	bool flag = false;
	try {
		RSA.genRSAKey(pubKey, privKey, keylength, password);
		RSA.importKey(pubKey, privKey2, password);
	}
	catch (exception& e) {
		flag = true;
		cout << "catch exception: " << e.what() << endl;
	}
	EXPECT_EQ(true, flag);
}

string RSAEncryptOutputstr, RSAEncryptOutputstr2;
string GloPubKey, GloPrivKey;
string GloPassword = "KevinLin";
int GloKeylength = 512;
TEST(CGPDCryptoRSA, Encrypt) {
	RSA.genRSAKey(GloPubKey, GloPrivKey, GloKeylength, GloPassword);

	string inputstr = "ABCDEF0123456789";	

	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);
	RSA.encrypt(inputvec, outputvec);
	convert.binary2HexString(outputvec, RSAEncryptOutputstr);
	EXPECT_STRNE("", RSAEncryptOutputstr.c_str());	
}

TEST(CGPDCryptoRSA, Encrypt2) {
	//RSA.genRSAKey(GloPubKey, GloPrivKey, GloKeylength, GloPassword);

	string inputstr = "9A8F765CDB132E04";

	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);
	RSA.encrypt(inputvec, outputvec);
	convert.binary2HexString(outputvec, RSAEncryptOutputstr2);
	EXPECT_STRNE("", RSAEncryptOutputstr.c_str());
}

TEST(CGPDCryptoRSA, Decrypt) {
	RSA.importKey(GloPubKey, GloPrivKey, GloPassword);
	string inputstr = RSAEncryptOutputstr;
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	RSA.decrypt(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("ABCDEF0123456789", outputstr.c_str());
}

TEST(CGPDCryptoRSA, Decrypt2) {
	//RSA.importKey(GloPubKey, GloPrivKey, GloPassword);
	string inputstr = RSAEncryptOutputstr2;
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	RSA.decrypt(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("9A8F765CDB132E04", outputstr.c_str());
}

//=========================================================================
CG_PD_Crypto_SHA SHA;

TEST(CG_PD_Crypto_SHA, SHA1Vec2Vec) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA1(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("719FC38765763899CE3F2FE43B71D2A0454FEE1B", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1Vec2Vec2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA1(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("2DF9E5A437011D8DDD554BB874936F1FD94E7CF1", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1Vec2Base64string) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA1(inputvec, outputstr);

	EXPECT_STREQ("cZ/Dh2V2OJnOPy/kO3HSoEVP7hs=", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1Vec2Base64string2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA1(inputvec, outputstr);

	EXPECT_STREQ("LfnlpDcBHY3dVUu4dJNvH9lOfPE=", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1String2Hexstring) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.SHA1(inputstr, outputstr);
	EXPECT_STREQ("38A59744C33F632DD146135FEDC755F0FF71DCDD", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1String2Hexstring2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	SHA.SHA1(inputstr, outputstr);
	EXPECT_STREQ("4D857D2408B00C3DD17F0C4FFCF15B97F1049867", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1HashVec2Vec) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA1(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("0F76ACE1DD171B482833B6DEE4884E8AB3981524", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1HashVec2Vec2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA1(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("8C230E6EFB32D0408B5B5679A4A20F5B1E4D9793", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1HashVec2Base64string) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA1(inputvec, outputstr);

	EXPECT_STREQ("D3as4d0XG0goM7be5IhOirOYFSQ=", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1HashVec2Base64string2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA1(inputvec, outputstr);

	EXPECT_STREQ("jCMObvsy0ECLW1Z5pKIPWx5Nl5M=", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1HashString2Hexstring) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.hashMACSHA1(inputstr, outputstr);
	EXPECT_STREQ("39B77EF8DDEC1D79A8A5987D189B37C6006E13D0", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA1HashString2Hexstring2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.hashMACSHA1(inputstr, outputstr);
	EXPECT_STREQ("266C3B284DABAE349B081672A547D7B3A8B263CA", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256Vec2Vec) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA256(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("C581B6D2414FA1F0417002CD96E8037276FBEF81F67A19962A7C16680FABC5E1", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256Vec2Vec2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA256(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("223E0A160AF9DA0A03E6DD2C4719C56F5D66A633CBE84E78AAA9F3735865522A", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256Vec2Base64string) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA256(inputvec, outputstr);

	EXPECT_STREQ("xYG20kFPofBBcALNlugDcnb774H2ehmWKnwWaA+rxeE=", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256Vec2Base64string2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA256(inputvec, outputstr);

	EXPECT_STREQ("Ij4KFgr52goD5t0sRxnFb11mpjPL6E54qqnzc1hlUio=", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256String2Hexstring) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.SHA256(inputstr, outputstr);
	EXPECT_STREQ("B3F6E70FB2A5F0F21337A82EE5F5A18F803C2D16DA50191D49033F154A17FFB2", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256String2Hexstring2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	SHA.SHA256(inputstr, outputstr);
	EXPECT_STREQ("CD6C1F7D1DC6717D6371D2647910CA71BA3BF0B611083D322466B8843B4285B6", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256HashVec2Vec) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA256(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("C83F8E2A4455E90B538E093002BCC761B92017FE2D1B91E980655D898ABAF8DF", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256HashVec2Vec2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA256(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("7559BC26E697BAADEA14771F872DDD291E84A9BF63465A02E5B03E950BB39D51", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256HashVec2Base64string) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA256(inputvec, outputstr);

	EXPECT_STREQ("yD+OKkRV6QtTjgkwArzHYbkgF/4tG5HpgGVdiYq6+N8=", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256HashVec2Base64string2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA256(inputvec, outputstr);

	EXPECT_STREQ("dVm8JuaXuq3qFHcfhy3dKR6Eqb9jRloC5bA+lQuznVE=", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256HashString2Hexstring) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.hashMACSHA256(inputstr, outputstr);
	EXPECT_STREQ("940E2F95475B524C6C1261992F4E678287586CACAB61ED41D071E2F6BC07E3E2", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA256HashString2Hexstring2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.hashMACSHA256(inputstr, outputstr);
	EXPECT_STREQ("20AECD04B8E183DC8B73E1E473C70DF60BBDA5510549CA93260EB4D0FB2814F5", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512Vec2Vec) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA512(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("B85B1AA17931D2791EE8995D860AE8D55DAE7DBA61E5474A8D5A2E578AF058C257B76EC1A84E3C583C829BB48859ADD0E2D2F6896430238F2A35A4F759926E3A", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512Vec2Vec2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA512(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("B40AEB46A4561B14803082EC451620844EF0A875745C81A93E3919F49C2F903D59C07A5652113556BC8160B3146754DBE54FE61331DD973DABD1A3A25C995E65", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512Vec2Base64string) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA512(inputvec, outputstr);

	EXPECT_STREQ("uFsaoXkx0nke6Jldhgro1V2ufbph5UdKjVouV4rwWMJXt27BqE48WDyCm7SIWa3Q4tL2iWQwI48qNaT3WZJuOg==", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512Vec2Base64string2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.SHA512(inputvec, outputstr);

	EXPECT_STREQ("tArrRqRWGxSAMILsRRYghE7wqHV0XIGpPjkZ9JwvkD1ZwHpWUhE1VryBYLMUZ1Tb5U/mEzHdlz2r0aOiXJleZQ==", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512String2Hexstring) {
	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.SHA512(inputstr, outputstr);
	EXPECT_STREQ("85301C19F9E84BB3EAA514F64F9F7DA0D14F7E777D4460773AAFB145A81C6ABA1DABD08B16D552E547F5196A55BA59C03C93E59F726439F45EE597BA5F73D156", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512String2Hexstring2) {
	//Change inputstr
	string inputstr = "0123456789ABCDEF0123456789ABCDEF";
	string outputstr;

	SHA.SHA512(inputstr, outputstr);
	EXPECT_STREQ("03168CDB0415E930DEAB0614EAE66FF0F8B34A472B6BBB371466B69CAEB6A64E5A4C4481D7CC4826D7F7E71973E9E9B31FF07F828DAAAAF1D05AAB5423514DD2", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512HashVec2Vec) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA512(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("2A3DDBBEC276AE67D24C10EE767D239FCB4C6B612442D8D79B7B4B68B52130CC0E73BA51A577895128CF2C7262F537306365A9F3453713646F8431FF3282EBBF", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512HashVec2Vec2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA512(inputvec, outputvec);
	convert.binary2HexString(outputvec, outputstr);
	EXPECT_STREQ("12BE8143E953128A47E6DEE985701BC6B2F391AEC925E817E0AD6B848C30867BE86766192C480C3012E08D7B11980C1283FEC77EB93E3BEEA975DBCFD7C48086", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512HashVec2Base64string) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA512(inputvec, outputstr);

	EXPECT_STREQ("Kj3bvsJ2rmfSTBDudn0jn8tMa2EkQtjXm3tLaLUhMMwOc7pRpXeJUSjPLHJi9TcwY2Wp80U3E2RvhDH/MoLrvw==", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512HashVec2Base64string2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;
	vector<unsigned char> inputvec, outputvec;
	convert.hexString2Binary(inputstr, inputvec);

	SHA.hashMACSHA512(inputvec, outputstr);

	EXPECT_STREQ("Er6BQ+lTEopH5t7phXAbxrLzka7JJegX4K1rhIwwhnvoZ2YZLEgMMBLgjXsRmAwSg/7Hfrk+O+6pddvP18SAhg==", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512HashString2Hexstring) {
	string HmacKey = "ABCDEF0123456789";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.hashMACSHA512(inputstr, outputstr);
	EXPECT_STREQ("8D060F3FD40A008064B86FACA3D4CBBBA68845684785BFC70CC9F174B695BC8FA750DDF31C26C2E655720D6B1FE94B376C970A21DF4932C155296206BCD0A66B", outputstr.c_str());
}

TEST(CG_PD_Crypto_SHA, SHA512HashString2Hexstring2) {
	//Change Key
	string HmacKey = "DB132E04C567F8A9";
	vector<unsigned char> HmacKeyVec;
	convert.hexString2Binary(HmacKey, HmacKeyVec);
	SHA.setHmacKey(HmacKeyVec);

	string inputstr = "9A8F765CDB132E04";
	string outputstr;

	SHA.hashMACSHA512(inputstr, outputstr);
	EXPECT_STREQ("57644C4EF4B8DA9F59302057B51CD1B9420FA705E525DD3753A75ED58AF6B89A77D2E6313E6020E4D9C0C92DF5419F5FC10C487BB97CB2D976390A3C8DCCDB13", outputstr.c_str());
}



int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}