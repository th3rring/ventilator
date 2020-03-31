#include <trajfactory.h>
#include <ArduinoJson.h>


TrajFactory tf = TrajFactory();
bool sent = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (!sent) {

    Trajectory* traj_ptr = tf.build(12, 0.5, 2000, 1, 40);
      
    /*const size_t CAPACITY = JSON_ARRAY_SIZE(traj_ptr->getLength());*/
    /*StaticJsonDocument<CAPACITY> doc;*/
    /*const size_t CAPACITY = JSON_ARRAY_SIZE(600);*/
    
    /*// allocate the memory for the document*/
    /*StaticJsonDocument<CAPACITY> doc;*/

    /*JsonArray array = doc.to<JsonArray>();*/

    /*for (int i = 0; i < traj_ptr->getLength(); i++){*/
      /*array.add(traj_ptr->nextStep());*/
    /*}*/

    /*serializeJson(doc, Serial);*/

    while(true){
      Serial.println(traj_ptr->nextStep());
      delay(10);
    }
  
  sent = true;
  }

}

