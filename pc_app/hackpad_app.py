"""
HACK-PAD Companion App
-----------------------
Desktop app (Tkinter) to configure the HACK-PAD over USB:
- Main screen text / image
- Macros for the 4 keys
- Color of the 6 LEDs
- Extra minigames (run on the PC, separate from the pad's secret one)

Requirements: pip install -r requirements.txt
Run:          python hackpad_app.py
"""
import tkinter as tk
from tkinter import ttk, filedialog, colorchooser, messagebox
import subprocess
import sys
import os
import threading

from serial_link import HackPadLink, list_ports
from image_convert import image_to_rgb565_bytes

try:
    from PIL import ImageTk
except ImportError:
    ImageTk = None

APP_DIR = os.path.dirname(os.path.abspath(__file__))


class HackPadApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("HACK-PAD Companion")
        self.geometry("560x560")
        self.link = HackPadLink()

        self._build_connection_bar()

        notebook = ttk.Notebook(self)
        notebook.pack(fill="both", expand=True, padx=8, pady=8)

        self.tab_screen = ttk.Frame(notebook)
        self.tab_macros = ttk.Frame(notebook)
        self.tab_leds = ttk.Frame(notebook)
        self.tab_games = ttk.Frame(notebook)

        notebook.add(self.tab_screen, text="Screen")
        notebook.add(self.tab_macros, text="Macros")
        notebook.add(self.tab_leds, text="LEDs")
        notebook.add(self.tab_games, text="Extra games")

        self._build_screen_tab()
        self._build_macros_tab()
        self._build_leds_tab()
        self._build_games_tab()

    # -------------------------------------------------- connection
    def _build_connection_bar(self):
        bar = ttk.Frame(self)
        bar.pack(fill="x", padx=8, pady=8)

        ttk.Label(bar, text="Port:").pack(side="left")
        self.port_var = tk.StringVar()
        self.port_combo = ttk.Combobox(bar, textvariable=self.port_var, width=18, state="readonly")
        self.port_combo.pack(side="left", padx=4)
        self._refresh_ports()

        ttk.Button(bar, text="Refresh", command=self._refresh_ports).pack(side="left", padx=4)
        self.connect_btn = ttk.Button(bar, text="Connect", command=self._toggle_connect)
        self.connect_btn.pack(side="left", padx=4)

        self.status_lbl = ttk.Label(bar, text="Disconnected", foreground="red")
        self.status_lbl.pack(side="left", padx=12)

    def _refresh_ports(self):
        ports = list_ports()
        self.port_combo["values"] = ports
        if ports and not self.port_var.get():
            self.port_var.set(ports[0])

    def _toggle_connect(self):
        if self.link.is_connected():
            self.link.disconnect()
            self.status_lbl.config(text="Disconnected", foreground="red")
            self.connect_btn.config(text="Connect")
            return
        port = self.port_var.get()
        if not port:
            messagebox.showwarning("HACK-PAD", "Pick a port first.")
            return
        try:
            self.link.connect(port)
            reply = self.link.ping()
            if "OK" not in reply:
                raise RuntimeError(f"Unexpected reply: {reply}")
            self.status_lbl.config(text=f"Connected ({port})", foreground="green")
            self.connect_btn.config(text="Disconnect")
        except Exception as e:
            self.link.disconnect()
            messagebox.showerror("HACK-PAD", f"Could not connect:\n{e}")

    def _require_connection(self):
        if not self.link.is_connected():
            messagebox.showwarning("HACK-PAD", "Connect to the pad first.")
            return False
        return True

    # -------------------------------------------------- screen
    def _build_screen_tab(self):
        f = self.tab_screen
        ttk.Label(f, text="Main screen text:").pack(anchor="w", pady=(10, 2))
        self.text_var = tk.StringVar(value="HACK-PAD")
        entry = ttk.Entry(f, textvariable=self.text_var, width=40)
        entry.pack(anchor="w")
        ttk.Button(f, text="Send text", command=self._send_text).pack(anchor="w", pady=6)

        ttk.Separator(f, orient="horizontal").pack(fill="x", pady=10)

        ttk.Label(f, text="Custom image (auto-cropped/resized to 128x128):").pack(anchor="w")
        ttk.Button(f, text="Choose image and send...", command=self._send_image).pack(anchor="w", pady=6)
        self.preview_lbl = ttk.Label(f, text="(no image)")
        self.preview_lbl.pack(anchor="w", pady=6)

        note = ("Note: the image is drawn instantly but is NOT saved to the\n"
                "pad's internal memory (it's small, the board's RAM isn't\n"
                "enough for that). If the pad loses power, you'll need to\n"
                "resend it from here. Text and macros DO get saved with\n"
                "'Save to pad'.")
        ttk.Label(f, text=note, foreground="#888").pack(anchor="w", pady=10)

        ttk.Button(f, text="Save to pad (text/macros/colors)", command=self._save_to_device).pack(anchor="w", pady=10)

    def _send_text(self):
        if not self._require_connection():
            return
        reply = self.link.set_text(self.text_var.get())
        if "OK" not in reply:
            messagebox.showerror("HACK-PAD", f"Error: {reply}")

    def _send_image(self):
        if not self._require_connection():
            return
        path = filedialog.askopenfilename(filetypes=[("Images", "*.png *.jpg *.jpeg *.bmp *.gif")])
        if not path:
            return
        try:
            raw, pil_img = image_to_rgb565_bytes(path)
        except Exception as e:
            messagebox.showerror("HACK-PAD", f"Could not convert the image:\n{e}")
            return

        if ImageTk is not None:
            thumb = pil_img.copy()
            thumb.thumbnail((96, 96))
            self._preview_img = ImageTk.PhotoImage(thumb)
            self.preview_lbl.config(image=self._preview_img, text="")

        def worker():
            reply = self.link.send_image_rgb565(raw)
            if "OK" not in reply:
                self.after(0, lambda: messagebox.showerror("HACK-PAD", f"Error sending image: {reply}"))

        threading.Thread(target=worker, daemon=True).start()

    def _save_to_device(self):
        if not self._require_connection():
            return
        reply = self.link.save()
        if "OK" in reply:
            messagebox.showinfo("HACK-PAD", "Saved to the pad's memory.")
        else:
            messagebox.showerror("HACK-PAD", f"Error: {reply}")

    # -------------------------------------------------- macros
    MACRO_PRESETS = ["(free text)", "@COPY", "@PASTE", "@CUT", "@UNDO", "@REDO",
                      "@SAVE", "@SELECTALL", "@ALTTAB", "@ENTER", "@ESC", "@TAB"]

    def _build_macros_tab(self):
        f = self.tab_macros
        self.macro_vars = []
        self.macro_preset_vars = []

        ttk.Label(f, text="Assign an action to each of the 4 keys.").pack(anchor="w", pady=(10, 4))
        ttk.Label(f, text="Pick a preset shortcut, or leave '(free text)' and type\nwhatever you want the key to type out.", foreground="#888").pack(anchor="w")

        for i in range(4):
            row = ttk.Frame(f)
            row.pack(fill="x", pady=6)
            ttk.Label(row, text=f"Key {i+1}:", width=10).pack(side="left")

            preset_var = tk.StringVar(value="(free text)")
            preset_combo = ttk.Combobox(row, textvariable=preset_var, values=self.MACRO_PRESETS, width=14, state="readonly")
            preset_combo.pack(side="left", padx=4)
            self.macro_preset_vars.append(preset_var)

            text_var = tk.StringVar()
            entry = ttk.Entry(row, textvariable=text_var, width=24)
            entry.pack(side="left", padx=4)
            self.macro_vars.append(text_var)

        ttk.Button(f, text="Send macros to pad", command=self._send_macros).pack(anchor="w", pady=12)

    def _send_macros(self):
        if not self._require_connection():
            return
        for i in range(4):
            preset = self.macro_preset_vars[i].get()
            value = preset if preset != "(free text)" else self.macro_vars[i].get()
            if not value:
                continue
            reply = self.link.set_macro(i + 1, value)
            if "OK" not in reply:
                messagebox.showerror("HACK-PAD", f"Error on key {i+1}: {reply}")
                return
        messagebox.showinfo("HACK-PAD", "Macros sent. Don't forget 'Save to pad' to make them persist.")

    # -------------------------------------------------- LEDs
    def _build_leds_tab(self):
        f = self.tab_leds
        self.led_color = "#FF0050"

        ttk.Label(f, text="All 6 LEDs share the same data line on purpose,\nso they always move together.", foreground="#888").pack(anchor="w", pady=(10, 10))

        self.led_swatch = tk.Button(f, text="LED color", width=20, height=4,
                                     bg=self.led_color, command=self._pick_color)
        self.led_swatch.pack(pady=10)

        ttk.Label(f, text="Brightness:").pack(anchor="w", padx=10)
        self.brightness_var = tk.IntVar(value=80)
        ttk.Scale(f, from_=0, to=255, variable=self.brightness_var, orient="horizontal").pack(fill="x", padx=10)

        ttk.Button(f, text="Apply color + brightness to pad", command=self._send_leds).pack(pady=12)

    def _pick_color(self):
        color = colorchooser.askcolor(color=self.led_color)
        if color[1]:
            self.led_color = color[1]
            self.led_swatch.config(bg=color[1])

    def _send_leds(self):
        if not self._require_connection():
            return
        reply = self.link.set_color(self.led_color.lstrip("#"))
        if "OK" not in reply:
            messagebox.showerror("HACK-PAD", f"Color error: {reply}")
            return
        reply = self.link.set_brightness(self.brightness_var.get())
        if "OK" not in reply:
            messagebox.showerror("HACK-PAD", f"Brightness error: {reply}")
            return
        messagebox.showinfo("HACK-PAD", "Color applied. Don't forget 'Save to pad' to make it persist.")

    # -------------------------------------------------- extra minigames
    def _build_games_tab(self):
        f = self.tab_games
        ttk.Label(f, text="These minigames run on the PC (separate from the\nsecret one that lives inside the HACK-PAD itself).", foreground="#888").pack(anchor="w", pady=(10, 10))

        ttk.Button(f, text="🐍 Play Snake (PC)", command=lambda: self._launch_game("snake_game.py")).pack(anchor="w", pady=6)
        ttk.Button(f, text="🎨 Play Memory / Simon (PC)", command=lambda: self._launch_game("memory_game.py")).pack(anchor="w", pady=6)

        ttk.Label(f, text="Tip: the pad's secret minigame is triggered by holding\nall 4 keys down together for ~1.2 seconds.", foreground="#888").pack(anchor="w", pady=(20, 0))

    def _launch_game(self, script_name):
        path = os.path.join(APP_DIR, "games", script_name)
        subprocess.Popen([sys.executable, path])


if __name__ == "__main__":
    app = HackPadApp()
    app.mainloop()
