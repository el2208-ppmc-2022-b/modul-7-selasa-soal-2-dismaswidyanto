/*EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
*Modul            : 7 - Stacks and Queues
*Percobaan        : -
*Hari dan Tanggal : Selasa, 5 April 2022
*Nama (NIM)       : -
*Asisten (NIM)    : -
*Nama File        : soal-02.c
*Deskripsi        : -
*/

#include <stdio.h>
#include <stdlib.h>

// Deklarasi tipe stack
typedef struct stack {
	char title;
	struct stack *next;
} stack;

// Fungsi untuk menampilkan stack (jika diperlukan untuk melihat ilustrasi stack)
void print_stack(stack *top) {
	stack *temp = top;
	while (temp != NULL) {
		printf("%c\n", temp->title);
		temp = temp->next;
	}
}

// Fungsi untuk memasukkan buku ke dalam stack
void push(stack **top, char data) {
	stack *temp = (stack*)malloc(sizeof(stack));
	temp->title = data;
	temp->next = *top;
	*top = temp;
}

// Fungsi untuk mengeluarkan buku dari stack
char pop(stack **top) {
	if (*top == NULL)
		return 0;
	stack *temp = *top;
	int popped = temp->title;
	*top = (*top)->next;
	free(temp);
	return popped;
}

// Fungsi untuk menghitung panjang/tinggi stack
int stack_length(stack *top) {
	if (top == NULL)
		return 0;
	stack *temp = top;
	int count = 1;
	while (temp->next != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}

int main() {
	char stack_order[8];

	printf("Masukkan urutan book_stack: ");
	scanf("%s", stack_order);

	// Deklarasi book_stack dan temp_stack
	stack *book_stack = NULL;
	stack *temp_stack = NULL;

	int i;
	// Masukkan input urutan buku ke book_stack
	for (i = 7; i >= 0; i--)
		push(&book_stack, stack_order[i]);

	int max_length = 0;
	char to_read;
	for (to_read = 'A'; to_read <= 'H'; to_read++) {
		// Tampilkan ilustrasi stack jika diperlukan
		/*
		printf("\nBook stack: %d\n", stack_length(book_stack));
		print_stack(book_stack);
		printf("\nTemp stack: %d\n", stack_length(temp_stack));
		print_stack(temp_stack);
		*/

		char taken;
		int found = 0;

		// Pencarian di book_stack
		do {
			taken = pop(&book_stack);
			if (taken == to_read)
				found = 1;
			else if (taken != 0)
				push(&temp_stack, taken);
		} while (taken != 0 && found == 0);

		int current_length = stack_length(temp_stack);
		// Update max length jika ditemukan yang lebih tinggi
		if (current_length > max_length)
			max_length = current_length;

		// Skip pencarian di temp_stack jika buku sudah ditemukan di book_stack
		if (found == 1)
			continue;

		// Pencarian di temp_stack
		do {
			taken = pop(&temp_stack);
			if (taken == to_read)
				found = 1;
			else if (taken != 0)
				push(&book_stack, taken);
		} while (taken != 0 && found == 0);

	}

	// Template output
	printf("Tinggi maksimum temp_stack: %d", max_length);

	return 0;
}
