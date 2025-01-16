import tkinter as tk
from tkinter import messagebox


def run_selected_code(event=None):
    try:
        # Get selected text
        selected_text = text_box.get(tk.SEL_FIRST, tk.SEL_LAST)
        # Execute the selected code
        exec(selected_text, {})
    except tk.TclError:
        messagebox.showerror("Error", "No text selected!")
    except Exception as e:
        messagebox.showerror("Execution Error", f"An error occurred:\n{e}")


# Create the main application window
root = tk.Tk()
root.title("Simple Code Editor")

# Create a text box for code input
text_box = tk.Text(root, wrap="none", font=("Consolas", 12))
text_box.pack(fill="both", expand=True)

# Bind the shortcut Ctrl+R to execute code
root.bind("<Control-r>", run_selected_code)

# Start the main event loop
root.mainloop()
