ELEMENT : 
cable, ecran oled, joystick, esp32

CONNECTION: 
ecran/esp32 : la pin sda ddu oled est connecté a la pin 21 (i2c_sda)
la pin scl (oled) est conneté a la pin 22 (i2c_scl)
les masse est connecté a la masse.
la pin vcc -> 3.3v

joystick/ecran -> URX -> GPIO 34 (entrée analogique)
URY -> GPIO 35 (entrée analogique)
SW (bouton) -> GPIO 32 (entrée numérique) c'est le bouton qu' on appuie pour choisir une casse
VCC -> 3.3V
GND -> GND//