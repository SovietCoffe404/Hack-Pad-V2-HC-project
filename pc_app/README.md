# pc_app/

App de escritorio en Python (Tkinter) para configurar el HACK-PAD por USB.

## Estructura

| Archivo | Qué hace |
|---|---|
| `hackpad_app.py` | App principal — pestañas Pantalla / Macros / LEDs / Minijuegos extra |
| `serial_link.py` | Comunicación por USB con el pad (protocolo de `firmware/`) |
| `image_convert.py` | Convierte cualquier imagen a RGB565 128x128 |
| `games/snake_game.py` | Snake extra, jugado con el teclado de la PC |
| `games/memory_game.py` | Simon Says temático, jugado con el mouse |
| `requirements.txt` | Dependencias |

## Uso

```bash
cd pc_app
pip install -r requirements.txt
python hackpad_app.py
```

1. Conectá el pad por USB, elegí el puerto en la app (es el mismo que
   usaste para subir el firmware) y dale **Conectar**.
2. **Pantalla**: texto personalizable, o subí una imagen (se recorta y
   escala sola a 128x128).
3. **Macros**: qué hace cada una de las 4 teclas — atajos predefinidos o
   texto libre.
4. **LEDs**: un solo color (los 6 LEDs van todos iguales, por diseño de
   hardware) + brillo.
5. **Minijuegos extra**: lanza Snake o Memory, corren en la PC (aparte del
   minijuego secreto que vive dentro del propio pad).

**Importante**: "Guardar en el pad" es lo que hace que texto/macros/color
sobrevivan sin la PC conectada. Sin ese paso se pierden al desconectar
(la imagen nunca se guarda en el pad, ver `firmware/README.md`).
