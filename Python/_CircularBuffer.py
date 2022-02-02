class _CircularBuffer(object):
    def __init__(self, buffer_size=5):
        self.buffer_size = buffer_size      # Размерность буффера
        self.data = [0] * self.buffer_size  # Массив данных (сам буффер)
        self.read_index = 0                 # Индекс для чтения данных
        self.write_index = 0                # Индекс для записи данных
        self.is_empty = True                # Флаг пустоты буффера
        self.is_full = False                # Флаг полноты буффера

    # Функиця проверки на заполненность буффера
    def checked_full(self):
        for i in range(self.buffer_size):
            if self.data[i] == 0:
                self.is_full = False
                break
            else:
                self.is_full = True

    # Функция проверки на пустоту буффера
    def checked_empty(self):
        for i in range(self.buffer_size):
            if self.data[i] != 0:
                self.is_empty = False
                break
            else:
                self.is_empty = True

    # Функция, вызывающая две функции проверки (можно объединить в одну, но я решил написать так)
    def checked(self):
        self.checked_full()
        self.checked_empty()

    # Вывод даннх буффера на экран
    def output_data(self):
        print("Значения буфера:")
        for i in range(self.buffer_size):
            print("[{}] = {}".format(i, self.data[i]))
        print("\n")

    # Запись данных в буффер
    def put_data(self, new_data):
        print("Проивзодится запись данных...")

        if not self.is_full:
            self.data[self.write_index] = new_data
            self.write_index += 1

            if self.write_index == self.buffer_size:
                self.write_index = 0

            print("Запись данных прошла успешно!")

        else:
            print("Запись не была осуществлена, буфер заполнен!")

        self.checked()

    # Удаление данных из буффера
    def delete_data(self):
        print("Производится удаление данных...")

        if not self.is_empty:
            self.data[self.read_index] = 0
            self.read_index += 1

            if self.read_index == self.buffer_size:
                self.read_index = 0

            print("Удаление прошло успешно!")
        else:
            print("Удаление не произошло, буфер пуст!")

        self.checked()