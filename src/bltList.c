
/*
 * bltList.c --
 *
 * The module implements generic linked lists for the BLT toolkit.
 *
 *	Copyright 1991-2004 George A Howlett.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining
 *	a copy of this software and associated documentation files (the
 *	"Software"), to deal in the Software without restriction, including
 *	without limitation the rights to use, copy, modify, merge, publish,
 *	distribute, sublicense, and/or sell copies of the Software, and to
 *	permit persons to whom the Software is furnished to do so, subject to
 *	the following conditions:
 *
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "bltInt.h"
#include <bltHash.h>
#include "bltList.h"

typedef struct _Blt_ListNode Node;
typedef struct _Blt_List List;

static Node *
FindString(List *listPtr, const char *key)	
{
    Node *np;
    char c;

    c = key[0];
    for (np = listPtr->head; np != NULL; np = np->next) {
	if ((c == np->key.string[0]) && (strcmp(key, np->key.string) == 0)) {
	    return np;
	}
    }
    return NULL;
}

static Blt_ListNode
FindOneWord(List *listPtr, const char *key)
{
    Node *np;

    for (np = listPtr->head; np != NULL; np = np->next) {
	if (key == np->key.oneWordValue) {
	    return np;
	}
    }
    return NULL;
}

static Blt_ListNode
FindArray(List *listPtr, const char *key)
{
    Node *np;
    size_t nBytes;

    nBytes = sizeof(uint32_t) * listPtr->type;
    for (np = listPtr->head; np != NULL; np = np->next) {
	if (memcmp(key, np->key.words, nBytes) == 0) {
	    return np;
	}
    }
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * FreeNode --
 *
 *	Free the memory allocated for the node.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
static void
FreeNode(Blt_ListNode node)
{
    Blt_Free(node);
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_Create --
 *
 *	Creates a new linked list structure and initializes its pointers
 *
 * Results:
 *	Returns a pointer to the newly created list structure.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
Blt_List 
Blt_List_Create(size_t type)
{
    List *listPtr;

    listPtr = Blt_Malloc(sizeof(List));
    if (listPtr != NULL) {
	Blt_List_Init(listPtr, type);
    }
    return listPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_CreateNode --
 *
 *	Creates a list node holder.  This routine does not insert the node
 *	into the list, nor does it no attempt to maintain consistency of the
 *	keys.  For example, more than one node may use the same key.
 *
 * Results:
 *	The return value is the pointer to the newly created node.
 *
 * Side Effects:
 *	The key is not copied, only the Uid is kept.  It is assumed this key
 *	will not change in the life of the node.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
Blt_ListNode
Blt_List_CreateNode(List *listPtr, const char *key)
{
    Node *np;
    size_t keySize;

    if (listPtr->type == BLT_STRING_KEYS) {
	keySize = strlen(key) + 1;
    } else if (listPtr->type == BLT_ONE_WORD_KEYS) {
	keySize = sizeof(void *);
    } else {
	keySize = sizeof(uint32_t) * listPtr->type;
    }
    np = Blt_AssertCalloc(1, sizeof(Node) + keySize - 4);
    np->clientData = NULL;
    np->next = np->prev = NULL;
    np->list = listPtr;
    switch (listPtr->type) {
    case BLT_STRING_KEYS:
	strcpy(np->key.string, key);
	break;
    case BLT_ONE_WORD_KEYS:
	np->key.oneWordValue = key;
	break;
    default:
	memcpy(np->key.words, key, keySize);
	break;
    }
    return np;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_Reset --
 *
 *	Removes all the entries from a list, removing pointers to the objects
 *	and keys (not the objects or keys themselves).  The node counter is
 *	reset to zero.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_Reset(List *listPtr)		/* List to clear */
{
    if (listPtr != NULL) {
	Node *nextPtr, *np;

	for (np = listPtr->head; np != NULL; np = nextPtr) {
	    nextPtr = np->next;
	    FreeNode(np);
	}
	Blt_List_Init(listPtr, listPtr->type);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_Destroy
 *
 *     Frees the list structure.
 *
 * Results:
 *	Returns a pointer to the newly created list structure.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_Destroy(Blt_List list)
{
    if (list != NULL) {
	Blt_List_Reset(list);
	Blt_Free(list);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_Init --
 *
 *	Initializes a linked list.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_Init(List *listPtr, size_t type)
{
    listPtr->nNodes = 0;
    listPtr->head = listPtr->tail = NULL;
    listPtr->type = type;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_LinkAfter --
 *
 *	Inserts an node following a given node.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_LinkAfter(List *listPtr, Node *np, Node *afterPtr)
{
    if (listPtr->head == NULL) {
	listPtr->tail = listPtr->head = np;
    } else {
	if (afterPtr == NULL) {
	    /* Prepend to the front of the list */
	    np->next = listPtr->head;
	    np->prev = NULL;
	    listPtr->head->prev = np;
	    listPtr->head = np;
	} else {
	    np->next = afterPtr->next;
	    np->prev = afterPtr;
	    if (afterPtr == listPtr->tail) {
		listPtr->tail = np;
	    } else {
		afterPtr->next->prev = np;
	    }
	    afterPtr->next = np;
	}
    }
    np->list = listPtr;
    listPtr->nNodes++;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_LinkBefore --
 *
 *	Inserts an node preceding a given node.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_LinkBefore(List *listPtr, Node *np, Node *beforePtr)
{
    if (listPtr->head == NULL) {
	listPtr->tail = listPtr->head = np;
    } else {
	if (beforePtr == NULL) {
	    /* Append onto the end of the list */
	    np->next = NULL;
	    np->prev = listPtr->tail;
	    listPtr->tail->next = np;
	    listPtr->tail = np;
	} else {
	    np->prev = beforePtr->prev;
	    np->next = beforePtr;
	    if (beforePtr == listPtr->head) {
		listPtr->head = np;
	    } else {
		beforePtr->prev->next = np;
	    }
	    beforePtr->prev = np;
	}
    }
    np->list = listPtr;
    listPtr->nNodes++;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_UnlinkNode --
 *
 *	Unlinks an node from the given list. The node itself is not
 *	deallocated, but only removed from the list.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_UnlinkNode(Node *np)
{
    List *listPtr;

    listPtr = np->list;
    if (listPtr != NULL) {
	int unlinked = 0;

	if (listPtr->head == np) {
	    listPtr->head = np->next;
	    unlinked++;
	}
	if (listPtr->tail == np) {
	    listPtr->tail = np->prev;
	    unlinked++;
	}
	if (np->next != NULL) {
	    np->next->prev = np->prev;
	    unlinked++;
	}
	if (np->prev != NULL) {
	    np->prev->next = np->next;
	    unlinked++;
	}
	np->list = NULL;
	if (unlinked) {
	    assert(listPtr->nNodes > 0);
	    listPtr->nNodes--;
	}
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_GetNode --
 *
 *	Find the first node matching the key given.
 *
 * Results:
 *	Returns the pointer to the node.  If no node matching the key given is
 *	found, then NULL is returned.
 *
 *---------------------------------------------------------------------------
 */

/*LINTLIBRARY*/
Blt_ListNode
Blt_List_GetNode(List *listPtr, const char *key)
{
    if (listPtr != NULL) {
	switch (listPtr->type) {
	case BLT_STRING_KEYS:
	    return FindString(listPtr, key);
	case BLT_ONE_WORD_KEYS:
	    return FindOneWord(listPtr, key);
	default:
	    return FindArray(listPtr, key);
	}
    }
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_DeleteNode --
 *
 *	Unlinks and deletes the given node.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_DeleteNode(Blt_ListNode node)
{
    Blt_List_UnlinkNode(node);
    FreeNode(node);
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_DeleteNodeByKey --
 *
 *	Find the node and free the memory allocated for the node.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_DeleteNodeByKey(Blt_List list, const char *key)
{
    Blt_ListNode node;

    node = Blt_List_GetNode(list, key);
    if (node != NULL) {
	Blt_List_DeleteNode(node);
    }
}

/*LINTLIBRARY*/
Blt_ListNode
Blt_List_Append(Blt_List list, const char *key, ClientData clientData)
{
    Blt_ListNode node;

    node = Blt_List_CreateNode(list, key);
    Blt_List_SetValue(node, clientData);
    Blt_List_AppendNode(list, node);
    return node;
}

/*LINTLIBRARY*/
Blt_ListNode
Blt_List_Prepend(Blt_List list, const char *key, ClientData clientData)
{
    Blt_ListNode node;

    node = Blt_List_CreateNode(list, key);
    Blt_List_SetValue(node, clientData);
    Blt_List_PrependNode(list, node);
    return node;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_GetNthNode --
 *
 *	Find the node based upon a given position in list.
 *
 * Results:
 *	Returns the pointer to the node, if that numbered element
 *	exists. Otherwise NULL.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
Blt_ListNode
Blt_List_GetNthNode(List *listPtr, long position, int direction)
{
    if (listPtr == NULL) {
	return NULL;
    }
    if (direction > 0) {
	Node *np;
	
	for (np = listPtr->head; np != NULL; np = np->next) {
	    if (position == 0) {
		return np;
	    }
	    position--;
	}
    } else {
	Node *np;
	
	for (np = listPtr->tail; np != NULL; np = np->prev) {
	    if (position == 0) {
		return np;
	    }
	    position--;
	}
    }
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_List_Sort --
 *
 *	Find the node based upon a given position in list.
 *
 * Results:
 *	Returns the pointer to the node, if that numbered element
 *	exists. Otherwise NULL.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
void
Blt_List_Sort(List *listPtr, Blt_ListCompareProc *proc)
{
    Node **nodes;
    Node *np;
    size_t i;

    if (listPtr->nNodes < 2) {
	return;
    }
    nodes = Blt_Malloc(sizeof(Node *) * (listPtr->nNodes + 1));
    if (nodes == NULL) {
	return;			/* Out of memory. */
    }
    for (i = 0, np = listPtr->head; np != NULL; np = np->next) {
	nodes[i++] = np;
    }
    qsort(nodes, listPtr->nNodes, sizeof(Node *), (QSortCompareProc *)proc);

    /* Rethread the list. */
    np = nodes[0];
    listPtr->head = np;
    np->prev = NULL;
    for (i = 1; i < listPtr->nNodes; i++) {
	np->next = nodes[i];
	np->next->prev = np;
	np = np->next;
    }
    listPtr->tail = np;
    np->next = NULL;
    Blt_Free(nodes);
}
