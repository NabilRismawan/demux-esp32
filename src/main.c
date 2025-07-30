// For information and examples see:
// https://link.wokwi.com/custom-chips-alpha

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

// define the pins that were using
typedef struct {
  pin_t pin_in;
  pin_t pin_sel;
  pin_t pin_en;
  pin_t pin_y0;
  pin_t pin_y1;
} chip_state_t;

// update logic function
static void update_demux(chip_state_t *chip) {
  // Baca nilai dari semua pin input
  // Pin EN di set sebagai active-low
  uint32_t enable = pin_read(chip->pin_en);
  uint32_t select = pin_read(chip->pin_sel);
  uint32_t input  = pin_read(chip->pin_in);

  // active low logic
  if (enable == HIGH) {
    pin_write(chip->pin_y0, LOW);
    pin_write(chip->pin_y1, LOW);
    return;
  }

  // Logika demultiplexer utama
  if (select == LOW) {
    pin_write(chip->pin_y0, input);
    pin_write(chip->pin_y1, LOW);
  } else {
    pin_write(chip->pin_y0, LOW);
    pin_write(chip->pin_y1, input);
  }

  printf("DEBUG: enable=%d, sel=%d, in=%d → Y0=%d, Y1=%d\n",
  enable, select, input,
  (select == LOW ? input : 0),
  (select == HIGH ? input : 0));

}

// Fungsi ini akan dipanggil setiap kali pin yang diawasi berubah nilainya
void on_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t*)user_data;
  update_demux(chip);
}

// Fungsi inisialisasi chip, dipanggil sekali saat simulasi dimulai
void chip_init() {
  // Alokasikan memori untuk state chip
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  // assign pin
  chip->pin_in = pin_init("IN", INPUT);
  chip->pin_sel = pin_init("SEL", INPUT);
  chip->pin_en = pin_init("EN", INPUT_PULLUP); // Gunakan PULLUP agar default aktif (dalam keadaan mati)
  chip->pin_y0 = pin_init("Y0", OUTPUT);
  chip->pin_y1 = pin_init("Y1", OUTPUT);

  // Atur agar fungsi `on_pin_change` dipanggil setiap kali IN, SEL, atau EN berubah
  const pin_watch_config_t config = {
    .user_data = chip,
    .edge = BOTH, // Panggil saat sinyal naik (RISING) maupun turun (FALLING)
    .pin_change = on_pin_change,
  };
  pin_watch(chip->pin_in, &config);
  pin_watch(chip->pin_sel, &config);
  pin_watch(chip->pin_en, &config);

  // Jalankan logika sekali di awal untuk menetapkan state awal
  update_demux(chip);

  printf("Custom C Chip: 1-to-2 DEMUX Initialized\n");
}