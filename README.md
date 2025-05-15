# Embedded-Project-Spring-25
Project Overview

This project was developed for the CSE 211s - Introduction to Embedded Systems [Spring 2025] course at the Faculty of Engineering, Computer and Systems Engineering Department.

The goal is to build an embedded system using Embedded C and the TM4C123G LaunchPad that gathers real-time GPS data and displays nearby landmarks when approached. The system should function autonomously and provide accurate, updated location data while in motion.

🎯 Features
Real-time acquisition of GPS coordinates

Parsing and display of location data

Matching current location with predefined landmarks

Live display of the closest landmark name

Optional autonomous setup with battery and LCD display

🧰 Hardware Requirements
TM4C123G LaunchPad (Tiva C Series)

GPS module (e.g., NEO-6M or similar)

USB/Serial cable

Personal Computer

LCD screen (optional, for autonomous mode)

Power source (battery for mobility, optional)

💻 Software Requirements
Keil uVision IDE

Embedded C

UART communication for GPS integration

Git/GitHub for version control

🏗️ Milestones
✅ Milestone 1
Flash code to the TM4C123G using Keil.

Initialize GPIO ports.

Configure UART communication with the GPS module.

✅ Milestone 2 (Final)
Parse GPS data (NMEA ASCII format).

Store and compare coordinates of at least 5 faculty landmarks.

Continuously update and display current location and closest landmark.
