<div align="center">
 <img src="https://avatars.githubusercontent.com/u/180070439?v=4" alt="logo" width="200" height="auto" />
 <h1>G-Ducky</h1>
  <a href="https://github.com/Cypher-Panda" title="Go to GitHub repo"><img src="https://img.shields.io/static/v1?label=Cypher Panda&message=G-Ducky&color=green&logo=github" alt="Cypher Panda - G-Ducky"></a>
</div> 

G-Ducky is a USB HID device based on the Arduino Pro Micro, designed to execute pre-defined scripts from an SD card, simulating keystrokes to automate tasks. The device features an OLED display for user interaction, allowing selection and execution of scripts stored on the SD card.

## 🎯 Features

- **USB HID Automation:** Executes DuckyScript-like commands stored in text files on an SD card.
- **OLED Display Menu:** Navigate through scripts stored on the SD card using an intuitive menu system.
- **Three-Button Control:** Easily navigate the menu, select scripts, and initiate execution with three buttons.
- **Script Feedback:** Displays the current script execution progress on the OLED screen.


## ⚙️ Hardware Requirements

- Arduino Pro Micro
- SSD1306 128x64 OLED Display
- SD Card Module
- Three Push Buttons
- Necessary wiring and power supply

## 💻⚙️ Software Requirements

- Arduino IDE
- `Keyboard.h` library
- `U8glib.h` library
- `SD.h` library

## 🪛 Wiring

**OLED Display:**

- SDA to Pro Micro SDA (Pin 2)
- SCL to Pro Micro SCL (Pin 3)

**SD Card Module:**

- MISO to Pro Micro MISO (Pin 14)
- MOSI to Pro Micro MOSI (Pin 16)
- SCK to Pro Micro SCK (Pin 15)
- CS to Pro Micro CS (Pin 10)

**Buttons:**

- **UP:** Connect to Pin 5
- **SELECT:** Connect to Pin 7
- **DOWN:** Connect to Pin 6

## 👨🏻‍💻 Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/Cypher-Panda/G-Ducky
    cd G-Ducky
    ```

2. Install the necessary libraries via the Arduino IDE or download them from the Library Manager.

3. Upload the code to your Arduino Pro Micro.

## 🧩 Usage

1. Power on the device.
2. Navigate the menu using the UP and DOWN buttons.
3. Select a script using the SELECT button.
4. The script will execute, simulating the keystrokes defined in the file.

## </> Example Script (DuckyScript)

```objectivec
STRING Hello World
ENTER
DELAY 1000
CTRL ALT DELETE
```
## 💡 Troubleshooting

- **SD Card Initialization Failed:** Check the SD card connections and format.
- **Script Execution Issues:** Ensure the script files are properly formatted.
- **OLED Display Not Working:** Verify the wiring and connections.

## 🤝 Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

## 📋 License

This project is licensed under the MIT License. See the LICENSE file for more details.

## 🤖 Author

**Hacker Nowful**

Hacker Nowful is a cybersecurity enthusiast with expertise in developing innovative security tools and educational content. For more projects, visit the [GitHub profile](https://github.com/HackerNowful).

## 🤝 Acknowledgments

Special thanks to the open-source community for Library resources.
