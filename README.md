Detección de factores importantes para la optimización y manejo de cultivos a través de sensores en Arduino Uno
======
   El proyecto consiste en la implementación de un dispositivo basado en arduino
para la recoleccion y analisis de los datos, con el fin de mandar una alertar
por vía SMS al dispositivo del usuario cuando se supera un límite establecido.

### Componentes
- Arduino Uno Genuino
- SIM900 GSM/GPRS Shield
- Tarjeta SIM
- Antena GSM
- Sensor de rayos UV SI1145
- Sensor de humeda y temperatura DHT22
- Sensor de lluvia 
- Mini Protoboard 
- Adaptador de Bateria de 9 voltios.
- Batería de 9 Voltios.

### Ensamblaje del prototipo
-Colocar la tarjeta SIM en la ranura ubicada en la parte inferior del Shield GSM.
**Nota**: Para facilitar el uso de la tarjeta SIM, **remueva** el PIN de desbloqueo.

![alt text](https://github.com/dani0105/Semestre-II-ProyectoArduino/doc/images/step1.jpeg)

-Colocar la antena al Shiel GSM y colocarlo sobre la placa Arduino uno
**Nota**: Asegurarse que los Jumpers estén en la configuración **RXD**->**D3**, **TXD**->**D2**.

![alt text](https://github.com/dani0105/Semestre-II-ProyectoArduino/doc/images/step2.jpeg)

-Hacer la conexion de los puertos de tierra (**GND**) y voltaje 3 y 5 a la protoboard

- Conectar el Sensor DHT 22 al puerto digital **D5**

![alt text](https://github.com/dani0105/Semestre-II-ProyectoArduino/doc/images/step3.jpeg)

- Conectar el Sensor UV SI1145, los puertos **SDA**->**A4** y **SCL**->**A5**, el sonsor permite voltajes entre 3 a 5 voltios, eentonces,
pueden conectarlo donde le sirva más.

![alt text](https://github.com/dani0105/Semestre-II-ProyectoArduino/doc/images/step4.jpeg)

- Conectar Sensor de lluvia en el analogico **A2**

![alt text](https://github.com/dani0105/Semestre-II-ProyectoArduino/doc/images/step5.jpeg)
![alt text](https://github.com/dani0105/Semestre-II-ProyectoArduino/doc/images/step6.jpeg)

- Conectar Ardruino al adaptador de batería.

### Codigo 
 Para un correcto funcionamiento del codigo es necesario instalar las siguientes librerias:
- Libreria DHT
- Libreria Adafruit_SI1145

**Nota**: La libreria de GSM no es ncesaria instalar, porque se encuentra junto al codigo de este proyecto.
**Nota**: En la seccion de referencias puede encontrar links donde puede descargar las librerias y material de referencia.

El codigo principal de la aplicacion se encuentra en el archivo main.ino.

Diagrama de flujo del codigo
![alt text](https://github.com/dani0105/Semestre-II-ProyectoArduino/doc/images/diagramFlow.jpeg)


### Contribuyentes:

Este proyecto fue echo por:
 - [@dani0105](https://github.com/dani0105)
 - [@YosineyMora](https://github.com/YosineyMora)
 - [@JairoPacheco](https://github.com/https://github.com/JairoPacheco)
 - [@kairack](https://github.com/kairack)

### Referencias
Libreria GSM:[https://github.com/MarcoMartines/GSM-GPRS-GPS-Shield](https://github.com/MarcoMartines/GSM-GPRS-GPS-Shield)
Liberia DHT: []()
Libreria Adafruit_SI1145: []()
Tutorial de como mandar y recibir mensajes por GSM: [http://educ8s.tv/arduino-gsm-shield/](http://educ8s.tv/arduino-gsm-shield/)
