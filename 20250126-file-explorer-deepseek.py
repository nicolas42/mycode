import os
import pygame
import subprocess
import platform
from pygame.locals import *

# Initialize Pygame
pygame.init()

# Constants
INITIAL_WIDTH, INITIAL_HEIGHT = 800, 600
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
ROW_HEIGHT = 30
FONT_SIZE = 24

# Setup display
screen = pygame.display.set_mode((INITIAL_WIDTH, INITIAL_HEIGHT), pygame.RESIZABLE)
pygame.display.set_caption("File Explorer with Execution")
font = pygame.font.SysFont(None, FONT_SIZE)
clock = pygame.time.Clock()

# Global variables for window size
current_width, current_height = INITIAL_WIDTH, INITIAL_HEIGHT

def get_file_list(path):
    """Get sorted list of directories and files with their types"""
    items = []
    try:
        for item in os.listdir(path):
            full_path = os.path.join(path, item)
            if os.path.isdir(full_path):
                items.append(('📁', item, 'folder'))
            else:
                items.append(('📄', item, 'file'))
        # Sort directories first
        items.sort(key=lambda x: (x[2] == 'file', x[1].lower()))
    except PermissionError:
        pass
    return items

def draw_file_list(items, scroll_offset, current_path):
    screen.fill(WHITE)
    
    # Draw current path
    path_text = font.render(current_path, True, BLACK)
    screen.blit(path_text, (10, 10))
    
    # Draw back button
    back_rect = pygame.Rect(10, 50, 100, ROW_HEIGHT)
    pygame.draw.rect(screen, BLUE, back_rect)
    back_text = font.render(".. (Up)", True, WHITE)
    screen.blit(back_text, (15, 55))
    
    # Calculate visible rows based on current window height
    visible_rows = (current_height - 100) // ROW_HEIGHT
    
    # Draw files and folders
    for i, (icon, name, type_) in enumerate(items):
        y_pos = 90 + (i - scroll_offset) * ROW_HEIGHT
        if 90 <= y_pos < current_height - ROW_HEIGHT:
            # Draw icon
            icon_text = font.render(icon, True, BLACK)
            screen.blit(icon_text, (10, y_pos))
            
            # Draw name
            name_text = font.render(name, True, BLACK)
            screen.blit(name_text, (50, y_pos))
            
            # Highlight selection
            if pygame.Rect(0, y_pos, current_width, ROW_HEIGHT).collidepoint(pygame.mouse.get_pos()):
                pygame.draw.rect(screen, (200, 200, 200), (0, y_pos, current_width, ROW_HEIGHT))

def open_file(path):
    """Open file with default application"""
    try:
        if platform.system() == 'Windows':
            os.startfile(path)
        elif platform.system() == 'Darwin':  # macOS
            subprocess.run(['open', path])
        else:  # Linux and others
            subprocess.run(['xdg-open', path])
    except Exception as e:
        print(f"Error opening file: {e}")

def main():
    global current_width, current_height
    current_path = os.path.expanduser('~')
    scroll_offset = 0
    running = True

    while running:
        items = get_file_list(current_path)
        draw_file_list(items, scroll_offset, current_path)
        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == QUIT:
                running = False
                
            if event.type == VIDEORESIZE:
                # Update window dimensions
                current_width, current_height = event.w, event.h
                screen = pygame.display.set_mode((current_width, current_height), pygame.RESIZABLE)
                
            if event.type == MOUSEBUTTONDOWN:
                if event.button == 1:  # Only handle left click
                    x, y = event.pos
                    
                    # Check back button
                    if 10 <= x <= 110 and 50 <= y <= 80:
                        new_path = os.path.dirname(current_path)
                        if os.path.exists(new_path):
                            current_path = new_path
                            scroll_offset = 0
                    
                    # Check file list items
                    for i, (_, name, type_) in enumerate(items):
                        item_y = 90 + (i - scroll_offset) * ROW_HEIGHT
                        if item_y <= y < item_y + ROW_HEIGHT:
                            full_path = os.path.join(current_path, name)
                            if type_ == 'folder':
                                current_path = full_path
                                scroll_offset = 0
                            else:
                                print(f"Opening file: {full_path}")
                                open_file(full_path)
            
            if event.type == MOUSEWHEEL:
                # Calculate maximum scroll offset based on current window height
                max_scroll = max(0, len(items) - ((current_height - 100) // ROW_HEIGHT))
                scroll_offset = max(0, min(scroll_offset - event.y, max_scroll))

        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()
