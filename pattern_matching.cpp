#include <string>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class TrieNode {
   public:
    char data;
    TrieNode **children;

    TrieNode(char data) {
        this->data = data;
        children = new TrieNode *[26];
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
    }
};

class Trie {
    private:
        TrieNode *root; //root of the trie
    public:
        Trie(){
            root=new TrieNode('\0');
        }
    private:
        void insert_helper(TrieNode *root,string word){
            if(word==""){
                return;
            }
            int index=word[0]-'a';
            TrieNode *child;
            if(root->children[index]!=NULL){
                child=root->children[index];
                //taaki recursive call kar skee
            }
            else{
                child=new TrieNode(word[0]);
                root->children[index]=child;//children ka index point on child
            }
            insert_helper(child,word.substr(1));
        }
    public:
        void insertWord(string word){
            insert_helper(this->root,word);
        }
    private:
        bool search_helper(TrieNode *root,string word){
            if(word==""){
                return true;
            }
            int index=word[0]-'a';
            if(root->children[index]!=NULL){
                return search_helper(root->children[index],word.substr(1));
            }
            else{
                return false;//agar pehla char hi not found toh aage not check
            }
        }
    public:
        bool search(string word){
            return search_helper(this->root,word);
        }
    bool patternMatching(vector<string> vect, string pattern) {
        for(int i=0;i<vect.size();i++){
            for(int j=0;j<vect[i].size();j++){
                insertWord(vect[i].substr(j));
            }
        }
        if(search(pattern)==true){
            return true;
        }
        else{
            return false;
        }
    }
};