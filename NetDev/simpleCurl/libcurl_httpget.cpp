#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>


static size_t WriteCallback(void* in_data, size_t size, size_t nmemb, void* out_data) {
    size_t realsize = size * nmemb;
    ((std::string*)out_data)->append((char*)in_data, realsize);
    return realsize;
}


int main(int argc, char* argv[]) {
    CURL* curl;
    CURLcode rc;
    std::string recvBuffer;
    char errbuf[CURL_ERROR_SIZE];
    memset(errbuf, 0, CURL_ERROR_SIZE);

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << "<url> [Option: <parameter>] [Option: -H]" << std::endl;
        std::cout << "Example: " << std::endl;
        std::cout << argv[0] << " http:192.168.0.107:1234/mEchoWS" << std::endl;
        std::cout << argv[0] << " http:192.168.0.107:1234/mEchoWS \"Name=Allan&Gender=Male\"" << std::endl;
        std::cout << argv[0] << " http:192.168.0.107:1234/mEchoWS \"Name=Allan&Gender=Male\" -H" << std::endl;
        return EXIT_FAILURE;
    }

    std::string url_string = argv[1];
    if (argc >= 3) {
        url_string += "?";
        url_string += std::string(argv[2]);
        std::cout << "Parameters: " << argv[2] << std::endl;
    }

    std::cout << "url: " << url_string << std::endl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url_string.c_str());
        curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &recvBuffer);

        struct curl_slist* headers = NULL;
        if (argc == 4) {
            headers = curl_slist_append(headers, "Content-Type: application/xml");
            headers = curl_slist_append(headers, "Content-Length: 256");
        }
        rc = curl_easy_perform(curl);
        if (rc != CURLE_OK)
            std::cout << "curl_easy_perform failed HTTP GET request " << rc << std::endl;

        std::cout << recvBuffer << std::endl;
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();
    return EXIT_SUCCESS;
}
