// Http_module_UnitTest_HttpServer.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "HttpServer.h"
#include "HttpRequest.h"
#include "Key.h"
#include "Poco/Process.h"

using namespace std;
using Poco::Net::HTMLForm;
using Poco::Net::PartHandler;
using Poco::Net::MessageHeader;
using Poco::StreamCopier;
using Poco::Net::NameValueCollection;
using Poco::CountingInputStream;
using Poco::NullOutputStream;
using Poco::Process;

bool SocketReceive;
//=========================================================================

class MyPartHandler : public Poco::Net::PartHandler
{
public:
	void handlePart(const MessageHeader& header, std::istream& stream)
	{
		if (header.has("Content-Disposition"))
		{
			std::string disp;
			NameValueCollection params;
			//cout << header.get("Content-Disposition") << endl;
			cout << "Receive Data:" << endl;
			MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
			cout << "File Type:" + header.get("Content-Type", "(unspecified)") << endl;
			cout << "Key Name:" + params.get("name", "(unnamed)") << endl;
			cout << "File Name:" + params.get("filename", "(unnamed)") << endl;
			cout << "Content:" << endl;
			int p = stream.tellg();  // remember where we are
			string inputdata(istreambuf_iterator<char>(stream), {});
			cout << inputdata << endl;
			stream.seekg(p);        // restore the position						
		}
		CountingInputStream istr(stream);
		NullOutputStream ostr;
		StreamCopier::copyStream(istr, ostr);
	}
};

void MPartHandle(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	cout << "==========================================" << endl;
	cout << "Request:" << request.getURI() << endl;
	cout << "Method:" << request.getMethod() << endl;
	cout << "Type:" << request.getContentType() << endl;
	MyPartHandler partHandler;
	HTMLForm form(request, request.stream(), partHandler);
	//cout << "Form Info:" << endl;
	NameValueCollection::ConstIterator it = form.begin();
	NameValueCollection::ConstIterator end = form.end();
	for (; it != end; ++it)
	{
		cout << it->first << ": " << it->second << endl;
	}
	string ans("{\"MPart_HTTPsHandler\":OK}");
	HttpServer::responseJSON(response, ans);
	cout << "==========================================" << endl;
}

void JSonHandle(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	cout << "==========================================" << endl;
	cout << "Request:" << request.getURI() << endl;
	cout << "Method:" << request.getMethod() << endl;
	cout << "Type:" << request.getContentType() << endl;
	cout << "Data:" << HttpServer::getRequestString(request) << endl;

	string ans;
	if (request.getMethod() == "GET") {
		ans = "{\"JSON_HTTPsHandler_Get\":OK}";
		HttpServer::responseJSON(response, ans);
	}
	else if (request.getMethod() == "POST") {
		ans = "{\"JSON_HTTPsHandler_Post\":OK}";
		HttpServer::responseJSON(response, ans);
	}
	else if (request.getMethod() == "PUT") {
		ans = "{\"JSON_HTTPsHandler_Put\":OK}";
		HttpServer::responseJSON(response, ans);
	}
	else if (request.getMethod() == "DELETE") {
		ans = "{\"JSON_HTTPsHandler_Delete\":OK}";
		HttpServer::responseJSON(response, ans);
	}
	cout << "==========================================" << endl << endl;
}

void JSHandle(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	cout << "==========================================" << endl;
	cout << "Request:" << request.getURI() << endl;
	cout << "Method:" << request.getMethod() << endl;
	cout << "Type:" << request.getContentType() << endl;
	cout << "Data:" << HttpServer::getRequestString(request) << endl;

	string ans;
	ans = "{\"JS_HTTPsHandler\":OK}";
	HttpServer::responseJSON(response, ans);

	cout << "==========================================" << endl << endl;
}

void URLENCHandle(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	cout << "==========================================" << endl;
	cout << "Request:" << request.getURI() << endl;
	cout << "Method:" << request.getMethod() << endl;
	cout << "Type:" << request.getContentType() << endl;
	cout << "Data:" << HttpServer::getRequestString(request) << endl;
	string ans("{\"URLENC_HTTPsHandler\":OK}");
	HttpServer::responseJSON(response, ans);
	cout << "==========================================" << endl << endl;
}

void ServerHandler(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	if (request.getContentType().find("multipart/form-data") != string::npos) {
		return MPartHandle(request, response);
	}
	else if (request.getContentType().find("application/json") != string::npos) {
		//cout << "Before" << HttpServer::getRequestString(request) << endl;
		return JSonHandle(request, response);
	}
	else if (request.getContentType().find("text/javascript") != string::npos) {
		return JSHandle(request, response);
	}
	else if (request.getContentType().find("application/x-www-form-urlencoded") != string::npos) {
		return URLENCHandle(request, response);
	}
}

void SocketHandler(HttpServer* server) {
	cout << "====================SocketHandler======================" << endl;
	string response;
	bool isNext = server->socketReceive(response);
	cout << "WSHandler:" + response << endl;
	if (response != "{\"test\":1,\"test2\":\"Socket\"}") {
		SocketReceive = false;
	}
	else {
		SocketReceive = true;
	}

	server->socketSend("{\"WSHandler\":\"OK\"}", true);
	Sleep(2000);
	server->socketSend("{\"WSHandler\":\"End\"}", false);
	server->socketClose();
	cout << "====================SocketHandler======================" << endl << endl;
}

bool filter(const Poco::Net::HTTPServerRequest& request) {
	string ip = HttpServer::getAddress(request);

	//if (request.getMethod() == "GET") {
	//	cout << "Wait 5s" << endl;
	//	Sleep(5000);
	//}

	cout << "Received Request From:" << ip << endl;
	if (request.getURI() == "/Test") {
		return true;
	}
	else if (request.getURI() == "/Close") {
		//關閉連線
		int pid = Process::id();
		//printf("pid %d\n", pid);
		Process::requestTermination(pid);
		//Process::kill(pid);
		return false;
	}
	else {
		cout << "Filter Reject:" << request.getURI() << endl;
		return false;
	}
}

TEST(HttpsServer, HttpsConnect) {
	int Port = 444;
	printf("Start Server Port:%d\n", Port);
	HttpServer *server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 446;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 447;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 448;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 449;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 450;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 451;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 452;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 453;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 454;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	Port = 455;
	printf("Start Server Port:%d\n", Port);
	server = new HttpServer(true);

	server->setPort(Port);
	server->handleRequest(ServerHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;
}

TEST(HttpsServer, HttpsSocket) {
	int Port = 456;
	printf("Start Server Port:%d\n", Port);
	HttpServer *server = new HttpServer(true);

	server->setPort(Port);
	server->handleWebsocket(SocketHandler);
	server->filterRequest(filter);
	server->setPriv(Key::getKey());
	server->setCert(Key::getCert());

	server->start();
	printf("%d\n", __LINE__);
	server->wait();
	printf("%d\n", __LINE__);
	server->stop();

	delete server;

	EXPECT_EQ(true, SocketReceive);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
