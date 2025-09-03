#include "Huffman.h"
#include <string.h>

int main() {
	char* source = "This is Algorithms.";
	char* Decoded = "";

	HuffmanNode* Tree = NULL;
	BitBuffer Encoded = { NULL ,  0 };
	HuffmanCode CodeTable[MAX_CHAR];

	memset(&CodeTable, 0, sizeof(HuffmanCode) * MAX_CHAR);

	Huffman_Encode(&Tree, (UCHAR*)source, &Encoded, CodeTable);

	printf("Original Size: %I64d Encoded Size: %d\n", (strlen(source) + 1) * sizeof(char) * 8, Encoded.Size);

	Decoded = (char*)malloc((strlen(source) + 1) * sizeof(char));
	Huffman_Decode(Tree, &Encoded, (UCHAR*)Decoded);

	printf("Original : %s\n", source);
	printf("Encoded : ");

	Huffman_PrintBinary(&Encoded);

	printf("\n");

	printf("Decoded : %s\n", Decoded);

	Huffman_DestroyTree(Tree);
	free(Decoded);

	return 0;
}