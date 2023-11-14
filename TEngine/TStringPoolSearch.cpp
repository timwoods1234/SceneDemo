#include <stddef.h>
#include "TStringPoolSearch.h"
#include "TStringHelper.h"
#include "TStringPool.h"
#include "TError.h"

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPoolSearch::Insert(TStringPoolEntry* root, TStringPoolEntry* toInsert)
{
	TASSERT((root != toInsert), "[TStringPoolSearch::Insert] Trying to parent entry to itself");

	if (root == NULL)
	{
		return toInsert;
	}
	else if (GetSmallestEntry(toInsert, root, (root->refCount == 0)) == toInsert)
	{
		toInsert->prevEntry = NULL;
		toInsert->nextEntry = root;

		root->prevEntry = toInsert;

		return toInsert;
	}
	else
	{
		TStringPoolEntry* current = root;

		while (current->nextEntry != NULL && GetSmallestEntry(toInsert, current->nextEntry, (root->refCount == 0)) == current->nextEntry)
		{
			current = current->nextEntry;
		}

		toInsert->nextEntry = current->nextEntry;

		if (current->nextEntry != NULL)
		{
			current->nextEntry->prevEntry = toInsert;
		}

		current->nextEntry = toInsert;
		toInsert->prevEntry = current;

		return root;
	}
}

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPoolSearch::FindAllocatedEntry(TStringPoolEntry* root, const char* term, int termLength)
{
	TStringPoolEntry* current = root;

	while (current != NULL)
	{
		if (current->stringLength < termLength)
		{
			current = current->nextEntry;
		}
		else if (current->stringLength > termLength)
		{
			current = NULL;
		}
		else
		{
			if (TStringHelper::TStrCmp(term, TStringPool::GetData(*current)) == 0)
			{
				break;
			}
			else
			{
				current = current->nextEntry;
			}
		}
	}

	return current;
}

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPoolSearch::FindFreeEntry(TStringPoolEntry* root, int blockLength)
{
	TStringPoolEntry* current = root;

	while (current != NULL)
	{
		if (current->blockLength < blockLength)
		{
			current = current->nextEntry;
		}
		else if (current->blockLength >= blockLength)
		{
			break;
		}
	}

	return current;
}

//-------------------------------------------------------------------------------
int TStringPoolSearch::GetTotalEntries(TStringPoolEntry* root)
{
	TStringPoolEntry* current = root;
	int result = 0;

	while (current != NULL)
	{
		result++;
		current = current->nextEntry;
	}

	return result;
}

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPoolSearch::Remove(TStringPoolEntry* root, TStringPoolEntry* toRemove)
{
	TStringPoolEntry* current = root;

	while (current != NULL && current != toRemove)
	{
		current = current->nextEntry;
	}

	TASSERT(current != NULL, "[TStringPoolSearch::Remove] Entry was not in the list");

	if (current == toRemove)
	{
		if (current->prevEntry != NULL)
		{
			current->prevEntry->nextEntry = current->nextEntry;
		}
		else
		{
			root = current->nextEntry;
		}

		if (current->nextEntry != NULL)
		{
			current->nextEntry->prevEntry = current->prevEntry;
		}

		current->prevEntry = NULL;
		current->nextEntry = NULL;
	}

	return root;
}

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPoolSearch::GetSmallestEntry(TStringPoolEntry* left, TStringPoolEntry* right, bool useBlockSize)
{
	if (useBlockSize)
	{
		if (left->blockLength < right->blockLength)
		{
			return left;
		}
	}
	else
	{
		if (left->stringLength < right->stringLength)
		{
			return left;
		}
		else if (left->stringLength == right->stringLength)
		{
			int comparison = TStringHelper::TStrCmp(TStringPool::GetData(*left), TStringPool::GetData(*right));

			if (comparison < 0)
			{
				return left;
			}
		}
	}

	return right;
}
