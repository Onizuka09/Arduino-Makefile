 void setup (){

Serial.begin(9600); 
pinMode (13,OUTPUT); 

}
String a="";  
void loop(){ 



//Serial.print ("hello world "); 
if (Serial.available ()){

a = Serial.readStringUntil('\n');
digitalWrite (13,!digitalRead(13)); 
Serial.println(a);

}
}
