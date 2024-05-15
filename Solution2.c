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

// tipe data ini digunakan sebagai data housing
typedef struct Housing
{
    char* loc1;
    char* loc2;
    int price;
    int rooms;
    int bathrooms;
    int carParks;
    int area;
    char* type;
    char* furnish;
} Housing;

// tipe data ini digunakan untuk menampung banyak data housing
typedef struct ListHousing
{
    int length;
    int max_length;
    Housing** housing;
} ListHousing;

// fungsi atau prosedur ini untuk menambahkan data housing ke dalam penampungnya
void push_ListHousing(ListHousing* list, Housing* housing)
{
    // jika besar penampung sudah mencapai nilai maksimum
    // maka besar penampung akan ditambah sebanyak 2x lipat
    if (list->length >= list->max_length)
    {
        list->max_length *= 2;
        list->housing = realloc(list->housing, sizeof(Housing) * list->max_length);
    }
    // simpan data housing ke dalam penampung
    list->housing[list->length++] = housing;
}

// fungsi ini untuk membuat data atau objek penampung data-data housing
ListHousing* new_ListHousing()
{
    // buat memori alikasi untuk penampung data housing
    // kemudian isi nilai atributny
    ListHousing* l = (ListHousing*) malloc(sizeof(ListHousing));
    l->length = 0;
    l->max_length = 2;
    l->housing = (Housing**)malloc(sizeof(Housing) * l->max_length);
    return l;
}

// fungsi ini untuk membuat data atau objek housing
Housing* new_Housing(
    const char* loc1,
    const char* loc2,
    int price,
    int rooms,
    int bathrooms,
    int carParks,
    const char* type,
    int area,
    const char* furnish)
{
    // buat memori alokasi untuk data housing
    // kemudian isi nilai atributnya
    Housing* h = (Housing*) malloc(sizeof(Housing));
    h->loc1 = strdup(loc1);
    h->loc2 = strdup(loc2);
    h->price = price;
    h->rooms = rooms;
    h->bathrooms = bathrooms;
    h->carParks = carParks;
    h->type = strdup(type);
    h->area = area;
    h->furnish = strdup(furnish);

    return h;
}

// fungsi ini untuk mencari data-data housing berdasarkan input user
ListHousing* search_Housing(ListHousing* list, const char* dataX, const char* columnName)
{
    // jika list kosong maka fungsi berakhir
    if (list->length == NULL)
    {
        printf("[Error] input list pada search_Housing kosong\n");
        return NULL;
    }
    // buat list housing baru untuk menampung hasil pencarian
    ListHousing* result = new_ListHousing();
    for (int i = 0; i < list->length; i++)
    {
        // cek nama kolom dan cari data sesuai input yang diberikan
        // kemudian simpan ke dalam penampung hasil pencarian
        if (strcmp(columnName, "loc1") == 0 && strstr(list->housing[i]->loc1, dataX) != NULL)
            push_ListHousing(result, list->housing[i]);
        else if (strcmp(columnName, "loc2") == 0 && strstr(list->housing[i]->loc2, dataX) != NULL)
            push_ListHousing(result, list->housing[i]);
        else if (strcmp(columnName, "rooms") == 0 && list->housing[i]->rooms == atoi(dataX))
            push_ListHousing(result, list->housing[i]);
        else if (strcmp(columnName, "bathrooms") == 0 && list->housing[i]->bathrooms == atoi(dataX))
            push_ListHousing(result, list->housing[i]);
        else if (strcmp(columnName, "carparks") == 0 && list->housing[i]->carParks == atoi(dataX))
            push_ListHousing(result, list->housing[i]);
        else if (strcmp(columnName, "type") == 0 && list->housing[i]->type == atoi(dataX))
            push_ListHousing(result, list->housing[i]);
        else if (strcmp(columnName, "furnish") == 0 && strstr(list->housing[i]->furnish, dataX) != NULL)
            push_ListHousing(result, list->housing[i]);
    }

    // jika hasil pencarian kosong maka tampilkan informasi tersebut
    if (result->length == NULL)
        printf("[Error] Hasil pencarian tidak ditemukan\n");

    // kembalikan nilai hasil untuk nanti ditampilkan
    return result;
}
void display_Housing(ListHousing* list)
{
    // jika list kosong maka proses berakhir
    if (list->length == 0)
    {
        printf("[Error] input list pada display_housing kosong\n");
        return;
    }

    // tampilkan data-data sesuai dengan pola tampilan
    const char* display_pattern = "%-26s| %-13s| %-9d| %-2d| %-2d| %-2d| %-10s| %-5d| %-12s| \n";
    for (int i = 0; i < list->length; i++)
    {
        printf(
            display_pattern, 
            list->housing[i]->loc1,
            list->housing[i]->loc2,
            list->housing[i]->price,
            list->housing[i]->rooms,
            list->housing[i]->bathrooms,
            list->housing[i]->carParks,
            list->housing[i]->type,
            list->housing[i]->area,
            list->housing[i]->furnish);
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

    // Buat list housing
    ListHousing* list = new_ListHousing();
    const char* scanpattern = "%[^,],%[^,],%d,%d,%d,%d,%[^,],%d,%[^\n]\n";
    do
    {
        int price, rooms, bathrooms, carParks, area;
        char loc1[28], loc2[28], type[28], furnish[28];
        // baca isi file sesuai pola yang dibuat
        fscanf(
            file, scanpattern,
            loc1, loc2, &price,
            &rooms, &bathrooms, &carParks,
            type, &area, furnish);

        // buat data housing
        Housing* housing = new_Housing(loc1, loc2, price, rooms, bathrooms, carParks, type, area, furnish);
        
        // masukkan data housing ke dalam list housing
        push_ListHousing(list, housing);

        // lakukan perulangan sampai akhir dari isi file
    } while (!feof(file));
    
    // input pencarian
    char dataX[32], fn[32], columnName[32];
    printf("Input pencarian (data, operator, kolom): ");
    scanf("%s %s %s", &dataX, &fn, &columnName);

    // cek input, jika ada yang kosong maka program berakhir
    if (dataX == NULL || fn == NULL || columnName == NULL)
    {
        printf("[Error] Input kosong \n");
        return 1;
    }

    // cek operator pencarian (in), jika beda maka program berakhir
    if (strcmp(fn, "in") != 0)
    {
        printf("[Error] Operator %s belum diimplementasi", fn);
        return 1;
    }
    
    // cari data-data housing sesuai input pencarian
    ListHousing* result = search_Housing(list, dataX, columnName);

    // tampilkan data-data pencarian
    display_Housing(result);

    return 0;
}