Absolutely! Here's a clean, human-friendly **README.md** for your terminal ASCII art project:

---

# Terminal Image ASCII Art Renderer

A simple **C program** that converts any image into **colorized ASCII art** and prints it directly in your terminal. The program uses the **brightness and hue of each pixel** to choose both the character and its color, producing a terminal-friendly, visually appealing representation of your image.

---

## Features

* Loads images in formats like PNG, JPEG, and more using `stb_image.h`.
* Compresses large images to a **150px width**, maintaining aspect ratio.
* Adjusts height to account for **terminal character ratio (2:1)**, so the image doesn't appear stretched.
* Converts each pixel to **HSV** to extract brightness (`V`) and hue (`H`).
* Maps brightness to **ASCII characters** (densest characters for brightest pixels).
* Prints **colorized ASCII art** in terminal using **ANSI 24-bit colors**.
* Works entirely in **terminal** — no GUI required.

---

## How It Works

1. **Image Loading:**
   The program reads the image from a file path supplied as a command-line argument using `stb_image.h`.

2. **Resize & Aspect Ratio:**
   The image is resized to a width of **150 pixels**, while maintaining the original aspect ratio.
   The height is divided by 2 to account for the **taller shape of terminal characters**, preventing vertical stretching.

3. **Pixel Processing:**
   Each pixel in the resized image is converted from **RGB → HSV**, so we can use the **V (brightness)** value to determine which ASCII character to print.

4. **Character Mapping:**
   Brightness is mapped to a **gradient of 24 characters** (or more if you like) from darkest (`' '`) to brightest (`'@'`).
   Example gradient: `" .'`^",:;Il!i~+_-?][}{1)(|\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"`

5. **Color Mapping:**
   Hue and saturation are used to calculate the corresponding **RGB color**, which is printed in terminal using **ANSI escape codes** for 24-bit color.

6. **Terminal Output:**
   The program prints the ASCII characters **row by row**, resulting in a **colorized ASCII art version of your image**.

---

## Usage

1. **Download `stb_image.h`**
   Get it from: [https://github.com/nothings/stb/blob/master/stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)
   Place it in the same folder as the `.c` file.

2. **Compile the program:**

   ```bash
   gcc image_in_terminal.c -lm -o image_in_terminal
   ```

3. **Run the program with an image path:**

   ```bash
   ./image_in_terminal image.jpg
   ```

4. **View the output:**
   Your terminal will display the **colorized ASCII art version** of the image.

---

## Notes

* The program currently uses a **default width of 150 characters**, but you can modify it in the code if your terminal is wider or narrower.
* The **gradient string** can be customized to produce different artistic effects.
* Works best on terminals that support **24-bit ANSI color**.

---

