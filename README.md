# cub3d

video

## Descripción general

**cub3d** es un motor gráfico minimalista escrito en C que implementa la técnica de raycasting para renderizar escenarios en 3D a partir de mapas 2D. Inspirado en clásicos como *Wolfenstein 3D*, el proyecto demuestra dominio de:

- Fundamentos de gráficos por computadora en tiempo real.
- Gestión de memoria y estructuras de datos en C.
- Procesamiento de archivos de configuración y validación de datos.
- Arquitectura modular para mantener la escalabilidad y mantenibilidad.

Este README profundiza en el funcionamiento interno y las decisiones técnicas, ideal para presentar a un posible empleador las competencias adquiridas.

## Tabla de contenido

1. [Características clave](#características-clave)
2. [Arquitectura del proyecto](#arquitectura-del-proyecto)
3. [Motor de raycasting](#motor-de-raycasting)
4. [Gestión de texturas y renderizado](#gestión-de-texturas-y-renderizado)
5. [Parsing y validación de mapas](#parsing-y-validación-de-mapas)
6. [Gestión de entrada y controles](#gestión-de-entrada-y-controles)
7. [Estructura de datos y utilidades](#estructura-de-datos-y-utilidades)
8. [Compilación y dependencias](#compilación-y-dependencias)
9. [Despliegue y uso](#despliegue-y-uso)
10. [Pruebas y validación](#pruebas-y-validación)
11. [Rendimiento y optimización](#rendimiento-y-optimización)
12. [Buenas prácticas de código](#buenas-prácticas-de-código)
13. [Contribuciones y roadmap](#contribuciones-y-roadmap)
14. [Autor y contacto](#autor-y-contacto)
15. [Licencia](#licencia)

---

## Características clave

- **Renderizado 3D en tiempo real** usando raycasting y cálculo de distancia perpendicular para evitar distorsiones.
- **Mapas configurables** mediante archivos `.cub`, donde se definen texturas, colores de cielo y suelo, y disposición de paredes.
- **Texturizado completo** de paredes (Norte, Sur, Este, Oeste) con archivos XPM.
- **Control de jugador fluido**, incluyendo movimiento en cuatro direcciones y rotación de cámara.
- **Colisión básica** para impedir atravesar muros.
- **Validación exhaustiva** de mapas con algoritmo flood-fill para garantizar mapas cerrados.
- **Estructura modular** que separa claramente parsing, renderizado, entrada y utilidades.

---

## Arquitectura del proyecto

La organización en carpetas sigue el principio de responsabilidad única:

```
├── core/               # Bucle principal, inicialización y limpieza
├── graphics/           # Raycasting, ancho de pantalla, buffer y texturas
├── input/              # Mapa de teclas y gestión de eventos
├── map/                # Parsing y validación de archivos .cub
├── utils/              # Funciones generales (math, strings, errores)
├── libft_ext/          # Biblioteca libft externa (funciones C básicas)
├── minilibx-linux/     # Wrapper de X11 para gestión de ventana y píxeles
├── Makefile            # Reglas de compilación y dependencias
└── examples/           # Mapas de ejemplo (.cub) y assets XPM
```

Cada módulo expone una API interna documentada con comentarios en código, permitiendo la extensión o sustitución de componentes.

---

## Motor de raycasting

1. **Emisión de rayos**: Por cada columna de la pantalla, se genera un rayo que parte desde la posición de la cámara.
2. **Digital Differential Analyzer (DDA)**: Se avanza paso a paso en la cuadrícula del mapa hasta colisionar con una pared.
3. **Determinación de distancia perpendicular**: Se calcula la distancia real al muro evitando el efecto de "fish-eye".
4. **Altura de pared proyectada**: A partir de la distancia, se determina la altura en píxeles de la sección de pared a renderizar.
5. **Selección de textura y coordenadas**: Según la cara del muro (N/S/E/W), se elige la textura y se calcula la posición en la imagen.
6. **Dibujo de columna texturizada** sobre el buffer en memoria.

Este flujo se repite a 60 FPS (u otro valor configurable) para crear la ilusión de movimiento suave.

---

## Gestión de texturas y renderizado

- Texturas en formato **XPM**, cargadas en memoria al inicio.
- **Buffer de píxeles** en memoria para minimizar llamadas a la API gráfica.
- Dibujo de **fondo**: primero cielos y suelos usando colores o gradientes simples.
- **Píxel a píxel**: cada columna se pinta directamente en el buffer con la sección adecuada de la textura.
- **Minilibx** se encarga de volcar el buffer a la ventana en pantalla.

---

## Parsing y validación de mapas

El parser de archivos `.cub` realiza:

1. **Lectura líne a línea** ignorando espacios y comentarios.
2. **Extracción de rutas** de texturas y colores de cielo/suelo (RGB).
3. **Construcción del mapa 2D**: matriz de caracteres con paredes (`1`), espacios (`0`) y spawn (`N/S/E/W`).
4. **Validación flood-fill**: comprueba que el mapa esté completamente cerrado por paredes.
5. **Gestión de errores**: mensaje detallado y salida controlada ante fallo de sintaxis o mapa inválido.

---

## Gestión de entrada y controles

- **Teclas configurables** para movimiento (W/A/S/D) y rotación (flechas).
- **Minilibx** notifica eventos de teclado y cierre de ventana.
- **Debounce** sencillo para evitar lecturas múltiples por pulsación prolongada.
- **Funciones callback**: cada evento invoca funciones en `input/` que actualizan el estado del jugador.

---

## Estructura de datos y utilidades

- **Vectores y matrices**: operaciones con vectores 2D para dirección y plano de cámara.
- **Funciones matemáticas**: conversión de grados a radianes, cálculo de distancias, normalización.
- **Gestión de memoria**: uso de malloc/free consistentemente y comprobación de errores.
- **Logging de errores**: macros para impresión de mensajes y exit en fallo crítico.

---

## Compilación y dependencias

Requisitos:

- Linux con **X11**.
- **gcc** o **clang**.
- **make**.

Para compilar:

```bash
make all   # Compila libft, minilibx y cub3d
```

Esto genera el ejecutable `cub3d` en la raíz.

---

## Despliegue y uso

```bash
./cub3d examples/mapa.cub
```

Parámetros opcionales:

- Resolución de ventana (`--width`, `--height`).
- Sensibilidad de giro de cámara.
- Toggle de FPS en pantalla.

---

## Pruebas y validación

- Mapas de ejemplo con variaciones de geometría.
- Colisiones en bordes y esquinas.
- Casos límite: texturas faltantes, colores fuera de rango.
- Uso de Valgrind para detectar fugas de memoria.

---

## Rendimiento y optimización

- **Buffer en memoria** para reducir overhead de dibujo por píxel.
- **DDA** rápido al evitar cálculos trigonométricos en bucle interno.
- **Compilación optimizada** con `-O2` en Makefile.
- Medido rendimiento estable en ~60 FPS en mapas de tamaño medio.

---

## Buenas prácticas de código

- Comentarios articulados en cada módulo.
- **Estilo 42**: 25 líneas máximo por función, indentación de 4 espacios.
- Modularidad: cada archivo `.c` emparejado con su `.h`.
- Uso de **libft** para funciones comunes y evitar código repetido.

---

## Contribuciones y roadmap

- Añadir sprites para objetos y enemigos.
- Implementar efecto de gravedad y saltos.
- Integrar minimapa 2D en HUD.
- Soporte para texturas PNG.

Para contribuir:
1. Abre un issue describiendo tu propuesta.
2. Haz un fork y crea tu rama (`feature/...`).
3. Envía un pull request revisado.

---

## Autor y contacto

- **jainavas** – <jainavas@student.42.fr>
- LinkedIn: Jaime Navascués Peña

---
