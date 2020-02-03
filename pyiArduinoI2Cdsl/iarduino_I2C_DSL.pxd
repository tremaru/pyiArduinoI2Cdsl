cdef extern from "iarduino_I2C_DSL.cpp":
    pass

cdef extern from "iarduino_I2C_DSL.h":
    cdef cppclass iarduino_I2C_DSL:
        iarduino_I2C_DSL() except +
        iarduino_I2C_DSL(unsigned char) except +
        bint begin()
        bint changeAddress(unsigned char)
        bint reset()
        unsigned char getAddress()
        unsigned char getVersion()
        unsigned short getLux()
        unsigned short getProximity()
        unsigned char getPulsation()
        bint getLuxChanged()
        bint setLuxChange(unsigned char)
        bint setAveraging(unsigned char)

