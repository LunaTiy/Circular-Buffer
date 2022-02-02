#include <iostream>

using std::cout;
using std::endl;

class Circular_Buffer {
private:
	int buffer_size;	//Размер буффера
	int* data;			//Данные
	int read_index;		//Индекс для чтения
	int write_index;	//Индекс для записи
	bool is_empty;		//Буфер пуст
	bool is_full;		//Буфер заполнен

	//Функция проверка на заполненность буфера (вынесена в private, т.к. не должна вызываться вне класса)
	void checked_full(void) {
		for (int i = 0; i < buffer_size; i++) {
			if (data[i] == 0) {
				is_full = false;
				break;
			}
			else
				is_full = true;
		}
	}

	//Функция проверка на пустоту буфера (вынесена в private, т.к. не должна вызываться вне класса)
	void checked_empty(void) {
		for (int i = 0; i < buffer_size; i++) {
			if (data[i] != 0) {
				is_empty = false;
				break;
			}
			else
				is_empty = true;
		}
	}

	//Функция для объединения двух функций проверки (можно реализовать все в одной функции, не прибегаю к дополнительным вызовам)
	void checked(void) {
		checked_full();
		checked_empty();
	}

public:
	//Конструктор класса
	Circular_Buffer(int size = 5) {
		cout << "Вызов конструктора...\n";

		this->buffer_size = size;
		data = new int [this->buffer_size];

		for (int i = 0; i < this->buffer_size; i++)
			data[i] = 0;

		read_index = 0;
		write_index = 0;
		is_empty = true;
		is_full = false;
	}

	//Деструктор класса
	~Circular_Buffer() {
		cout << "Вызов деструктора...\n";
		delete[] data;
	}

	//Вывод данных пользователю
	void output_data(void) {
		cout << "Значения буффера:\n";
		for (int i = 0; i < this->buffer_size; i++)
			cout << "[" << i << "] = " << data[i] << endl;
		cout << endl;
	}

	//Запись данных в буфер
	void put_data(int new_data) {
		cout << "Запись данных в буфер\n";
		if (!is_full) {
			cout << "Запись прошла успешно!\n";
			data[write_index] = new_data;
			write_index++;

			if (write_index == buffer_size)
				write_index = 0;

		}
		else
			cout << "Запись не была осуществлена, буфер заполнен!\n";

		checked();
	}

	//Удаление данных из буфера
	void delete_data(void) {
		cout << "Удаление данных из буфера...\n";
		if (!is_empty) {
			cout << "Удаление произошло успешно!\n";
			data[read_index] = 0;
			read_index++;

			if (read_index == buffer_size)
				read_index = 0;
		}
		else
			cout << "Удаление не произошло, буфер пуст!\n";

		checked();
	}

	//Получение размера буфера
	int get_size(void) {
		return this->buffer_size;
	}
};

//Тестовый блок программы
void test(Circular_Buffer* buffer) {
	buffer->output_data();	//Вывод буфера (инициализирован нулями)
	buffer->delete_data();	//Попытка удаления данных

	/*
		Запись данных в буфер
		Запись производится специально на 1 элемент больше, чем может вместить буфер с той целью,
		чтобы увидеть, произойдет запись или нет.
	*/
	for (int i = 1; i < buffer->get_size() + 2; i++) 
		buffer->put_data(i);
	buffer->output_data();

	/*
		Удаление данных из буфер
		Удаление производится специально на 1 элемент больше с той целью,
		чтобы увидеть, произойдет удаление пустых данных или нет.
	*/
	for (int i = 1; i < buffer->get_size() + 2; i++) 
		buffer->delete_data();
	buffer->output_data();
}

int main(int argc, char* argv) {
	setlocale(LC_ALL, "ru");
	Circular_Buffer* buffer = new Circular_Buffer(4);

	test(buffer);

	delete buffer;
	return 0;
}