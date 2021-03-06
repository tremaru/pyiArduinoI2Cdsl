// ПРИМЕР ЧТЕНИЯ ОСВЕЩЁННОСТИ ПРИ ЕЁ ИЗМЕНЕНИИ:   // * Строки со звёздочкой являются необязательными.
                                                  //
#include <iostream>
#include "../iarduino_I2C_DSL.h"                     //   Подключаем библиотеку для работы с датчиком освещённости I2C-flash (Digital Sensor Light).
iarduino_I2C_DSL dsl;                             //   Объявляем объект dsl для работы с функциями и методами библиотеки iarduino_I2C_DSL.
void loop(void);
                                                  //   Если при объявлении объекта указать адрес, например, dsl(0xBB), то пример будет работать с тем модулем, адрес которого был указан.
int main()
{
    dsl.begin();                                  //   Инициируем работу с датчиком освещённости.
    dsl.setLuxChange(10);                         //   Указываем фиксировать изменение освещённости более чем на 10 лк.
    for(;;)
        loop();
}                                                 //
                                                  //
void loop(){                                      //
    if (dsl.getLuxChanged()) {                    //   Если освещённость изменилась более чем на значение указанное в функции setLuxСhanged(), то ...
        std::cout << "Освещённость = ";           //
        std::cout << dsl.getLux();                //   Выводим текущую освещённость, от 0 до 8191 лк.
        std::cout << " лк.\n";                    //
    }                                             //
}                                                 //
