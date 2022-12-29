#include <iostream>
#include <string>
using namespace std;
#include <vector>

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
        bool isLeaf(TrieNode *node){
            for(int i=0;i<26;i++){
                if(node->children[i]!=NULL){
                    return false;
                }
            }
            return true;
        }
        void helper(TrieNode *node,vector<string> &answer,string current_string){
            //base case
            if(isLeaf(node)==true){
                if(node->isTerminal==true){
                    answer.push_back(current_string);
                }
                return;
            }
            //small calculation
            if(node->isTerminal==true){
                answer.push_back(current_string);
            }
            //recursive call on node ke saare children
            for(int i=0;i<26;i++){
                if(node->children[i]!=NULL){
                    helper(node->children[i],answer,current_string+node->children[i]->data);
                }
            }
            return;
        }
    public:
        void autoComplete(vector<string> input, string pattern){
            for(int i=0;i<input.size();i++){
                insertWord(input[i]);
            }
            int i=0;
            int index=pattern[i]-'a';
            TrieNode *node=root->children[index];
            while (node != NULL and i != pattern.size()-1){
                if (node == NULL){
                    return;
                }
                index = pattern[++i] - 'a';
                node = node->children[index];
            }
            //reached woh last letter of pattern node whi
            vector<string> answer;
            for(int i=0;i<26;i++){
                if(node->children[i]!=NULL){
                    helper(node,answer,pattern);
                }
            }
            for(int i=0;i<answer.size();i++){
                cout<<answer[i]<<endl;
            }
        }
};
int main(){
    Trie t;
    vector<string> v;
    v.push_back("do");
    v.push_back("dont");
    v.push_back("no");
    v.push_back("note");
    v.push_back("notes");
    v.push_back("den");
    v.push_back("not");
    t.autoComplete(v,"no");
}