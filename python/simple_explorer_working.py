import os
import tkinter as tk
from tkinter import filedialog, Listbox, Entry, Button, Scrollbar

def list_files(directory):
    with os.scandir(directory) as entries:
        return [(entry.name, entry.is_file()) for entry in entries]

def execute_file(file_path):
    # if file_path.endswith(('.exe', '.bat', '.cmd')):
    os.startfile(file_path)

root = tk.Tk()
root.title("Simple Explorer")
root.geometry("400x400")

input_dir = Entry(root)
input_dir.pack(fill=tk.X, padx=10, pady=5)

listbox = Listbox(root)
listbox.pack(fill=tk.BOTH, expand=1, padx=10, pady=5)

scrollbar = Scrollbar(root)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

listbox.config(yscrollcommand=scrollbar.set)
scrollbar.config(command=listbox.yview)

def on_enter_press(event=None):
    selected = listbox.get(listbox.curselection())
    path = os.path.join(current_directory, selected)
    if os.path.isdir(path):
        input_dir.delete(0, tk.END)
        input_dir.insert(0, path)
        refresh_files()
    else:
        execute_file(path)

def on_alt_left(event=None):
    global current_directory
    current_directory = os.path.dirname(current_directory)
    input_dir.delete(0, tk.END)
    input_dir.insert(0, current_directory)
    refresh_files()

def refresh_files(event=None):
    global current_directory
    listbox.delete(0, tk.END)
    path = input_dir.get()

    if os.path.exists(path) and os.path.isdir(path):
        current_directory = path
        for name, is_file in list_files(path):
            listbox.insert(tk.END, name)


def select_address_bar(event=None):
    input_dir.focus()
    input_dir.select_range(0, tk.END)



if __name__ == "__main__":
    root.bind('<Alt-d>', select_address_bar)
    root.bind('<Control-l>', select_address_bar)

    listbox.bind('<Return>', on_enter_press)
    listbox.bind('<Alt-Left>', on_alt_left)
    input_dir.bind('<Return>', refresh_files)

    # Initialize current directory to user's home directory
    current_directory = os.path.expanduser("~")
    input_dir.insert(0, current_directory)
    refresh_files()

    root.mainloop()
