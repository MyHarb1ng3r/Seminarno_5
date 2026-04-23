#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product {
    char product_name[21];
    float price;
    int ID;
} Product;

typedef struct Orders {
    char client_address[31];
    int product_ID;
} Orders;

typedef struct Word {
    char text[51];
} Word;

typedef struct Employee {
    int id;
    float hourly_rate;
    float hours_worked;
    float weekly_salary;
} Employee;

void clear_buffer() {
    while(getchar() != '\n');
}

int anagram_check(char* first, char* second) {
    int first_size = strlen(first);
    int second_size = strlen(second);
    int check;

    if(first_size != second_size) {
        return 0;
    }

    char temp_second[51];
    strcpy(temp_second, second);

    for(int i = 0; i < first_size; i++) {
        check = -1;
        char temp = first[i];

        for(int j = 0; j < first_size; j++) {
            if(temp == temp_second[j]) {
                check = 0;
                temp_second[j] = '*';
                break;
            }
        }

        if(check != 0) {
            return 0;
        }
    }

    return 1;
}

void task1() {
    int guests, table_count = 0, chair_count = 0, cups_count = 0, dishes_count = 0;
    float price = 0;

    printf("Въведете броя гости: ");
    scanf("%d", &guests);
    clear_buffer();

    while(1) {
        char buf[50];

        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';
        buf[strcspn(buf, "\r")] = '\0';

        if(strcmp(buf, "PARTY!") == 0) {
            break;
        }

        if(strcmp(buf, "Chair") == 0) {
            chair_count++;
            price += 13.99;
        }
        else if(strcmp(buf, "Table") == 0) {
            table_count++;
            price += 42.00;
        }
        else if(strcmp(buf, "Cups") == 0) {
            cups_count++;
            price += 5.98;
        }
        else if(strcmp(buf, "Dishes") == 0) {
            dishes_count++;
            price += 21.02;
        }
    }

    printf("\nИзход: \n");
    printf("%.2f\n", price);
    
    int temp;

    temp = ((guests + 7) / 8) - table_count;
    
    if(temp > 0) {
        if(temp == 1) {
            printf("%d Table\n", temp);
        } else {
            printf("%d Tables\n", temp);
        }
    }
    
    temp = guests - chair_count;
    
    if(temp > 0) {
        if(temp == 1) {
            printf("%d Chair\n", temp);
        } else {
            printf("%d Chairs\n", temp);
        }
    }

    temp = ((guests + 5) / 6) - cups_count;

    if(temp > 0) {
        printf("%d Cups\n", temp);
    }

    temp = ((guests + 5) / 6) - dishes_count;

    if(temp > 0) {
        printf("%d Dishes\n", temp);
    }
}

void task2() {
    int product_count = 0;
    int order_count = 0;

    Product *products = NULL;
    Orders *orders = NULL;

    while(1) {
        char buf[20];
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';
        buf[strcspn(buf, "\r")] = '\0';

        if(strcmp(buf, "END") == 0) {
            break;
        }

        if(strcmp(buf, "Product") == 0) {
            char temp_name[21];
            float temp_price;
            int temp_id;

            printf("Product\n");
            printf("Въведете име на продукт: ");
            fgets(temp_name, sizeof(temp_name), stdin);
            temp_name[strcspn(temp_name, "\n")] = '\0';

            printf("Въведете цена: ");
            scanf("%f", &temp_price);

            printf("Въведете номер на продукта: ");
            scanf("%d", &temp_id);
            clear_buffer();

            int order_fulfilled = -1;
            for(int j = 0; j < order_count; j++) {
                if(orders[j].product_ID == temp_id) {
                    order_fulfilled = j;
                    break;
                }
            }

            if(order_fulfilled != -1) {
                printf("Client %s ordered %s\n", orders[order_fulfilled].client_address, temp_name);
                
                for(int j = order_fulfilled; j < order_count - 1; j++) {
                    orders[j] = orders[j + 1];
                }
                order_count--;
                
                if(order_count > 0) {
                    orders = (Orders *)realloc(orders, order_count * sizeof(Orders));
                } else {
                    free(orders);
                    orders = NULL;
                }
            } else {
                products = (Product *)realloc(products, (product_count + 1) * sizeof(Product));
                strcpy(products[product_count].product_name, temp_name);
                products[product_count].price = temp_price;
                products[product_count].ID = temp_id;
                product_count++;
            }
        }

        if(strcmp(buf, "Order") == 0) {
            char temp_address[31];
            int temp_id;

            printf("Order\n");
            printf("Въведете адрес на клиента: ");
            fgets(temp_address, sizeof(temp_address), stdin);
            temp_address[strcspn(temp_address, "\n")] = '\0';

            printf("Въведете номер на продукта: ");
            scanf("%d", &temp_id);
            clear_buffer();

            int product_fulfilled = -1;
            for(int j = 0; j < product_count; j++) {
                if(products[j].ID == temp_id) {
                    product_fulfilled = j;
                    break;
                }
            }

            if(product_fulfilled != -1) {
                printf("Client %s ordered %s\n", temp_address, products[product_fulfilled].product_name);
                
                for(int j = product_fulfilled; j < product_count - 1; j++) {
                    products[j] = products[j + 1];
                }
                product_count--;

                if(product_count > 0) {
                    products = (Product *)realloc(products, product_count * sizeof(Product));
                } else {
                    free(products);
                    products = NULL;
                }
            } else {
                orders = (Orders *)realloc(orders, (order_count + 1) * sizeof(Orders));
                strcpy(orders[order_count].client_address, temp_address);
                orders[order_count].product_ID = temp_id;
                order_count++;
            }
        }
    }

    free(products);
    free(orders);
}

void task3() {
    FILE *in_file = fopen("input.txt", "r");

    if (in_file == NULL) {
        printf("Грешка при отваряне на входния файл!\n");
        return;
    }

    int word_count = 0;
    Word *words = NULL;
    char last_char = '\0';
    char buf[51];

    while (fscanf(in_file, "%50s", buf) == 1) {
        if (word_count == 0 || buf[0] == last_char) {
            Word *temp_words = (Word *)realloc(words, (word_count + 1) * sizeof(Word));

            if (temp_words == NULL) {
                printf("Неуспешно заделяне на памет!\n");
                free(words);
                fclose(in_file);
                return;
            }

            words = temp_words;
            strcpy(words[word_count].text, buf);
            last_char = buf[strlen(buf) - 1];
            word_count++;
        }
    }

    fclose(in_file);

    FILE *out_file = fopen("output.bin", "wb");

    if (out_file == NULL) {
        printf("Грешка при създаване на бинарния файл!\n");
        free(words);
        return;
    }

    for (int i = 0; i < word_count; i++) {
        fwrite(words[i].text, sizeof(char), strlen(words[i].text), out_file);
        
        if (i < word_count - 1) {
            char space = ' ';
            fwrite(&space, sizeof(char), 1, out_file);
        }
    }

    fclose(out_file);
    free(words);

    FILE *bin_file = fopen("output.bin", "rb");

    if (bin_file == NULL) {
        printf("Грешка при отваряне на бинарния файл!\n");
        return;
    }

    printf("Изход:\n");
    
    int ch;
    
    while ((ch = fgetc(bin_file)) != EOF) {
        printf("%c", ch);
    }
    
    printf("\n");

    fclose(bin_file);
}

void task4() {
    int n;

    printf("Въведете ключа (цяло число между 2 и 10): ");
    scanf("%d", &n);
    clear_buffer(); 

    if(n < 2 || n > 10) {
        printf("Невалиден ключ\n");
        return;
    }

    char input_filename[50];
    printf("Въведете името на файла за кодиране (оригиналния): ");
    fgets(input_filename, sizeof(input_filename), stdin);
    input_filename[strcspn(input_filename, "\n")] = '\0';
    input_filename[strcspn(input_filename, "\r")] = '\0';

    char output_filename[50];
    printf("Въведете името на кодирания файл: ");
    fgets(output_filename, sizeof(output_filename), stdin);
    output_filename[strcspn(output_filename, "\n")] = '\0';
    output_filename[strcspn(output_filename, "\r")] = '\0';

    FILE *original_file = fopen(input_filename, "r");
    FILE *encrypted_file = fopen(output_filename, "w");

    if(original_file == NULL || encrypted_file == NULL) {
        printf("Неуспешно отваряне на файловете!\n");
        if(original_file) fclose(original_file);
        if(encrypted_file) fclose(encrypted_file);
        return;
    }

    int ch;

    while((ch = fgetc(original_file)) != EOF) {
        fputc(ch + n, encrypted_file);
    }

    fclose(original_file);
    fclose(encrypted_file);

    printf("Файлът е кодиран успешно!\n");
}

void task5() {
    char word[51];
    char hidden[51];
    int len, max_guesses, guesses = 0, is_won = 0;

    printf("Въведете дума за игра: ");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0';
    word[strcspn(word, "\r")] = '\0';

    len = strlen(word);
    max_guesses = len + 2;

    for(int i = 0; i < len; i++) {
        hidden[i] = '_';
    }
    hidden[len] = '\0';

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    while(guesses < max_guesses) {
        printf("Дума: %s\n", hidden);
        printf("Въведете буква: ");
        
        char ch;
        scanf("%c", &ch);
        clear_buffer();

        guesses++;

        for(int i = 0; i < len; i++) {
            if(word[i] == ch) {
                hidden[i] = ch;
            }
        }

        if(strcmp(word, hidden) == 0) {
            is_won = 1;
            break;
        }
    }

    if(is_won == 1) {
        printf("Печелите!\n");
        printf("Думата е: %s\n", word);
        printf("Брой въведени букви: %d\n", guesses);
    } else {
        printf("Загубихте!\n");
        printf("Думата беше: %s\n", word);
    }
}

void task6() {
    char first[51];
    printf("Въведете първа дума: ");
    fgets(first, sizeof(first), stdin);
    first[strcspn(first, "\n")] = '\0';
    first[strcspn(first, "\r")] = '\0';

    char second[51];
    printf("Въведете втора дума: ");
    fgets(second, sizeof(second), stdin);
    second[strcspn(second, "\n")] = '\0';
    second[strcspn(second, "\r")] = '\0';

    int result = anagram_check(first, second);

    printf("\n");

    if(result == 1) {
        printf("%s = %s\n", first, second);
    }
    else {
        printf("%s != %s\n", first, second);
    }
}

void task7() {
    while(1) {
        int choice;
        
        printf("\n--- Меню Сътрудници ---\n");
        printf("1. Добавяне на нов запис\n");
        printf("2. Извеждане на данните и заплатите\n");
        printf("3. Назад към главното меню\n");
        printf("Въведете вашия избор: ");
        
        scanf("%d", &choice);
        clear_buffer();

        if(choice == 3) {
            break;
        }

        if(choice == 1) {
            FILE *file = fopen("employees.bin", "ab+");
            
            if(file == NULL) {
                printf("Грешка при отваряне на файла!\n");
                continue;
            }

            fseek(file, 0, SEEK_END);
            long file_size = ftell(file);
            int current_count = file_size / sizeof(Employee);

            if(current_count >= 30) {
                printf("Достигнат е максималният брой от 30 сътрудници!\n\n");
                fclose(file);
                continue;
            }

            Employee emp;
            
            printf("Въведете ID на сътрудника: ");
            scanf("%d", &emp.id);
            
            printf("Въведете почасово плащане: ");
            scanf("%f", &emp.hourly_rate);
            
            printf("Въведете брой отработени часове за седмицата: ");
            scanf("%f", &emp.hours_worked);
            clear_buffer();

            float gross_salary;
            
            if(emp.hours_worked > 40.0) {
                float overtime = emp.hours_worked - 40.0;
                gross_salary = (40.0 * emp.hourly_rate) + (overtime * emp.hourly_rate * 1.5);
            } else {
                gross_salary = emp.hours_worked * emp.hourly_rate;
            }

            float taxes = gross_salary * 0.0365;
            emp.weekly_salary = gross_salary - taxes;

            fwrite(&emp, sizeof(Employee), 1, file);
            fclose(file);
            
            printf("\n");
        }
        else if(choice == 2) {
            FILE *file = fopen("employees.bin", "rb");
            
            if(file == NULL) {
                printf("Няма записани данни!\n\n");
                continue;
            }

            Employee emp;
            
            printf("\nСписък на сътрудниците:\n");
            
            while(fread(&emp, sizeof(Employee), 1, file) == 1) {
                printf("ID: %d | Ставка: %.2f | Часове: %.2f | Заплата: %.2f\n", 
                       emp.id, emp.hourly_rate, emp.hours_worked, emp.weekly_salary);
            }
            
            printf("\n");
            fclose(file);
        }
    }
}

int main() {
    int main_choice;

    while(1) {
        printf("\nИзберете задача:\n");
        printf("1. Задача 1 (Парти)\n");
        printf("2. Задача 2 (Сладкарница)\n");
        printf("3. Задача 3 (Верига от думи - файл)\n");
        printf("4. Задача 4 (Кодиране на файл)\n");
        printf("5. Задача 5 (Бесеница)\n");
        printf("6. Задача 6 (Анаграма)\n");
        printf("7. Задача 7 (Сътрудници във фирма)\n");
        printf("8. Изход\n");
        printf("\n");
        printf("Изберете задача за стартиране (1-8): ");

        scanf("%d", &main_choice);
        clear_buffer();

        if(main_choice == 8) {
            break;
        }

        switch(main_choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 4:
                task4();
                break;
            case 5:
                task5();
                break;
            case 6:
                task6();
                break;
            case 7:
                task7();
                break;
            default:
                printf("Невалиден избор!\n");
                break;
        }
    }

    return 0;
}
