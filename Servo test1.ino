/*本代码使用abcdef6个代号控制舵机
 * joystick模式下通过键盘ijkl 小键盘8456控制方向
 * o按键输出当前舵机位置
 */


#include <Servo.h>
Servo one, two, three, four, five, six ;    //创建6个servo对象

 
//存储电机极限值
const int oneMin = 0;
const int oneMax = 180;
const int twoMin = 45;
const int twoMax = 180;
const int threeMin = 35;
const int threeMax = 120;
const int fourMin = 25;
const int fourMax = 100;
const int fiveMin = 25;
const int fiveMax = 100;
const int sixMin = 25;
const int sixMax = 100;

 
int DSD = 15; //Default Servo Delay (默认电机运动延迟时间)
              //此变量用于控制电机运行速度.增大此变量数值将
              //降低电机运行速度从而控制机械臂动作速度。


void setup(){
  one.attach(7);    
  delay(200);         
  two.attach(6);    
  delay(200);          
  three.attach(5);    
  delay(200);         
  four.attach(4);     
  delay(200);   
  five.attach(3);
  delay(200);   
  six.attach(2);
  delay(200);   


  one.write(80);      //数值增大抓手增大     
  delay(10);
  two.write(60);       
  delay(10);
  three.write(160);   //数值增大机械臂下抬
  delay(10);
  four.write(100);   //数值增大机械臂下抬
  delay(10); 
  five.write(115);  //数值增大机械臂上抬
  delay(10); 
  six.write(150);  //数值增大逆时针旋转
  delay(10); 

  
  Serial.begin(9600); 
  Serial.println("电机初始化成功");   
}
 
 
void loop()
{
  if (Serial.available()>0) 
  {  
    char serialCmd = Serial.read();
    armDataCmd(serialCmd);
  }
}
 
void armDataCmd(char serialCmd)    //Arduino根据串行指令执行相应操作    指令示例：b45 底盘转到45度角度位置 o 输出机械臂舵机状态信息
  { 
   if (serialCmd == 'a' || serialCmd == 'b' || serialCmd == 'c' || serialCmd == 'd' || serialCmd == 'e' || serialCmd == 'f')
    {
     int servoData = Serial.parseInt();
     servoCmd(serialCmd, servoData, DSD);  // 机械臂舵机运行函数（参数：舵机名，目标角度，延迟/速度）
    } 
   else 
   {
    switch(serialCmd)
    {    
      case 'o':  // 输出舵机状态信息
       reportStatus();
       break; 
    }
   }  
}
 
void servoCmd(char servoName, int toPos, int servoDelay)
{  
  Servo servo2go;               //创建servo对象
  
  Serial.println("");           //串口监视器输出接收指令信息
  Serial.print("操纵: 电机 ");
  Serial.print(servoName);
  Serial.print(" 至 ");
  Serial.print(toPos);
  Serial.print(" at servoDelay value ");
  Serial.print(servoDelay);
  Serial.println("。");
  Serial.println("");  
  
  int fromPos;               //建立变量，存储电机起始运动角度值
  
  switch(servoName){
    case 'a':
      if(toPos >= oneMin && toPos <= oneMax){
        servo2go = one;
        fromPos = one.read();  // 获取当前电机角度值用于“电机运动起始角度值”
        break;
      } else {
        Serial.println("+Warning: one Value Out Of Limit!");
        return;
      }
 
    case 'b':
      if(toPos >= twoMin && toPos <= twoMax){    
        servo2go = two;
        fromPos = two.read();  // 获取当前电机角度值用于“电机运动起始角度值”
        break;
      } else {
        Serial.println("+Warning: two Value Out Of Limit!");
        return;        
      }
 
    case 'c':
      if(toPos >= threeMin && toPos <= threeMax){
        servo2go = three;
        fromPos = three.read();  // 获取当前电机角度值用于“电机运动起始角度值”
        break;
      } else {
        Serial.println("+Warning: three Value Out Of Limit!");
        return;
      }
         
    case 'd':
      if(toPos >= fourMin && toPos <= fourMax){
        servo2go = four;
        fromPos = four.read();  // 获取当前电机角度值用于“电机运动起始角度值”
        break;
      } else {
        Serial.println("+Warning: four Value Out Of Limit!");
        return;
      }   
         
     case 'e':
      if(toPos >= fiveMin && toPos <= fiveMax){
        servo2go = five;
        fromPos = five.read();  // 获取当前电机角度值用于“电机运动起始角度值”
        break;
      } else {
        Serial.println("+Warning: five Value Out Of Limit!");
        return;
      }      
         
     case 'f':
      if(toPos >= sixMin && toPos <= sixMax){
        servo2go = six;
        fromPos = six.read();  // 获取当前电机角度值用于“电机运动起始角度值”
        break;
      } else {
        Serial.println("+Warning: six Value Out Of Limit!");
        return;
      }     
  }
 
  //指挥电机运行
  if (fromPos <= toPos)                     //如果“起始角度值”小于“目标角度值”
   {                          
    for (int i=fromPos; i<=toPos; i++)
    {
      servo2go.write(i);
      delay (servoDelay);
    }
   }  
  else 
  {                                 //否则“起始角度值”大于“目标角度值”
    for (int i=fromPos; i>=toPos; i--)
     {
      servo2go.write(i);
      delay (servoDelay);
     }
  }
}
 
void reportStatus()                   //舵机状态信息
{  
  Serial.println("");
  Serial.println("++++++++++++++++++++++++++");
  Serial.println("当前舵机状态");
  Serial.print("one Position: "); Serial.println(one.read());
  Serial.print("two Position: "); Serial.println(two.read());
  Serial.print("three Position:"); Serial.println(three.read());
  Serial.print("four Position:"); Serial.println(four.read());
  Serial.print("five Position:"); Serial.println(five.read());
  Serial.print("six Position:"); Serial.println(six.read());
  Serial.println("++++++++++++++++++++++++++");
  Serial.println("");
}
