struct CELL {
	int ref;
} HEAP[HEAPsz];

void dump_heap() {
	for (int i = 0; i < HEAPsz; i++)
		printf("%.4X:\n", i);
}

int main() {
	dump_heap();
	return 0;
}
