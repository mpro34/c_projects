;Chris Whiting
;12/6/2012
;Ball Sorting Program 
 
  INCLUDE 'MC9S12C128.inc'
     
          ORG   RAMStart                                  
          LDS   #RAMEnd
          
          JSR   setup
          
         
;*Demos* 
          ;JSR   demo1  
          ;JSR   demo2
          ;JSR   demo3
                   
          
          
;*Main Program Loop*     ;Compares the pulse widths of the different colored balls.     
balls     JSR   det_freq
          LDAB  time
          CMPB  #150
          BHS   balls
          JSR   delay_40
          BSET  PORTB,%00000000  ;Set 00 filter
          JSR   det_freq
          LDAB  time
          CMPB  #17
          BLS   y_ball
          CMPB  #44
          BHS   rcheck
          BRA   balls
          
rcheck    CMPB  #60
          BLS   r_ball
          BRA   balls

y_ball    JSR   open1
          BRSET PORTB,%01000000,*
          JSR   close1  
          BRA   balls         
r_ball    JSR   open2
          BRSET PORTB,%10000000,*
          JSR   close2  
          BRA   balls   
          
;*Determines the pulse width at FREQ*     
det_freq  LDAB   #$00
          STAB   time
          BRCLR PORTB,%00000001,*
          BRSET PORTB,%00000001,*         
          BRCLR PORTB,%00000001,*
freq1     LDAA  PORTB
          ANDA  #$01
          CMPA  #$01
          BNE   endcount
          LDAB  time
          INCB
          STAB  time
          BRA   freq1 
endcount  RTS    
         
;*5s delay demonstration*          
demo2    JSR   open1
         JSR   delay_5s
         JSR   close1
         JSR   delay_5s
         JSR   open2
         JSR   delay_5s        
         JSR   close2
         JSR   delay_5s
         BRA   demo2
         SWI  
;*Swinging Arms Demo*                 
demo3     JSR   delay_5s   
          JSR   open1 
servo1    BRSET PORTB,%01000000,servo2
          JSR   close1   
          JSR   delay_5s   
          JSR   open2
servo2    BRSET PORTB,%10000000,servo1
          JSR   close2
          BRA   demo3 
 
;*Gate Control Code* 
setup     MOVB  #$77,PWMPRCLK
          MOVB  #$FF,PWMPOL
          MOVB  #255,PWMPER0
          MOVB  #255,PWMPER1 
          MOVB  #25,PWMDTY0
          MOVB  #25,PWMDTY1
          MOVB  #$03,PWME
          RTS  
          ;The duty cycle determines the rotation of the servos                         
open1     MOVB  #15,PWMDTY0
          RTS
      
close1    MOVB  #25,PWMDTY0 
          RTS           
             
open2     MOVB  #15,PWMDTY1
          RTS
     
close2    MOVB  #25,PWMDTY1 
          RTS           
          
 ;*40ms delay* 
          ;EQN: cc*x-value = (clock freq*delay)
          ;Delay 40ms, 2MHz clock
delay_40  LDX   #4900                      ;2
loop_40   PSHA                             ;2
          PULA                             ;3
          PSHA                             ;2
          PULA                             ;3    
          PSHA                             ;2
          PULA                             ;3    
          PSHA                             ;2
          PULA                             ;3                                                                                            
          NOP                              ;1
          NOP                              ;1
          DBNE  x,loop_40                  ;3
          RTS      
          
 ;*5s Delay*                                           
          ;EQN: cc*x-value = (clock freq*delay)
          ;Delay 5s, 2MHz clock
delay_5s  LDAB  #10                        ;1
out_loop  LDX   #20000                     ;2
in_loop   PSHA                             ;2
          PULA                             ;3                                                                
          PSHA                             ;2 
          PULA                             ;3
          PSHA                             ;2
          PULA                             ;3
          PSHA                             ;2
          PULA                             ;3 
          PSHA                             ;2
          PULA                             ;3                                                                
          PSHA                             ;2 
          PULA                             ;3
          PSHA                             ;2
          PULA                             ;3
          PSHA                             ;2
          PULA                             ;3
          PSHA                             ;2
          PULA                             ;3
          NOP                              ;1
          NOP                              ;1
          DBNE  x,in_loop                  ;3
          DBNE  b,out_loop                 ;3
          RTS                              ;25 total       
         
          
          SWI
;*Variables*
time      RMB    1                       ;Current pulse width value
    
          

     
           
           
