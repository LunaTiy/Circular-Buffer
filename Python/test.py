def test(buffer):
    buffer.output_data()
    buffer.delete_data()
    print("\n")

    for i in range(buffer.buffer_size + 1):
        buffer.put_data(i + 1)
    buffer.output_data()

    for i in range(buffer.buffer_size + 1):
        buffer.delete_data()
    buffer.output_data()