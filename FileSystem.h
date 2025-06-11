#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

class FileSystem {
public:
    FileSystem();
    void create(const std::string &name, bool isFolder);
    void deleteItem(const std::string &name);
    void changeDirectory(const std::string &name);
    void listDirectory();
    void restoreDeleted();
    void showRecent();
    void writeFile(const std::string &name, const std::string &content);
    void readFile(const std::string &name);

private:
    struct Node {
        std::string name;
        bool isFolder;
        std::string content;
        time_t lastModified;
        Node* parent;
        std::map<std::string, Node*> children;

        Node(const std::string& n, bool f, Node* p);
    };

    Node* root;
    Node* current;
    std::vector<Node*> deletedFiles;
    std::vector<Node*> recentFiles;

    void updateRecent(Node* node);
};

#endif
