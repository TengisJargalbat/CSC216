#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <queue>
#include <vector>

class Node {
public:
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};
class Compare {
public:
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};
Node* HuffmanTree(std::unordered_map<char, int> wordFreq){
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto& [c, f] : wordFreq) {
        pq.push(new Node(c, f));
    }
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}
void encodeTree(Node* node, const std::string& prefix, std::unordered_map<char, std::string>& codes) {
    if (node == nullptr) {
        return;
    }
    if (!node->left && !node->right) {
        codes[node->ch] = prefix;
    }
    encodeTree(node->left, prefix + "0", codes);
    encodeTree(node->right, prefix + "1", codes);

}
std::tuple <
    std::unordered_map<char, int>,
    std::unordered_map<char, std::string>,
    std::string > 
    compress(std::string text){
    std::unordered_map<char, int> wordFreq;
    for (char ch : text) {
        wordFreq[ch]++;
    }
    Node* root = HuffmanTree(wordFreq);
    std::unordered_map<char, std::string> codes;
    encodeTree(root, "", codes);
    std::string result;
    for (char ch : text) {
        result += codes[ch];
    }
    return {wordFreq, codes, result};
}
std::string decompress(const std::string& encoded, const std::unordered_map<char, std::string>& codes) {
    std::unordered_map<std::string, char> rev;
    for (auto& p : codes) {
        rev[p.second] = p.first;
    }
    std::string result;
    std::string temp;
    for (char ch : encoded) {
        temp += ch;
        auto it = rev.find(temp);
        if (it != rev.end()) {
            result += rev[temp];
            temp = "";
        }
    }
    return result;
}
int main()
{
    auto [freq, codes, encoded] = compress("Hello World");

    std::cout << "Encoded bits:\n" << encoded << "\n\n";
    std::cout << "Decoded text:\n" << decompress(encoded, codes) << "\n";
    return 0;
}
