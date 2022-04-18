/****************************************************
 * ก่อน upload ให้กด Ctrl+K เพื่อเปิด folder ของโปรเจคขึ้นมา
 *  และนำ ไฟล์รูปภาพ dial.jpg, dial.png, good_cat.png
 *  ไปวางบน SD Card แล้วนำ SD card เสียบที่ BlynkGO Board
 * 
 ****************************************************/

#include <BlynkGOv2.h>

FONT_DECLARE(NotoSansBI_36);

GImage background; //(img_good_cat);
GCircle cir;
  GImage dial(cir);
    GLine  pin(dial);
    GLabel txt(dial);

void setup() {
  Serial.begin(115200); Serial.println();
  BlynkGO.begin();

  background= "SD://good_cat.png";
  cir.radius(119);
  cir.color(TFT_BLACK);
  cir.opa(200);                 // โปร่งใส 255
  cir.clickable(true);          // ให้สัมผัสได้
  cir.dragable(true);           // ให้ลากไปมาได้
    dial = "SD://dial.png";     // "SD://dial.jpg"
      txt.font(NotoSansBI_36);
      pin.thickness(4, TFT_RED);

  // สร้าง animation กำหนดค่า speed จาก 0->240 ในเวลา 5 วินาที
  dial_anim_speed(0,240,5000); 
}

void loop() {
  BlynkGO.update();
}

void dial_set_speed(uint8_t speed){
  speed = constrain(speed,0,240);
  txt   = speed; // พอดี dial ที่เป็นรูป ค่า speed = angle ของมุมที่จะหมุนพอดี
  Point dial_c  = Point(119,118); // จดศูนย์กลางหน้าปัด
  Point p0 = Point(105, speed, 150, dial_c, CLOCKWISE); // แขนยาว 105px ด้วยมุม speed มีมุมเริ่มต้น 150 นับตามเข็ม
  Point p1 = Point( 65, speed, 150, dial_c, CLOCKWISE); // แขนยาว  65px ด้วยมุม speed มีมุมเริ่มต้น 150 นับตามเข็ม 
  pin.setPoints(p0,p1);
}

void dial_anim_speed(uint8_t from, uint8_t to, uint32_t ms ){
  static GAnimation anim;
  anim.init(dial, [](GWidget*widget, int16_t speed){
    dial_set_speed(speed);
  },from, to, ms);      //
  anim.repeat(true);    // ให้เล่นซ้ำด้วย
  anim.playback(true);  // ให้เล่นย้อนค่ากลับด้วย
  anim.create();
}
