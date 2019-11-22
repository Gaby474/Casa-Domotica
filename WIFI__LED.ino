#include <ESP8266WiFi.h>
#include <DHT.h>
#define SensorTemperatura 2
#define DHTTYPE DHT11
DHT sensor(SensorTemperatura, DHTTYPE);
int Temperatura;
const char* ssid = "Karlojn";
const char* password = "karlojn123";

int perimetro = 16; // GPIO16
int habitacion1 = 5; // GPIO16
int habitacion2 = 4; // GPIO16

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  sensor.begin();

  pinMode(perimetro, OUTPUT);
    pinMode(habitacion1, OUTPUT);
      pinMode(habitacion2, OUTPUT);
  digitalWrite(perimetro, HIGH);
    digitalWrite(habitacion1, HIGH);
      digitalWrite(habitacion2, HIGH);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  int value = LOW;
  if (request.indexOf("/perimetroON") != -1)  {
    digitalWrite(perimetro, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/perimetroOFF") != -1)  {
    digitalWrite(perimetro, LOW);
    value = LOW;
  }


  int value1 = LOW;
  if (request.indexOf("/habitacion1ON") != -1)  {
    digitalWrite(habitacion1, HIGH);
    value1 = HIGH;
  }
  if (request.indexOf("/habitacion1OFF") != -1)  {
    digitalWrite(habitacion1, LOW);
    value1 = LOW;
  }

    int value2 = LOW;
  if (request.indexOf("/habitacion2ON") != -1)  {
    digitalWrite(habitacion2, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/habitacion2OFF") != -1)  {
    digitalWrite(habitacion2, LOW);
    value2 = LOW;
  }
 
  // Return the response
  client.println("HTTP/1.1 400 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.print("<!DOCTYPE html>");
  client.print("<html>");
  
  client.print("<head>");
  client.print("<title>Casa Inteligente</title>");
   client.print("<script rel='styleshee' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.css'></script>");
  client.print("</head>");
  client.print("<body bgcolor= aqua href=\"/LED=OFF\"\">");
  client.print("<i class='fa fa-power-off fa-5x' aria-hidden='true'></i>");
 
   
  client.print("<font  size=70px style=color:purple><center><h1>Casa Domotica</h1></center></font>");
  client.print("<br><br>");
  client.print("<br>");
  client.print("<br>");
  client.print("<br>");
  client.print("<CENTER>");
  client.print("<TABLE>");
  client.print("<TR>");
   client.print("<TD>");
   client.print("<center>");
client.print("<font  size=50px ><center><h1>Habitacion</h1></center></font>");
  client.print("</TD>");
  client.print("</TR>");
  client.print("<TR>");
  client.print("<TD>");
  client.print("<CENTER><a href=\"/perimetroON\"\"> <button style='width:200px; height:100px' ><font  size=15px<H3>Apagar</H3></font></button> </a>");
  client.print("</TD>");
  client.print("<TD width= 70 ></TD>");

  client.print("<TD><a href=\"/perimetroOFF\"\"> <button style='width:200px; height:100px' ><b><font  size=6px<H3>Encender</H3></font></b></button> </a></TD></CENTER>");
  client.print("</TR></TABLE></CENTER>");
  client.print("<br><br><br>");

    client.print("<CENTER>");
  client.print("<TABLE>");
  client.print("<TR>");
  client.print("<TD>");
 client.print("<font  size=50px ><center><h1>Sala</h1></center></font>");
  client.print("</TD>");
  client.print("</TR>");
 client.print("<TR>");
  client.print("<TD>");
  client.print("<CENTER><a href=\"/habitacion1ON\"\"> <button style='width:200px; height:100px' ><font  size=15px<H3>Apagar</H3></font></button> </a>");
  client.print("</TD>");
  client.print("<TD width= 70 ></TD>");

  client.print("<TD><a href=\"/habitacion1OFF\"\"> <button style='width:200px; height:100px' ><b><font  size=6px<H3>Encender</H3></font></b></button> </a></TD></CENTER>");
  client.print("</TR></TABLE></CENTER>");

  client.print("<br><br><br>");
  client.print("<CENTER>");
  client.print("<TABLE>");
  client.print("<TR>");
  client.print("<TD>");
  client.print("<font  size=50px ><center><h1>Perimetro</h1></center></font>");
  client.print("</TD>");
  client.print("</TR>");
  client.print("<TR>");
  client.print("<TD>");
  client.print("<CENTER><a href=\"/habitacion2ON\"\"> <button style='width:200px; height:100px' ><font  size=15px<H3>Apagar</H3></font></button> </a>");
  client.print("</TD>");
  client.print("<TD width= 70 ></TD>");
    client.print("<TD><a href=\"/habitacion2OFF\"\"> <button style='width:200px; height:100px' ><b><font  size=6px<H3>Encender</H3></font></b></button> </a></TD></CENTER>");
  client.print("</TR></TABLE></CENTER>");
    client.print("</center>");
  client.print("<br><br><br><br>");
  client.print("<center><p>Copyright © Todos los derechos reservados a <br>Gonzalez Villa Bryn<br>Jaca Nava Roberto Karlo<br>Lopez Mercado Gabriela Susana<br>Nava Aceves Eduardo<br>Ortiz Flores Laura Vianey</p></center>");
  client.print("</body>");
  client.print("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
