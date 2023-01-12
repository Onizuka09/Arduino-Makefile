String str="";  
void setup (){

Serial.begin(9600); 
pinMode (13,OUTPUT); 

}

void loop(){ 

if (Serial.available ()){
str = Serial.readString();
digitalWrite (13,!digitalRead(13)); 
<<<<<<< HEAD
Serial.println(a);
=======
Serial.println(str);
>>>>>>> 1d4b8c4156987cefe4e12b84d6665228f81adb03

}
}
