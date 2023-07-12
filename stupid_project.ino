#include <TridentTD_LineNotify.h>

#define SSID        "FF1_15"      // บรรทัดที่ 11 ให้ใส่ ชื่อ Wifi ที่จะเชื่อมต่อ
#define PASSWORD    "123456789"     // บรรทัดที่ 12 ใส่ รหัส Wifi
#define LINE_TOKEN  "pgVLVql6bBwFIsG7I6gyCskO21PbHQfTCWH8xLU4sVs"   // บรรทัดที่ 13 ใส่ รหัส TOKEN ที่ได้มาจากข้างบน

int siren = D1;
int light = D2;
int val = 0;

void setup() {
  Serial.begin(115200); 
  Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  // set pin
  pinMode(light, OUTPUT);  // sets the pin as output
  pinMode(siren, OUTPUT);

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
}

/*
  // ตัวอย่างส่งข้อความ
  LINE.notify("อุณหภูมิ เกินกำหนด");
*/

void loop() {
  val = analogRead(analogPin);  //อ่านค่าสัญญาณ analog 
  Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(val); // พิมพ์ค่าของตัวแปร val
  if (val > 500) { // สามารถกำหนดปรับค่าได้ตามสถานที่ต่างๆ
    LINE.notify("อุณหภูมิ เกินกำหนด");
    digitalWrite(light, HIGH); // สั่งให้ LED ติดสว่าง
    digitalWrite(siren, HIGH);
  }
  delay(1000);
}