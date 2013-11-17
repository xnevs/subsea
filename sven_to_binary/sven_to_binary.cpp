#include <cstdio>

int main(int argc, char *argv[]) {
	FILE *f_sven = fopen(argv[1], "r");
	FILE *f_binary = fopen(argv[2], "w");

	short n;

	unsigned char out[2];
	fscanf(f_sven, "%hd", &n);

	fwrite(&n, 1, 2, f_binary);


	for(int i=0; i<n; i++) {
		short num;
		fscanf(f_sven, "%hd", &num);
		fwrite(&num, 1, 2, f_binary);
		for(int j=0; j<num; j++) {
			short end;
			fscanf(f_sven, "%hd", &end);
			fwrite(&end, 1, 2, f_binary);
		}
	}
}
