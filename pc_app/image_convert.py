"""Convierte cualquier imagen a 128x128 RGB565 (big-endian), listo para
enviar al HACK-PAD con IMG_START."""
from PIL import Image


def image_to_rgb565_bytes(path, size=128):
    img = Image.open(path).convert("RGB")

    # recorte centrado a cuadrado, luego resize
    w, h = img.size
    side = min(w, h)
    left = (w - side) // 2
    top = (h - side) // 2
    img = img.crop((left, top, left + side, top + side)).resize((size, size), Image.LANCZOS)

    out = bytearray()
    px = img.load()
    for y in range(size):
        for x in range(size):
            r, g, b = px[x, y]
            rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
            out.append((rgb565 >> 8) & 0xFF)  # big-endian: byte alto primero
            out.append(rgb565 & 0xFF)
    return bytes(out), img
