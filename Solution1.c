#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_minMaxAverage(int list[], int length)
{
    int min = 0, max = 0, average = 0, total = 0;

    // iterasi sebanyak baris data
    for (int i = 0; i < length; i++)
    {
        // cari nilai min max
        if (min > list[i] || min == 0)
            min = list[i];
        if (max < list[i])
            max = list[i];
        total += list[i];
    }
    // hitung nilai rata-rata
    average = total / length;

    // tampil min max dan rata-rata
    printf("%Maximum value: %d\n", max);
    printf("%Minimum value: %d\n", min);
    printf("Average value: %d\n", average);
}
void show_minMaxFrequencyInt(int list[], int length)
{
    int freq[3939], min = 0, max = 0, indexMin = 0, indexMax = 0, count;

    // iterasi sebanyak baris data
    for (int i = 0; i < length; i++)
    {
        count = 0;

        // jika nilai belum terbaca
        if (freq[i] != 1)
        {
            // iterasi sebanyak baris data
            for (int j = 0; j < length; j++)
            {
                // cek kesamaan data, jika sama maka jumlah frekuensi bertambah
                // dan tandai nilai yg sudah terbaca
                if (list[i] == list[j])
                {
                    count++;
                    freq[j] = 1;
                }
            }
            // jika jumlah frekuensi ada, maka hitung nilai min dan max frekuensi
            // dan simpan bersama dengan indexnya
            if (count != 0)
            {
                if (max < count)
                {
                    max = count;
                    indexMax = i;
                }
                if (min > count || min == 0)
                {
                    min = count;
                    indexMin = i;
                }
                // tampil data beserta min max frekuensinya
                printf("%d : %d\n", list[i], count);
            }
        }
    }
    // tampil data yang frekuensinya min dan max
    printf("%Maximum value: %d with frequency : %d \n", list[indexMax], max);
    printf("%Minimum value: %d with frequency : %d \n", list[indexMin], min);
}

void show_minMaxFrequencyStr(char list[3939][28], int length)
{
    int freq[3939], min = 0, max = 0, indexMin = 0, indexMax = 0, count;

    // iterasi sebanyak baris data
    for (int i = 0; i < length; i++)
    {
        count = 0;

        // jika nilai belum terbaca
        if (freq[i] != 1)
        {
            // iterasi sebanyak baris data
            for (int j = 0; j < length; j++)
            {
                // cek kesamaan data, jika sama maka jumlah frekuensi bertambah
                // dan tandai nilai yg sudah terbaca
                if (strcmp(list[i], list[j]) == 0)
                {
                    count++;
                    freq[j] = 1;
                }
            }
            // jika jumlah frekuensi ada, maka hitung nilai min dan max frekuensi
            // dan simpan bersama dengan indexnya
            if (count != 0)
            {
                if (max < count)
                {
                    max = count;
                    indexMax = i;
                }
                if (min > count || min == 0)
                {
                    min = count;
                    indexMin = i;
                }
                // tampil data beserta min max frekuensinya
                printf("%s : %d\n", list[i], count);
            }
        }
    }
    // tampil data yang frekuensinya min dan max
    printf("%Maximum value: %s with frequency : %d \n", list[indexMax], max);
    printf("%Minimum value: %s with frequency : %d \n", list[indexMin], min);
}

FILE* read_csv(const char* filepath)
{
    // Buka file pada path
    FILE* file = fopen(filepath, "r");
    if (!file)
    {
        printf("File tidak ditemukan");
        return 1;
    }

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
int main() {
    int freq[4000];

    // Ganti pathnya dengan full path
    const char* filepath = 
        // "Change path to file.csv";
    FILE* file = read_csv(filepath);


    const char* scanpattern = "%[^,],%[^,],%d,%d,%d,%d,%[^,],%d,%[^\n]\n";

    int i = 0, prices[3939], areas[3939], bathrooms[3939], rooms[3939], carParks[3939];
    char loc1[3939][28], loc2[3939][28], furnish[3939][28], type[3939][28];
    do
    {
        // baca isi file dengan format sesuai dengan pola data pada csv
        // kemudian simpan ke dalam temporari
        fscanf(file, scanpattern,
            loc1[i], loc2[i], &prices[i],
            &rooms[i], &bathrooms[i], &carParks[i],
            type[i], &areas[i], furnish[i]);
        
        i++;
        // ulangi sampai seluruh file terbaca
    } while (!feof(file));

    // Tampil dan pilih menu
    printf("Pilih kolom untuk ditampilkan\n1.loc1\n2.loc2\n3.price\n4.rooms\n5.bathrooms\n6.carparks\n7.type\n8.area\n9.furnish\nPilih: ");
    char input;
    scanf("%c", &input);
    printf("\n");
    if (input == '1')
        show_minMaxFrequencyStr(loc1, sizeof(loc1) / sizeof(loc1[0]));
    else if (input == '2')
        show_minMaxFrequencyStr(loc2, sizeof(loc2) / sizeof(loc1[0]));
    else if (input == '3')
        show_minMaxAverage(prices, sizeof(prices) / sizeof(int));
    else if (input == '4')
        show_minMaxFrequencyInt(rooms, sizeof(rooms) / sizeof(int));
    else if (input == '5')
        show_minMaxFrequencyInt(bathrooms, sizeof(bathrooms) / sizeof(int));
    else if (input == '6')
        show_minMaxFrequencyInt(carParks, sizeof(carParks) / sizeof(int));
    else if (input == '7')
        show_minMaxFrequencyStr(type, sizeof(type) / sizeof(type[0]));
    else if (input == '8')
        show_minMaxAverage(areas, sizeof(areas) / sizeof(int));
    else if (input == '9')
        show_minMaxFrequencyStr(furnish, sizeof(furnish) / sizeof(furnish[0]));
    return 0;
}