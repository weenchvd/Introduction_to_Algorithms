#include "HuffmanCodes.h"

int ParseFilename(FNSet_t* fn, char* argv)
{
	int i, j, k, size;
	if ((size = strlen(argv)) > PATHNAMESIZE - 6) {
		printf("\n\n\t| ERROR | \'PATH\\FILENAME.EXT\' length is longer than %d characters |\n", PATHNAMESIZE - 6);
		return FAILURE;
	}
	strcpy(fn->pathname, argv);
	for (i = size - 1; i >= 0 && fn->pathname[i] != '.'; i--);
	if (i < 0) {
		printf("\n\n\t| ERROR | Incorrect file extension |\n");
		return FAILURE;
	}
	for (j = ++i, k = 0;  fn->pathname[j] && k < EXTSIZE; j++, k++) {
		fn->ext[k] = (char)tolower(fn->pathname[j]);
	}
	fn->pathname[i] = '\0';
	if (k >= EXTSIZE) {
		printf("\n\n\t| ERROR | Incorrect file extension |\n");
		return FAILURE;
	}
	else {
		fn->ext[k] = '\0';
	}
	if (strcmp(fn->ext, "txt") == 0) {
		fn->optype = COMPRESSTXT;
		strcat(fn->pathname, OUTPUTFILEEXTENSION);
	}
	else if (strcmp(fn->ext, OUTPUTFILEEXTENSION) == 0) {
		fn->optype = DECOMPRESSTXT;
		strcat(fn->pathname, "txt");
	}
	else {
		printf("\n\n\t| ERROR | Incorrect file extension |\n");
		return FAILURE;
	}
	return SUCCESS;
}

int CompressFile(FILE* fo, FILE* fw)
{
	int i, j;
	FBT_t* root;
	FBTHeapQueue_t* queue;
	Alphabet_t alph;
	SymbolCode_t symcode;
	BuildAlphabet(fo, &alph);
	if ((queue = malloc(sizeof(FBTHeapQueue_t))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	InitializeHeap(queue);
	BuildMinHeap(queue, &alph);
	if ((root = BuildHuffmanCode(queue)) == NULL) {
		return FAILURE;
	}
	for (i = 0; i < ALPHABETSIZE; i++) {
		symcode.code[i] = NULL;
	}
	if ((i = WalkThroughTree(fw, &alph, root, &symcode)) == FAILURE) {
		return FAILURE;
	}
	else if (i == EXITWITHSUCCESS) {
		return SUCCESS;
	}
	if (EncodeSymbols(fo, fw, &symcode) == FAILURE) {
		return FAILURE;
	}
	for (i = 0; i < ALPHABETSIZE; i++) {
		if (symcode.code[i] != NULL) {
			free(symcode.code[i]);
		}
 	}
	FreeFBTNode(root);
	free(queue);
	return SUCCESS;
}

int DecompressFile(FILE* fo, FILE* fw)
{
	FBT_t* root;
	FileHeader_t fh;
	root = NULL;
	if (ParseFileHeader(fo, &fh) == FAILURE) {
		return FAILURE;
	}
	if (fh.uniquesymbols > 1 && (root = ReconstructHuffmanCode(&fh)) == NULL) {
		return FAILURE;
	}
	if (DecodeSymbols(fo, fw, &fh, root) == FAILURE) {
		return FAILURE;
	}
	FreeFBTNode(root);
	return SUCCESS;
}

void BuildAlphabet(FILE* fo, Alphabet_t* alph)
{
	int i, j, bufsize;
	char buf[BUFFERSIZE];
	for (i = 0; i < ALPHABETSIZE; i++) {
		alph->symbol[i] = i;
		alph->freq[i] = 0;
	}
	do {
		bufsize = fread(buf, sizeof(char), BUFFERSIZE, fo);
		for (i = 0; i < bufsize; i++) {
			alph->freq[buf[i]]++;
		}
	} while (bufsize == BUFFERSIZE);
	rewind(fo);
	alph->uniquesymbols = alph->totalsymbols = 0;
	for (i = j = 0; i < ALPHABETSIZE; i++) {
		if (alph->freq[i] > 0) {
			alph->uniquesymbols++;
			alph->totalsymbols += alph->freq[i];
			alph->freq[j] = alph->freq[i];
			alph->symbol[j++] = alph->symbol[i];
		}
	}
	return;
}

FBT_t* BuildHuffmanCode(FBTHeapQueue_t* queue)
{
	int i, n;
	FBT_t* node;
	for (i = HEAPSTARTINDEX, n = queue->heapsize; i < n; i++) {
		if ((node = CreateFBTNode(0, FBTINTERNALNODE)) == NULL) {
			return NULL;
		}
 		node->left = HeapExtractMin(queue);
		node->left->parent = node;
		node->right = HeapExtractMin(queue);
		node->right->parent = node;
		node->freq = node->left->freq + node->right->freq;
		MinHeapInsert(queue, node);
	}
	return HeapExtractMin(queue);
}

FBT_t* CreateFBTNode(int freq, int symbol)
{
	FBT_t* node;
	if ((node = malloc(sizeof(FBT_t))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return NULL;
	}
	node->parent = node->left = node->right = NULL;
	node->freq = freq;
	node->symbol = symbol;
	return node;
}

int WalkThroughTree(FILE* fw, Alphabet_t* alph, FBT_t* root, SymbolCode_t* symcode)
{
	int i;
	unsigned int structp;					/* pointer of structure of full binary tree */
	char structure[2 * ALPHABETSIZE - 1];	/* structure of full binary tree */
	unsigned int cscp;						/* code pointer of current symbol code */
	char cursymcode[ALPHABETSIZE];			/* code of the current symbol */
	unsigned int ap;						/* alphabet pointer */
	char alphabet[ALPHABETSIZE];			/* alphabet in order of walking through the tree */
	unsigned char bitfield;
	FBT_t* node, * prev;
	if (root == NULL) {
		printf("\n\n\t| ERROR | The root of tree is NULL |\n");
		return FAILURE;
	}
	if (fwrite(&alph->totalsymbols, sizeof(unsigned int), 1, fw) != 1) { /* write item {#1} */
		printf("\n\n\t| ERROR | fwrite |\n");
		return FAILURE;
	}
	if (fwrite(&alph->uniquesymbols, sizeof(unsigned char), 1, fw) != 1) { /* write item {#2} */
		printf("\n\n\t| ERROR | fwrite |\n");
		return FAILURE;
	}
	if (root->symbol != FBTINTERNALNODE) { /* if the number of unique symbols is 1, then write the item {#3}, which is the last item in the output file */
		if (fwrite(&root->symbol, sizeof(char), 1, fw) != 1) {
			printf("\n\n\t| ERROR | fwrite |\n");
			return FAILURE;
		}
		return EXITWITHSUCCESS;
	}
	structp = cscp = ap = 0;
	prev = root;
	node = root->left;
	structure[structp++] = INTERNALNODE;
	cursymcode[cscp++] = LEFTDIR;
	while (node != root) {
		if (node->symbol == FBTINTERNALNODE) { /* node == internal node */
			if (node == prev->parent) {
				if (prev == node->left) {
					prev = node;
					node = node->right;
					cursymcode[cscp++] = RIGHTDIR;
				}
				else { /* prev == node->right */
					prev = node;
					node = node->parent;
					cscp--;
				}
			}
			else { /* node == prev->left || node == prev->right */
				structure[structp++] = INTERNALNODE;
				prev = node;
				node = node->left;
				cursymcode[cscp++] = LEFTDIR;
			}
		}
		else { /* node == leaf node */
			structure[structp++] = LEAFNODE;
			alphabet[ap++] = node->symbol;
			if ((symcode->code[node->symbol] = malloc(sizeof(char) * (cscp + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			for (i = 0; i < cscp; i++) {
				symcode->code[node->symbol][i] = cursymcode[i];
			}
			symcode->code[node->symbol][i] = ENDOFSYMBOLCODE;
			prev = node;
			node = node->parent;
			cscp--;
		}
	}
	prev = root;
	node = root->right;
	cursymcode[cscp++] = RIGHTDIR;
	while (node != root) {
		if (node->symbol == FBTINTERNALNODE) { /* node == internal node */
			if (node == prev->parent) {
				if (prev == node->left) {
					prev = node;
					node = node->right;
					cursymcode[cscp++] = RIGHTDIR;
				}
				else { /* prev == node->right */
					prev = node;
					node = node->parent;
					cscp--;
				}
			}
			else { /* node == prev->left || node == prev->right */
				structure[structp++] = INTERNALNODE;
				prev = node;
				node = node->left;
				cursymcode[cscp++] = LEFTDIR;
			}
		}
		else { /* node == leaf node */
			structure[structp++] = LEAFNODE;
			alphabet[ap++] = node->symbol;
			if ((symcode->code[node->symbol] = malloc(sizeof(char) * (cscp + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			for (i = 0; i < cscp; i++) {
				symcode->code[node->symbol][i] = cursymcode[i];
			}
			symcode->code[node->symbol][i] = ENDOFSYMBOLCODE;
			prev = node;
			node = node->parent;
			cscp--;
		}
	}
	if (ap != alph->uniquesymbols) {
		printf("\n\n\t| ERROR | ap != uniquesymbols |\n");
		return FAILURE;
	}
	if (fwrite(alphabet, sizeof(char), ap, fw) != ap) { /* write item {#3} */
		printf("\n\n\t| ERROR | fwrite |\n");
		return FAILURE;
	}
	bitfield = 0;
	for (i = 0; i < structp; ) {
		bitfield = bitfield << 1 | structure[i++];
		if (i % CHAR_BIT == 0) {
			if (fwrite(&bitfield, sizeof(unsigned char), 1, fw) != 1) { /* write item {#4} */
				printf("\n\n\t| ERROR | fwrite |\n");
				return FAILURE;
			}
		}
	}
	if ((i %= CHAR_BIT) != 0) {
		while (i < CHAR_BIT) {
			bitfield <<= 1;
			i++;
		}
		if (fwrite(&bitfield, sizeof(unsigned char), 1, fw) != 1) { /* write item {#4} with padding bits */
			printf("\n\n\t| ERROR | fwrite |\n");
			return FAILURE;
		}
	}
	return SUCCESS;
}

int EncodeSymbols(FILE* fo, FILE* fw, SymbolCode_t* symcode)
{
	int i, j, bufsize;
	char buf[BUFFERSIZE];
	char bfp;								/* bitfield pointer */
	unsigned char bitfield;
	char* curcode;
	bitfield = bfp = 0;
	do {
		bufsize = fread(buf, sizeof(char), BUFFERSIZE, fo);
		for (i = 0; i < bufsize; i++) {
			curcode = symcode->code[buf[i]];
			for (j = 0; curcode[j] != ENDOFSYMBOLCODE; j++) {
				bitfield = bitfield << 1 | curcode[j];
				bfp++;
				if (bfp == CHAR_BIT) {
					if (fwrite(&bitfield, sizeof(unsigned char), 1, fw) != 1) { /* write item {#5} */
						printf("\n\n\t| ERROR | fwrite |\n");
						return FAILURE;
					}
					bfp = 0;
				}
			}
		}
	} while (bufsize == BUFFERSIZE);
	if (bfp != 0) {
		while (bfp < CHAR_BIT) {
			bitfield <<= 1;
			bfp++;
		}
		if (fwrite(&bitfield, sizeof(unsigned char), 1, fw) != 1) { /* write item {#5} with padding bits */
			printf("\n\n\t| ERROR | fwrite |\n");
			return FAILURE;
		}
	}
	return SUCCESS;
}

void FreeFBTNode(FBT_t* root)
{
	if (root != NULL) {
		if (root->symbol == FBTINTERNALNODE) {
			FreeFBTNode(root->left);
			FreeFBTNode(root->right);
		}
		free(root);
	}
	return;
}

void InitializeHeap(FBTHeapQueue_t* queue)
{
	queue->heapsize = 0;
	queue->heapsizelimit = FBTHEAPQUEUESIZE - 1;
	return;
}

void BuildMinHeap(FBTHeapQueue_t* queue, Alphabet_t* alph)
{
	int i;
	queue->heapsize = alph->uniquesymbols;
	for (i = HEAPSTARTINDEX; i < alph->uniquesymbols + HEAPSTARTINDEX; i++) {
		queue->node[i] = CreateFBTNode(alph->freq[i - HEAPSTARTINDEX], alph->symbol[i - HEAPSTARTINDEX]);
	}
	for (i = queue->heapsize >> 1; i >= HEAPSTARTINDEX; i--) {
		MinHeapify(queue, i);
	}
	return;
}

FBTHeapQueue_t* HeapExtractMin(FBTHeapQueue_t* queue)
{
	FBT_t* node;
	if (queue->heapsize < 1) {
		printf("\n\n\t| ERROR | Heap underflow |\n");
		return NULL;
	}
	node = queue->node[HEAPSTARTINDEX];
	queue->node[HEAPSTARTINDEX] = queue->node[queue->heapsize--];
	MinHeapify(queue, HEAPSTARTINDEX);
	return node;
}

void MinHeapInsert(FBTHeapQueue_t* queue, FBT_t* node)
{
	if (queue->heapsize >= queue->heapsizelimit) {
		printf("\n\n\t| ERROR | Heap size limit reached |\n");
		return;
	}
	queue->node[++queue->heapsize] = node;
	HeapDecreaseKey(queue, queue->heapsize, node->freq);
	return;
}

void HeapDecreaseKey(FBTHeapQueue_t* queue, int index, int freq)
{
	int parent;
	FBT_t* node;
	if (index > queue->heapsize) {
		printf("\n\n\t| ERROR | Index is greater than heap size |\n");
		return;
	}
	if (index < HEAPSTARTINDEX) {
		printf("\n\n\t| ERROR | Index is less than %d |\n", HEAPSTARTINDEX);
		return;
	}
	if (freq > queue->node[index]->freq) {
		printf("\n\n\t| ERROR | New key is bigger than current key |\n");
		return;
	}
	node = queue->node[index];
	while (index > HEAPSTARTINDEX && queue->node[parent = HEAPPARENT(index)]->freq > freq) {
		queue->node[index] = queue->node[parent];
		index = parent;
	}
	queue->node[index] = node;
	return;
}

void MinHeapify(FBTHeapQueue_t* queue, int index)
{
	int left, right, smallest;
	FBT_t* tmp;
	while (TRUE)
	{
		left = HEAPLEFTCHILD(index);
		right = HEAPRIGHTCHILD(index);
		if (left <= queue->heapsize && queue->node[left]->freq < queue->node[index]->freq) {
			smallest = left;
		}
		else {
			smallest = index;
		}
		if (right <= queue->heapsize && queue->node[right]->freq < queue->node[smallest]->freq) {
			smallest = right;
		}
		if (smallest != index) {
			tmp = queue->node[index];
			queue->node[index] = queue->node[smallest];
			queue->node[smallest] = tmp;
			index = smallest;
		}
		else {
			break;
		}
	}
	return;
}

int ParseFileHeader(FILE* fo, FileHeader_t* fh)
{
	int structsizeinbits, structsizeinbytes;
	if (fread(&fh->totalsymbols, sizeof(unsigned int), 1, fo) != 1) { /* read item {#1} */
		printf("\n\n\t| ERROR | fread |\n");
		return FAILURE;
	}
	if (fread(&fh->uniquesymbols, sizeof(unsigned char), 1, fo) != 1) { /* read item {#2} */
		printf("\n\n\t| ERROR | fread |\n");
		return FAILURE;
	}
	if (fread(fh->symbolsinorder, sizeof(char), fh->uniquesymbols, fo) != fh->uniquesymbols) { /* read item {#3} */
		printf("\n\n\t| ERROR | fread |\n");
		return FAILURE;
	}
	if (fh->uniquesymbols == 1) {
		return SUCCESS;
	}
	structsizeinbits = 2 * fh->uniquesymbols - 1;
	structsizeinbytes = structsizeinbits / CHAR_BIT;
	if (structsizeinbits % CHAR_BIT > 0) {
		structsizeinbytes++;
	}
	if (fread(fh->structure, sizeof(char), structsizeinbytes, fo) != structsizeinbytes) { /* read item {#4} */
		printf("\n\n\t| ERROR | fread |\n");
		return FAILURE;
	}
	return SUCCESS;
}

FBT_t* ReconstructHuffmanCode(FileHeader_t* fh)
{
	int i, j, k, nodetype, structsizeinbits;
	char bfp;
	unsigned char bitfield;
	FBT_t** node, * root, * prev;
	structsizeinbits = 2 * fh->uniquesymbols - 1;
	if ((root = CreateFBTNode(0, FBTINTERNALNODE)) == NULL) {
		return NULL;
	}
	prev = root;
	node = &prev->left;
	k = j = 0;
	bitfield = fh->structure[k];
	bfp = CHAR_BIT - 1;
	for (i = 1; i < structsizeinbits; i++) {
		if (bfp < 1) {
			bfp = CHAR_BIT;
			bitfield = fh->structure[++k];
		}
		if ((nodetype = bitfield >> --bfp & LEAFNODE) == LEAFNODE) {
			if ((*node = CreateFBTNode(0, fh->symbolsinorder[j++])) == NULL) {
				return NULL;
			}
			(*node)->parent = prev;
			if (*node == prev->left) {
				node = &prev->right;
			}
			else if (i < structsizeinbits - 1) { /* *node == prev->right */
				while (*node != prev->left) {
					node = &prev->right->parent;
					prev = prev->parent;
				}
				node = &prev->right;
			}
		}
		else { /* the next node is INTERNALNODE */
			if ((*node = CreateFBTNode(0, FBTINTERNALNODE)) == NULL) {
				return NULL;
			}
			(*node)->parent = prev;
			prev = *node;
			node = &(*node)->left;
		}
	}
	return root;
}

int DecodeSymbols(FILE* fo, FILE* fw, FileHeader_t* fh, FBT_t* root)
{
	unsigned int i, k;
	long long int j;
	int r;									/* number of symbols in the buffer after reading */
	int n;									/* number of symbols in the buffer for write */
	unsigned char rbuf[BUFFERSIZE];			/* buffer for read */
	char wbuf[BUFFERSIZE];					/* buffer for write */
	char bfp;								/* bitfield pointer */
	unsigned char bitfield;
	FBT_t* node;
	if (fh->uniquesymbols == 1) {
		char symbol;
		symbol = fh->symbolsinorder[0];
		for (i = k = 0; i < fh->totalsymbols; i += n) {
			j = (long long int)fh->totalsymbols - ++k * BUFFERSIZE;
			j = (j >= 0) ? BUFFERSIZE : BUFFERSIZE + j;
			for (n = 0; n < j; n++) {
				wbuf[n] = symbol;
			}
			if (fwrite(wbuf, sizeof(char), n, fw) != n) { /* write the decoded item {#5} */
				printf("\n\n\t| ERROR | fwrite |\n");
				return FAILURE;
			}
		}
		return SUCCESS;
	}
	if (root == NULL) {
		return FAILURE;
	}
	for (i = k = r = n = bfp = 0; i < fh->totalsymbols; i++) {
		node = root;
		while (node->symbol == FBTINTERNALNODE) {
			if (bfp < 1) {
				bfp = CHAR_BIT;
				if (k >= r) {
					k = 0;
					r = fread(rbuf, sizeof(unsigned char), BUFFERSIZE, fo);
				}
				bitfield = rbuf[k++];
			}
			node = ((bitfield >> --bfp & 1) == LEFTDIR) ? node->left : node->right;
		}
		if (n >= BUFFERSIZE) {
			if (fwrite(wbuf, sizeof(char), n, fw) != n) { /* write the decoded item {#5} */
				printf("\n\n\t| ERROR | fwrite |\n");
				return FAILURE;
			}
			n = 0;
		}
		wbuf[n++] = node->symbol;
	}
	if (n > 0) {
		if (fwrite(wbuf, sizeof(char), n, fw) != n) { /* write the decoded item {#5} */
			printf("\n\n\t| ERROR | fwrite |\n");
			return FAILURE;
		}
	}
	return SUCCESS;
}