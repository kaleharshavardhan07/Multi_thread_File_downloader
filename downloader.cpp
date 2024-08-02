#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <curl/curl.h>
#include <cstdlib>

using namespace std;

size_t WriteCallback(void* ptr, size_t size, size_t nmemb, std::ofstream* stream) {
    stream->write(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

void downloadPart(const std::string& url, long start, long end, const std::string& output) {
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        std::ostringstream range;
        range << start << "-" << end;

        std::ofstream outFile(output, std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << output << std::endl;
            curl_easy_cleanup(curl);
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);
        curl_easy_setopt(curl, CURLOPT_RANGE, range.str().c_str());

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        outFile.close();
    } else {
        std::cerr << "Error: Could not initialize CURL" << std::endl;
    }
}

void mergeParts(const std::vector<std::string>& parts, const std::string& output) {
    std::ofstream outFile(output, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << output << std::endl;
        return;
    }

    for (const auto& part : parts) {
        std::ifstream inFile(part, std::ios::binary);
        if (!inFile.is_open()) {
            std::cerr << "Error: Could not open file " << part << std::endl;
            continue;
        }
        outFile << inFile.rdbuf();
        inFile.close();
        std::remove(part.c_str());
    }
    outFile.close();
}

int main() {
    std::string url;
    std::cout << "ENTER THE LINK ADDRESS: ";
    std::getline(std::cin, url); 
    std::string outputFileName = "largefile.zip";
    long fileSize;
    std::cout << "ENTER THE SIZE OF ZIP FILE IN BYTES: ";
    std::cin >> fileSize;  // Replace with the actual file size in bytes
    int numThreads = 4;

    std::vector<thread> threads;
    std::vector<std::string> partFiles;

    long partSize = fileSize / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        long start = i * partSize;
        long end = (i == numThreads - 1) ? fileSize - 1 : (start + partSize - 1);
        std::string partFileName = "part" + std::to_string(i);
        partFiles.push_back(partFileName);

        threads.emplace_back(downloadPart, url, start, end, partFileName);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    mergeParts(partFiles, outputFileName);

    std::cout << "Download completed: " << outputFileName << std::endl;

    return 0;
}
