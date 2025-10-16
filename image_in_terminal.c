#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float h, s, v;
} HSV;

typedef struct {
    unsigned char r, g, b;
} RGB;

// Convert RGB (0–255) → HSV (0–1)
HSV rgb_to_hsv(RGB in) {
    float r = in.r / 255.0f, g = in.g / 255.0f, b = in.b / 255.0f;
    float max = fmaxf(r, fmaxf(g, b)), min = fminf(r, fminf(g, b));
    float delta = max - min;

    HSV out;
    out.v = max;
    out.s = (max == 0) ? 0 : delta / max;

    if (delta == 0)
        out.h = 0;
    else if (max == r)
        out.h = fmodf(((g - b) / delta), 6.0f);
    else if (max == g)
        out.h = ((b - r) / delta) + 2.0f;
    else
        out.h = ((r - g) / delta) + 4.0f;

    out.h *= 60.0f;
    if (out.h < 0)
        out.h += 360.0f;

    return out;
}

// Simple nearest-neighbor resize
RGB *resize_image(unsigned char *img, int w, int h, int c, int new_w, int new_h) {
    RGB *resized = malloc(new_w * new_h * sizeof(RGB));
    for (int y = 0; y < new_h; y++) {
        for (int x = 0; x < new_w; x++) {
            int src_x = (int)((x / (float)new_w) * w);
            int src_y = (int)((y / (float)new_h) * h);
            int src_index = (src_y * w + src_x) * c;
            resized[y * new_w + x].r = img[src_index + 0];
            resized[y * new_w + x].g = img[src_index + 1];
            resized[y * new_w + x].b = img[src_index + 2];
        }
    }
    return resized;
}

// Map brightness (V) → ASCII character
char brightness_to_char(float v) {
    const char *gradient = " .'`^,:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    int index = (int)(v * (strlen(gradient) - 1));
    return gradient[index];
}

// Print pixel with terminal color
void print_colored_char(RGB color, char ch) {
    printf("\033[38;2;%d;%d;%dm%c", color.r, color.g, color.b, ch);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int width, height, channels;
    unsigned char *img = stbi_load(filename, &width, &height, &channels, 3);
    if (!img) {
        printf("Failed to load image: %s\n", filename);
        return 1;
    }
    // Set the target width according to your terminal size, mine is 150.
    int target_width = 100;
    int target_height = (int)((height * (target_width / (float)width)) / 2.0f); // fix for 2:1 terminal ratio
    if (target_height < 1) target_height = 1;

    RGB *resized = resize_image(img, width, height, channels, target_width, target_height);

    for (int y = 0; y < target_height; y++) {
        for (int x = 0; x < target_width; x++) {
            RGB color = resized[y * target_width + x];
            HSV hsv = rgb_to_hsv(color);
            char ch = brightness_to_char(hsv.v);
            print_colored_char(color, ch);
        }
        printf("\033[0m\n"); // reset color after each row
    }

    stbi_image_free(img);
    free(resized);
    printf("\033[0m"); // reset at end
    return 0;
}
