import numpy as np
import matplotlib.pyplot as plt

def simulate_bullet(mass, v0, angle, Cd, A):
    # Constants
    g = 9.81  # Acceleration due to gravity (m/s^2)
    rho = 1.225  # Air density at sea level (kg/m^3)

    # Time step and simulation time
    dt = 0.001
    t_max = 10  # simulation time in seconds
    t = np.arange(0, t_max, dt)

    # Initialize arrays for x, y, vx, vy
    x, y = np.zeros_like(t), np.zeros_like(t)
    vx, vy = v0 * np.cos(angle), v0 * np.sin(angle)

    for i in range(1, len(t)):
        # Previous step velocities
        v_prev = np.sqrt(vx**2 + vy**2)
        
        # Calculate drag force
        drag = 0.5 * rho * v_prev**2 * Cd * A
        
        # Drag components in x and y directions
        drag_x = drag * vx / v_prev if v_prev != 0 else 0
        drag_y = drag * vy / v_prev if v_prev != 0 else 0
        
        # Update velocities
        vx += -drag_x / mass * dt
        vy += (-g - drag_y / mass) * dt
        
        # Update positions
        x[i] = x[i-1] + vx * dt
        y[i] = y[i-1] + vy * dt
        
        # Stop simulation if bullet hits the ground
        if y[i] < -20:
            break

    # Slice arrays to only keep valid data
    valid_indices = y != 0
    return t[valid_indices], x[valid_indices], y[valid_indices]
# Simulate both bullets


bullets = {
    '5.56 NATO (M193)': {
        'mass': 0.0036,  # kg
        'v0': 925,       # m/s
        'angle': np.radians(0),  # radians
        'Cd': 0.30,      # Drag coefficient (Spitzer bullet)
        'A': 0.000024    # Cross-sectional area in m^2
    },
    '.308 Winchester': {
        'mass': 0.0097,  # kg
        'v0': 835,       # m/s
        'angle': np.radians(0),  # radians
        'Cd': 0.295,     # Drag coefficient (Spitzer bullet)
        'A': 0.000051    # Cross-sectional area in m^2
    },
    '6.5 Creedmoor': {
        'mass': 0.0091,  # kg
        'v0': 875,       # m/s
        'angle': np.radians(0),  # radians
        'Cd': 0.27,      # Drag coefficient (VLD bullet)
        'A': 0.000033    # Cross-sectional area in m^2
    },
    '9mm Luger': {
        'mass': 0.0080,  # kg
        'v0': 375,       # m/s
        'angle': np.radians(0),  # radians
        'Cd': 0.42,      # Drag coefficient (Round-nose bullet)
        'A': 0.000045    # Cross-sectional area in m^2
    },
    '.45 ACP': {
        'mass': 0.0149,  # kg
        'v0': 260,       # m/s
        'angle': np.radians(0),  # radians
        'Cd': 0.45,      # Drag coefficient (Flat-nosed bullet)
        'A': 0.000114    # Cross-sectional area in m^2
    }
}


# Plotting
plt.figure(figsize=(10, 6))


colors = ['red', 'green', 'blue', 'purple', 'orange']
color_index = 0

for name, bullet in bullets.items():
    t1, x1, y1 = simulate_bullet(**bullet)
    if color_index >= len(colors):
        color_index = 0  
    plt.plot(x1, y1, '-', color=colors[color_index], label=name)
    color_index += 1  

# for name, bullet in bullets.items():
#     t1, x1, y1 = simulate_bullet(**bullet)
#     plt.plot(x1, y1, 'b-', label=name)


plt.xlabel('Horizontal Distance (m)')
plt.ylabel('Vertical Distance (m)')
plt.title('Trajectory of Two Bullets with Air Resistance')
plt.legend()
plt.grid(True)
plt.show()
