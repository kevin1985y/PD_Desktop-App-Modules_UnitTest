// Log_module_UnitTest.cpp : 定義主控台應用程式的進入點。

#include "stdafx.h"
#include "gtest/gtest.h"
#include "CG_PD_Log.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <ctime>
#include < windows.h >

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
using namespace std;

CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
//=========================================================================
string FullName;
string ReadIP(bool default, bool flag);
string ReadMsg(bool default, bool flag);
string ReadAppName(bool default, bool flag);
string ReadFileNameTime(bool default, int flag);
string ReadOutputFormat(bool default, string flag);
string ReadMode(string flag);
string ReadPrintSeverity(bool default, bool flag);
string ReadSeverity(bool default, CG_PD_Log::severity flag);
void FullPath();
///*
TEST(CGPDLog, TimeUTCTrue) {
	FullPath();
	CGLog.setTimeUTC(true);
	string output = __FUNCTION__;
	CGLog.debug("Event: %s", output.c_str());

	fstream File;
	char Buffer[100];
	char *Content;
	//char Target[100] = { 0 };
	char Target[100];
	//char TargetT[] = {'T','E', '0', '9' };
	//printf("%s \n", TargetT);
	Sleep(10);
	File.open(FullName, ios::in);
	File.getline(Buffer, sizeof(Buffer));
	Content = strstr(Buffer, "+");
	//printf("%s \n", Content);
	if (!Content) {
		//printf("This is not \"TimeUTC\". \n");
	}
	else {
		strncpy(Target, Content, 6);
		Target[6] = '\0';
		//printf("Taget is %s \n", Target);
		//printf("Done. \n");
	}
	File.close();

	EXPECT_STREQ("+08:00", string(Target).c_str());

	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, TimeUTCFalse) {
	FullPath();
	CGLog.setTimeUTC(false);
	string output = __FUNCTION__;
	CGLog.debug("Event: %s", output.c_str());

	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100];
	Sleep(10);
	File.open(FullName, ios::in);
	File.getline(Buffer, sizeof(Buffer));
	Content = strstr(Buffer, "Z");
	if (!Content) {
		//printf("This is \"TimeUTC\". \n");
		//printf("Taget is %s \n", Target);
	}
	else {
		strncpy(Target, Content, 1);
		Target[1] = '\0';
		//printf("Taget is %s \n", Target);
		//printf("Done. \n");
	}
	File.close();

	EXPECT_STREQ("Z", Target);

	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, TimeUTCDefault) {
	FullPath();
	string output = __FUNCTION__;
	CGLog.debug("Event: %s", output.c_str());

	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100];
	Sleep(10);
	File.open(FullName, ios::in);
	File.getline(Buffer, sizeof(Buffer));
	Content = strstr(Buffer, "Z");
	if (!Content) {
		//printf("This is \"TimeUTC\". \n");
		//printf("Taget is %s \n", Target);
	}
	else {
		strncpy(Target, Content, 1);
		Target[1] = '\0';
		//printf("Taget is %s \n", Target);
		//printf("Done. \n");
	}
	File.close();

	EXPECT_STREQ("Z", Target);

	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, OnlyMsgTrue) {
	fstream File;
	string Target = ReadMsg(false, true);
	EXPECT_STREQ("", Target.c_str());
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, OnlyMsgFalse) {
	fstream File;
	string Target = ReadMsg(false, false);
	EXPECT_STREQ("[Debug]", Target.c_str());
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, OnlyMsgDefault) {
	fstream File;
	string Target = ReadMsg(true, false);
	EXPECT_STREQ("[Debug]", Target.c_str());
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, PrintIPTrue) {
	string Target = ReadIP(false, true);
	EXPECT_STREQ("[127.0.0.1]", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, PrintIPFalse) {
	string Target = ReadIP(false, false);
	EXPECT_STREQ("", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, PrintIPDefault) {
	string Target = ReadIP(true, false);
	EXPECT_STREQ("", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, PrintAppNameTrue) {
	string Target = ReadAppName(false, true);
	EXPECT_STREQ("[KevinTest]", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, PrintAppNameFalse) {
	string Target = ReadAppName(false, false);
	EXPECT_STREQ("", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, PrintAppNameDefault) {
	string Target = ReadAppName(true, false);
	EXPECT_STREQ("", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetOutputFormatJSON) {
	string Target = ReadOutputFormat(false, "JSON");
	EXPECT_STREQ("Serverity", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetOutputFormatNormal) {
	string Target = ReadOutputFormat(false, "Normal");
	EXPECT_STREQ("", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetOutputFormatDefault) {
	string Target = ReadOutputFormat(true, "JSON");
	EXPECT_STREQ("", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetDebug) {
	string Target = ReadMode("debug");
	EXPECT_STREQ("Debug", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetInfo) {
	string Target = ReadMode("info");
	EXPECT_STREQ("Information", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetNotice) {
	string Target = ReadMode("notice");
	EXPECT_STREQ("Notice", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetWarning) {
	string Target = ReadMode("warn");
	EXPECT_STREQ("Warning", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetError) {
	string Target = ReadMode("error");
	EXPECT_STREQ("Error", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetCritical) {
	string Target = ReadMode("crit");
	EXPECT_STREQ("Critical", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetAlert) {
	string Target = ReadMode("alert");
	EXPECT_STREQ("Alert", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetEmergency) {
	string Target = ReadMode("emer");
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetPrintSeverityTrue) {
	string Target = ReadPrintSeverity(false, true);
	EXPECT_STREQ("[Debug]", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetPrintSeverityFalse) {
	string Target = ReadPrintSeverity(false, false);
	EXPECT_STREQ("", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetPrintSeverityDefault) {
	string Target = ReadPrintSeverity(true, false);
	EXPECT_STREQ("[Debug]", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetSeverityDebug) {
	//FullPath();
	//printf("fullname:%s\n", FullName.c_str());
	string Target = ReadSeverity(false, CG_PD_Log::severity::Debug);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;	
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetSeverityInformation) {
	string Target = ReadSeverity(false, CG_PD_Log::severity::Information);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetSeverityNotice) {
	string Target = ReadSeverity(false, CG_PD_Log::severity::Notice);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetSeverityWarning) {
	string Target = ReadSeverity(false, CG_PD_Log::severity::Warning);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetSeverityError) {
	string Target = ReadSeverity(false, CG_PD_Log::severity::Error);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetSeverityCritical) {
	string Target = ReadSeverity(false, CG_PD_Log::severity::Critical);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetSeverityAlert) {
	string Target = ReadSeverity(false, CG_PD_Log::severity::Alert);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}


TEST(CGPDLog, SetSeverityEmergency) {
	string Target = ReadSeverity(false, CG_PD_Log::severity::Emergency);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetSeverityDefault) {
	string Target = ReadSeverity(true, CG_PD_Log::severity::Debug);
	EXPECT_STREQ("Emergency", Target.c_str());
	fstream File;
	File.open(FullName, ios::out | ios::trunc);
	File.close();
}

TEST(CGPDLog, SetFileNameTimeNoDate) {
	string Target = ReadFileNameTime(false, 0);
	//printf("target is %s\n", Target);
	bool Found;
	fstream File;
	File.open(Target, ios::in);
	if (!File) {
		Found = false;
	}
	else {
		Found = true;
	}
	EXPECT_EQ(true, Found);
}

TEST(CGPDLog, SetFileNameTimeDateFirst) {
	string Target = ReadFileNameTime(false, 1);
	//printf("target is %s\n", Target);
	bool Found;
	fstream File;
	File.open(Target, ios::in);
	if (!File) {
		Found = false;
	}
	else {
		Found = true;
	}
	EXPECT_EQ(true, Found);
}

TEST(CGPDLog, SetFileNameTimeDateALast) {
	string Target = ReadFileNameTime(false, 2);
	//printf("target is %s\n", Target);
	bool Found;
	fstream File;
	File.open(Target, ios::in);
	if (!File) {
		Found = false;
	}
	else {
		Found = true;
	}
	EXPECT_EQ(true, Found);
}

TEST(CGPDLog, SetFileNameTimeDefault) {
	string Target = ReadFileNameTime(false, 2);
	//printf("target is %s\n", Target);
	bool Found;
	fstream File;
	File.open(Target, ios::in);
	if (!File) {
		Found = false;
	}
	else {
		Found = true;
	}
	EXPECT_EQ(true, Found);
}

string ReadMsg(bool default, bool flag)
{
	CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
	if (default == false) {
		CGLog.setOnlyPrintMsg(flag);
		//printf("It's no default.\n");
	}
	string output = __FUNCTION__;
	CGLog.debug("Event: %s", output.c_str());

	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100] = { 0 };
	Sleep(10);
	File.open(FullName, ios::in);
	File.getline(Buffer, sizeof(Buffer));
	Content = strstr(Buffer, "[Debug]");
	if (!Content) {
		//printf("It is only Msg. \n");
		//printf("Taget is %s \n", Target);
	}
	else {
		strncpy(Target, Content, 7);
		//Target[7] = '\0';
		//printf("Taget is %s \n", Target);
		//printf("Done. \n");
	}
	File.close();
	return Target;
}

string ReadIP(bool default, bool flag)
{	
	CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
	if (default == false) {
		CGLog.setPrintIP(flag);
		//printf("It's no default.\n");
	}
	CGLog.setIP("127.0.0.1");
	string input = __FUNCTION__;
	CGLog.debug("Event: %s", input.c_str());

	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100] = { 0 };
	Sleep(10);
	File.open(FullName, ios::in);
	File.getline(Buffer, sizeof(Buffer));
	Content = strstr(Buffer, "[127.0.0.1]");
	if (!Content) {
		//printf("Not Found. \n");
		//return Target;
	}
	else {
		strncpy(Target, Content, 11);
		//Target[11] = '\0';
		//printf("Taget is %s \n", Target);
		//return Target;
	}
	//printf("Read done. \n");
	File.close();
	return Target;
}

string ReadAppName(bool default, bool flag)
{
	CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
	if (default == false) {
		CGLog.setPrintAppName(flag);
		//printf("It's no default.\n");
	}
	CGLog.setAppName(L"KevinTest");
	string input = __FUNCTION__;
	CGLog.debug("Event: %s", input.c_str());

	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100] = { 0 };
	Sleep(10);
	File.open(FullName, ios::in);
	File.getline(Buffer, sizeof(Buffer));
	Content = strstr(Buffer, "[KevinTest]");
	if (!Content) {
		//printf("Not Found. \n");
	}
	else {
		strncpy(Target, Content, 11);
		//Target[11] = '\0';
		//printf("Taget is %s \n", Target);
	}
	//printf("Read done. \n");
	File.close();
	return Target;
}

string ReadOutputFormat(bool default, string flag)
{
	CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
	if (default == false) {
		if (flag == "JSON") {
			CGLog.setOutputFormat(CG_PD_Log::outputFormat::JSON);
			//printf("It's JSON.\n");
		}
		else if (flag == "Normal") {
			CGLog.setOutputFormat(CG_PD_Log::outputFormat::Normal);
			//printf("It's Normal.\n");
		}		
		//printf("It's no default.\n");
	}
	string input = __FUNCTION__;
	CGLog.debug("Event: %s", input.c_str());

	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100] = { 0 };
	Sleep(10);
	File.open(FullName, ios::in);
	File.getline(Buffer, sizeof(Buffer));
	//printf("Buffer is %s \n", Buffer);
	Content = strstr(Buffer, "Serverity");
	if (!Content) {
		//printf("Not Found. \n");
	}
	else {
		strncpy(Target, Content, 9);
		//Target[11] = '\0';
		//printf("Taget is %s \n", Target);
	}
	//printf("Read done. \n");
	File.close();
	return Target;
}

string ReadMode(string flag)
{
	CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
	string input = __FUNCTION__;
	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100] = { 0 };

	if (flag == "debug") {
		CGLog.debug("Event: %s", input.c_str());
		Sleep(10);
		File.open(FullName, ios::in);
		File.getline(Buffer, sizeof(Buffer));
		Content = strstr(Buffer, "Debug");
		strncpy(Target, Content, 5);
		File.close();
	}
	else if (flag == "info") {
		CGLog.info("Event: %s", input.c_str());
		Sleep(10);
		File.open(FullName, ios::in);
		File.getline(Buffer, sizeof(Buffer));
		Content = strstr(Buffer, "Information");
		//printf("Content is %s \n", Content);
		strncpy(Target, Content, 11);
		//printf("Target is %s", Target);
		File.close();
	}
	else if (flag == "notice") {
		CGLog.notice("Event: %s", input.c_str());
		Sleep(10);
		File.open(FullName, ios::in);
		File.getline(Buffer, sizeof(Buffer));
		Content = strstr(Buffer, "Notice");
		strncpy(Target, Content, 6);
		File.close();
	}
	else if (flag == "warn") {
		CGLog.warn("Event: %s", input.c_str());
		Sleep(10);
		File.open(FullName, ios::in);
		File.getline(Buffer, sizeof(Buffer));
		Content = strstr(Buffer, "Warning");
		strncpy(Target, Content, 7);
		File.close();
	}
	else if (flag == "error") {
		CGLog.error("Event: %s", input.c_str());
		Sleep(10);
		File.open(FullName, ios::in);
		File.getline(Buffer, sizeof(Buffer));
		Content = strstr(Buffer, "Error");
		strncpy(Target, Content, 5);
		File.close();
	}
	else if (flag == "crit") {
		CGLog.crit("Event: %s", input.c_str());
		Sleep(10);
		File.open(FullName, ios::in);
		File.getline(Buffer, sizeof(Buffer));
		Content = strstr(Buffer, "Critical");
		strncpy(Target, Content, 8);
		File.close();
	}
	else if (flag == "alert") {
		CGLog.alert("Event: %s", input.c_str());
		Sleep(10);
		File.open(FullName, ios::in);
		File.getline(Buffer, sizeof(Buffer));
		Content = strstr(Buffer, "Alert");
		strncpy(Target, Content, 5);
		File.close();
	}
	else if (flag == "emer") {
		CGLog.emer("Event: %s", input.c_str());
		Sleep(10);
		File.open(FullName, ios::in);
		File.getline(Buffer, sizeof(Buffer));
		Content = strstr(Buffer, "Emergency");
		strncpy(Target, Content, 9);
		File.close();
	}
	//printf("Target is %s", Target);
	return Target;
}

string ReadPrintSeverity(bool default, bool flag)
{
	CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
	if (default == false) {
		CGLog.setPrintServerity(flag);
		//printf("It's no default.\n");
	}
	string input = __FUNCTION__;
	CGLog.debug("Event: %s", input.c_str());

	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100] = { 0 };
	Sleep(10);
	File.open(FullName, ios::in);
	File.getline(Buffer, sizeof(Buffer));
	Content = strstr(Buffer, "[Debug]");
	if (!Content) {
		//printf("Not Found. \n");
	}
	else {
		strncpy(Target, Content, 7);
		//Target[11] = '\0';
		//printf("Taget is %s \n", Target);
	}
	//printf("Read done. \n");
	File.close();
	return Target;
}

string ReadSeverity(bool default, CG_PD_Log::severity flag)
{
	CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
	string input = __FUNCTION__;
	fstream File;
	char Buffer[100];
	char *Content;
	char Target[100] = { 0 };
	if (default == false) {
		CGLog.setServerity(flag);
	}
	CGLog.debug("Event: %s", input.c_str());
	CGLog.info("Event: %s", input.c_str());
	CGLog.notice("Event: %s", input.c_str());
	CGLog.warn("Event: %s", input.c_str());
	CGLog.error("Event: %s", input.c_str());
	CGLog.crit("Event: %s", input.c_str());
	CGLog.alert("Event: %s", input.c_str());
	CGLog.emer("Event: %s", input.c_str());
	Sleep(1000);

	string level[] = { "Debug","Information", "Notice", "Warning", "Error",  "Critical", "Alert" , "Emergency" };
	int i = 7 - flag;
	File.open(FullName, ios::in);
	//printf("start \n");
	string Level, LastWord;
	while (!File.eof()) {
		//printf("i is %d \n", i);
		File.getline(Buffer, sizeof(Buffer));
		//printf("Buffer is %s \n", Buffer);
		Content = strstr(Buffer, level[i].c_str());
		//printf("Content is %s \n", Content);
		strncpy(Target, Content, level[i].length());
		Target[level[i].length()] = '\0';
		//printf("Taget is %s \n", Target);
		i++;
		Level = Target;
		if (Level != "") {
			LastWord = Level;
			//printf("LastWord is %s \n", LastWord);
		}
	}
		//printf("LastWord is %s \n", LastWord);
		File.close();
		return LastWord;
}

string ReadFileNameTime(bool default, int flag)
{
	CG_PD_Log CGLog(L"E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\file.log");
	string input = __FUNCTION__;
	string FileNameTime;

	time_t NowTime;
	time(&NowTime);
	struct tm* timeInfo = nullptr;
	timeInfo = gmtime(&NowTime);
	string fileFormat = "%Y-%m-%d";
	char timeStr[32];
	strftime(timeStr, sizeof(timeStr), fileFormat.c_str(), timeInfo);
	string Path = "E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\";
	string Date = timeStr;

	if (default == false) {
		CGLog.setFileNameTime(flag);
		CGLog.debug("Event: %s", input.c_str());

		if (flag == 0) {
			FileNameTime = "file.log";
			FileNameTime = Path + FileNameTime;
		}
		else if (flag == 1) {
			FileNameTime = "_file.log";
			FileNameTime = Path + timeStr + FileNameTime;
		}
		else if (flag = 2) {
			FileNameTime = ".log";
			FileNameTime = Path + "file_" + timeStr + FileNameTime;
		}
	}
	else {
		CGLog.debug("Event: %s", input.c_str());
		FileNameTime = "_file.log";
		FileNameTime = Path + timeStr + FileNameTime;
	}
	return FileNameTime;
}

void FullPath() 
{
	time_t NowTime;
	time(&NowTime);
	struct tm* timeInfo = nullptr;
	timeInfo = gmtime(&NowTime);
	string fileFormat = "%Y-%m-%d";
	char timeStr[32];
	strftime(timeStr, sizeof(timeStr), fileFormat.c_str(), timeInfo);
	string Path = "E:\\Project_Git\\PD_Desktop App Modules\\UnitTest\\Log_module_UnitTest\\";
	string Date = timeStr;
	string FileName = "_file.log";
	FullName = Path + timeStr + FileName;
	//printf("Fullpath: \n%s \n", FullName.c_str());
}

int main(int argc, char* argv[])
{

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

