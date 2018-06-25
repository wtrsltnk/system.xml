#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <winsock.h>

#include <system.xml/system.xml.h>

#define BUFFERSIZE 2

std::string HTTP_POST(std::string host, int port, std::string path, std::string data);
void ReplaceAll(std::string &str, const std::string &from, const std::string &to);

void printXml(System::Xml::XmlNode *node, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        std::cout << "\t";
    }
    std::cout << node->Name();
    if (node->Name() == "#comment" || node->Name() == "#cdata-section")
    {
        std::cout << " [" << node->Value() << "]";
    }
    std::cout << std::endl;
    System::Xml::XmlNodeList childNodes = node->ChildNodes();
    for (int i = 0; i < childNodes.Count(); i++)
    {
        System::Xml::XmlNode *childNode = childNodes[i];
        printXml(childNode, depth + 1);
    }
}

int main(int argc, char *argv[])
{
    try
    {
        System::Xml::XmlDocument docc;

        docc.LoadXml("<?xml version=\"1.0\"?>\
<item class=\"attr value\">\
    <!-- Comments -->\
    <name>wrench</name>\
    <length>2.4</length>\
    <data><![CDATA[<html>body</html>]]></data>\
</item>");

        printXml(&docc, 0);
    } catch (System::Xml::XmlUnexpectedCharacterException &uce)
    {
        std::cout << "XmlUnexpectedCharacterException: " << uce.Message() << ", " << std::endl
                  << "Found character: " << uce.Found() << std::endl
                  << "Expected character: " << uce.Expected();
    } catch (System::Xml::XmlException &e)
    {
        std::cout << "XmlException: " << e.Message() << std::endl;
    }

    //    WSADATA wsaData;

    //    if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
    //    {
    //        std::string  host = argv[1],
    //                path = "/srvs/iq.exe",
    //                data = "";
    //        try
    //        {
    //            std::string res = HTTP_POST(host, 80, path, data);
    //            ReplaceAll(res, "\r\n", "\n");
    //            std::string headers = res.substr(0, res.find("\n\n"));
    //            std::string response = res.substr(res.find("\n\n") + 2);
    //            std::cout << "###################################################" << std::endl;
    //            std::cout << "headers: " << std::endl;
    //            std::cout << headers << std::endl;
    //            std::cout << "###################################################" << std::endl;
    //            std::cout << "response: " << std::endl;
    //            std::cout << response << std::endl;

    //            System::Xml::XmlDocument doc;
    //            doc.LoadXml(std::string("<!DOCTYPE html><?xml version=\"1.0\"?><!-- test comment -->") + response);
    //        }
    //        catch (const System::Xml::XmlException& ex)
    //        {
    //            std::cout << "XmlException : " << ex.Message() << std::endl;
    //        }
    //        catch (const std::string& err)
    //        {
    //            std::cout << err << std::endl;
    //        }
    //        WSACleanup();
    //    }
    //    else
    //    {
    //        std::cout << "WSAStartup() failed" << std::endl;
    //    }

    return 0;
}

std::string HTTP_POST(std::string host, int port, std::string path, std::string data)
{
    std::string request;
    std::string response;
    int resp_leng;

    char buffer[BUFFERSIZE + 1];
    struct sockaddr_in serveraddr;
    int sock;

    std::stringstream request2;

    request2 << "GET http://" << host << path << " HTTP/1.1" << std::endl;
    request2 << "Content-Type: application/AOB-XML" << std::endl;
    request2 << "Host: " << host << std::endl;
    request2 << "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8" << std::endl;
    request2 << "Connection: Keep-Alive" << std::endl;

    request2 << std::endl;
    request2 << data;
    request = request2.str();
    std::cout << request << std::endl
              << std::endl;

    struct hostent *h = gethostbyname(host.c_str());
    if (h == NULL)
        throw "Failed to resolve hostname.";

    //open socket
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        throw "socket() failed";

    //connect
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = *((unsigned long *)h->h_addr);
    serveraddr.sin_port = htons((unsigned short)port);
    if (connect(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
        throw "connect() failed";

    //send request
    if (send(sock, request.c_str(), request.length(), 0) != request.length())
        throw "send() sent a different number of bytes than expected";

    std::ofstream out("test.txt");
    //get response
    response = "";
    resp_leng = BUFFERSIZE;
    while (resp_leng == BUFFERSIZE)
    {
        resp_leng = recv(sock, (char *)&buffer, BUFFERSIZE, 0);
        if (resp_leng > 0)
        {
            buffer[resp_leng] = 0;
            out << buffer;
            response += std::string(buffer);
        }
        //note: download lag is not handled in this code
    }

    //disconnect
    closesocket(sock);

    //cleanup
    WSACleanup();

    return response;
}

void ReplaceAll(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}
