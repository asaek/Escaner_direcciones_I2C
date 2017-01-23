#include <Wire.h>


void setup()
{
	Wire.begin(); // Iniciamos la comunicación I2C

	Serial.begin(9600); // Iniciamos la comunicación con el monitor serie
						//while (!Serial);             // Leonardo: wait for serial monitor
	Serial.println("\nEscaner de direcciones I2C");
}


void loop()
{
	byte error, address;
	int nDevices;

	Serial.println("Escaneando...");

	nDevices = 0;
	for (address = 1; address < 127; address++)
	{
		// Se utiliza el valor de retorno de Write.endTransmisstion() para ver si se ha reconocido
		// o no la dirección I2C de un dispositivo

		Wire.beginTransmission(address);
		error = Wire.endTransmission();

		if (error == 0)
		{
			Serial.print("Dispositivo I2C encontrado en la direccion 0x");
			if (address<16)
				Serial.print("0");
			Serial.println(address, HEX);

			nDevices++;
		}
		else if (error == 4)
		{
			Serial.print("Error desconocido en la direccion 0x");
			if (address<16)
				Serial.print("0");
			Serial.println(address, HEX);
		}
	}
	if (nDevices == 0)
		Serial.println("No se han encontrado direcciones I2C de ningun dispositivo \n");
	else
		Serial.println("Hecho\n");

	delay(5000);           // Espera 5 segundos hasta el siguiente escaneo
}

