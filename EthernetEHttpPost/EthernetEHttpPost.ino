
#include <UIPEthernet.h>
// The connection_data struct needs to be defined in an external file.
#include <UIPServer.h>
#include <UIPClient.h>

EthernetServer server = EthernetServer(1000);
EthernetClient client;
int incomingByte = 0;

void setup()
{
  Serial.begin(9600);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  IPAddress myIP(10,100,7,10);

  Ethernet.begin(mac,myIP); 
  
  server.begin();
  
}

void loop()
{

  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  /*if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    //while (true);
  }*/
  
  // send data only when you receive data:
  if (Serial.available() > 0) {         
          String msg = Serial.readString();
          Serial.println("I received: "+ msg);          
          send(msg);
  }
}

void send(String msg){
  String data = "msg="+msg;
  
  char server[] = "www.rukspot.com";
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("POST /restapi/test.php HTTP/1.1");
    client.println("Host: www.rukspot.com");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

