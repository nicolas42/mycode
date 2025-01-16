import tkinter as tk
from tkinter import filedialog, messagebox
import os
import fnmatch

class FileFinderGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Simple File Finder")

        # Frame for the pattern and directory input
        frame_input = tk.Frame(root)
        frame_input.pack(padx=10, pady=5, fill=tk.X)

        # Pattern label + entry
        tk.Label(frame_input, text="Pattern (e.g. *.txt):").pack(side=tk.LEFT)
        self.pattern_entry = tk.Entry(frame_input, width=15)
        self.pattern_entry.pack(side=tk.LEFT, padx=5)
        self.pattern_entry.insert(0, "*.txt")  # default

        # Directory label + entry
        tk.Label(frame_input, text="Directory:").pack(side=tk.LEFT)
        self.dir_entry = tk.Entry(frame_input, width=30)
        self.dir_entry.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)
        
        # Button to browse for directory
        browse_btn = tk.Button(frame_input, text="Browse...", command=self.browse_directory)
        browse_btn.pack(side=tk.LEFT, padx=5)

        # Frame for the search button
        frame_buttons = tk.Frame(root)
        frame_buttons.pack(padx=10, pady=5)
        
        # Search button
        search_btn = tk.Button(frame_buttons, text="Search", command=self.perform_search)
        search_btn.pack(side=tk.LEFT, padx=10)

        # Quit button
        quit_btn = tk.Button(frame_buttons, text="Quit", command=root.quit)
        quit_btn.pack(side=tk.LEFT, padx=10)

        # Frame for the results listbox + scrollbar
        frame_results = tk.Frame(root)
        frame_results.pack(padx=10, pady=5, fill=tk.BOTH, expand=True)

        # Scrollbar
        scrollbar = tk.Scrollbar(frame_results)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        # Results listbox
        self.results_list = tk.Listbox(frame_results, height=15, width=80)
        self.results_list.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.results_list.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=self.results_list.yview)

    def browse_directory(self):
        """Open a dialog to select a directory and place it in the dir_entry."""
        directory = filedialog.askdirectory()
        if directory:
            self.dir_entry.delete(0, tk.END)
            self.dir_entry.insert(0, directory)

    def perform_search(self):
        """Recursively search the given directory for files matching the pattern."""
        pattern = self.pattern_entry.get().strip()
        directory = self.dir_entry.get().strip()

        # Clear old results
        self.results_list.delete(0, tk.END)

        if not pattern:
            messagebox.showwarning("Warning", "Please enter a file pattern to search (e.g. *.txt).")
            return

        if not directory or not os.path.isdir(directory):
            messagebox.showwarning("Warning", "Please select a valid directory.")
            return

        # Perform recursive search
        matches_found = 0
        for root_dir, dirs, files in os.walk(directory):
            for filename in files:
                if fnmatch.fnmatch(filename, pattern):
                    full_path = os.path.join(root_dir, filename)
                    self.results_list.insert(tk.END, full_path)
                    matches_found += 1

        if matches_found == 0:
            messagebox.showinfo("No Matches", f"No files matching '{pattern}' found in '{directory}'.")

def main():
    root = tk.Tk()
    app = FileFinderGUI(root)
    root.mainloop()

if __name__ == "__main__":
    main()
