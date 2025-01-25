# Monitor de Archivos y Directorios

Este programa en C++ escanea una carpeta dada y genera un informe sobre su estructura de archivos y directorios. El programa recorre la carpeta de manera recursiva, registrando las rutas de los archivos y directorios, junto con el tamaño de cada archivo. Los resultados se guardan en un archivo de texto llamado `reporte-de-integridad.txt`.

## Características
- Escanea y registra la estructura de directorios y archivos.
- Incluye los tamaños de los archivos en el informe.
- Guarda la salida en `reporte-de-integridad.txt`.

## Uso

1. Clona el repositorio o descarga el código fuente.
2. Compila el código C++ con un compilador compatible con C++17 o posterior (por ejemplo, `g++`).
3. Ejecuta el programa desde la línea de comandos proporcionando la ruta de la carpeta que deseas escanear.

### Comando:

```bash
./monitor_de_carpetas <ruta_de_carpeta>
