# TSE_TP3
Trabajo práctico nº 3 para TSE de CESE

Partes del sistema

Proceso Writer:
Este proceso iniciará y se quedará esperando que el usuario ingrese la temperatura ambiente hasta que presione ENTER. 
En ese momento escribirá en una named fifo los datos con el siguiente formato: DATA:XX.X e informará que se escribió correctamente con la palabra DATA.
La temperatura tendrá un formato numérico con 1 decimal del tipo 99.9. La temperatura inferior a los 100º y superior a 0º.
De no existir el name fifo lo deberá crear e informar que fue creado correctamente con el nombre fifo_data.

En cualquier momento el proceso podrá recibir las signals SIGUSR1 y SIGUSR2. En dicho caso deberá escribir en el named fifo el siguiente mensaje:
SIGN:1 o SIGN:2 y devolverá la información SIGN.

Proceso Reader:
Este proceso leerá los datos del named fifo y según el encabezado “DATA” o “SIGN” escribirá en el archivo log.txt o signals.txt. Informará si se logró escribir correctamente con TRUE o FALSE.
No podrá superar los 10 datos ingresados, en ese caso informar y no escribir en el archivo.

Arquitectura del sistema:


<img width="640" alt="image" src="https://github.com/VictorBelaunde/TSE_TP3/assets/112257613/2760d307-1b46-4988-9b84-445486146272">

