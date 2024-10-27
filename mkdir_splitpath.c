

#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    printf("TO BE IMPLEMENTED\n");

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
    char* tokenDirString;
    strcpy(tokenDirString, dirName);
    
    // string that stores tokens of pathName, grab first token
    char* tokenized = strtok(pathName, "/");

    // iterating through pathName
    while (tokenized) {
        // indicator of if a name match is found
        int found = 0;

        // loop through siblings
        while (currentNode->childPtr) {
            if (strcmp(currentNode->childPtr->name, tokenized) == 0) {
                currentNode = currentNode->childPtr;
                found = 1;
                break;
        }

        // if not found, throw an error and return a null pointer
        if (!found) {
            printf("ERROR: directory %s does not exist", tokenized);
            return NULL;
        }

        // token grabber
        tokenized = strtok(NULL, "/");
    }

    // return the last checked node
    return currentNode;
}
