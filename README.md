# Laboratorio Nº6 - MMap

Este laboratorio hace hincapié en la utilización de archivos binarios y de mecanismos de mapeo de memoria.\
En  la carpeta _rawdata_ se encuentra el archivo binario llamado _datos_. El archivo contiene información obtenida por el radar meteorológio RMA1 instalado en Ciudad Universitaria (UNC). Este programa debe mapear el archivo en memoria RAM y castearlo al tipo de dato de acuerdo a la siguiente estructura:

| Nombre      | Tipo    |  Tamaño [B]      | Descripción |  
| ----------- | ----------- | ----------- | ----------- |
| version      | unsigned int | 2 | Versión del dato n1 |
| drxVersion   | unsigned int | 2 | Version del DRX que generó el dato n1 |
| RESERVADO   |  | 4 | - |
| initCW   | double | 8 | Inicio de la ventana de recepción, en segundos |
| azimuth   | float | 4 | Apuntamiento acimut en grados |
| elevation   | float | 4 | Apuntamiento elevación en grados |
| idVolumen   | unsigned int  | 2 | Identificador de volumen |
| idBarrido   | unsigned int  | 2 | Identificador de barrido |
| idCnjunto  | unsigned int  | 2 | Identificador de conjunto |
| idGrupo  | unsigned int  | 2 | Identificador de grupo |
| idPulso   | unsigned int  | 2 | Identificador de pulso |
| iniBarrido   | bool | 1 | Bandera del primer pulso de barrido |
| finBarrido   | bool  | 1 | Bandera del último pulso de barrido |
| finGrupo   | bool  | 1 |  Bandera del último pulso del grupo |
| inhibido   | bool  | 1 | Bandera de transmisión inhibida |
| validSamples  | unsigned int  | 2 | Cantidad de muestras complejas válidas |
| nroAdquisicion  | unsigned int  | 2 | Contador de adquisiciones |
| RESERVADO   |  | 2 | - |
| nroSecuencia   | unsigned int | 4 | Número de secuencia |
| readTime_high   | unsigned int | 8 | Campo alto de la marca de tiempo |
| readTime_low   | unsigned int | 8 | Campo bajo de la marca de tiempo |
| RESERVADO   |  | 64 | - |


La estructura fue extraida de la documentación de INVAP y representa el header de un pulso de radar, con los metadatos que describen al mismo.

Se lee todo el archivo para retornar la cantidad de instancias de muestras (estructuras) contenidas en el archivo, y se obtiene la media de la variable _validSamples_ contenida en cada instancia de muestras halladas en el archivo.
