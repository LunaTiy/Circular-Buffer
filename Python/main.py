import CircularBuffer as CB
import _CircularBuffer as _CB
import test

print("Тестирование буффера без проверки на полноту данных:")
buffer = CB.CircularBuffer(4)
test.test(buffer)

# Создание объекта класса буффера с проверкой (без перезаписи данных)
print("Тестирование буффера с проверкой на полноту данных (если буфер заполнен, данные не буду записаны):")
_buffer = _CB._CircularBuffer(6)
test.test(_buffer)