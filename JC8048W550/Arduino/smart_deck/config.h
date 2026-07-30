/*******************************************************************************
 * config.h - SmartDeck Hardware Configuration
 *
 * Pin definitions, display selection and layout constants.
 * Grid layout is auto-calculated based on SCREEN_INCH.
 ******************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

//=============================================================================
// DEVICE INFO
//=============================================================================
#define DEVICE_NAME   "Smart Deck"

//=============================================================================
// DISPLAY SELECTION (uncomment ONE)
//=============================================================================
// #define ESP32_3248S035       // 3.5" 480x320 (ST7796 SPI)
// #define ESP32_JC8048W550     // Guition JC8048W550 - 5" 800x480 (RGB)
// #define ESP32_8048S070       // 7.0" 800x480 (RGB)
#define ESP32_TOUCHDOWN        // Dustin Watts ESP32 TouchDown - 3.5" 480x320 (ILI9488)

//=============================================================================
// SCREEN SETTINGS
//=============================================================================
#if defined(ESP32_TOUCHDOWN)
  #define SCREEN_INCH       3
  #define SCREEN_WIDTH      480
  #define SCREEN_HEIGHT     320
  #define SCREEN_ROTATION   1       // Landscape (480x320)
#else
  #define SCREEN_INCH       5       // 3, 5, or 7 (affects grid layout)
  #define SCREEN_WIDTH      800
  #define SCREEN_HEIGHT     480
  #define SCREEN_ROTATION   0       // 0, 1, 2, 3 (0°, 90°, 180°, 270°)
#endif

//=============================================================================
// TOUCH SETTINGS
//=============================================================================
#define TOUCH_ROTATION    ROTATION_INVERTED   // ROTATION_NORMAL, ROTATION_INVERTED

//=============================================================================
// GRID LAYOUT (Auto-calculated based on SCREEN_INCH)
//=============================================================================
#if SCREEN_INCH == 3
  #define CELL_W              80
  #define CELL_H              80
  #define CELL_PADDING        10
  #define CORNER_RADIUS       20
  #define TITLE_BOX_HEIGHT    15
  #define TITLE_BOX_MARGIN_Y  2
  #define STROKE_WIDTH        2
#elif SCREEN_INCH == 5
  #define CELL_W              110
  #define CELL_H              110
  #define CELL_PADDING        17
  #define CORNER_RADIUS       20
  #define TITLE_BOX_HEIGHT    35
  #define TITLE_BOX_MARGIN_Y  3
  #define STROKE_WIDTH        2
#elif SCREEN_INCH == 7
  #define CELL_W              90
  #define CELL_H              90
  #define CELL_PADDING        17
  #define CORNER_RADIUS       15
  #define TITLE_BOX_HEIGHT    35
  #define TITLE_BOX_MARGIN_Y  3
  #define STROKE_WIDTH        2
#else
  #error "Invalid SCREEN_INCH! Use 3, 5, or 7"
#endif

//=============================================================================
// TOUCH PANEL PINS
//=============================================================================
#if defined(ESP32_TOUCHDOWN)
  // FT6236 (I2C) - ESP32 TouchDown
  #define TOUCH_SDA         21
  #define TOUCH_SCL         22
  #define TOUCH_INT         27
  #define TOUCH_WIDTH       SCREEN_WIDTH
  #define TOUCH_HEIGHT      SCREEN_HEIGHT
#else
  // GT911 - Guition / Sunton displays
  #define TOUCH_SDA         19
  #define TOUCH_SCL         20
  #define TOUCH_INT         0
  #define TOUCH_RST         38
  #define TOUCH_WIDTH       SCREEN_WIDTH
  #define TOUCH_HEIGHT      SCREEN_HEIGHT
#endif

//=============================================================================
// SD CARD
//=============================================================================
#if defined(ESP32_TOUCHDOWN)
  #define SD_CS             25
  #define SD_SCK            18
  #define SD_MISO           19
  #define SD_MOSI           23
#else
  #define SD_CS             10
#endif

//=============================================================================
// NEOPIXEL LED (optional external ring on broken-out GPIO)
//=============================================================================
#if defined(ESP32_TOUCHDOWN)
  #define LED_PIN           13
#else
  #define LED_PIN           18
#endif
#define LED_COUNT         16
#define LED_OFFSET        0   // LED ring rotation offset in degrees (0-359)

//=============================================================================
// ROTARY ENCODER (AS5600) - shares I2C bus with touch on TouchDown
//=============================================================================
#if defined(ESP32_TOUCHDOWN)
  #define KNOB_SDA          21
  #define KNOB_SCL          22
#else
  #define KNOB_SDA          17
  #define KNOB_SCL          19
#endif
#define KNOB_THRESHOLD    25

//=============================================================================
// BACKLIGHT PWM
//=============================================================================
#define BL_PWM_CHANNEL    0
#define BL_PWM_FREQ       1500
#define BL_PWM_RESOLUTION 8

//=============================================================================
// COMMUNICATION
// 0: Direct USB Serial to PC
// 1: ESP-NOW to dongle
//=============================================================================
#define DONGLE_MODE       0
#define RECEIVER_MAC      { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF }

#endif // CONFIG_H
