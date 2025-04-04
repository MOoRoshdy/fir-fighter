# 🚒 Arduino Fire Fighting Robot

![Title Image](https://github.com/Circuit-Digest/Arduino-Based-Fire-Fighting-Robot/blob/main/DIY-Arduino-based-Fire-Fighting-Robot.jpg)
## 🌟 Overview

This project demonstrates how to build a fire-fighting robot using **Arduino**. The robot is designed to autonomously detect fire (using a flame sensor) and extinguish it (using a water pump or similar mechanism). It’s a great way to learn about integrating sensors, motors, and robotics using the Arduino platform.

## 🎯 Features

- 🔥 **Flame Detection**: The robot uses a flame sensor to detect fire sources.
- 🤖 **Automatic Movement**: The robot moves toward the detected fire.
- 💦 **Extinguishing Mechanism**: Once the fire is detected, the robot triggers a water pump to put it out.
- 🛑 **Obstacle Avoidance**: The robot can avoid obstacles while navigating toward the fire source.

## 🧩 Components

- **Arduino UNO**: The main controller for the robot.
- **Flame Sensor**: Used to detect fire or heat sources.
- **DC Motors with Motor Driver**: Provides movement control.
- **Water Pump or Solenoid Valve**: For the extinguishing mechanism.
- **Ultrasonic Sensor (optional)**: For obstacle detection and avoidance.
- **Chassis**: The physical frame for the robot.
- **Power Supply**: A battery pack to power the robot and components.
- **Jumper Wires**: For connections between components.

## 🔌 Circuit Diagram

You can view the full circuit diagram for connecting all the components to the Arduino [here](https://github.com/Circuit-Digest/Arduino-Based-Fire-Fighting-Robot/blob/main/DIY-Arduino-based-Fire-Fighting-Robot-circuit-diagram.png).




## 🛠️ How to Set Up

### Hardware Setup:

- Connect all the components as per the circuit diagram provided in the link above.
- Make sure the flame sensor is correctly connected to the analog input pin of Arduino.
- The motors should be connected to a motor driver, and the water pump should be connected to the digital pin of the Arduino.

### Software Setup:

- Install the **Arduino IDE** (if not already installed).
- Open the **Arduino IDE** and upload the code to your Arduino board.
- Ensure that the necessary libraries (if any) are installed in your IDE.

### Testing:

- Power up the robot and place it in an environment with controlled fire.
- The robot should autonomously detect the fire, navigate toward it, and activate the pump to extinguish it.

---

## 🛠️ Customization

- You can adjust the **fire detection threshold** in the code by modifying the value `500` to suit your environment.
- The **movement** and **pump activation** can be customized by changing the motor pins and logic in the code.

---

## 🐞 Troubleshooting

- **Motor Not Running**: Check the wiring and ensure the motor driver is properly powered.
- **Flame Sensor Not Detecting**: Make sure the sensor is placed in the right position and is facing the flame.

---

## 🤝 Contributing

If you want to contribute to this project, feel free to fork the repository, make improvements, and submit a pull request.

---

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).
