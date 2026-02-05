# Windows Keyboard Input Monitoring Research

This repository contains a C-based research implementation designed to
study how keyboard input events can be detected at the operating system
level on Microsoft Windows.

The project focuses on understanding:
- Windows input APIs
- Virtual-key codes (VK_*)
- Asynchronous key state polling
- File system access using Win32 APIs
- User environment paths and system folders

This code is intended strictly for educational and research purposes.

## 🎯 Purpose

The goal of this project is to help students and researchers understand:
- How keyboard events are exposed by the Windows API
- How input monitoring works at a low level
- How defensive software (such as antivirus or EDR tools) may detect
  unauthorized input capture
- Why secure applications avoid relying solely on client-side input secrecy

## 🧠 Topics Covered

- Win32 API (`GetAsyncKeyState`, `GetConsoleWindow`, `ShowWindow`)
- Virtual-key codes and keyboard layouts
- File handling on Windows
- Environment-specific directory resolution
- Basic event polling and debouncing logic

## ⚠️ Ethical Use Notice

This project must only be used:
- On systems you own
- In controlled lab environments
- For learning, auditing, or defensive security research

Any other use may be illegal or unethical.

## 🛠 Platform

- Windows only
- C / Win32 API
- Desktop environment required

## 📚 Disclaimer
This software is provided for **educational and research purposes only**.

The author does **not** condone or support:
- Unauthorized monitoring of user input
- Invasion of privacy
- Surveillance without informed consent
- Malware development or deployment

You are solely responsible for ensuring that your use of this code:
- Complies with all applicable local, national, and international laws
- Respects privacy and consent requirements
- Is limited to systems and environments you are authorized to test

The author assumes **no responsibility or liability** for misuse,
damages, or legal consequences resulting from this software.
