🏠🔥 Kitchen Safety Heat & Gas Monitoring System
An LPC2148-based embedded system for kitchen temperature and gas monitoring system.
**Monitor. Detect. Alert. Record.**

📌 Project Overview
The **Kitchen Safety Heat & Gas Monitoring System** is an embedded safety project built around the **LPC2148 ARM7 microcontroller**. It monitors kitchen temperature using an **LM35 temperature sensor** and gas levels using an **MQ-2 gas sensor**.

The measured information and real-time clock (RTC) date/time are shown on a 16×2 LCD. If a configured temperature or gas threshold is crossed, the system activates a buzzer and LED alert. It also records the latest threshold-crossing event with an RTC timestamp and displays that event periodically.

A password-protected settings menu allows the user to adjust the RTC, sensor thresholds, and password through a 4×4 matrix keypad.

🎯 Objectives
• 🌡️ Continuously monitor kitchen temperature with the LM35.

• 💨 Monitor the analog output of the MQ-2 gas sensor.

• 🚨 Indicate unsafe temperature or gas readings using the buzzer, LED, and LCD.

• 🕒 Display RTC time and date.

• 🧾 Store the most recent unsafe threshold-crossing event and its time.

• 🔐 Protect configuration changes with a keypad-entered password.

• ⚙️ Allow the user to edit RTC settings and temperature/gas thresholds.

🧰 Hardware Components
Component	Purpose
🧠 LPC2148 (ARM7) -->	Reads sensors and coordinates the system

🌡️  LM35 -->	Provides an analog signal proportional to temperature

💨 MQ-2 gas sensor -->	Provides an analog signal related to gas/smoke concentration

📟 16×2 LCD --> Displays time, date, temperature, gas status, menus, and alerts

⌨️ 4×4 matrix keypad -->	Password entry and settings-menu navigation

🔔 Buzzer -->	Audible alert when an unsafe condition is detected

💡 LED -->	Visual alarm indication

🕒 On-chip RTC -->	Provides time/date for the display and event records

🔌 Power supply / development board -->	Powers the controller and connected modules

🖥️ Software & Tools
• Language: Embedded C

• Target controller: LPC2148

• IDE/toolchain: Keil µVision or a compatible ARM7 toolchain

• Programming utility: Flash Magic (as listed in the project requirements)

• Simulation (optional): Proteus, depending on component/model availability

🧩 System Block Diagram
![image alt](https://github.com/SriNagaVijaya/Kitchen-Safety-Heat-and-Gas-Monitoring-System/blob/main/Block%20Diagram.png?raw=true)
Kitchen safety system block diagram

🧪 Hardware Prototype

Kitchen safety system hardware prototype

Main signal flow: LM35 and MQ-2 provide sensor signals to the LPC2148. The controller reads analog values through its ADC, checks configured thresholds, and updates the LCD and alarm outputs. The RTC supplies date/time information, while the keypad and switch provide user input.

🔄 Program Flowchart
The flowchart below describes the main program behaviour implemented in `main.c`.


flowchart TD

![image alt](https://github.com/SriNagaVijaya/Kitchen-Safety-Heat-and-Gas-Monitoring-System/blob/main/Flow%20chart.webp.png?raw=true)
  


⚙️ How It Works

1. **🚀 Startup:** The firmware initializes the LCD, ADC, gas-sensor input, RTC, keypad, timer, interrupt input, buzzer, and LED. Startup screens are shown.

2. **🌡️ Temperature sampling:** The LM35 analog output is read through the ADC. The temperature conversion in `LM35.c` uses the ADC voltage multiplied by 100.

3. **💨 Gas sampling:** The MQ-2 analog reading is obtained through the ADC and compared with the configured gas threshold.

4. **🚨 Hazard detection:** When a reading crosses from safe to above its configured threshold, the firmware records the event and activates the buzzer/LED alert.

5. **📟 LCD monitoring:** The LCD displays RTC time/date, temperature, and a gas unsafe-status indicator.

6. **🧾 Event display:** The latest recorded temperature or gas event and its timestamp are shown periodically for approximately three seconds.

7. **🔕 Alarm silencing:** Switch 2 is checked as the alarm-silence input in the main loop. The alarm may turn on again while an unsafe condition remains active, according to the program logic.

8. **🔐 Secure settings:** Switch 1 requests the settings menu. The user must enter the password using the keypad. Three incorrect attempts trigger a lockout countdown.

9. **⚙️ Configuration:** After successful password validation, the user can edit RTC fields, temperature/gas thresholds, or the password.

🚦 Alarm & LCD Indicators
Indicator	Meaning
🌡️ `TEMP IS HIGH!`	Temperature crossed the configured temperature limit

💨 `GAS IS HIGH!`	MQ-2 reading crossed the configured gas limit

🔔 Buzzer ON	Audible warning output is active

💡 LED ON	Visual warning output is active

🔐 `Enter Password:`	Settings access is requesting a password

⛔ `Access Denied`	Password validation failed

🔒 `System Locked`	Three failed attempts occurred; countdown is displayed

🧾 Latest event popup	Shows the most recently saved event and time

🧑‍💻 Source Files


File	Responsibility
`main.c`	Main application, initialization, monitoring loop, alarms, event logging, password check, and settings menu

`LCD.c`	LCD command/data writes, initialization, and number/string display helpers

`ADC.c`	ADC initialization and conversion of analog input to a 10-bit digital value

`LM35.c`	LM35 temperature conversion helpers

`KPM.c`	4×4 keypad scanning and key lookup

`RTC.c`	RTC initialization and time/date read/write helpers

> 📁 The source files shown above depend on project header files such as `types.h`, `LCD.h`, `LCD_defines.h`, `ADC.h`, `ADC_defines.h`, `LM35.h`, `KPM.h`, `KPM_defines.h`, `RTC.h`, and `delay.h`. Include the matching header and support files from your working project when building or uploading the complete source to GitHub.

🛠️ Configuration Values
The current `main.c` defines these initial values:

Setting	Initial value in source
🌡️ Temperature threshold	`25` °C

💨 Gas ADC threshold	`300` (10-bit ADC scale: 0–1023)

🔐 Default password	`1234`

🧾 Event popup interval	`10,000 ms` (10 seconds)

🧾 Event popup duration	`3,000 ms` (3 seconds)

⏳ Settings menu wait	`30,000 ms` (30 seconds)

🔔 Buzzer output	P0.27, as defined in `main.c`

💡 LED output	P0.25, as defined in `main.c`

⌨️ Switch 2 input	P0.0, as defined in `main.c`

⚡ Switch 1	External interrupt input, configured in `setup_switch1()`

**Important:** Check the actual board wiring and pin-configuration header files before using these pin details. The comments in source files and the physical development board wiring should be verified against each other.

🧪 Suggested Test Cases
Test	Action	Expected behaviour
1️⃣ Normal monitoring	Keep both readings below their limits	LCD continues showing time/date and temperature/status

2️⃣ High temperature	Raise the LM35 reading above the configured limit	Temperature alert, buzzer/LED indication, and event timestamp

3️⃣ High gas reading	Raise the MQ-2 analog reading above the configured limit	Gas alert, buzzer/LED indication, and event timestamp

4️⃣ Event popup	Wait after at least one event has been recorded	Latest event appears periodically on the LCD

5️⃣ Correct password	Press Switch 1 and enter the configured password	Settings menu opens

6️⃣ Incorrect password	Enter an incorrect password	Access-denied message and brief alarm indication

7️⃣ Three failed attempts	Enter an incorrect password three times	System Locked message and countdown

8️⃣ Change threshold	Open settings and select a new limit	New threshold is used during subsequent checks

9️⃣ Silence input	Press Switch 2 while an alarm is active	Alarm output is silenced while the input is detected; verify behaviour under           persistent unsafe readings

▶️ Build & Flash (General Steps)
1. Create/open an LPC2148 project in Keil µVision or your chosen compatible toolchain.
2. Add `main.c`, the driver `.c` files, and all required matching header/support files.
3. Confirm the target device, startup file, clock settings, include paths, and pin mappings.
4. Build the project and resolve any missing-header, linker, or device-configuration errors.
5. Generate the appropriate output file (commonly HEX, depending on the toolchain settings).
6. Use the board's supported programming method, such as Flash Magic where applicable, to program the LPC2148.
7. Power the board and test each case above carefully.

⚠️ Safety & Engineering Notes
• MQ-2 readings depend on sensor warm-up, calibration, load resistance, environment, and the specific module. The configured ADC threshold is a project setting, **not a calibrated gas concentration in ppm**.

• Test alarm behaviour using safe, controlled methods. Do not deliberately release flammable gas or create a fire hazard.

• A development-board demonstration is not a substitute for certified gas detectors, smoke alarms, ventilation, or professional safety equipment.

• Confirm sensor voltage levels and power requirements before connecting modules to the LPC2148.

🚀 Future Improvements
• 📈 Calibrate MQ-2 readings against a suitable reference and document the method.

• 🌀 Drive a properly rated ventilation fan through a suitable driver stage and protection circuitry.

• 💾 Store multiple event records in non-volatile memory.

• 📡 Add remote notifications or wireless monitoring.

• 🧪 Add repeatable calibration and fault-detection tests.

• 🔐 Improve password handling and persistent configuration storage.

👩‍🔧 Project Summary
This project demonstrates the integration of **ARM7 microcontroller programming, ADC-based sensor acquisition, LCD interfacing, RTC timekeeping, keypad scanning, external interrupts, threshold checking, and alarm control** in one embedded application.

🏡 Safer kitchens through embedded systems! 🔥💨🚨
