#include <Keyboard.h>
#include <SPI.h>
#include <SD.h>
#include <U8glib.h>
const unsigned char bitmap_item_sel_outline [] PROGMEM = {
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};

const int NUM_ITEMS = 20; 
const int MAX_ITEM_LENGTH = 20; 
char menu_items[NUM_ITEMS][MAX_ITEM_LENGTH];
int num_files = 0;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
File root;
File myFile;

String NOTEPAD = "file.txt";

#define BUTTON_UP_PIN 5  
#define BUTTON_SELECT_PIN 7
#define BUTTON_DOWN_PIN 6 

int button_up_clicked = 0; 
int button_select_clicked = 0; 
int button_down_clicked = 0;
int item_selected = 0; 
int item_sel_previous;
int item_sel_next; 
int current_screen = 0;  
void setup() {
  Keyboard.begin();
  if (!SD.begin(4)) {
    return;
  }
  root = SD.open("/");
  listFiles(root);

  u8g.setColorIndex(1);
  drawProductName();

  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
}

void listFiles(File dir) {
  num_files = 0;
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      break;
    }
    if (entry.isDirectory()) {
      continue;
    }
    if (num_files < NUM_ITEMS) {
      strncpy(menu_items[num_files], entry.name(), MAX_ITEM_LENGTH);
      menu_items[num_files][MAX_ITEM_LENGTH - 1] = '\0'; // Ensure null termination
      num_files++;
    }
    entry.close();
  }
}

void drawProductName() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_7x14B);
    u8g.drawStr(40, 20, "D-Ducky");
    u8g.drawStr(55, 35, "By");
    u8g.drawStr(20, 50, "Hacker Nowful");
  } while (u8g.nextPage());
  delay(2000);
}

void Line(String l) {
  int space_1 = l.indexOf(" ");
  if (space_1 == -1) {
    Press(l);
  } else if (l.substring(0, space_1) == "STRING") {
    Keyboard.print(l.substring(space_1 + 1));
  } else if (l.substring(0, space_1) == "DELAY") {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  } else if (l.substring(0, space_1) == "REM") {} 
  else {
    String remain = l;
    while (remain.length() > 0) {
      int latest_space = remain.indexOf(" ");
      if (latest_space == -1) {
        Press(remain);
        remain = "";
      } else {
        Press(remain.substring(0, latest_space));
        remain = remain.substring(latest_space + 1);
      }
      delay(5);
    }
  }
  Keyboard.releaseAll();
}

void Press(String b) {
  if (b.length() == 1) {
    char c = b[0];
    Keyboard.press(c);
  } else if (b.equals("ENTER")) {
    Keyboard.press(KEY_RETURN);
  } else if (b.equals("CTRL")) {
    Keyboard.press(KEY_LEFT_CTRL);
  } else if (b.equals("SHIFT")) {
    Keyboard.press(KEY_LEFT_SHIFT);
  } else if (b.equals("ALT")) {
    Keyboard.press(KEY_LEFT_ALT);
  } else if (b.equals("GUI")) {
    Keyboard.press(KEY_LEFT_GUI);
  } else if (b.equals("UP") || b.equals("UPARROW")) {
    Keyboard.press(KEY_UP_ARROW);
  } else if (b.equals("DOWN") || b.equals("DOWNARROW")) {
    Keyboard.press(KEY_DOWN_ARROW);
  } else if (b.equals("LEFT") || b.equals("LEFTARROW")) {
    Keyboard.press(KEY_LEFT_ARROW);
  } else if (b.equals("RIGHT") || b.equals("RIGHTARROW")) {
    Keyboard.press(KEY_RIGHT_ARROW);
  } else if (b.equals("DELETE")) {
    Keyboard.press(KEY_DELETE);
  } else if (b.equals("PAGEUP")) {
    Keyboard.press(KEY_PAGE_UP);
  } else if (b.equals("PAGEDOWN")) {
    Keyboard.press(KEY_PAGE_DOWN);
  } else if (b.equals("HOME")) {
    Keyboard.press(KEY_HOME);
  } else if (b.equals("ESC")) {
    Keyboard.press(KEY_ESC);
  } else if (b.equals("INSERT")) {
    Keyboard.press(KEY_INSERT);
  } else if (b.equals("TAB")) {
    Keyboard.press(KEY_TAB);
  } else if (b.equals("END")) {
    Keyboard.press(KEY_END);
  } else if (b.equals("CAPSLOCK")) {
    Keyboard.press(KEY_CAPS_LOCK);
  } else if (b.equals("F1")) {
    Keyboard.press(KEY_F1);
  } else if (b.equals("F2")) {
    Keyboard.press(KEY_F2);
  } else if (b.equals("F3")) {
    Keyboard.press(KEY_F3);
  } else if (b.equals("F4")) {
    Keyboard.press(KEY_F4);
  } else if (b.equals("F5")) {
    Keyboard.press(KEY_F5);
  } else if (b.equals("F6")) {
    Keyboard.press(KEY_F6);
  } else if (b.equals("F7")) {
    Keyboard.press(KEY_F7);
  } else if (b.equals("F8")) {
    Keyboard.press(KEY_F8);
  } else if (b.equals("F9")) {
    Keyboard.press(KEY_F9);
  } else if (b.equals("F10")) {
    Keyboard.press(KEY_F10);
  } else if (b.equals("F11")) {
    Keyboard.press(KEY_F11);
  } else if (b.equals("F12")) {
    Keyboard.press(KEY_F12);
  } else if (b.equals("SPACE")) {
    Keyboard.press(' ');
  }
}

void attack() {
  if (myFile) {
    Keyboard.begin();
    String line = "";
    while (myFile.available()) {
      char m = myFile.read();
      if (m == '\n') {
        Line(line);
        u8g.firstPage();
        do {
          u8g.setFont(u8g_font_7x14);
          u8g.drawStr(0, 10, "Executing Script:");
          u8g.drawStr(0, 28, line.c_str());
        } while (u8g.nextPage());
        delay(700);
        line = "";
      } else if ((int)m != 13) {
        line += m;
      }
    }
    Line(line);
    myFile.close();
  }
  Keyboard.end();
  current_screen = 0;
}

void loop() {
  if (current_screen == 0) {
    if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) { 
      item_selected--;
      button_up_clicked = 1; 
      if (item_selected < 0) {
        item_selected = num_files - 1;
      }
    }
    else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) { 
      item_selected++;
      button_down_clicked = 1; 
      if (item_selected >= num_files) { 
        item_selected = 0;
      }
    } 
    if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) { 
      button_up_clicked = 0;
    }
    if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) { 
      button_down_clicked = 0;
    }
  }
  if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { 
    button_select_clicked = 1;
    if (current_screen == 0) {
      myFile = SD.open(menu_items[item_selected]);
      attack();
    }
  }
  if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) { 
    button_select_clicked = 0;
  }
  
  item_sel_previous = item_selected - 1;
  if (item_sel_previous < 0) {item_sel_previous = num_files - 1;}
  item_sel_next = item_selected + 1;  
  if (item_sel_next >= num_files) {item_sel_next = 0;} 
  
  u8g.firstPage();
  do {
    if (current_screen == 0) { 
      u8g.drawBitmapP(0, 22, 128 / 8, 21, bitmap_item_sel_outline);
      u8g.setFont(u8g_font_7x14);
      u8g.drawStr(25, 15, menu_items[item_sel_previous]);
      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(25, 15 + 20 + 2, menu_items[item_selected]); 
      u8g.setFont(u8g_font_7x14);
      u8g.drawStr(25, 15 + 20 + 20 + 2 + 2, menu_items[item_sel_next]); 
      u8g.drawBox(125, 64 / num_files * item_selected, 3, 64 / num_files);
    } else if (current_screen == 1) {
    }
  } while (u8g.nextPage());
}
