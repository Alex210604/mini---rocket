# Mini Rocket

**A mini rocket designed, built and launched in a single weekend.** CAD, custom electronics and flight software, from the first sketch to the launch pad.

▶️ **[Watch the launch video](https://youtu.be/uuqFKgB75sc)**

> **Launch result:** the launch was not successful. The motor retaining ring was not securely fixed to the fuselage, so the motor moved through the whole rocket and destroyed it. See [What went wrong](#what-went-wrong).

## Overview

The goal was to take a rocket through the whole engineering loop in one weekend: mechanical design, electronics, firmware, assembly and launch. The rocket was meant to detect its own flight and, at apogee, release its parachute by opening the nose cone with a servomotor.


## Repository structure

| Folder | Contents |
|---|---|
| [`CAD_github/`](CAD_github) | 3D models of all the parts, designed in SolidWorks |
| [`Electric Schematic/`](Electric%20Schematic) | Schematic of the flight computer board |
| [`Code/Servo_Acc_Time_/`](Code/Servo_Acc_Time_) | Flight software |
| [`Launch/`](Launch) | Mini-rocket picture + Launch video |

## Design (CAD)

Every part was modeled in 3D with SolidWorks. The parts were then assembled into the complete rocket, and the assembly was used to find the position of the **center of gravity** and judge whether the rocket would be **stable**.
The **center of pression** was estimated by StabTraj, which is an open-source, spreadsheet-based simulation software distribuited by CNES

## Electronics

The flight computer is a custom PCB built around an **ATmega328P-PU** microcontroller.

- **Power:** a battery pack, with a voltage regulator that provides the 5 V supply.
- **Power selection:** a jumper chooses whether the board runs from the batteries or from USB.
- **Actuators:** two servomotor connectors, `SERV1` and `SERV2`.

## Flight software

The firmware has three jobs:

1. detect lift-off,
2. detect apogee,
3. at apogee, turn a servomotor from 0° to 90° to open the nose cone (mechanically secured with springs) and deploy the parachute.

**Detection is time-based.** I first tried to detect lift-off and apogee with an IMU, but I could not get it to communicate with the microcontroller, so I fell back to a simple timer. A timer follows a fixed schedule: it does not measure the real flight.

When the mini-rocket is on the ramp, there is a small loop of wires coming out of the rocket creating a closed circuit. once the rocket lifts off, the circuit opens up, detecting the departure and starting the timer. The apogee is around 8sec after the lift off, calculated once again thanks to the StrabTraj.

## What went wrong

At launch, the motor retaining ring was not properly fixed to the rocket's fuselage. When the motor fired, it moved through the entire airframe and destroyed the rocket. The full video is linked at the top of this page.

## What I learned

- **The motor retention is a critical joint.** It has to be checked, and ideally tested, before every launch.
- **A fallback is not a sensor.** The IMU should have been validated on the bench before building the rest of the system around it.
- **Modeling the full assembly in CAD pays off.** It made it possible to check the center of gravity before anything was built.

## Next steps

- Redesign how the motor retaining ring is fixed to the fuselage and verify it before launch.
- Get the IMU working, so that lift-off and apogee are detected from measured data instead of a timer.
- Record flight data on board, so that the next flight can be analyzed afterwards.

## Author

Built by the help of a friend of mine, Cyprien Regis
