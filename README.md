# CG-project Analog Clock

This is a simple analog clock implemented using OpenGL and GLUT library in C++. The clock displays the current time with hour, minute, and second hands rotating around a circular dial. It provides options to change the color of the clock and toggle between Roman numerals and digits for the hour markers.
<h3>Output at the end of this page</h3>

## Prerequisites

- OpenGL
- GLUT

## Usage

1. Clone the repository or download the source code files.
2. Compile the code using a C++ compiler that supports OpenGL and GLUT.
3. Run the compiled executable.

## Functionality

The analog clock provides the following features:

- Display of current time: The hour, minute, and second hands rotate around the dial to represent the current time.
- Color selection: Right-click on the clock to access a menu that allows changing the color of the clock. Options include orange, green, and blue.
- Hour markers: The clock can display hour markers as either Roman numerals or digits. Right-click on the clock to toggle between the two options.

## Code Structure

The code is organized into several functions and uses OpenGL and GLUT library functions for rendering and interaction. Here's an overview of the main functions:

- `draw()`: This function is responsible for drawing the clock. It sets up the projection and modelview matrices, clears the buffer, and calls other functions to draw the clock components such as the circular dial, hour markers, and clock hands.
- `changeColor(int option)`: This function is called when the user selects a color from the menu. It updates the `currentColor` variable and triggers a redraw of the clock.
- `toggleNumerals(int option)`: This function is called when the user selects the "Toggle Numerals" option from the menu. It toggles the `useRomanNumerals` flag and triggers a redraw of the clock.
- `createMenu()`: This function creates the right-click menu for selecting the clock color and options.
- `updateClock(int value)`: This function is called periodically to update the clock's time based on the system time. It retrieves the current hour, minute, and second and triggers a redraw of the clock.
- `WelcomeDisplay()`: This function displays a welcome message and the names of the contributors when the program starts.
- `keys(unsigned char key, int x, int y)`: This function handles keyboard input and allows the user to proceed to the clock display by pressing the 'X' key.

## Acknowledgments

This code is based on the work of the contributor Ashutosh Aditya.

https://github.com/Ashutosh-aditya/CG-project/assets/78680582/ac2805bd-04d4-41be-8145-5dcb6fd842be

