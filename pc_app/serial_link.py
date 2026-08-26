"""
Serial communication with the HACK-PAD.
Text protocol (see firmware/src/serial_protocol.cpp) plus raw binary
transfer for images (IMG_START + 128*128*2 bytes RGB565).
"""
import serial
import serial.tools.list_ports
import time

BAUD = 115200
SCREEN_W = 128
SCREEN_H = 128


def list_ports():
    return [p.device for p in serial.tools.list_ports.comports()]


class HackPadLink:
    def __init__(self):
        self.ser = None

    def is_connected(self):
        return self.ser is not None and self.ser.is_open

    def connect(self, port):
        self.ser = serial.Serial(port, BAUD, timeout=2)
        time.sleep(2)  # the board resets when the USB CDC port is opened
        self.ser.reset_input_buffer()

    def disconnect(self):
        if self.ser:
            self.ser.close()
        self.ser = None

    def _send_line(self, line):
        self.ser.write((line + "\n").encode("utf-8"))
        return self.ser.readline().decode("utf-8", errors="replace").strip()

    def ping(self):
        return self._send_line("PING")

    def set_text(self, text):
        return self._send_line(f"SET_TEXT {text}")

    def set_macro(self, index_1to4, value):
        return self._send_line(f"SET_MACRO {index_1to4} {value}")

    def set_color(self, hex_rrggbb):
        return self._send_line(f"SET_COLOR {hex_rrggbb}")

    def set_brightness(self, value_0to255):
        return self._send_line(f"SET_BRIGHTNESS {value_0to255}")

    def save(self):
        return self._send_line("SAVE")

    def get_config(self):
        self.ser.write(b"GET_CONFIG\n")
        lines = []
        while True:
            line = self.ser.readline().decode("utf-8", errors="replace").strip()
            if not line or line == "OK":
                break
            lines.append(line)
        return lines

    def send_image_rgb565(self, rgb565_bytes):
        """rgb565_bytes must be exactly 128*128*2 = 32768 bytes long,
        row by row, big-endian per pixel."""
        assert len(rgb565_bytes) == SCREEN_W * SCREEN_H * 2
        self.ser.write(b"IMG_START\n")
        self.ser.write(rgb565_bytes)
        return self.ser.readline().decode("utf-8", errors="replace").strip()
