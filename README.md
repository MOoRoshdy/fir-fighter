# Autonomous Fire-Fighting Robot with Li-Fi Communication

This project features an autonomous fire-fighting robot capable of detecting and extinguishing fires using flame sensors and a water pump. The robot is also equipped with a solar-powered radar system for navigation and energy optimization. It communicates with other fire-fighting robots via **Li-Fi technology**, allowing fast and efficient data transfer through visible light for real-time coordination during fire-fighting operations.

## Features

- **Fire Detection**: The robot uses three flame sensors to detect fire and navigate toward it.
- **Fire Fighting**: Once close to the fire, the robot activates a water pump and navigates accordingly to extinguish the fire.
- **Solar-Powered Radar**: The solar panel is mounted on a servo, which adjusts its angle to optimize solar charging, ensuring the robot remains operational during fire-fighting tasks.
- **Li-Fi Communication**: The robot communicates with other fire-fighting robots using light-based communication (Li-Fi), enabling real-time coordination and efficient data transfer.
- **Obstacle Avoidance**: The robot uses an ultrasonic sensor to detect and avoid obstacles while moving.

## Hardware Components

- **Arduino UNO**: The main controller.
- **L298N Motor Driver**: For controlling the motors.
- **Flame Sensors**: For detecting fire.
- **Ultrasonic Sensor**: For obstacle detection.
- **Servo Motors**: For movement control and solar panel tracking.
- **Li-Fi Module**: For communication between multiple robots.

## Installation

1. **Hardware Setup**:
   - Connect all the components as shown in the schematic. Ensure that the flame sensors, ultrasonic sensors, motor driver, and servos are connected to the correct pins on the Arduino.
   - The Li-Fi module is used for communication with other robots (see Li-Fi communication section below for details).

2. **Upload Code**:
   - Open the provided Arduino code in the Arduino IDE.
   - Select your board type (Arduino UNO) and the correct port in the IDE.
   - Upload the code to your Arduino.

3. **Li-Fi Communication**:
   - The robots use visible light for communication, which requires the use of photodiodes and LEDs.
   - You need to set up a Li-Fi module (LED and photodiode) for both transmitting and receiving data.
   - Ensure that the Li-Fi modules are correctly oriented for line-of-sight communication between the robots.

## Li-Fi Communication

The Li-Fi technology allows for fast and reliable data transmission between the fire-fighting robots using visible light. This is achieved by:
- **LEDs**: Transmit data through light signals.
- **Photodiodes**: Receive the light signals and convert them back into data.

The robots communicate with each other to share status updates, fire location, and other critical information during a fire-fighting mission. The communication is established by aligning the photodiodes and LEDs, ensuring that the robots remain in each other's line of sight.

## Code Explanation

The provided Arduino code handles the following:
1. **Fire Detection**: The robot checks the flame sensors to detect fire. If fire is detected, the robot moves toward the source.
2. **Fire Fighting**: When the robot approaches the fire (using distance sensors), it activates the water pump and adjusts its movement based on the fire's location.
3. **Solar Tracking**: The robot uses a solar-powered radar system to optimize energy use. A second servo moves the solar panel to track the sunlight.
4. **Obstacle Avoidance**: Using the ultrasonic sensor, the robot avoids obstacles while navigating towards the fire.


