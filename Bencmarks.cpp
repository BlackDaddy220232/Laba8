#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <random>
#include <vector>
#include"hash.h"
#include <time.h>
using namespace std;
// Функция для генерации случайных строк заданной длины
char* Generaterandomstring(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    static uniform_int_distribution<int> distribution(0, sizeof(alphanum) - 1);

    char* str = new char[length+1];
    for (int i = 0; i < length; ++i) {
        str[i] = alphanum[distribution(rng)];
    }
    str[length] = '\0';

    return str;
}

// Функция для заполнения unordered_map рандомными логинами и паролями
void FillUnorderedMap(unordered_map<char*, char*, std::hash<char*>, std::equal_to<char*>>& login_password_map, const vector<pair<char*, char*>>& data) {
    for (const auto& entry : data) {
        login_password_map[entry.first] = entry.second;
    }
}

void benchmark() {
    unordered_map<char*,char*> login_password_map;
    int num_entries = 1000;
    vector<pair<char*,char*>> data;
    data.reserve(num_entries);
    for (int i = 0; i < num_entries; ++i) {
        char* login = Generaterandomstring(8); // Генерация случайного логина
        char* password = Generaterandomstring(12); // Генерация случайного пароля
        data.emplace_back(login,password);
    }
    Hash *mas=(Hash*)malloc(300000*sizeof(Hash));
    auto start=clock();
    for (const auto& entry:data)
    {
        HandleCreate(mas,entry.first,entry.second);
    }
    auto end=clock();
    long int MyCreate=end-start;
    auto start=clock();
    FillUnorderedMap(login_password_map, data);
    auto end=clock();
    long int NotMyCreate=end-start;
    auto start=clock();
    for (const auto& entry: data)
    {
        Delete(mas,entry.first);
    }
    auto end=clock();
    long int MyDelete=end-start;
    auto start=clock();
    for(const auto& entry: data)
    {
        Search(mas,entry.first);
    }
    auto end=clock();
    long int MySearch=end-start;
    auto start=clock();
    for (auto& entry : login_password_map) {
        delete[] entry.first;
        delete[] entry.second;
    }
    auto end=clock();
    long int NotMyDelete=end-start;
    auto start=clock();
    for (const auto& entry: data)
    {
        char* result=login_password_map[entry.first];
    }
    auto end=clock();
    long int NotMySearch=end-start;
    printf("Write\nMy table\nTime:%ld\nNot my table\nTime:%ld\nK=%lf\n",MyCreate,NotMyCreate,1.0*MyCreate/NotMyCreate);
    printf("Read\nMy table\nTime:%ld\nNot my table\nTime:%ld\nK=%lf\n",MySearch,NotMySearch,1.0*MySearch/NotMySearch);
    printf("Delete\nMy table\nTime:%ld\nNot my table\nTime:%ld\nK=%lf\n",MyDelete,NotMyDelete,1.0*MyDelete/NotMyDelete);
}
