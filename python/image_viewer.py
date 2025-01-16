import pygame
import sys
import os

class ImageDisplay:

    def __init__(self, directory_path, width=800, height=600):
        pygame.init()

        self.screen = pygame.display.set_mode((width, height), pygame.RESIZABLE)
        pygame.display.set_caption('Image Display')

        self.supported_formats = (".png", ".jpg", ".jpeg", ".gif", ".bmp", ".tiff")
        self.images = self.get_image_files_recursively(directory_path)
        
        if not self.images:
            print("No images found in the provided directory.")
            sys.exit()

        self.current_image_index = 0
        self.image = pygame.image.load(self.images[self.current_image_index])
        pygame.display.set_caption(self.images[self.current_image_index])

        self.zoom_scale = 1.0  # Initial zoom scale
        self.image_offset = [0, 0]  # Offset for panning the image
        self.full_size = True
        self.display_image()
        pygame.display.flip()
        self.run()

    def get_image_files_recursively(self, directory):
        image_files = []
        for root, _, files in os.walk(directory):
            for file in files:
                if file.lower().endswith(self.supported_formats):
                    image_files.append(os.path.join(root, file))
        return image_files

    def run(self):
        clock = pygame.time.Clock()

        key_repeat_delay = 500  # Time in milliseconds before a held key repeats
        key_repeat_interval = 50  # Time in milliseconds between repeats when holding a key
        pygame.key.set_repeat(key_repeat_delay, key_repeat_interval)

        # Enable DROPFILE events
        pygame.event.set_allowed([pygame.QUIT, pygame.KEYDOWN, pygame.KEYUP, pygame.MOUSEWHEEL, pygame.VIDEORESIZE, pygame.DROPFILE])

        while True:
            self.update_needed = False

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_RETURN or event.key == pygame.K_f:
                        self.toggle_full_size()
                        self.update_needed = True
                    if event.key == pygame.K_ESCAPE:
                        self.toggle_full_size()
                        self.update_needed = True
                        # pygame.quit()
                        # sys.exit()

                    elif event.key == pygame.K_RIGHT or event.key == pygame.K_j:
                        self.next_image()
                        self.update_needed = True
                    elif event.key == pygame.K_LEFT or event.key == pygame.K_k:
                        self.prev_image()
                        self.update_needed = True

                elif event.type == pygame.VIDEORESIZE:
                    # Handle window resizing
                    self.screen = pygame.display.set_mode((event.w, event.h), pygame.RESIZABLE)
                    self.update_needed = True

                # Handle mouse wheel scroll for zooming when "super" key is held down
                elif event.type == pygame.MOUSEWHEEL:
                    keys = pygame.key.get_pressed()
                    if keys[pygame.K_LSUPER] or keys[pygame.K_RSUPER]:
                        if event.y > 0:  # Scroll up to zoom in
                            self.zoom_scale /= 1.1
                        elif event.y < 0:  # Scroll down to zoom out
                            self.zoom_scale *= 1.1
                        self.update_needed = True
                    else:
                        # Normal panning behavior without "super" key
                        self.image_offset[0] -= event.x * 20  # Scroll left/right
                        self.image_offset[1] += event.y * 20  # Scroll up/down
                        self.update_needed = True

                elif event.type == pygame.DROPFILE:
                    dropped_file = event.file
                    if os.path.isdir(dropped_file):
                        # User dropped a directory
                        self.images = self.get_image_files_recursively(dropped_file)
                        if not self.images:
                            print("No images found in the provided directory.")
                            continue
                        self.current_image_index = 0
                        self.image = pygame.image.load(self.images[self.current_image_index])
                        pygame.display.set_caption(self.images[self.current_image_index])

                        self.zoom_scale = 1.0
                        self.image_offset = [0, 0]
                        self.update_needed = True
                    elif os.path.isfile(dropped_file):
                        # User dropped a file
                        if dropped_file.lower().endswith(self.supported_formats):
                            self.images = [dropped_file]
                            self.current_image_index = 0
                            self.image = pygame.image.load(self.images[self.current_image_index])
                            pygame.display.set_caption(self.images[self.current_image_index])
                            self.zoom_scale = 1.0
                            self.image_offset = [0, 0]
                            self.update_needed = True
                        else:
                            print("Unsupported file type.")

            if self.update_needed:
                self.display_image()
                pygame.display.flip()

            clock.tick(60)  # Limit the frame rate to 60 FPS

    def display_image(self):
        screen_rect = self.screen.get_rect()
        img_rect = self.image.get_rect()

        if self.full_size:
            # Display at full size with zoom
            scaled_width = int(img_rect.width * self.zoom_scale)
            scaled_height = int(img_rect.height * self.zoom_scale)
            scaled_image = pygame.transform.scale(self.image, (scaled_width, scaled_height))
            img_rect = scaled_image.get_rect()
        else:
            # Fit image to screen with zoom
            scaling_factor = min(screen_rect.width / img_rect.width, screen_rect.height / img_rect.height)
            scaled_width = int(img_rect.width * scaling_factor * self.zoom_scale)
            scaled_height = int(img_rect.height * scaling_factor * self.zoom_scale)
            scaled_image = pygame.transform.scale(self.image, (scaled_width, scaled_height))
            img_rect = scaled_image.get_rect()

        # Apply the panning offset
        x0 = int(screen_rect.w / 2 - img_rect.w / 2)
        y0 = int(screen_rect.h / 2 - img_rect.h / 2)
        img_rect.topleft = (x0 + self.image_offset[0], y0 + self.image_offset[1])


        self.screen.fill((0, 0, 0))  # Fill the screen with black
        self.screen.blit(scaled_image, img_rect.topleft)

    def toggle_full_size(self):
        self.full_size = not self.full_size
        self.zoom_scale = 1.0  # Reset the zoom scale when toggling modes
        self.image_offset = [0, 0]  # Reset the offset when switching images        
        self.display_image()

    def next_image(self):
        if self.current_image_index >= len(self.images) - 1:
            self.current_image_index = 0
        else:
            self.current_image_index += 1

        self.image = pygame.image.load(self.images[self.current_image_index])
        pygame.display.set_caption(self.images[self.current_image_index])
        self.zoom_scale = 1.0  # Reset the zoom scale when switching images
        self.image_offset = [0, 0]  # Reset the offset when switching images

    def prev_image(self):
        if self.current_image_index == 0:
            self.current_image_index = len(self.images) - 1
        else:
            self.current_image_index -= 1
            
        self.image = pygame.image.load(self.images[self.current_image_index])
        pygame.display.set_caption(self.images[self.current_image_index])
        self.zoom_scale = 1.0  # Reset the zoom scale when switching images
        self.image_offset = [0, 0]  # Reset the offset when switching images

if __name__ == '__main__':
    dir_path = os.path.dirname(os.path.realpath(__file__))
    app = ImageDisplay(dir_path)
