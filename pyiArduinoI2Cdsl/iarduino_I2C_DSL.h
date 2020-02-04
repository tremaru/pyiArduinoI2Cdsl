//  Библиотека для работы с датчиком освещенности, люксметром, I2C-flash для Arduino: https://iarduino.ru/shop/Sensory-Datchiki/datchik-osveschennosti-lyuksmetr-i2c-trema-modul-v2-0.html
//  Версия: 1.0.1
//  Последнюю версию библиотеки Вы можете скачать по ссылке: https://iarduino.ru/file/517.html
//  Подробное описание функций бибилиотеки доступно по ссылке: https://wiki.iarduino.ru/page/DSL-trema-i2c/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел.
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_I2C_DSL_h                                                                                                              //
#define iarduino_I2C_DSL_h                                                                                                              //
                                                                                                                                        //
//#if defined(ARDUINO) && (ARDUINO >= 100)                                                                                                //
//#include        <Arduino.h>                                                                                                             //
//#else                                                                                                                                   //
//#include        <WProgram.h>                                                                                                            //
//#endif                                                                                                                                  //
                                                                                                                                        //
#include        "iarduino_I2C_PI.h"                                                                                                //  Подключаем файл iarduino_I2C_DSL.h - для работы с шиной I2C     (используя функции структуры iI2C)
                                                                                                                                        //
#define         DEF_CHIP_ID_FLASH       0x3C                                                                                            //  ID линейки чипов - константа для всех чипов серии Flash (позволяет идентифицировать принадлежность чипа к серии).
#define         DEF_CHIP_ID_METRO       0xC3                                                                                            //  ID линейки чипов - константа для всех чипов серии Metro (позволяет идентифицировать принадлежность чипа к серии).
#define         DEF_MODEL_DSL           0x06                                                                                            //  Идентификатор модели - константа.
//              Адреса регистров модуля:                                                                                                //
#define         REG_FLAGS_0             0x00                                                                                            //  Адрес регистра флагов управления для чтения.
#define         REG_BITS_0              0x01                                                                                            //  Адрес регистра битов  управления для чтения и записи.
#define         REG_FLAGS_1             0x02                                                                                            //  Адрес регистра флагов управления для чтения.
#define         REG_BITS_1              0x03                                                                                            //  Адрес регистра битов  управления для чтения и записи.
#define         REG_MODEL               0x04                                                                                            //  Адрес регистра содержащего номер типа модуля.
#define         REG_VERSION             0x05                                                                                            //  Адрес регистра содержащего версию прошивки.
#define         REG_ADDRESS             0x06                                                                                            //  Адрес регистра содержащего текущий адрес модуля на шине I2C. Если адрес указан с флагом IF-PIN-ADDRES то адрес установится (и запишется в регистр) только при наличии 1 на входе PIN_ADDRES.
#define         REG_CHIP_ID             0x07                                                                                            //  Адрес регистра содержащего ID линейки чипов «Flash». По данному ID можно определить принадлежность чипа к линейки «Flash».
#define         REG_DSL_AVERAGING       0x08                                                                                            //  Адрес регистра содержащего коэффициент усреднения показаний освещённости и расстояния (0-без усреднений...255-максимальное усреднение).
#define         REG_DSL_FLG             0x10                                                                                            //  Адрес регистра содержащего флаг «GET_CHANGED». Флаг устанавливается если «REG_DSL_LUX» изменится более чем на «REG_DSL_LUX_CHANGE» то установится флаг «GET_CHANGED». Флаг сбрасывается автоматически, сразу после чтения данного регистра.
#define         REG_DSL_LUX_L           0x11                                                                                            //  Адрес регистра содержащего значение усреднённой освещённости в лк (младший байт).
#define         REG_DSL_LUX_CHANGE      0x13                                                                                            //  Адрес регистра содержащего значение для установки флага «GET_CHANGED». Если «REG_DSL_LUX» изменится более чем на «REG_DSL_LUX_CHANGE» то установится флаг «GET_CHANGED».
#define         REG_DSL_COEFFICIENT     0x14                                                                                            //  Адрес регистра содержащего коэффициент пульсаций света в процентах (0...100%).
#define         REG_DSL_PROXIMITY_L     0x15                                                                                            //  Адрес регистра содержащего значение усреднённого расстояния (младший байт).
//              Позиция битов и флагов:                                                                                                 //
#define         DSL_GET_CHANGED         0x01                                                                                            //  Флаг изменения освещённости.    Устанавливается если «REG_DSL_LUX» изменится более чем на «REG_DSL_LUX_CHANGE». Ссбрасывается автоматически (сразу после чтения).
                                                                                                                                        //
class iarduino_I2C_DSL{                                                                                                                 //
    public:                                                                                                                             //
    /** Конструктор класса **/                                                                                                          //
        iarduino_I2C_DSL                                (uint8_t address=0){                                                            //  Конструктор класса                                                  (Параметр: адрес модуля на шине I2C, если не указан (=0), то адрес будет определён).
                                                        if(address>0x7F){ address>>=1; }                                                //  Корректируем адрес, если он указан с учётом бита RW.
                            valAddrTemp             =   address;                                                                        //  Сохраняем переданный адрес модуля.
                            objI2C                  =   new iarduino_I2C;                                                               //  Переопределяем указатель objI2C на объект производного класса iarduino_I2C.
        }                                                                                                                               //
    /** Пользовательские функции **/                                                                                                    //
        bool                begin                       (void                                                   );                      //  Объявляем  функцию инициализации модуля                             (Параметр:  отсутствует).
        bool                reset                       (void                                                   );                      //  Объявляем  функцию перезагрузки модуля                              (Параметр:  отсутствует).
        bool                changeAddress               (uint8_t                                                );                      //  Объявляем  функцию смены адреса модуля на шине I2C                  (Параметр:  новый адрес модуля).
        uint8_t             getAddress                  (void                                                   ){ return valAddr;  }   //  Определяем функцию возвращающую текущий адрес модуля на шине I2C    (Параметр:  отсутствует).
        uint8_t             getVersion                  (void                                                   ){ return valVers;  }   //  Определяем функцию возвращающую текущую версию прошивки модуля      (Параметр:  отсутствует).
        uint16_t            getLux                      (void                                                   );                      //  Объявляем  функцию возвращающую текущую освещённость в люксах       (Параметр:  отсутствует).
        uint16_t            getProximity                (void                                                   );                      //  Объявляем  функцию возвращающую близость препятствий                (Параметр:  отсутствует).
        uint8_t             getPulsation                (void                                                   );                      //  Объявляем  функцию возвращающую коэффициент пульсаций света         (Параметр:  отсутствует).
        bool                getLuxChanged               (void                                                   );                      //  Объявляем  функцию возвращающую флаг изменения освщённости          (Параметр:  отсутствует).
        bool                setLuxChange                (uint8_t                                                );                      //  Объявляем  функцию установки порога чувств к изменению освещённости (Параметр:  освещённость в лк).
        bool                setAveraging                (uint8_t                                                );                      //  Объявляем  функцию установки коэффициента усреднения показаний      (Параметр:  коэффициент).
    private:                                                                                                                            //
    /** Внутренние переменные **/                                                                                                       //
        uint8_t             valAddrTemp             =   0;                                                                              //  Определяем переменную для хранения адреса модуля на шине I2C который был указан, но не был проверен.
        uint8_t             valAddr                 =   0;                                                                              //  Определяем переменную для хранения адреса модуля на шине I2C.
        uint8_t             valVers                 =   0;                                                                              //  Определяем переменную для хранения версии прошивки модуля.
        uint32_t            tmrReadFLG              =   0;                                                                              //  Определяем переменную для хранения времени (в мс) последнего чтения регистра флагов «REG_DSL_FLG».
static const uint32_t            tmrPeriodFLG            =   10;                                                                             //  Определяем константу  для хранения минимального времени между опросом регистра флагов «REG_DSL_FLG».
        uint8_t             data[8];                                                                                                    //  Объявляем  массив     для хранения получаемых/передаваемых данных.
        iarduino_I2C_BASE*  objI2C;                                                                                                     //  Объявляем  указатель  на  объект полиморфного класса iarduino_I2C_BASE, но в конструкторе данного класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C.
    /** Внутренние функции **/                                                                                                          //
        bool                _readBytes              (uint8_t    , uint8_t                                       );                      //  Объявляем  функцию чтения данных в  массив  data                    (Параметры:  номер первого регистра, количество байт).
        bool                _writeBytes             (uint8_t    , uint8_t, uint8_t=0                            );                      //  Объявляем  функцию записи данных из массива data                    (Параметры:  номер первого регистра, количество байт, номер первого элемента массива data).
};                                                                                                                                      //
                                                                                                                                        //
#endif                                                                                                                                  //