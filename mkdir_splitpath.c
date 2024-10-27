

#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    // no input to mkdir or path provided is root, throw error
    if (strcmp(pathName, "") == 0 || pathName == NULL) {
        printf("MKDIR ERROR: no path provided");
        return;
    }

    // initialize strings to hold baseName and dirName
    char* baseName = (char *)malloc(sizeof(char)*100);
    char* dirName = (char *)malloc(sizeof(char)*100);

    // call splitPath, storing return node in a node pointer
    struct NODE* parentDir = splitPath(pathName, baseName, dirName);

    // only call if parentDir exists
    if (parentDir) {

        // declare a node to iterate through children / siblings
        struct NODE* child = parentDir->childPtr;

        // loop through children via sibling pointers, check if directory already exists
        while (child) {
            if (strcmp(child->name, baseName) == 0 && child->fileType == 'D') {
                printf("MKDIR ERROR: directory %s already exists", baseName);
                return;
            }
            child = child->siblingPtr;
        }

        // create a new node, allocate memory
        struct NODE* mkdirNew = (struct NODE*) malloc(sizeof(struct NODE));

        // initialize new node's values
        strcpy(mkdirNew->name, baseName);
        mkdirNew->childPtr = NULL;
        mkdirNew->siblingPtr = NULL;
        mkdirNew->parentPtr = parentDir;
        mkdirNew->fileType = 'D';

        // link to either last existing sibling or parent if first child
        if (parentDir->childPtr == NULL) {
            parentDir->childPtr = mkdirNew;
        } else {
            struct NODE* lastSibling = parentDir->childPtr;
            while (lastSibling->siblingPtr) {
                lastSibling = lastSibling->siblingPtr;
            }
            lastSibling->siblingPtr = mkdirNew;
        }

        printf("MKDIR SUCCESS: node %s successfully created\n", pathName);

    }

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    //

    // edge case, pathName = "/"
    if (strcmp(pathName, "/") == 0) {
        strcpy(dirName, "/");
        strcpy(baseName, "");
        return root;
    }

    // grab where the last slash is in pathName
    char* lastSlash = strrchr(pathName, '/');

    // splits pathName into dirName and baseName, only if the string contains '/'
    if (lastSlash) {
        strncpy(dirName, pathName, lastSlash - pathName);
        dirName[lastSlash - pathName] = '\0';
        strcpy(baseName, lastSlash + 1);
    } else {
        strcpy(dirName, "");
        strcpy(baseName, pathName);
        return cwd;
    }

    // create a node pointer starting at current directory node, used to track directory existence
    struct NODE* currentNode = cwd;

    // create a copy of dirName that can be ran through strtok
    char* tokenDirString = (char*) malloc(strlen(dirName) + 1);
    strcpy(tokenDirString, dirName);
    
    // string that stores tokens of pathName, grab first token
    char* tokenized = strtok(tokenDirString, "/");

    // iterating through pathName
    while (tokenized) {
        // indicator of if a name match is found
        int found = 0;

        // declare node to keep track of children and iterate through siblings
        struct NODE* child = currentNode->childPtr;

        // loop through siblings
        while (child) {
            if (strcmp(child->name, tokenized) == 0) {
                currentNode = child;
                found = 1;
                break;
            }
            child = child->siblingPtr;
        }

        // if not found, throw an error and return a null pointer
        if (!found) {
            printf("ERROR: directory %s does not exist\n", dirName);
            return NULL;
        }

        // token grabber
        tokenized = strtok(NULL, "/");
    }

    free(tokenDirString);

    // return the last checked node
    return currentNode;
}
