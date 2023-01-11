#include <SPI.h>
#include <WiFi.h>
#include <LiquidCrystal.h>
#define UPDATE_TIME 20
#define servoPin D7
#define NOTE_Low_SO  392
#define NOTE_Low_LA  440
#define NOTE_Low_SI  494
#define NOTE_Med_DO  523
#define NOTE_Med_RE  587
#define NOTE_Med_MI  659
#define NOTE_Med_FA  698
#define NOTE_Med_SO  784
#define NOTE_Med_LA  880
#define NOTE_Med_SI  988
#define NOTE_High_DO  1046
#define NOTE_High_RE  1175
#define NOTE_High_MI  1318
#define NOTE_High_FA  1397
#define NOTE_High_SO  1568
int speakerPin = D3;
int degree = 0;
int endcode;

int convertAngleToImp(int degree){
  float a = 2000/180;
  float b = 500;
  return int(a*degree+b);
}
void ServoControl(int degree) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(convertAngleToImp(degree));
  digitalWrite(servoPin,LOW);
  delay(UPDATE_TIME);
}

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

char ssid[] = "你打鼓很吵";      //  your network SSID (name)
char pass[] = "12101202";   // your network password

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);      // initialize serial communication
  pinMode(LED1, OUTPUT);      // set the LED1 pin mode
  pinMode(LED2, OUTPUT);      // set the LED2 pin mode
  lcd.begin(16, 2);
  
  pinMode(speakerPin, OUTPUT);
  pinMode(BT1, INPUT);
  
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }


String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}

bool light =false;
bool lock=false;
String ss="";
int i=0;
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  
  if (client) {                             // if you get a client,
    Serial.println("WIFI Demo");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();


          // the content of the HTTP response follows the header:
           client.print("<font color=\"blue\" size=\"7\">======== Mind 2 Lock ========</font><br>");

           client.print(" <div style=\"top:80px;left:1px;position:absolute;\">");
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'1\'\" <type=\"button\">1</button>");
           client.print(" </div>");
            
           client.print(" <div style=\"top:80px;left:111px;position:absolute;\">");
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'2\'\" <type=\"button\">2</button>");
           client.print(" </div>");

           client.print(" <div style=\"top:80px;left:221px;position:absolute;\">");
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'3\'\" <type=\"button\">3</button>");
           client.print(" </div>");
            
           client.print(" <div style=\"top:180px;left:1px;position:absolute;\">");
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'4\'\" <type=\"button\">4</button>");
           client.print(" </div>");

           client.print(" <div style=\"top:180px;left:111px;position:absolute;\">");
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'5\'\" <type=\"button\">5</button>");
           client.print(" </div>");
           
           client.print(" <div style=\"top:180px;left:221px;position:absolute;\">"); 
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'6\'\" <type=\"button\">6</button>");
           client.print(" </div>"); 

           client.print(" <div style=\"top:280px;left:1px;position:absolute;\">"); 
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'7\'\" <type=\"button\">7</button>");
           client.print(" </div>"); 

           client.print(" <div style=\"top:280px;left:111px;position:absolute;\">"); 
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'8\'\" <type=\"button\">8</button>");
           client.print(" </div>"); 

           client.print(" <div style=\"top:280px;left:221px;position:absolute;\">"); 
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'9\'\" <type=\"button\">9</button>");
           client.print(" </div>"); 

           client.print(" <div style=\"top:380px;left:111px;position:absolute;\">"); 
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'0\'\" <type=\"button\">0</button>");
           client.print(" </div>"); 

           client.print(" <div style=\"top:380px;left:111px;position:absolute;\">"); 
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'11\'\" <type=\"button\">OnLock</button>");
           client.print(" </div>");

           client.print(" <div style=\"top:380px;left:221px;position:absolute;\">"); 
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'12\'\" <type=\"button\">Lock</button>");
           client.print(" </div>");

           client.print(" <div style=\"top:380px;left:0px;position:absolute;\">"); 
           client.print("<button style=\"height:100px;width:100px\"  onclick=\"location.href=\'13\'\" <type=\"button\">Clean</button>");
           client.print(" </div>");
           
           client.print(" <div style=\"top:500px;left:111px;position:absolute;\">");
           client.print("<font color=\"blue\" size=\"40\">");
           client.print(ss);
           client.print("</font><br>");
           client.print(" </div>");
           client.print(" <div style=\"top:700px;left:111px;position:absolute;\">");
           client.print("<font color=\"red\" size=\"80\">");
           if(lock==true){
               client.print("ONLOCK!");
  		 
           }else{
              client.print("LOCK!");
           }
           client.print("</font><br>");
           client.print(" </div>");
            // The HTTP response ends with another blank line:
           client.println(); 
            // break out of the while loop:
            break;
          }else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

     /*   if (currentLine.endsWith("GET /1")) {
          if(light==false){
            ServoControl(90);
            digitalWrite(LED1, HIGH);
            light=true;
          }else{
            ServoControl(90);
            digitalWrite(LED1, LOW);
            light=false;
          } 
        }*/
        if (currentLine.endsWith("GET /1")) {
          ss=ss+"1";
        }else if(currentLine.endsWith("GET /2")){
          ss=ss+"2";
        }else if(currentLine.endsWith("GET /3")){
          ss=ss+"3";
        }else if(currentLine.endsWith("GET /4")){
          ss=ss+"4";
        }else if(currentLine.endsWith("GET /5")){
          ss=ss+"5";
        }else if(currentLine.endsWith("GET /6")){
          ss=ss+"6";
        }else if(currentLine.endsWith("GET /7")){
          ss=ss+"7";
        }else if(currentLine.endsWith("GET /8")){
          ss=ss+"8";
        }else if(currentLine.endsWith("GET /9")){
          ss=ss+"9";
        }else if(currentLine.endsWith("GET /0")){
          ss=ss+"0";
        }else if(currentLine.endsWith("GET /11")){
          if(ss="12345678"){
            lock=true;
            delay(100);
            ServoControl(0);
            tone(speakerPin, NOTE_Med_RE);
            delay(200);
            noTone(speakerPin);
            tone(speakerPin, NOTE_Med_LA);
            delay(200);
            noTone(speakerPin);
            tone(speakerPin, NOTE_Med_RE);
            delay(200);
            noTone(speakerPin); 
            }
        }else if(currentLine.endsWith("GET /12")){
           lock=false;
           ServoControl(180);
           ss="";
        }else if(currentLine.endsWith("GET /13")){
           ss="";
         }
       }
    }
    // close the connection:
    client.stop();
    delay(50);
    Serial.println("client disonnected");
}}
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
