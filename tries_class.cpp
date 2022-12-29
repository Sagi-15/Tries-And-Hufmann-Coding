#include <iostream>
#include <string>
using namespace std;

class TrieNode{
    public:
        char data;
        TrieNode **children;
        bool isTerminal;

        /******Constructor******/
        TrieNode(char data){
            this->data=data;
            this->children=new TrieNode*[26];
            for(int i=0;i<26;i++){
                this->children[i]=NULL;
            }
            this->isTerminal=false;
        }
};

class Trie{
    private:
        TrieNode *root; //root of the trie
    public:
        Trie(){
            root=new TrieNode('\0');
        }
    private:
        void insert_helper(TrieNode *root,string word){
            if(word==""){
                root->isTerminal=true;
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
                if(root->isTerminal==true){
                    return true;
                }
                else{
                    return false;
                }
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
    private:
        void removeWord(TrieNode *root,string word){
            if(word==""){
                root->isTerminal=false;
                return;
            }
            TrieNode *child;
            int index=word[0]-'a';
            if(root->children[index]!=NULL){
                child=root->children[index];
            }
            else{
                return;
            }
            removeWord(child,word.substr(1));
            if(child->isTerminal==false){
                for(int i=0;i<26;i++){
                    if(child->children[i]!=NULL){
                        return;
                    }
                }
                delete child;
                root->children[index]=NULL;
            }
        }
    public:
        void removeWord(string word){
            removeWord(this->root,word);
        }
};
int main(){
    Trie t;
    t.insertWord("are");
    t.insertWord("bed");
    t.insertWord("bend");
    t.insertWord("do");
    t.insertWord("no");
    t.insertWord("note");
    t.insertWord("this");
    t.removeWord("note");
    cout<<t.search("note")<<endl;
}