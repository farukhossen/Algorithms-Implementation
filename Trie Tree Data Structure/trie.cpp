#include <cstdio>
#include <cstdlib>
#include <vector>

#define ALPHABETS 52
#define MAX_WORD_SIZE 25

using namespace std;

struct Node
{
    struct Node * parent;
    struct Node * children[ALPHABETS];
    vector<int> occurrences;
};

int getIndex(char c){

    if(c >= 'A' && c < 'a' ) return c - 'A';
    else return c - 'a' + 26;

}

void InsertWord(struct Node * trieTree, char * word, int index)
{
    struct Node * traverse = trieTree;

    while (*word != '\0') {
        if (traverse->children[getIndex(*word)] == NULL) {
            traverse->children[getIndex(*word)] = (struct Node *) calloc(1, sizeof(struct Node));
            traverse->children[getIndex(*word)]->parent = traverse;  // Assigning parent
        }

        traverse = traverse->children[getIndex(*word)];
        ++word; // The next alphabet
    }

    traverse->occurrences.push_back(index);
}

struct Node * SearchWord(struct Node * treeNode, char * word)
{
    while (*word != '\0') {
        if (treeNode->children[getIndex(*word)] != NULL) {
            treeNode = treeNode->children[getIndex(*word)];
            ++word;
        } else {
            break;
        }
    }

    if (*word == '\0' && treeNode->occurrences.size() != 0) {
        // Word found
        return treeNode;
    } else {
        // Word not found
        return NULL;
    }
}

void RemoveWord(struct Node * trieTree, char * word)
{
    struct Node * trieNode = SearchWord(trieTree, word);

    if (trieNode == NULL) {
        return;
    }

    trieNode->occurrences.pop_back();
    bool noChild = true;
    int childCount = 0;
    int i;

    for (i = 0; i < ALPHABETS; ++i) {
        if (trieNode->children[i] != NULL) {
            noChild = false;
            ++childCount;
        }
    }

    if (!noChild) {
        return;
    }

    struct Node * parentNode;

    while (trieNode->occurrences.size() == 0 && trieNode->parent != NULL && childCount == 0) {

        childCount = 0;
        parentNode = trieNode->parent;

        for (i = 0; i < ALPHABETS; ++i) {
            if (parentNode->children[i] != NULL) {
                if (trieNode == parentNode->children[i]) {
                    parentNode->children[i] = NULL;
                    free(trieNode);
                    trieNode = parentNode;
                } else {
                    ++childCount;
                }
            }
        }
    }
}

void LexicographicalPrint(struct Node * trieTree, vector<char> word)
{
    int i;
    bool noChild = true;

    if (trieTree->occurrences.size() != 0) {

        vector<char>::iterator charItr = word.begin();

        while (charItr != word.end()) {
            printf("%c", *charItr);
            ++charItr;
        }
        printf(" -> @ index -> ");

        vector<int>::iterator counter = trieTree->occurrences.begin();

        while (counter != trieTree->occurrences.end()) {
            printf("%d, ", *counter);
            ++counter;
        }

        printf("\n");
    }

    for (i = 0; i < ALPHABETS; ++i) {
        if (trieTree->children[i] != NULL) {
            noChild = false;

            word.push_back(i <=25 ? 'A' + i : 'a' + i - 26);

            LexicographicalPrint(trieTree->children[i], word);
            word.pop_back();

        }
    }

    word.pop_back();
}

int main()
{
    int n, i;
    vector<char> printUtil;

    struct Node * trieTree = (struct Node *) calloc(1, sizeof(struct Node));
    char word[MAX_WORD_SIZE];

    printf("Enter the number of words-\n");
    scanf("%d", &n);

    for (i = 1; i <= n; ++i) {
        scanf("%s", word);
        InsertWord(trieTree, word, i);
    }

    printf("\n");
    LexicographicalPrint(trieTree, printUtil);

    printf("\nEnter the Word to be removed - ");
    scanf("%s", word);
    RemoveWord(trieTree, word);

    printf("\n");
    LexicographicalPrint(trieTree, printUtil);

    return 0;
}
