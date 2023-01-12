String str="";  
void setup (){

Serial.begin(9600); 
pinMode (13,OUTPUT); 

}

void loop(){ 

if (Serial.available ()){
str = Serial.readString();
digitalWrite (13,!digitalRead(13)); 

Serial.println(a);

Serial.println(str);


}
}
