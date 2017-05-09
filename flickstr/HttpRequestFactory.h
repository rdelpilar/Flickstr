#ifndef HTTPREQUESTFACTORY_H
#define HTTPREQUESTFACTORY_H

#include <memory>
#include "SearchParameters.h"
#include "HttpRequest.h"

class HttpRequestFactory
{
public:
    HttpRequestFactory(HttpRequestFactory&&) = delete;
    HttpRequestFactory(const HttpRequestFactory&) = delete;
    HttpRequestFactory& operator=(const HttpRequestFactory&) = delete;
    HttpRequestFactory& operator=(const HttpRequestFactory&&) = delete;
    ~HttpRequestFactory() = default;

    static HttpRequestFactory& getInstance() {
        static HttpRequestFactory mInstance;
        return mInstance;
    }

    std::shared_ptr<HttpRequest> createRequest() {
        return std::make_shared<HttpRequest>(mAccessManager);
    }

private:
    HttpRequestFactory()
        : mAccessManager(std::shared_ptr<QNetworkAccessManager>(new QNetworkAccessManager)){}

private:
    std::shared_ptr<QNetworkAccessManager> mAccessManager;
};

#endif
