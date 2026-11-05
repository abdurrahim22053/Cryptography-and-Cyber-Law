#!/usr/bin/env python3
"""Tkinter live event visualizer for the C OSI simulation client."""
import subprocess
import threading
import queue
import tkinter as tk
from tkinter import ttk, messagebox

LAYERS = [
    ("7", "Application", "User message"),
    ("6", "Presentation", "UTF-8 representation"),
    ("5", "Session", "Session management"),
    ("4", "Transport", "TCP reliable stream"),
    ("3", "Network", "IP routing concept"),
    ("2", "Data Link", "Frame / local delivery"),
    ("1", "Physical", "Bits over socket"),
]

class OSIVisualizer:
    def __init__(self, root):
        self.root = root
        root.title("OSI Layer Simulation – Live Dashboard")
        root.geometry("1080x760")
        root.minsize(900, 650)
        self.events = queue.Queue()
        self.busy = False
        self.layer_items = {}
        self._build()
        self.root.after(100, self._poll)

    def _build(self):
        top = ttk.Frame(self.root, padding=12)
        top.pack(fill="x")
        ttk.Label(top, text="OSI Layer Simulation", font=("TkDefaultFont", 20, "bold")).pack(anchor="w")
        ttk.Label(top, text="C TCP Client/Server • Python visualization • Seven-layer encapsulation/decapsulation").pack(anchor="w", pady=(3, 10))
        controls = ttk.Frame(top)
        controls.pack(fill="x")
        ttk.Label(controls, text="Server IP").grid(row=0, column=0, sticky="w")
        self.host = tk.StringVar(value="127.0.0.1")
        ttk.Entry(controls, textvariable=self.host, width=18).grid(row=0, column=1, padx=6)
        ttk.Label(controls, text="Port").grid(row=0, column=2, sticky="w")
        self.port = tk.StringVar(value="5050")
        ttk.Entry(controls, textvariable=self.port, width=8).grid(row=0, column=3, padx=6)
        ttk.Label(controls, text="Message").grid(row=0, column=4, sticky="w")
        self.message = tk.StringVar(value="Hello Server! OSI simulation test.")
        ttk.Entry(controls, textvariable=self.message, width=42).grid(row=0, column=5, padx=6)
        self.send_button = ttk.Button(controls, text="Send through OSI", command=self.send)
        self.send_button.grid(row=0, column=6, padx=6)

        body = ttk.Panedwindow(self.root, orient="horizontal")
        body.pack(fill="both", expand=True, padx=12, pady=8)
        left = ttk.Frame(body, padding=8)
        right = ttk.Frame(body, padding=8)
        body.add(left, weight=2)
        body.add(right, weight=3)
        ttk.Label(left, text="Zig-Zag OSI Data Flow", font=("TkDefaultFont", 14, "bold")).pack(anchor="w")
        self.canvas = tk.Canvas(left, height=510, background="#f7f8fa", highlightthickness=1, highlightbackground="#d0d0d0")
        self.canvas.pack(fill="both", expand=True, pady=8)
        self._draw_layers()
        ttk.Label(right, text="Live Event Log", font=("TkDefaultFont", 14, "bold")).pack(anchor="w")
        self.log = tk.Text(right, wrap="word", height=25, state="disabled", font=("TkFixedFont", 9))
        self.log.pack(fill="both", expand=True, pady=8)
        self.progress = ttk.Progressbar(right, maximum=7, mode="determinate")
        self.progress.pack(fill="x")
        self.progress_text = ttk.Label(right, text="Ready • 0/7 layers")
        self.progress_text.pack(anchor="w", pady=5)
        bottom = ttk.Frame(self.root, padding=12)
        bottom.pack(fill="x")
        ttk.Label(bottom, text="Educational simulation: OSI wrappers run in user space; actual network transfer uses TCP/IP sockets.", wraplength=1000).pack(anchor="w")

    def _draw_layers(self):
        self.canvas.delete("all")
        w = max(self.canvas.winfo_width(), 430)
        self.canvas.configure(scrollregion=(0, 0, w, 530))
        x_left, x_right = 22, w - 22
        for i, (num, name, desc) in enumerate(LAYERS):
            y = 18 + i * 68
            x1, x2 = (x_left, x_left + 170) if i % 2 == 0 else (x_right - 170, x_right)
            rect = self.canvas.create_rectangle(x1, y, x2, y + 48, fill="#e8eef7", outline="#536b8c", width=2)
            text = self.canvas.create_text((x1+x2)//2, y+15, text=f"L{num} • {name}", font=("TkDefaultFont", 10, "bold"))
            sub = self.canvas.create_text((x1+x2)//2, y+33, text=desc, font=("TkDefaultFont", 8))
            self.layer_items[num] = (rect, text, sub)
            if i < 6:
                next_y = y + 48
                if i % 2 == 0:
                    self.canvas.create_line(x2, next_y, x_right-170, next_y+18, arrow=tk.LAST, fill="#7b8794", width=2)
                else:
                    self.canvas.create_line(x1, next_y, x_left+170, next_y+18, arrow=tk.LAST, fill="#7b8794", width=2)
        self.canvas.create_text(w//2, 500, text="↓ REAL TCP SOCKET TRANSFER ↓", font=("TkDefaultFont", 10, "bold"), fill="#145a32")

    def _log(self, line):
        self.log.configure(state="normal")
        self.log.insert("end", line + "\n")
        self.log.see("end")
        self.log.configure(state="disabled")

    def _reset(self):
        self.progress["value"] = 0
        self.progress_text.configure(text="Ready • 0/7 layers")
        self.log.configure(state="normal")
        self.log.delete("1.0", "end")
        self.log.configure(state="disabled")
        for num, items in self.layer_items.items():
            self.canvas.itemconfigure(items[0], fill="#e8eef7")

    def send(self):
        if self.busy:
            return
        msg, host, port = self.message.get(), self.host.get().strip(), self.port.get().strip()
        if not msg.strip():
            messagebox.showwarning("Missing message", "Please enter a message.")
            return
        if not port.isdigit() or not 1 <= int(port) <= 65535:
            messagebox.showwarning("Invalid port", "Port must be between 1 and 65535.")
            return
        self._reset()
        self.busy = True
        self.send_button.configure(state="disabled")
        self._log("Starting C client: encapsulation begins...")
        threading.Thread(target=self._run_client, args=(host, port, msg), daemon=True).start()

    def _run_client(self, host, port, msg):
        try:
            proc = subprocess.Popen(["./osi_client", host, port, msg], stdout=subprocess.PIPE,
                                    stderr=subprocess.STDOUT, text=True, bufsize=1)
            for line in proc.stdout:
                self.events.put(("line", line.rstrip()))
            code = proc.wait()
            self.events.put(("done", code))
        except Exception as exc:
            self.events.put(("line", f"[GUI][ERROR] {exc}"))
            self.events.put(("done", 1))

    def _poll(self):
        try:
            while True:
                kind, value = self.events.get_nowait()
                if kind == "line":
                    self._log(value)
                    if "[PROGRESS]" in value:
                        try:
                            count = int(value.split("]")[2].split("/")[0].strip())
                            self.progress["value"] = count
                            self.progress_text.configure(text=f"Progress • {count}/7 layers completed")
                        except (ValueError, IndexError):
                            pass
                    if "[L" in value and "CLIENT" in value:
                        try:
                            num = value.split("[L")[1].split("]")[0]
                            if num in self.layer_items:
                                self.canvas.itemconfigure(self.layer_items[num][0], fill="#c9f2d5")
                        except IndexError:
                            pass
                elif kind == "done":
                    self.busy = False
                    self.send_button.configure(state="normal")
                    if value == 0:
                        self._log("GUI status: transfer completed successfully.")
                        self.progress_text.configure(text="Completed • 7/7 layers")
                    else:
                        self._log("GUI status: failed. Check server terminal and host/port.")
        except queue.Empty:
            pass
        self.root.after(100, self._poll)

if __name__ == "__main__":
    root = tk.Tk()
    app = OSIVisualizer(root)
    root.mainloop()
