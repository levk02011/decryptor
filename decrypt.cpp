#include <iostream>
#include <fstream>
#include <json/json.h>

void decryptFile(const std::string& encryptedFile, const std::string& explanationFile, const std::string& outputFile) {
    std::ifstream encFile(encryptedFile);
    std::ifstream explFile(explanationFile);
    std::ofstream outFile(outputFile);

    if (!encFile.is_open()  !explFile.is_open()  !outFile.is_open()) {
        std::cerr << "Помилка при відкритті файлів!" << std::endl;
        return;
    }

    Json::Value jsonRoot;
    explFile >> jsonRoot;

    std::unordered_map<char, char> reverseCharMap;
    for (const auto& key : jsonRoot.getMemberNames()) {
        reverseCharMap[jsonRoot[key].asCString()[0]] = key[0];
    }

    char ch;
    while (encFile.get(ch)) {
        outFile.put(reverseCharMap[ch]);
    }

    encFile.close();
    explFile.close();
    outFile.close();
}

int main() {
    decryptFile("C:\\output.txt", "C:\\Windows\\system32\\Werhoun.json", "decrypted.txt");
    std::cout << "Дешифрування завершено!" << std::endl;
    return 0;
}
