#include "ResponseGenerator.hpp"
#include "Request.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Response *GetResponseGenerator::generateResponse(Request *request)
{
    Response *response = new Response();
    long fileSize;
    ifstream fileToRead (request->getPath().c_str());
    if(fileToRead.is_open())
    {
        /* Get file data */
        fileSize = fileToRead.tellg();
        fileToRead.seekg(0, ios::beg);
        response->setBody(new char[fileSize]);
        fileToRead.read(response->getBody(), fileSize);
        fileToRead.close();

        cout << "Response File Size: " << sizeof(response->getBody());

        /* Sent response header lines */
        response->setStatus(OK);
        time_t currentTime = time(0);
        stringstream timeStream;
        timeStream << ctime(&currentTime);
        response->addToHeaderLine("Connection: Closed" + REQ_DELIMITER);
        response->addToHeaderLine("Date: " + timeStream.str());
        response->addToHeaderLine("Server: Customized" + REQ_DELIMITER);
        response->addToHeaderLine("Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT" + REQ_DELIMITER);
        ostringstream convertIntToString;
        convertIntToString << sizeof(response->getBody());
        response->addToHeaderLine("Content-Length: " + convertIntToString.str() + REQ_DELIMITER);
        response->addToHeaderLine("Content-Type: text/html" + REQ_DELIMITER);
        response->addToHeaderLine(REQ_DELIMITER);
        return response;
    }

    response->setStatus(INTERNALERROR);
    return response;
}

Response *PostResponseGenerator::generateResponse(Request *request)
{
    Response *response = new Response();

    if(!request->getBody().empty())
    {
        ofstream fileToWrite (request->getPath().c_str(), ios::out | ios::trunc);
        if(fileToWrite.is_open())
        {
            fileToWrite << request->getBody().c_str();
            fileToWrite.close();
            response->setStatus(OK);
            return response;
        }
    }

    response->setStatus(INTERNALERROR);
    return response;
}

Response *HeadResponseGenerator::generateResponse(Request *request)
{
    return new Response();
}

Response *DefaultResponseGenerator::generateResponse(Request *request)
{
    Response *response = new Response();
    response->setStatus(NOTIMPLEMENTED);
    return response;
}

ResponseGenerator *getResponseGenerator(REQUESTTYPE generator)
{
    switch(generator)
    {
        case GET:
            return new GetResponseGenerator();
            break;
        case POST:
            return new PostResponseGenerator();
            break;
        case HEAD:
            return new HeadResponseGenerator();
            break;
        default:
            return new DefaultResponseGenerator();
            break;
    }
}
