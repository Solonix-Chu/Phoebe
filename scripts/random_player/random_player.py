import tkinter as tk
from tkinter import filedialog, messagebox
import os
import subprocess
import random

def select_folder():
    folder_selected = filedialog.askdirectory()
    if folder_selected:
        folder_path.set(folder_selected)

def play_videos():
    folder = folder_path.get()
    if not folder:
        messagebox.showerror("Error", "Please select a folder.")
        return

    # Generate a list of video files in the selected folder
    video_files = []
    for root, _, files in os.walk(folder):
        for file in files:
            if file.lower().endswith(('.mp4', '.mkv', '.avi', '.mov', '.flv')):
                video_files.append(os.path.join(root, file))
    
    if not video_files:
        messagebox.showerror("Error", "No video files found in the selected folder.")
        return
    
    # Shuffle the list of video files
    random.shuffle(video_files)

    # Play videos using VLC
    for video in video_files:
        subprocess.run(["vlc", "-f", video])

# Create the main window
root = tk.Tk()
root.title("Random Video Player")

# Set window size
root.geometry("800x480")

# Create a StringVar to store the folder path
folder_path = tk.StringVar()

# Create and place widgets
tk.Label(root, text="Select a folder with videos:").pack(pady=10)
tk.Entry(root, textvariable=folder_path, width=50).pack(pady=5)
tk.Button(root, text="Browse", command=select_folder).pack(pady=5)
tk.Button(root, text="Play Videos", command=play_videos).pack(pady=20)

# Run the application
root.mainloop()
