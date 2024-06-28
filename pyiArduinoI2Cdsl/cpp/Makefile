all: FindDevices NewAddress getLuxChanged getAll

FindDevices             :FindDevices.cpp ../iarduino_I2C_DSL.cpp
NewAddress              :NewAddress.cpp ../iarduino_I2C_DSL.cpp
getAll                  :getAll.cpp ../iarduino_I2C_DSL.cpp
getLuxChanged           :getLuxChanged.cpp ../iarduino_I2C_DSL.cpp
newBus           	:newBus.cpp ../iarduino_I2C_DSL.cpp

clean:
	rm -f FindDevices NewAddress getAll getLuxChanged newBus
