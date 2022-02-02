#include <iostream>

using std::cout;
using std::endl;

class Circular_Buffer {
private:
	int buffer_size;	//������ �������
	int* data;			//������
	int read_index;		//������ ��� ������
	int write_index;	//������ ��� ������
	bool is_empty;		//����� ����
	bool is_full;		//����� ��������

	//������� �������� �� ������������� ������ (�������� � private, �.�. �� ������ ���������� ��� ������)
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

	//������� �������� �� ������� ������ (�������� � private, �.�. �� ������ ���������� ��� ������)
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

	//������� ��� ����������� ���� ������� �������� (����� ����������� ��� � ����� �������, �� �������� � �������������� �������)
	void checked(void) {
		checked_full();
		checked_empty();
	}

public:
	//����������� ������
	Circular_Buffer(int size = 5) {
		cout << "����� ������������...\n";

		this->buffer_size = size;
		data = new int [this->buffer_size];

		for (int i = 0; i < this->buffer_size; i++)
			data[i] = 0;

		read_index = 0;
		write_index = 0;
		is_empty = true;
		is_full = false;
	}

	//���������� ������
	~Circular_Buffer() {
		cout << "����� �����������...\n";
		delete[] data;
	}

	//����� ������ ������������
	void output_data(void) {
		cout << "�������� �������:\n";
		for (int i = 0; i < this->buffer_size; i++)
			cout << "[" << i << "] = " << data[i] << endl;
		cout << endl;
	}

	//������ ������ � �����
	void put_data(int new_data) {
		cout << "������ ������ � �����\n";
		if (!is_full) {
			cout << "������ ������ �������!\n";
			data[write_index] = new_data;
			write_index++;

			if (write_index == buffer_size)
				write_index = 0;

		}
		else
			cout << "������ �� ���� ������������, ����� ��������!\n";

		checked();
	}

	//�������� ������ �� ������
	void delete_data(void) {
		cout << "�������� ������ �� ������...\n";
		if (!is_empty) {
			cout << "�������� ��������� �������!\n";
			data[read_index] = 0;
			read_index++;

			if (read_index == buffer_size)
				read_index = 0;
		}
		else
			cout << "�������� �� ���������, ����� ����!\n";

		checked();
	}

	//��������� ������� ������
	int get_size(void) {
		return this->buffer_size;
	}
};

//�������� ���� ���������
void test(Circular_Buffer* buffer) {
	buffer->output_data();	//����� ������ (��������������� ������)
	buffer->delete_data();	//������� �������� ������

	/*
		������ ������ � �����
		������ ������������ ���������� �� 1 ������� ������, ��� ����� �������� ����� � ��� �����,
		����� �������, ���������� ������ ��� ���.
	*/
	for (int i = 1; i < buffer->get_size() + 2; i++) 
		buffer->put_data(i);
	buffer->output_data();

	/*
		�������� ������ �� �����
		�������� ������������ ���������� �� 1 ������� ������ � ��� �����,
		����� �������, ���������� �������� ������ ������ ��� ���.
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