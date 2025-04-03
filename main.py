import win32pipe, win32file, tkinter as tk, threading
from tkinter import ttk

PIPE_NAME = r'\\.\pipe\dxhr'

EXITTING = 1
CHEAT_INVINCIBILITY = 2
CHEAT_INFINITE_AMMO = 3
CHEAT_NO_ENERGY_COST = 4
CHEAT_KIT_OUT_CURRENT_GUN = 5
CHEAT_SILENCER = 6
CHEAT_LASER_SIGHT = 7
CHEAT_DAMAGE = 8
CHEAT_RATE_OF_FIRE = 9

def itob(number: int) -> bytes:

	return number.to_bytes(4, byteorder='little', signed=True)

def sendCommand(pipe, command: int) -> None:

	msg = itob(command)

	win32file.WriteFile(pipe, msg)

def clientConnected(pipe) -> None:
	label.destroy()

	invincibility = tk.IntVar()
	infiniteAmmo = tk.IntVar()
	noEnergyCost = tk.IntVar()

	frame = ttk.Frame(root, padding=10)
	frame.grid(row=0, column=0)

	ttk.Label(frame, text="Cheat Options", font=('Arial', 12)).grid(row=0, column=0, pady=5)

	ttk.Checkbutton(frame, text="Invincibility",variable=invincibility, command=lambda: sendCommand(pipe, CHEAT_INVINCIBILITY)).grid(row=1, column=0, pady=5)

	ttk.Checkbutton(frame, text="Infinite Ammo", variable=infiniteAmmo, command=lambda: sendCommand(pipe, CHEAT_INFINITE_AMMO)).grid(row=2, column=0, pady=5)

	ttk.Checkbutton(frame, text="No Energy Cost", variable=noEnergyCost, command=lambda: sendCommand(pipe, CHEAT_NO_ENERGY_COST)).grid(row=3, column=0, pady=5)

	ttk.Button(frame, text="Kit Out Current Gun", command=lambda: sendCommand(pipe, CHEAT_KIT_OUT_CURRENT_GUN)).grid(row=4, column=0, pady=5)

	ttk.Button(frame, text="Attach Silencer To Current Gun", command=lambda: sendCommand(pipe, CHEAT_SILENCER)).grid(row=5, column=0, pady=5)

	ttk.Button(frame, text="Attach Laser Sight To Current Gun", command=lambda: sendCommand(pipe, CHEAT_LASER_SIGHT)).grid(row=6, column=0, pady=5)

	ttk.Button(frame, text="Max Out Damage Of Current Gun", command=lambda: sendCommand(pipe, CHEAT_DAMAGE)).grid(row=7, column=0, pady=5)

	ttk.Button(frame, text="Max Out Rate Of Fire (ROF) Of Current Gun", command=lambda: sendCommand(pipe, CHEAT_RATE_OF_FIRE)).grid(row=8, column=0, pady=5)

def waitForClient() -> None:

	pipe = win32pipe.CreateNamedPipe(
		PIPE_NAME,
		win32pipe.PIPE_ACCESS_DUPLEX,
		win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_WAIT,
		1, 65536, 65536, 0, None
	)

	win32pipe.ConnectNamedPipe(pipe, None)

	root.after(0, clientConnected, pipe)

if __name__ == "__main__":

	pipe_thread = threading.Thread(target=waitForClient, daemon=True)
	pipe_thread.start()

	root = tk.Tk()
	root.title("DXHR Menu")

	label = ttk.Label(root, text="Waiting for client...", font=('Arial', 12))
	label.pack(pady=10)

	root.mainloop()
