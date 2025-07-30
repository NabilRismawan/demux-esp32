// Definisikan pin ESP32 yang terhubung ke custom chip
#define PIN_INPUT_DATA 18 // Pin untuk mengirim data ke IN
#define PIN_SELECTOR   19 // Pin untuk mengontrol SEL
#define LED 0
// Pin EN (Enable) bisa dihubungkan langsung ke GND di diagram
// agar chip selalu aktif.

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(PIN_INPUT_DATA, OUTPUT);
  pinMode(PIN_SELECTOR, OUTPUT);
  digitalWrite(PIN_INPUT_DATA, HIGH);
  Serial.begin(115200);
}

void loop() {
  Serial.println("SEL -> LOW. Output di Y0.");
  digitalWrite(PIN_SELECTOR, LOW);

  // Kirim sinyal HIGH ke pin IN
  delay(2000); // Tunggu 2 detik


  Serial.println("SEL -> HIGH. Output di Y1.");
  digitalWrite(PIN_SELECTOR, HIGH);

  delay(2000); // Tunggu 2 detik
}