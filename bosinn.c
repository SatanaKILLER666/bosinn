#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для удаления символа из строки на месте (без доп. памяти)
void remove_char(char *str, char char_to_remove) {
  int i, j = 0;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] != char_to_remove) {
      str[j] = str[i];
      j++;
    }
  }
  str[j] = '\0'; // Важно: Завершаем строку нулевым символом!
}

int main(int argc, char *argv[]) {
  FILE *outfile;

  // Проверка количества аргументов командной строки
  if (argc != 3) {
    fprintf(stderr, "Использование: %s \"строка\" символ_для_удаления\n", argv[0]);
    return 1;
  }

  // Получение аргументов командной строки
  char *str = argv[1];
  char char_to_remove = argv[2][0]; // Берем первый символ из второго аргумента

  // Удаление символа из строки
  remove_char(str, char_to_remove);

  // Открытие файла для записи
  outfile = fopen("out.txt", "w");
  if (outfile == NULL) {
    perror("Ошибка при открытии файла out.txt");
    return 1;
  }

  // Запись результата в файл
  fprintf(outfile, "%s\n", str);

  // Закрытие файла
  fclose(outfile);

  return 0;
}