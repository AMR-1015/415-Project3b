#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readWords(string fileName);

int main(){
    string fileName;

    cout << "Enter name of the file: ";
    cin >> fileName;

    vector<string> words = readWords(fileName);
    for(auto ele: words){
        cout << ele << endl;
    }
    
    return 0;
}

vector<string> readWords(string fileName){
    ifstream inputFile;
    inputFile.open(fileName);
    string word;
    vector<string> words;

   if(inputFile.is_open()){
        while(inputFile){
            getline(inputFile, word);
            int lastCharacter = word.size()-1;
            if(!isalpha(word.at(lastCharacter))){
                word.pop_back();
            }
            words.push_back(word);
            if(inputFile.eof()) break;
        }
   }else{ cout << "Unable to open file." << endl;}

   return words;
    
}