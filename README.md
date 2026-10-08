# Kitchen Safety – Heat and Gas Monitoring & Alert System

## 1. Project Overview

The **Kitchen Safety – Heat and Gas Monitoring & Alert System** is an embedded safety project developed using the **NXP LPC2148 ARM7 microcontroller**.

The system continuously monitors:

- Kitchen temperature using an **LM35 temperature sensor**
- Gas/smoke level using an **MQ-2 gas sensor**
- Current date and time using the **LPC2148 RTC**
- User commands through a **4×4 matrix keypad**
- System status through a **16×2 LCD**
- Unsafe conditions through a **buzzer and LED indication**

When a temperature or gas value crosses its configured safety limit, the system generates an alert. The project also records the latest safety event together with the RTC time at which the event occurred.

The system includes a password-protected **Edit Mode**, allowing authorized users to change parameters such as sensor thresholds and RTC settings.

---

## 2. Aim

To design and implement a smart kitchen safety system using the **LPC2148 microcontroller** that continuously monitors temperature and gas levels, detects hazardous conditions, records threshold-crossing events with RTC timestamps, periodically displays the latest safety event, and provides timely alerts.

---

## 3. Objectives

### Temperature Monitoring
Continuously measure kitchen temperature using the LM35 sensor and detect abnormal heat levels.

### Gas Leakage Detection
Monitor combustible gas/smoke levels using the MQ-2 sensor.

### Alert Mechanism
Generate an immediate warning through the buzzer and LED indication when an unsafe condition is detected.

### Event Recording
When a monitored value changes from a safe condition to an unsafe condition, record:

- Sensor responsible for the event
- Sensor value at the event
- RTC hour
- RTC minute
- RTC second

### User Configuration
Provide a secure menu through which authorized users can modify system parameters.

### Safety Enhancement
Provide a low-cost embedded solution for improving kitchen safety.

---

# 4. System Block Diagram

```text
             +----------------------+
             |      LM35 Sensor     |
             | Temperature Sensing  |
             +----------+-----------+
                        |
                        v
                 +------+------+
                 |             |
                 |   LPC2148   |
                 | ARM7 MCU    |
                 |             |
                 | ADC         |
                 | RTC         |
                 | GPIO        |
                 | EINT        |
                 +--+---+---+--+
                    |   |   |
          ----------+   |   +----------------
          |              |                    |
          v              v                    v
   +-------------+  +----------+       +-------------+
   |   16x2 LCD  |  |  Buzzer  |       | LED Alert   |
   | Display     |  |  Alarm   |       | Indication  |
   +-------------+  +----------+       +-------------+
          ^
          |
   +------+------+
   |   Keypad    |
   |    4x4      |
   +-------------+

             +----------------------+
             |       MQ-2 Sensor    |
             | Gas / Smoke Sensing  |
             +----------+-----------+
                        |
                        v
                       ADC
```

> The project documentation specifies a DC motor/exhauster concept for ventilation, but also specifies using LEDs instead of the DC motor in the implemented setup.

---

# 5. Hardware Requirements

| Component | Purpose |
|---|---|
| LPC2148 | Main ARM7 microcontroller |
| 16×2 LCD | Displays sensor values, RTC information, menus and alerts |
| 4×4 Matrix Keypad | User input and menu navigation |
| Switch | Used for system control / edit-mode operation |
| LEDs | Visual alert indication |
| MQ-2 | Gas/smoke sensing |
| LM35 | Temperature sensing |
| Buzzer | Audible safety alert |
| USB-UART Converter / DB-9 | Serial communication/programming support |

---

# 6. Software Requirements

- Embedded C
- Keil/ARM development environment
- Flash Magic
- LPC2148 device support
- Proteus can be used for simulation where the required sensor models are available

---

# 7. Main System Working

The application operates continuously.

```text
                    START
                      |
                      v
             Initialize peripherals
                      |
        +-------------+-------------+
        |             |             |
        v             v             v
       LCD           ADC           RTC
        |             |             |
        +-------------+-------------+
                      |
                      v
              Read temperature
                from LM35
                      |
                      v
                 Read gas
                 from MQ-2
                      |
                      v
             Compare with limits
                      |
          +-----------+-----------+
          |                       |
       SAFE                    UNSAFE
          |                       |
          v                       v
   Normal display        Buzzer + LED alert
          |                       |
          +-----------+-----------+
                      |
                      v
             Check new event
                      |
                      v
           Save event + RTC time
                      |
                      v
        Periodically show latest event
                      |
                      v
             Check user input
                      |
          +-----------+-----------+
          |                       |
        EDIT                   NORMAL
          |                       |
          v                       |
       Password                  |
       verification              |
          |                       |
          v                       |
     Edit parameters              |
          |                       |
          +-----------+-----------+
                      |
                      v
                 Repeat loop
```

---

# 8. Temperature Monitoring – LM35

The LM35 is used as the temperature sensing device.

The controller reads the sensor output through the LPC2148 ADC.

```text
LM35
 |
 | Analog voltage
 v
LPC2148 ADC
 |
 | Digital ADC value
 v
Temperature calculation
 |
 v
Temperature in °C
 |
 v
Compare with TEMP_LIMIT
 |
 +------ Safe ------> Normal operation
 |
 +---- Unsafe ------> Alarm condition
```

The temperature threshold can be configured by the user through the protected edit menu.

---

# 9. Gas Monitoring – MQ-2

The MQ-2 is used for detecting combustible gas/smoke conditions.

```text
MQ-2
 |
 | Analog sensor output
 v
LPC2148 ADC
 |
 v
Digital ADC value
 |
 v
Gas-level processing
 |
 v
Compare with GAS_LIMIT
 |
 +------ Safe ------> Normal operation
 |
 +---- Unsafe ------> Alarm condition
```

The MQ-2 output is read through the ADC and compared with the configured gas safety limit.

---

# 10. ADC Block

The LPC2148 contains an internal ADC that converts analog sensor voltages into digital values.

The ADC block is used by both the LM35 and MQ-2 sensing sections.

```text
Analog Sensor
      |
      v
  ADC Channel
      |
      v
Sample & Convert
      |
      v
Digital Value
      |
      v
Application Processing
```

The project contains:

- `ADC.c`
- `ADC.h`
- `ADC_defines.h`

These files form the ADC driver/interface section of the project.

---

# 11. LCD Block

The 16×2 LCD is the main user interface.

It can display:

- Project/startup information
- Temperature
- Gas value
- RTC time/date
- Safety status
- Edit menus
- Password prompts
- Access-denied messages
- Latest safety event

LCD-related files:

```text
LCD.c
LCD.h
LCD_defines.h
```

The LCD driver isolates low-level LCD operations from the application code.

---

# 12. RTC Block

The LPC2148 RTC is used to maintain real-time information.

The project uses RTC information for:

- Current time
- Date
- Month
- Year
- Event timestamp

When a safety event occurs, the system stores the RTC information associated with that event.

Example:

```text
Temperature exceeds limit
          |
          v
     Event detected
          |
          v
    Read RTC values
          |
          v
Store:
Sensor + Value + Hour + Minute + Second
```

RTC-related files:

```text
RTC.c
RTC.h
```

---

# 13. Keypad / KPM Block

The 4×4 matrix keypad is used as the user input device.

It can be used for:

- Password entry
- Menu navigation
- Threshold modification
- RTC modification
- Password change
- Selecting edit options

Keypad-related files:

```text
KPM.c
KPM.h
KPM_defines.h
```

The keypad driver handles the low-level row/column scanning, while the application decides what each key means.

---

# 14. LM35 Driver Block

The LM35-specific files are:

```text
LM35.c
LM35.h
```

The driver provides the interface required by the application to obtain temperature information from the LM35 sensor.

The overall data path is:

```text
LM35
  |
  v
ADC
  |
  v
ADC Digital Value
  |
  v
LM35 Driver
  |
  v
Temperature Value
  |
  v
main.c
```

---

# 15. Alarm Block

The alarm mechanism provides immediate feedback when an unsafe condition occurs.

```text
Temperature unsafe
        OR
Gas unsafe
        |
        v
   Alarm condition
        |
        +------> Buzzer
        |
        +------> LED
```

The alarm can be silenced using the configured switch operation.

The project source contains alarm-related functions such as:

```c
alarm_on();
alarm_off();
```

The application also checks the alarm state continuously during normal operation.

---

# 16. Safety Event Recording

One important feature of the project is that it does not simply keep the buzzer ON whenever a sensor is above its threshold.

The application detects a **threshold-crossing event**.

Conceptually:

```text
SAFE
 |
 | sensor crosses configured limit
 v
UNSAFE
 |
 v
Create event record
 |
 +--> Sensor name
 +--> Sensor value
 +--> RTC hour
 +--> RTC minute
 +--> RTC second
```

The stored event represents the most recent safety event.

The event information is updated when a new threshold-crossing event occurs.

---

# 17. Periodic Event Popup

During normal operation, the LCD continuously displays the live monitoring information.

After a configured interval, the system temporarily displays the latest safety event.

The project specification defines:

- Event popup interval: approximately 10 seconds
- Popup duration: approximately 2–3 seconds

Example:

```text
NORMAL SCREEN
Temperature: 31.5 C
Gas: 245
Time: 18:32:10

        |
        | periodic popup
        v

LAST EVENT
TEMP HIGH
Value: 42.5 C
Time: 18:31:47

        |
        | after popup
        v

NORMAL SCREEN
```

This allows the user to see the latest important safety event without permanently replacing the live monitoring screen.

---

# 18. Edit Mode

The project provides an external-switch-based edit mechanism.

When the user presses the configured switch:

```text
Switch1 Pressed
       |
       v
External Interrupt
       |
       v
Enter Edit Mode
       |
       v
Password Request
```

The external interrupt allows the application to respond to the switch without depending only on normal polling.

The project contains an interrupt-related function such as:

```c
switch1_interrupt()
```

---

# 19. Password Protection

Edit Mode is protected using a basic password.

```text
Enter Edit Mode
      |
      v
Enter Password
      |
      v
Compare Password
      |
   +--+--+
   |     |
Correct Wrong
   |     |
   v     v
Allow   Deny
Edit    Access
          |
          v
     Wrong attempt++
```

This prevents unauthorized modification of safety thresholds and RTC settings.

---

# 20. Wrong Password Handling

The documented security flow uses a wrong-attempt counter.

When the password is incorrect:

1. Access is denied.
2. The wrong-attempt counter is incremented.
3. The LCD displays an access-denied message.
4. An optional buzzer/LED indication can be used.

After **3 incorrect attempts**, the system can lock Edit Mode temporarily or until reset.

```text
Wrong password
      |
      v
Attempt count++
      |
      v
Is count >= 3?
   /        \
 NO          YES
 |            |
 v            v
Try again   System Locked
```

---

# 21. Editable Parameters

After successful password verification, the user can access the configuration menu.

The documented editable parameters include:

- Current RTC time
- Day/date
- Sensor threshold values
- Password change option

The keypad is used to navigate through the menu and enter values.

After editing:

```text
Save Parameters
      |
      v
Exit Edit Mode
      |
      v
Return to Normal Monitoring
```

---

# 22. Project File Structure

The repository contains separate files for different hardware/software modules.

```text
ARM---Mini-Project/
│
├── ADC.c
├── ADC.h
├── ADC_defines.h
│
├── KPM.c
├── KPM.h
├── KPM_defines.h
│
├── LCD.c
├── LCD.h
├── LCD_defines.h
│
├── LM35.c
├── LM35.h
│
├── RTC.c
├── RTC.h
│
├── delay.c
├── delay.h
│
├── pin_connect_block.c
├── pin_connect_block.h
│
├── defines.h
├── types.h
│
├── main.c
│
└── README.md
```

---

# 23. File-by-File Explanation

## `main.c`

This is the **main application file**.

It coordinates the complete project.

Responsibilities include:

- System initialization
- Sensor monitoring
- Temperature safety checking
- Gas safety checking
- LCD screen handling
- RTC information handling
- Alarm control
- Event recording
- Event popup handling
- Switch handling
- Edit-mode control
- Password/security flow

In simple terms:

```text
All drivers
    |
    v
 main.c
    |
    +--> Read sensors
    +--> Check safety
    +--> Control alarm
    +--> Display information
    +--> Record events
    +--> Handle user input
```

---

## `ADC.c`

Contains the ADC driver implementation.

It handles the low-level ADC operations required to read analog sensor values.

Used by:

- LM35
- MQ-2

---

## `ADC.h`

Contains the declarations/interface of ADC functions used by other modules.

---

## `ADC_defines.h`

Contains ADC-related definitions such as channel/configuration constants used by the ADC module.

---

## `LCD.c`

Contains the LCD driver implementation.

It handles low-level communication with the 16×2 LCD.

Typical LCD operations include:

```text
Initialize LCD
Send command
Send data
Display string
Move cursor
Clear display
```

---

## `LCD.h`

Contains LCD function declarations used by application code.

---

## `LCD_defines.h`

Contains LCD-specific constants and definitions.

---

## `KPM.c`

Contains the keypad driver implementation.

It handles scanning of the 4×4 matrix keypad and identifying the pressed key.

---

## `KPM.h`

Contains keypad function declarations.

---

## `KPM_defines.h`

Contains keypad-related pin and configuration definitions.

---

## `LM35.c`

Contains the LM35 temperature-sensor driver/application interface.

It provides temperature information to the main application.

---

## `LM35.h`

Contains LM35 function declarations and the interface used by `main.c`.

---

## `RTC.c`

Contains RTC-related implementation.

It handles the real-time clock functions used for displaying current time/date and recording event timestamps.

---

## `RTC.h`

Contains RTC function declarations.

---

## `delay.c`

Contains software delay implementation.

Delays are useful when hardware devices require timing gaps between operations.

---

## `delay.h`

Contains delay-function declarations.

---

## `pin_connect_block.c`

Contains the implementation associated with the LPC2148 **Pin Connect Block** configuration.

The Pin Connect Block determines the function assigned to multiplexed LPC2148 pins.

For example, a physical pin may be configured for:

```text
GPIO
UART
I2C
SPI
PWM
External interrupt
```

depending on the pin's available alternate functions.

---

## `pin_connect_block.h`

Contains declarations/interface for the pin configuration module.

---

## `types.h`

Provides commonly used application-specific data types.

Examples may include:

```text
u8   -> unsigned 8-bit type
u16  -> unsigned 16-bit type
u32  -> unsigned 32-bit type
s8   -> signed 8-bit type
s16  -> signed 16-bit type
s32  -> signed 32-bit type
```

Using these names makes embedded code easier to understand and portable between modules.

---

## `defines.h`

Contains common project-level definitions and constants shared by multiple modules.

Examples can include:

- Pin numbers
- Threshold constants
- Project configuration values
- Application-specific macros

---

# 24. Software Architecture

The project follows a modular embedded-C structure.

```text
                 APPLICATION LAYER
                       |
                    main.c
                       |
        +--------------+--------------+
        |              |              |
        v              v              v
     Sensors         User I/O        RTC
        |              |              |
   +----+----+      +--+--+        RTC.c
   |         |      |     |
  LM35      MQ-2   LCD   KPM
   |         |      |     |
   +----+----+      +-----+
        |
       ADC
        |
     ADC Driver
        |
        v
    LPC2148 Hardware
```

This separation makes the project easier to understand, test, debug and maintain.

---

# 25. Safety Decision Logic

The basic decision logic is:

```text
Read Temperature
       |
       v
Temperature > TEMP_LIMIT?
       |
    +--+--+
    |     |
   YES    NO
    |     |
    v     |
Temp unsafe
    |     |
    +-----+
       |
       v
Read Gas
       |
       v
Gas > GAS_LIMIT?
       |
    +--+--+
    |     |
   YES    NO
    |     |
    v     |
Gas unsafe
    |     |
    +-----+
       |
       v
If either condition is unsafe
       |
       v
Activate alarm
```

---

# 26. Normal Operating Screen

During normal operation, the LCD displays the current monitoring information.

The project specification states that the normal display includes:

- Current time
- Live temperature
- Live gas reading

The screen periodically changes to the latest recorded safety event and then returns to the normal screen.

---

# 27. Alert Silencing

The alarm can be silenced using the configured switch.

```text
Unsafe condition
      |
      v
Buzzer ON
      |
      v
Switch2 pressed?
   /          \
 NO           YES
 |             |
 v             v
Keep alarm    Silence alarm
```

The sensor monitoring continues even after the audible alert is silenced.

---

# 28. Startup Flow

A typical startup sequence is:

```text
RESET
  |
  v
Initialize GPIO
  |
  v
Configure Pin Connect Block
  |
  v
Initialize LCD
  |
  v
Initialize ADC
  |
  v
Initialize RTC
  |
  v
Initialize Keypad
  |
  v
Configure Alarm Pins
  |
  v
Display Startup Information
  |
  v
Enter Monitoring Loop
```

---

# 29. Complete Application Flow

```text
                 +---------+
                 |  RESET  |
                 +----+----+
                      |
                      v
              Initialize System
                      |
                      v
              Display Startup
                      |
                      v
             +----------------+
             | Normal Monitor |
             +-------+--------+
                     |
             +-------+--------+
             |                |
             v                v
       Read Temperature     Read Gas
             |                |
             +-------+--------+
                     |
                     v
              Compare Limits
                     |
              +------+------+
              |             |
            SAFE          UNSAFE
              |             |
              |       +-----+-----+
              |       |           |
              |       v           v
              |    Buzzer        LED
              |       |
              |       v
              |   Alert state
              |             |
              +------+------+
                     |
                     v
             Detect new event
                     |
                     v
               Store event
                     |
                     v
              Read RTC time
                     |
                     v
          Periodic event popup
                     |
                     v
             Check Switch 1
                     |
              +------+------+
              |             |
             NO            YES
              |             |
              |             v
              |       External Interrupt
              |             |
              |             v
              |        Password Check
              |             |
              |       +-----+-----+
              |       |           |
              |     WRONG       CORRECT
              |       |           |
              |       v           v
              |    Deny       Edit Menu
              |       |           |
              |       |           v
              |       |      Save Parameters
              |       |           |
              +-------+-----------+
                      |
                      v
                Repeat Forever
```

---

# 30. Important Design Features

### Modular Design
Separate drivers are used for ADC, LCD, keypad, RTC, LM35, delays and pin configuration.

### Real-Time Monitoring
The LPC2148 continuously monitors sensor inputs.

### Threshold-Based Safety
The system identifies unsafe conditions by comparing sensor readings with configured limits.

### Event Timestamping
The RTC provides the time associated with a safety event.

### Event Popup
The latest event is periodically displayed without permanently interrupting the normal monitoring screen.

### Password Protection
System configuration is protected from unauthorized modification.

### External Interrupt
Switch1 can trigger entry into Edit Mode through an external interrupt.

### Audible and Visual Alerts
The buzzer and LED provide immediate safety indication.

---

# 31. Programming / Build Flow

A general development flow is:

```text
Write Embedded C
      |
      v
Compile Source Files
      |
      v
Link Object Files
      |
      v
Generate HEX
      |
      v
Program LPC2148
      |
      v
Test Hardware
      |
      v
Validate Sensor / Alarm / LCD / RTC
```

Flash Magic can be used for programming the LPC2148 with the generated firmware.

---

# 32. Testing Checklist

| Test | Expected Result |
|---|---|
| Power ON | System initializes and LCD starts |
| LM35 temperature changes | Displayed temperature changes |
| Temperature exceeds limit | Alarm condition occurs |
| MQ-2 gas level changes | Gas reading changes |
| Gas exceeds limit | Alarm condition occurs |
| Switch2 pressed during alarm | Audible alarm is silenced |
| Safety event occurs | Event information is recorded |
| Event popup interval reached | Latest event is displayed temporarily |
| Switch1 pressed | Edit Mode is requested |
| Correct password | Edit menu is accessible |
| Wrong password | Access is denied |
| Three wrong attempts | System can enter lock condition |
| RTC changes | Displayed time/date updates |
| Threshold changed | New limit is used for monitoring |

---

# 33. Future Enhancements

Possible extensions include:

- Automatic exhaust fan control using a relay/driver
- GSM/SMS alert
- IoT/cloud monitoring
- Mobile application
- EEPROM/Flash-based permanent event history
- Multiple stored safety events
- More advanced gas concentration calibration
- Battery backup for RTC
- Password lockout timer
- Sensor fault detection
- Non-volatile storage of configurable thresholds

---

# 34. Applications

This project can be adapted for:

- Domestic kitchens
- Restaurants
- Hotels
- Canteens
- Food-processing areas
- Small industrial kitchens
- Gas-cylinder storage areas
- Other environments requiring temperature and gas monitoring

---

# 35. Key Concepts Demonstrated

This project provides practical experience with:

- ARM7TDMI / LPC2148
- Embedded C
- GPIO
- ADC
- RTC
- LCD interfacing
- Matrix keypad interfacing
- LM35 interfacing
- MQ-2 interfacing
- Pin Connect Block
- External interrupts
- Buzzer and LED control
- Threshold-based decision making
- Event logging
- Password-based access control
- Modular driver development

---

# 36. Conclusion

The **Kitchen Safety – Heat and Gas Monitoring & Alert System** demonstrates how an ARM7-based embedded controller can combine multiple peripherals and sensors to create a practical safety application.

The LPC2148 acts as the central controller, receiving sensor information through its ADC, maintaining real-time information through its RTC, displaying system information on a 16×2 LCD, accepting user input through a keypad/switch, and controlling the alarm indicators.

The event-recording and password-protected configuration features make the project more than a simple sensor-monitoring application. The modular driver structure also provides a good foundation for extending the system with additional sensors, communication interfaces, storage and IoT features.

---

## 37. Repository Structure at a Glance

```text
ARM---Mini-Project
│
├── ADC.c / ADC.h / ADC_defines.h
│       └── ADC driver
│
├── KPM.c / KPM.h / KPM_defines.h
│       └── 4×4 keypad driver
│
├── LCD.c / LCD.h / LCD_defines.h
│       └── 16×2 LCD driver
│
├── LM35.c / LM35.h
│       └── Temperature sensing
│
├── RTC.c / RTC.h
│       └── Real-time clock
│
├── delay.c / delay.h
│       └── Timing/delay functions
│
├── pin_connect_block.c / .h
│       └── LPC2148 pin multiplexing
│
├── types.h
│       └── Application data types
│
├── defines.h
│       └── Common project definitions
│
├── main.c
│       └── Main application and system control
│
└── README.md
        └── Project documentation
```

---

## Author / Project

**Kitchen Safety – Heat and Gas Monitoring & Alert System**

**Controller:** LPC2148 ARM7  
**Language:** Embedded C  
**Sensors:** LM35 + MQ-2  
**Display:** 16×2 LCD  
**Input:** 4×4 Matrix Keypad + Switch  
**Alert:** Buzzer + LEDs  
**Timekeeping:** LPC2148 RTC
