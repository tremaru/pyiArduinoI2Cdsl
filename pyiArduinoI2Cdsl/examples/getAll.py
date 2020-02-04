# ПРИМЕР ЧТЕНИЯ ВСЕХ ЗНАЧЕНИЙ ДАТЧИКА:
# Подключаем библиотеку для работы с датчиком
# освещённости I2C-flash (Digital Sensor Light).
from pyiArduinoI2Cdsl import *

from time import sleep

# Объявляем объект dsl для работы с функциями и методами
# библиотеки pyiArduinoI2Cdsl.
# Если при объявлении объекта указать адрес, например, dsl(0x0B),
# то пример будет работать с тем модулем, адрес которого был указан.
dsl = pyiArduinoI2Cdsl()

while True:
    # Получаем освещённость с датчика
    lux = dsl.getLux()

    # Получаем коэффициент пульсаций
    pulse = dsl.getPulsation()

    # Получаем близость препятствий
    prox = dsl.getProximity()

    # Выводим показания в stdout
    print("Освещённость = "
          + str(lux)
          + " лк.\t"
          + "Мерцание = "
          + str(pulse)
          + "%\t"
          + "Близость = "
          + str(prox)
          )
    sleep(.5)
