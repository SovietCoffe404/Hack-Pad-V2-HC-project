# Producción — HACK-PAD V2

Archivos listos para fabricación: PCB (Gerbers) y carcasa (STEP).

## Archivos

| Archivo | Tipo | Uso |
|---|---|---|
| `Hack_Pad-V2_Gerber.zip` | Gerber (PCB) | Fabricación de la placa |
| `3D_HACK-PAD_Body.step` | STEP | Impresión 3D / mecanizado — cuerpo |
| `3D_HACK-PAD_Top.step` | STEP | Impresión 3D / mecanizado — tapa superior |
| `3D_HACK-PAD_Battery_cover.step` | STEP | Impresión 3D / mecanizado — tapa de batería |

## PCB — `Hack_Pad-V2_Gerber.zip`

**Origen**: KiCad (Pcbnew 10.0.2)

| Parámetro | Valor |
|---|---|
| Dimensiones | 60.05 mm × 91.05 mm |
| Capas | 2 (F.Cu / B.Cu) |
| Espesor | 1.6 mm |
| Acabado superficial | No especificado |
| Pad-to-pad / Pad-to-track / Track-to-track | 0.2 mm |
| Ancho mínimo de pista | 0.2 mm |
| Revisión | `rev?` (sin asignar) |

**Contenido del zip:**
- `*-F_Cu.gbr` / `*-B_Cu.gbr` — cobre top/bottom
- `*-F_Mask.gbr` / `*-B_Mask.gbr` — máscara de soldadura
- `*-F_Paste.gbr` / `*-B_Paste.gbr` — pasta de soldadura (stencil)
- `*-F_Silkscreen.gbr` / `*-B_Silkscreen.gbr` — serigrafía
- `*-Edge_Cuts.gbr` — contorno de la placa
- `*-PTH.drl` / `*-NPTH.drl` — taladros pasantes y no pasantes
- `*-job.gbrjob` — metadata del trabajo (formato KiCad)

**Para fabricar:** subir el `.zip` completo tal cual al fabricante (JLCPCB, PCBWay, OSH Park, etc.); la mayoría detecta el formato KiCad automáticamente.

⚠️ Antes de producción en volumen, asignar un número de revisión real (actualmente `rev?`) y confirmar acabado superficial (HASL, ENIG, etc.) con el fabricante.

## Carcasa — archivos STEP

Formato STEP (AP214), editable en cualquier CAD (FreeCAD, Fusion 360, SolidWorks, etc.) y compatible con la mayoría de slicers tras exportar a STL.

| Pieza | Archivo | Notas |
|---|---|---|
| Cuerpo principal | `3D_HACK-PAD_Body.step` | Aloja la PCB |
| Tapa superior | `3D_HACK-PAD_Top.step` | Cierre superior |
| Tapa de batería | `3D_HACK-PAD_Battery_cover.step` | Compartimento de batería |

**Para fabricar:** abrir en CAD → exportar a `.stl` → ajustar tolerancias según impresora/material → imprimir. Si se mecaniza, verificar tolerancias de ensamble contra las dimensiones reales de la PCB (60.05 × 91.05 mm).
