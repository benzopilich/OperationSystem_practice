#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

struct ThreadData {
    vector<string> strArray;
};

bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    cout << endl<<"Thread starts"<<endl;
    cout << "Ответ:" << endl;
    for (const auto& str : data->strArray) 
    {
        if (!isNumber(str)) {
            cout << str << "\n";
        }
        Sleep(10);
    }
    cout << "Thread ends" << endl;
    return 0;
}

int main() {
    setlocale(LC_ALL, "ru");
    int size;
    cout << "Введите размер массива: ";
    cin >> size;

    ThreadData data;
    data.strArray.resize(size);

    cout << "Введите элементы массива:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> data.strArray[i];
    }
    DWORD	IDThread;
    HANDLE hThread = CreateThread(NULL,0,ThreadFunction,&data,0, &IDThread);

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    return 0;
}