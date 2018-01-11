// Http_module_UnitTest_Client.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "HttpRequest.h"
#include  "JsonTool.h"
#include <windows.h>
using namespace std;
//=========================================================================

TEST(HttpClient, HttpSetURLSuccess) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setURL("http://127.0.0.1:81/");

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}

	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPHandler_Get\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpSetIPnPortSuccess) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(82);

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}

	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPHandler_Get\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpSetPathFailure) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(83);

	printf("==================Get=================\n");
	helper->setPath("/Echo");
	helper->setContentType(HttpRequest::TYPE_JSON);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}

	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ(501, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpTypeForm) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(84);

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_FORM);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	//printf("HttpModuleException:(%d)%s\n", e.code(), e.what());
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"MPart_HTTPHandler\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpTypeJS) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(85);

	//helper->addQuery("num","5");
	//helper->addQuery("num2", "25");	

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JS);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	//helper->setException();

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	//printf("HttpModuleException:(%d)%s\n", e.code(), e.what());
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JS_HTTPHandler\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpTypeURLENC) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(86);

	//helper->addQuery("num","5");
	//helper->addQuery("num2", "25");	

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_URLENC);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	//helper->setException();

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	//printf("HttpModuleException:(%d)%s\n", e.code(), e.what());
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"URLENC_HTTPHandler\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpPost) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;
	string json;

	helper->setURL("http://127.0.0.1:87/");

	printf("=================Post=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);

	printf("URL:%s\n", helper->getURL().c_str());
	json.assign("{\"test\":1,\"test2\":\"11111\"}");
	helper->setData(json);
	printf("SetJson:%s\n", json.c_str());
	printf("======================================\n");

	code = helper->doPost(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPHandler_Post\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpPut) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;
	string json;

	helper->setURL("http://127.0.0.1:88/");

	printf("=================Put=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);

	printf("URL:%s\n", helper->getURL().c_str());
	json.assign("{\"test\":1,\"test2\":\"11111\"}");
	helper->setData(json);
	printf("SetJson:%s\n", json.c_str());
	printf("=====================================\n");

	code = helper->doPut(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPHandler_Put\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpDelete) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;
	string json;

	helper->setURL("http://127.0.0.1:89/");

	printf("================Delete================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);

	printf("URL:%s\n", helper->getURL().c_str());
	json.assign("{\"test\":1,\"test2\":\"11111\"}");
	helper->setData(json);
	printf("SetJson:%s\n", json.c_str());
	printf("======================================\n");

	code = helper->doDelete(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPHandler_Delete\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpPostForm) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setURL("http://127.0.0.1:90/");

	printf("===============PostForm===============\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_FORM);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->addFormFile(L"testform.txt", "file1", "text/plain");
	//helper->addFormFile(L"testform2.txt", "file2", "text/plain");
	printf("======================================\n");

	code = helper->doPost(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"MPart_HTTPHandler\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpPostFormNoFile) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setURL("http://127.0.0.1:91/");

	printf("===============PostForm===============\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_FORM);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->addFormFile(L"testform2.txt", "file1", "text/plain");
	//helper->addFormFile(L"testform2.txt", "file2", "text/plain");
	printf("======================================\n");

	code = helper->doPost(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ(500, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpSocket) {
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code = 0;
	string json;
	bool isNext = false;

	helper->setURL("http://127.0.0.1:92/");

	printf("================Socket================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);

	printf("URL:%s\n", helper->getURL().c_str());
	json.assign("{\"test\":1,\"test2\":\"Socket\"}");
	helper->setContentType(HttpRequest::TYPE_JSON);
	helper->initWebsocket();
	helper->socketSend(json, true);
	do {
		code = helper->socketReceive(response, isNext);
		//EXPECT_EQ("{\"WSHandler\":\"OK\"}", response);
		cout << "testSocket" << response << endl;

	} while (isNext);
	printf("======================================\n");
	EXPECT_EQ("{\"WSHandler\":\"End\"}", response);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpClient, HttpConnectFailure) {
	Sleep(500);
	HttpRequest *helper = new HttpRequest(false);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(81);

	//helper->addQuery("num","5");
	//helper->addQuery("num2", "25");	

	printf("==================Get=================\n");
	helper->setPath("/Echo");
	helper->setContentType(HttpRequest::TYPE_JSON);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	//helper->setException();

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	//printf("HttpModuleException:(%d)%s\n", e.code(), e.what());
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("HttpRequest.cpp(252):doGet:Connection refused", response);
	EXPECT_EQ(0, status);
}
TEST(HttpsClient, HttpsSetURLSuccess) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setURL("http://127.0.0.1:444/");

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}

	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPsHandler_Get\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsSetIPnPortSuccess) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(446);

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}

	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPsHandler_Get\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsSetPathFailure) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(447);

	printf("==================Get=================\n");
	helper->setPath("/Echo");
	helper->setContentType(HttpRequest::TYPE_JSON);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}

	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ(501, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsTypeForm) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(448);

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_FORM);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	//printf("HttpModuleException:(%d)%s\n", e.code(), e.what());
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"MPart_HTTPsHandler\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsTypeJS) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(449);

	//helper->addQuery("num","5");
	//helper->addQuery("num2", "25");	

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JS);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	//helper->setException();

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	//printf("HttpModuleException:(%d)%s\n", e.code(), e.what());
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JS_HTTPsHandler\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsTypeURLENC) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(450);

	//helper->addQuery("num","5");
	//helper->addQuery("num2", "25");	

	printf("==================Get=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_URLENC);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	//helper->setException();

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	//printf("HttpModuleException:(%d)%s\n", e.code(), e.what());
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"URLENC_HTTPsHandler\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsPost) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;
	string json;

	helper->setURL("http://127.0.0.1:451/");

	printf("=================Post=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);

	printf("URL:%s\n", helper->getURL().c_str());
	json.assign("{\"test\":1,\"test2\":\"11111\"}");
	helper->setData(json);
	printf("SetJson:%s\n", json.c_str());
	printf("======================================\n");

	code = helper->doPost(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPsHandler_Post\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsPut) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;
	string json;

	helper->setURL("http://127.0.0.1:452/");

	printf("=================Put=================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);

	printf("URL:%s\n", helper->getURL().c_str());
	json.assign("{\"test\":1,\"test2\":\"11111\"}");
	helper->setData(json);
	printf("SetJson:%s\n", json.c_str());
	printf("=====================================\n");

	code = helper->doPut(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPsHandler_Put\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsDelete) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;
	string json;

	helper->setURL("http://127.0.0.1:453/");

	printf("================Delete================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);

	printf("URL:%s\n", helper->getURL().c_str());
	json.assign("{\"test\":1,\"test2\":\"11111\"}");
	helper->setData(json);
	printf("SetJson:%s\n", json.c_str());
	printf("======================================\n");

	code = helper->doDelete(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"JSON_HTTPsHandler_Delete\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsPostForm) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setURL("http://127.0.0.1:454/");

	printf("===============PostForm===============\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_FORM);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->addFormFile(L"testform.txt", "file1", "text/plain");
	//helper->addFormFile(L"testform2.txt", "file2", "text/plain");
	printf("======================================\n");

	code = helper->doPost(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("{\"MPart_HTTPsHandler\":OK}", response);
	EXPECT_EQ(200, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsPostFormNoFile) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setURL("http://127.0.0.1:455/");

	printf("===============PostForm===============\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_FORM);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->addFormFile(L"testform2.txt", "file1", "text/plain");
	//helper->addFormFile(L"testform2.txt", "file2", "text/plain");
	printf("======================================\n");

	code = helper->doPost(response);
	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ(500, status);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsSocket) {
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code = 0;
	string json;
	bool isNext = false;

	helper->setURL("http://127.0.0.1:456/");

	printf("================Socket================\n");
	helper->setPath("/Test");
	helper->setContentType(HttpRequest::TYPE_JSON);

	printf("URL:%s\n", helper->getURL().c_str());
	json.assign("{\"test\":1,\"test2\":\"Socket\"}");
	helper->setContentType(HttpRequest::TYPE_JSON);
	helper->initWebsocket();
	helper->socketSend(json, true);
	do {
		code = helper->socketReceive(response, isNext);
		//EXPECT_EQ("{\"WSHandler\":\"OK\"}", response);
		cout << "testSocket" << response << endl;

	} while (isNext);
	printf("======================================\n");
	EXPECT_EQ("{\"WSHandler\":\"End\"}", response);

	//關閉連線
	helper->setPath("/Close");
	code = helper->doGet(response);
}

TEST(HttpsClient, HttpsConnectFailure) {
	Sleep(500);
	HttpRequest *helper = new HttpRequest(true);
	string response;
	int code;

	helper->setAddress("127.0.0.1");
	helper->setPort(444);

	//helper->addQuery("num","5");
	//helper->addQuery("num2", "25");	

	printf("==================Get=================\n");
	helper->setPath("/Echo");
	helper->setContentType(HttpRequest::TYPE_JSON);
	printf("URL:%s\n", helper->getURL().c_str());
	helper->setConnectionsTimeout(5);
	printf("======================================\n");

	//helper->setException();

	code = helper->doGet(response);

	int status = helper->getHTTPstatus();

	if (code != 0) {
		response.assign(helper->getLastError());
	}
	//printf("HttpModuleException:(%d)%s\n", e.code(), e.what());
	printf("Status:%d\n", status);
	printf("Result:(%d)%s\n", code, response.c_str());

	EXPECT_EQ("HttpRequest.cpp(252):doGet:Connection refused", response);
	EXPECT_EQ(0, status);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

