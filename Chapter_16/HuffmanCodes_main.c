/* Chapter 16.3 | Huffman-codes */
/* Exercise 16.3-6 | Huffman-codes */
/*	Plain text (.txt) and ASCII is only type of the source file.
	File structure from the beginning: {5 items}
	{#1} [4 bytes] (total number of symbols in the entire source file) +
	{#2} [1 byte] (number of unique symbols in the entire source file 'n') +
	{#3} [n bytes] (ASCII code for every symbol discovered by a walk of the tree) +
	{#4} [2n - 1 bits] (the structure of the full binary tree: internal node '0', leaf '1') + padding with zero bits up to the end of the byte in the last not full byte +
	{#5} bits of the compressed symbols + padding with zero bits up to the end of the byte in the last not full byte.
	*/

#include "HuffmanCodes_common.h"
#include "HuffmanCodes_struct.h"
#include <stdio.h>
#include <stdlib.h>

int ParseFilename(FNSet_t* fn, char* argv);
int CompressFile(FILE* fo, FILE* fw);
int DecompressFile(FILE* fo, FILE* fw);

int main(int argc, char* argv[])
{
	FILE* fo, * fw;
	FNSet_t fn;
	if (argc != 2) {
		printf("Please enter the \'PATH/NAME.EXT\' as an argument\n");
		return FAILURE;
	}
	if ((fo = fopen(argv[1], "rb")) == NULL) {
		perror("\n\n\t| ERROR | ");
		return FAILURE;
	}
	if (ParseFilename(&fn, argv[1]) == FAILURE) {
		return FAILURE;
	}
	if ((fw = fopen(fn.pathname, "wb")) == NULL) {
		perror("\n\n\t| ERROR | ");
		return FAILURE;
	}
	if (fn.optype == DECOMPRESSTXT) {
		if (DecompressFile(fo, fw) == FAILURE) {
			return FAILURE;
		}
	}
	else if (fn.optype == COMPRESSTXT) {
		if (CompressFile(fo, fw) == FAILURE) {
			return FAILURE;
		}
	}
	fclose(fo);
	fclose(fw);
	return SUCCESS;
}