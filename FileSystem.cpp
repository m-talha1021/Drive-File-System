#include "FileSystem.h"
using namespace std;

FileSystem::Node::Node(const string& n, bool f, Node* p)
    : name(n), isFolder(f), parent(p), content(""), lastModified(time(nullptr)) {}

FileSystem::FileSystem() {
    root = new Node("root", true, nullptr);
    current = root;
}

void FileSystem::create(const string& name, bool isFolder) {
    if (current->children.count(name)) {
        cout << "Item already exists.\n";
        return;
    }
    Node* newNode = new Node(name, isFolder, current);
    current->children[name] = newNode;
    updateRecent(newNode);
    cout << (isFolder ? "Folder" : "File") << " created.\n";
}

void FileSystem::deleteItem(const string& name) {
    if (!current->children.count(name)) {
        cout << "Item not found.\n";
        return;
    }
    deletedFiles.push_back(current->children[name]);
    current->children.erase(name);
    cout << "Item deleted.\n";
}

void FileSystem::changeDirectory(const string& name) {
    if (name == "..") {
        if (current->parent)
            current = current->parent;
    } else if (current->children.count(name) && current->children[name]->isFolder) {
        current = current->children[name];
    } else {
        cout << "Directory not found.\n";
    }
}

void FileSystem::listDirectory() {
    for (auto& [name, node] : current->children)
        cout << (node->isFolder ? "[Folder] " : "[File] ") << name << "\n";
}

void FileSystem::restoreDeleted() {
    if (deletedFiles.empty()) {
        cout << "No files to restore.\n";
        return;
    }
    Node* file = deletedFiles.back();
    deletedFiles.pop_back();
    current->children[file->name] = file;
    cout << "File restored.\n";
}

void FileSystem::showRecent() {
    for (auto node : recentFiles)
        cout << node->name << " (Last Modified: " << ctime(&node->lastModified) << ")";
}

void FileSystem::writeFile(const string& name, const string& content) {
    if (!current->children.count(name) || current->children[name]->isFolder) {
        cout << "File not found.\n";
        return;
    }
    Node* file = current->children[name];
    file->content = content;
    file->lastModified = time(nullptr);
    updateRecent(file);
    cout << "Content written.\n";
}

void FileSystem::readFile(const string& name) {
    if (!current->children.count(name) || current->children[name]->isFolder) {
        cout << "File not found.\n";
        return;
    }
    cout << "Content: " << current->children[name]->content << "\n";
}

void FileSystem::updateRecent(Node* node) {
    recentFiles.push_back(node);
    if (recentFiles.size() > 5)
        recentFiles.erase(recentFiles.begin());
}
