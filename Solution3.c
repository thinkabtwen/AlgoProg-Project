#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// fungsi ini digunakan untuk membaca file
FILE* read_csv(const char* filepath)
{
	// buka file
	FILE* file = fopen(filepath, "r");

	// Hapus baris pertama atau header
	char c;
	do
	{
		c = fgetc(file);
		if (ferror(file))
		{
			printf("Error reading file.\n");
			return 1;
		}
	} while (c != '\n');
	return file;
}

// objek string
typedef struct String
{
	const char* value;
} String;

// untuk membuat objek string
String* new_String(const char* str)
{
	String* s = (String*)malloc(sizeof(String));
	s->value = strdup(str);
	return s;
}

// objek list
typedef struct ListString
{
	int length;
	int max_length;
	String** data;
} ListString;

// untuk membuat objek list
ListString* new_ListString()
{
	ListString* l = malloc(sizeof(ListString));
	l->length = 0;
	l->max_length = 2;
	l->data = (String**) malloc(sizeof(String) * l->max_length);
	return l;
}

// untuk menambahkan string ke dalam list
void push_String(ListString* list, String* str)
{
	// jika besar list mencapai batasnya
	// maka batas ditambah
	if (list->length >= list->max_length)
	{
		list->max_length *= 2;
		list->data = (String**) realloc(list->data, sizeof(String) * list->max_length);
	}
	// menambahkan string ke dalam list
	list->data[list->length++] = str;
}

// fungsi ini untuk mengurutkan string sesuai alfabet
void sort_List(ListString* list)
{
	for (int i = 0; i < list->length; i++)
	{
		int min = i;
		for (int j = i+1; j < list->length; j++)
		{
			// Cek string, jika ada karakter yang lebih kecil maka nilai strcmp < 0
			if (strcmp(list->data[j]->value, list->data[min]->value) < 0)
			{
				min = j;
			}
		}
		// untuk menghindari pembacaan index yang sama
		if (min != i)
		{
			// melakukan pertukaran string
			String* temp = list->data[i];
			list->data[i] = list->data[min];
			list->data[min] = temp;
		}
	}
}


void display_list(ListString* list)
{
	for (int i = 0; i < list->length; i++)
	{
		printf("%s \n", list->data[i]->value);
	}
}

int main()
{
	// Ganti pathnya dengan full path
	const char* path =
		// "Change path to file.csv";

	// Baca file csv
	FILE* file = read_csv(path);
	if (!file)
	{
		printf("File tidak ditemukan");
		return 1;
	}

	// Buat list string
	ListString* list = new_ListString();
	const char* scanpattern = "%[^,]%*s\n";
	do
	{
		char loc1[28];
		// baca isi file sesuai pola yang dibuat
		fscanf(
			file, scanpattern,
			loc1);

		// Buat string
		String* s = new_String(loc1);

		// masukkan string ke dalam list
		push_String(list, s);

		// lakukan perulangan sampai akhir dari isi file
	} while (!feof(file));

	sort_List(list);
	display_list(list);

	return 0;
}