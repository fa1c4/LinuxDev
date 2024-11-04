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

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << "<url> <Post Contents>" << std::endl;
        std::cout << "Example: " << std::endl;
        std::cout << argv[0] << " http:192.168.0.107:1234/mEchoWS \"{ Name : Susan Collin, Gender : Famale }\" " << std::endl;
        return EXIT_FAILURE;
    }

    std::string url_string = argv[1];
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url_string.c_str());
        curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &recvBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, argv[2]);

        rc = curl_easy_perform(curl);
        if (rc != CURLE_OK)
            std::cout << "curl_easy_perform failed HTTP POST request " << rc << std::endl;

        std::cout << recvBuffer << std::endl;
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return EXIT_SUCCESS;
}
