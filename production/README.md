# HACK-PAD V2

Mini teclado / pad "hackeable" open hardware. Incluye el diseño de PCB (Gerbers, listo para fabricar) y los archivos 3D de la carcasa (STEP, listos para imprimir o mecanizar).

## Contenido del repo

```
├── Hack_Pad-V2_Gerber.zip        # Archivos de fabricación de la PCB (Gerber + taladros)
├── 3D_HACK-PAD_Body.step         # Carcasa / cuerpo principal
├── 3D_HACK-PAD_Top.step          # Tapa superior
└── 3D_HACK-PAD_Battery_cover.step # Tapa de la batería
```

## PCB

- **Software**: KiCad (Pcbnew 10.0.2)
- **Capas**: 2 (F.Cu / B.Cu)
- **Dimensiones**: 60.05 mm × 91.05 mm
- **Espesor**: 1.6 mm
- **Acabado**: sin especificar (None)

Archivos Gerber incluidos: cobre top/bottom, máscara de soldadura, pasta de soldadura, serigrafía, contorno de la placa (Edge Cuts) y taladros (PTH/NPTH). Listos para subir directamente a un fabricante de PCBs (JLCPCB, PCBWay, etc.).

## Carcasa 3D

Tres piezas en formato STEP (editable en cualquier CAD: FreeCAD, Fusion 360, SolidWorks, etc.):

- **Body**: cuerpo principal, aloja la PCB.
- **Top**: tapa superior.
- **Battery cover**: tapa para el compartimento de la batería.

Listas para exportar a STL e imprimir en 3D, o mecanizar según el material deseado.

## Fabricación rápida

1. **PCB**: descomprime `Hack_Pad-V2_Gerber.zip` y súbelo tal cual al fabricador de tu preferencia.
2. **Carcasa**: abre los `.step` en tu software de CAD, ajusta tolerancias si tu impresora lo requiere, exporta a `.stl` e imprime.

## Notas

- Revisión de la placa: sin definir (`rev?`) — se recomienda asignar un número de revisión antes de producción en volumen.
- No se incluyen aquí el esquemático, BOM ni firmware; si existen, agrégalos en carpetas separadas (`/hardware`, `/firmware`, `/docs`) para completar el repo.
