# SmartDeck Hardware Assembly Guide

## Prerequisites

### 3D Printed Parts
Print all parts from the `3D Print Files` folder with the following settings:
- **Supports:** Enabled (required for overhangs)
- **Infill:** 15-20% recommended
- **Layer Height:** 0.2mm or finer for better tolerances

**Parts List:**
- Main Body (1x)
- Knob (1x)
- AS5600 Holder (1x)
- Back Cover (1x)
- Stand/Feet (optional, 1x)

### Bill of Materials

| Item | Description | Source |
|------|-------------|--------|
| 25×52×15 Ball Bearing | Deep-groove ball bearing | [Link](https://simmering.pl/en/deep-groove-ball-bearings/28183-6205-zz-nectech-25x52x15-deep-groove-ball-bearing.html) |
| AS5600 Magnetic Encoder Module | Includes matching magnet | [Link](https://tr.aliexpress.com/item/1005009252608246.html) |
| NeoPixel RGB LED Ring (16 LEDs) | WS2812-compatible, ~53mm inner / ~66mm outer diameter | [Link](https://tr.aliexpress.com/item/33039423907.html) |
| 90° Type-C Male to Female Adapter | Prefer "40Gbps" printed version | [Link](https://tr.aliexpress.com/item/1005006997812852.html) |
| 6×3mm Round Neodymium Magnets | 80-150 pieces for back cover and stand | [Link](https://www.temu.com/tr/80-150pcs-6x3mm-round-magnets-strong-neodymium--mini-refrigerator-whiteboard-magnets-durable-metal-construction-for-office-kitchen-fridge-organization-magnets-for-fridge-kitchen-accessories-sleek-metallic---magnets-g-601101415928711.html) |
| 1.25mm to Dupont 2.54 Terminal Cable (4-Pin) | For display connector routing (optional) | [Link](https://tr.aliexpress.com/item/1005006621865408.html) |
| M2 Screws | Various lengths: M2×3mm, M2×4mm, M2×5mm | [Link 1](https://www.temu.com/goods.html?_bg_fs=1&goods_id=601099519474986&sku_id=17592228808109) / [Link 2](https://www.aliexpress.us/item/3256804422855415.html) |
| Soldering Iron | For wiring connections | — |
| Cables/Wires | For external connections | — |
| Tape | Electrical or general-purpose | — |

---

## Assembly Instructions

### Step 1: Prepare the Knob Assembly

1. **Install the ball bearing:**
   - Press the **25×52×15mm ball bearing** into the knob print until it sits flush.
   - It should be a snug fit; apply even pressure around the edges.

2. **Attach the magnet:**
   - Locate the small hole on the underside of the knob (center).
   - Take the **magnet included with the AS5600 module** and apply a small amount of adhesive to its back only (the side that will contact the knob).
   - **Important:** Keep the face of the magnet that will face the sensor completely free of adhesive. Any glue residue on this surface can cause signal fluctuations and erratic readings.
   - Press the magnet into the hole and allow it to cure.

---

### Step 2: Prepare the SD Card

The ESP32 display requires a FAT32-formatted SD card.

1. Insert your SD card into your computer.
2. Format it as **FAT32**.

> **Note for large capacity cards (64GB+):** Windows cannot natively format cards larger than 32GB as FAT32. Use the free tool **guiformat** from:
> http://ridgecrop.co.uk/index.htm?guiformat.htm

3. Once formatted, insert the SD card into the display's SD card slot.

---

### Step 3: Mount the Display

1. Attach the **90° Type-C adapter** to the display's USB-C port.
2. Place the display into the main body with the USB connector oriented toward the knob side.
3. Align the four mounting holes and secure with **M2×4mm or M2×5mm screws** (the screw holes are approximately 5mm deep).

---

### Step 4: Install the NeoPixel LED Ring

1. **Solder wires to the LED ring:**
   - Solder individual wires to the **5V**, **GND**, and **DI (Data In)** pads.
   - Cut wires longer than needed; you can trim them later.

2. **Mount the ring:**
   - Route the wires through the cable channel in the main body.
   - Press the **16-LED NeoPixel ring** into the knob-side recess, aligning the four screw holes.
   - Secure with **M2×3mm or M2×3.5mm screws** (hole depth is ~7.5mm; do not exceed this).

---

### Step 5: Prepare and Install the AS5600 Encoder Module

1. **Solder wires to the AS5600 module:**
   - Attach wires to: **SDA**, **SCL**, **VCC**, and **GND** pads.

2. **Mount the module in its holder:**
   - Insert the AS5600 module into the **AS5600 Holder** print with wires passing through the designated holes.
   - The fit should be snug. If there's slight play, use a small amount of adhesive to secure it.

3. **Install the holder in the main body:**
   - Position the holder inside the main body so the **sensor faces the knob hole** (where the magnet will be).
   - Secure with four **M2×5mm screws** (hole depth is ~7.5mm).

---

### Step 6: Clean the Main Body and Install the Knob

> **Important:** Before proceeding, thoroughly clean all support material residue from the main body, especially inside the bearing seat. Leftover supports can prevent proper seating and cause friction.

1. Take the knob assembly (with bearing and magnet installed).
2. Align it with the bearing seat on the main body.
3. Press firmly until the bearing snaps into place. It should rotate smoothly.

---

### Step 7: Prepare the Back Cover

1. Remove all support material from the back cover print.
2. Insert **6×3mm neodymium magnets** into each magnet slot.
   - **Critical:** Ensure all magnets have the **same polarity orientation** (e.g., all north-facing up).
   - Some holes may be tight due to printer tolerances; apply gentle pressure.
   - Some may be loose; proceed to the next step.
3. Once all magnets are seated, cover them with a strip of tape to prevent them from dislodging.

---

### Step 8: Prepare the Stand (Optional)

1. Insert **6×3mm neodymium magnets** into the stand's magnet slots.
2. **Critical:** These magnets must be in the **opposite orientation** to those in the back cover (so they attract, not repel).
3. Double-check each magnet before fully seating it. A reversed magnet will cause the stand and body to repel each other.
4. Secure with tape if needed.

---

### Step 9: Wiring Connections

You have two options for connecting the components to the display's GPIO pins:

| Method | Pros | Cons |
|--------|------|------|
| **Soldering directly to pins** | Most reliable, clean | Requires soldering skill |
| **Dupont connectors** (included with display) | No soldering needed | Bulkier, may come loose |

**Recommended:** Direct soldering for best long-term reliability.

If you choose the Dupont connector method, you'll need to connect your soldered component wires to the Dupont cables. You can do this by twisting the wires together—this is the quickest solution but also the least clean. For a more secure connection, solder the component wires directly to the Dupont cable ends or use crimp connectors.

#### AS5600 Encoder Connections

| AS5600 Pin | ESP32 GPIO | Notes |
|------------|------------|-------|
| SDA | Pin 19 | I²C Data |
| SCL | Pin 20 | I²C Clock |
| VCC | 3.3V | **Do not use 5V** |
| GND | GND | |

#### NeoPixel LED Ring Connections

| NeoPixel Pin | ESP32 GPIO | Notes |
|--------------|------------|-------|
| DI (Data In) | Pin 18 | Data signal |
| 5V | 5V | Power |
| GND | GND | |

---

### Step 10: Final Assembly

1. Route all wires neatly inside the enclosure.
2. Align the **back cover** with the USB cutout facing the correct direction.
3. Secure with **M2×5mm screws** into the main body.
4. Attach the **stand** to the back cover—the magnets should snap together satisfyingly.

---

## Software Setup

1. Connect SmartDeck to your computer via USB.
2. Download and install the **SmartDeck** application from:
   
   👉 **https://github.com/ozancs/smartdeck/releases**

3. Launch the application.
4. Click **"Install Firmware"** in the bottom-right corner.
5. Select your device's **COM port** from the dropdown.
6. Click **Install** to flash the firmware to your ESP32 display.
7. Once complete, configure your buttons, LED colors, themes, and macros.

---

**Enjoy your SmartDeck!**
