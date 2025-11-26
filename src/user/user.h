#include <string>
#include <cstdlib>
#include <chrono>
#include <format>
#include <iostream>
#include <curl/curl.h>
#include "../bycrypt/src/bcrypt.h"

char* supabaseUrl = std::getenv("SUPABASE_URL");
char* supabaseApikey = std::getenv("SUPABASE_APIKEY");

void validatePath(){
    if (supabaseUrl == nullptr || supabaseApikey == nullptr){
        std::cerr<<"An error occured in opening path to env"<<std::endl<<std::flush;
    }
}


#pragma once

class User {
    public:
        std::string username;
        std::string created_at;

        User() = default;

        User(std::string un,std::string pass) : username(un),password(pass){
            password = bcrypt::generateHash(password);
            auto now = std::chrono::system_clock::now();
            std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

            created_at = std::ctime(&timeNow);
        }

        void createNewUser(){
            validatePath();
            
            std::string jsonData = "{ \"username\": \"" + username +
                       "\", \"password\": \"" + password +
                       "\", \"created_at\": \"" + created_at + "\" }";
            std::string key = std::string("apikey: ") + supabaseApikey;
            std::string authorization = std::string("Authorization: Bearer ") + supabaseApikey;
            // std::string api-
            CURL* curl = curl_easy_init();
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, key.c_str());
            headers = curl_slist_append(headers, authorization.c_str());
            headers = curl_slist_append(headers, "Content-Type: application/json");
            headers = curl_slist_append(headers, "Prefer: return=minimal");

            curl_easy_setopt(curl, CURLOPT_URL, supabaseUrl);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

            CURLcode res = curl_easy_perform(curl);
            if(res != CURLE_OK){
                std::cerr << "curl_easy_perform() failed: "<< curl_easy_strerror(res) << "\n";
            }

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        
    private:
        std::string password;
};