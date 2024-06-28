# distutils: language = c++
# cython: language_level = 3

from iarduino_I2C_DSL cimport iarduino_I2C_DSL
#from time import sleep

DEF_CHIP_ID_FLASH =  0x3C
DEF_CHIP_ID_METRO =  0xC3
DEF_MODEL_DSL = 0x06

# Адреса регистров модуля:
REG_FLAGS_0          =  0x00
REG_BITS_0           =  0x01
REG_FLAGS_1          =  0x02
REG_BITS_1           =  0x03
REG_MODEL            =  0x04
REG_VERSION          =  0x05
REG_ADDRESS          =  0x06
REG_CHIP_ID          =  0x07
REG_DSL_AVERAGING    =  0x08
REG_DSL_FLG          =  0x10
REG_DSL_LUX_L        =  0x11
REG_DSL_LUX_CHANGE   =  0x13
REG_DSL_COEFFICIENT  =  0x14
REG_DSL_PROXIMITY_L  =  0x15

# Позиция битов и флагов:
DSL_FLG_CHANGED      =  0x01

NO_BEGIN = 1

cdef class pyiArduinoI2Cdsl:
    cdef iarduino_I2C_DSL c_module

    def __cinit__(self, address=None, auto=None, bus=None):


        if address is not None:

            self.c_module = iarduino_I2C_DSL(address)

            if bus is not None:
                self.changeBus(bus)

            if auto is None:
                #sleep(.5)
                if not self.c_module.begin():

                    print("ошибка инициализации модуля.\n"
                          "Проверьте подключение и адрес модуля,"
                          " возможно не включен интерфейс I2C.\n"
                          " Запустите raspi-config и включите интерфейс"
                          ", инструкция по включению:"
                          " https://wiki.iarduino.ru/page/raspberry-i2c-spi/")

        else:

            self.c_module = iarduino_I2C_DSL()

            if bus is not None:
                self.changeBus(bus)

            if auto is None:
                #sleep(.5)
                if not self.c_module.begin():

                    print("ошибка инициализации модуля.\n"
                          "Проверьте подключение и адрес модуля, "
                          " возможно не включен интерфейс I2C.\n"
                          " Запустите raspi-config и включите интерфейс"
                          ", инструкция по включению:"
                          " https://wiki.iarduino.ru/page/raspberry-i2c-spi/")

    def begin(self):
        return self.c_module.begin()

    def changeAddress(self, unsigned char newAddr):
        return self.c_module.changeAddress(newAddr)

    def reset(self):
        return self.c_module.reset()

    def getAddress(self):
        return self.c_module.getAddress()

    def getVersion(self):
        return self.c_module.getVersion()

    def getLux(self):
        return self.c_module.getLux()

    def getProximity(self):
        return self.c_module.getProximity()

    def getPulsation(self):
        return self.c_module.getPulsation()

    def getLuxChanged(self):
        return self.c_module.getLuxChanged()

    def setLuxChange(self, lux):
        return self.c_module.setLuxChange(lux)

    def setAveraging(self, k):
        return self.c_module.setAveraging(k)

    def changeBus(self, bus):
        return self.c_module.changeBus(bytes(bus, 'utf-8'))
