# 5-Bar Pick and Place Mechanism

This project was developed as part of our SYDE 261 Engineering Prototyping course. 
Developed by **Tharun Ganeshram** and **Ahorna Chowdhury**.

Welcome to the 5-Bar Pick and Place Mechanism project! This implementation utilizes hobby servos controlled by a Botboarduino controller board to create a pick and place mechanism. Below are the key features and instructions for using the project:

## Features
- **Servo Control**: The code utilizes the Servo library to control gripper and axis servos.
- **Smooth Movement**: Implements functions for smooth movement of the mechanism to specified positions.
- **Payload Manipulation**: Enables accurate picking up and placing of the payload using gripper control.
- **Communication**: Utilizes digital pins for communication between two systems.

## Code Explanation
- **Servo Initialization**: Initialize servos for gripper, axis 1, and axis 2.
- **Movement Functions**: Implement `moveTopos()` function to move the mechanism smoothly.
- **Pick and Place Logic**: Define `picknplace()` function to execute pick and place operations.
- **Main Loop**: Read input from the serial monitor and execute pick and place based on the input.

## How to Use
1. **Setup**: Connect the required hardware and upload the code to the Botboarduino.
2. **Serial Communication**: Use the serial monitor to input destination locations (1, 2, or 3).
3. **Operation**: Watch as the mechanism moves to pick up the payload and place it at the specified destination.

Feel free to explore and modify the code for further experimentation and optimization!

![5-Bar Pick and Place Mechanism](https://github.com/TharunGaneshram/Pick-N-Place/assets/76886618/5ce17c62-2f6a-4ae9-8960-9a923b6d7238)
