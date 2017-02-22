;Chris Whiting
;Sun Tracking System
;1/15/2013

;2MHz Clock

          INCLUDE "MC9S12C128.inc"
          
          ORG   RAMStart                    ;RAM starts at $400          
start     LDS   #RAMEnd                     ;RAM ends at $FFF

;there1    JSR    analog
;          BRA    there1
          
          MOVB   #%00001111, DDRA   ;Set all PORTS to OUTPUT 
          MOVB   #%00000000, DDRB   ;Set all PORTS to OUTPUT 
                 
beginC    LDAA   #$05               ;Set the threshold 
          STAA   thresh
      

   ;EAST - WEST
;*East>West* RETRACT
WEComp1   MOVB   #%00000000, PORTA  ;(STOP all Actuator Movement)
WEComp2   JSR    analog

          LDAA   LEast              ;LEast  (A), A-M -> A
          SUBA   LWest              ;LWest  (M)
          BMI    WEneg1             ;Branch if Minus                                
          CMPA   thresh             ;threshhold is $05
          BLO    NSComp1            ;Branch if Lower  
                  
          MOVB   #%00000001, PORTA   ;PA0 - Put positive terminal in Retract mode(MOVE ACTUATOR)  
          JSR    WEPulsin            ;**MOVE 1inch then recheck LED values**    
          MOVB   #%00000000, PORTA   ;(STOP all ACTUATOR) 
          BRA    WEComp2            ;Check values again...
          
;*East<West* EXTEND          
WEneg1    MOVB   #%00000000, PORTA   ;(STOP all Actuator Movement)
WEneg2    ;JSR    analog
          
          LDAA   LWest              ;LWest  (M)
          SUBA   LEast              ;LEast  (A)          
          CMPA   thresh             ;threshhold is $05
          BLO    NSComp1            ;Branch if Lower   
                           
          MOVB   #%00000010, PORTA   ;PA1 - Put ground terminal in Retract mode(MOVE ACTUATOR) 
          JSR    WEPulsout           ;**MOVE 1inch then recheck LED values**  
          MOVB   #%00000000, PORTA   ;(STOP all Actuator Movement)  
          JSR    analog
          BRA    WEneg2
          
   ;NORTH - SOUTH 
;*North>South* RETRACT     
NSComp1   MOVB   #%00000000, PORTA   ;(STOP all Actuator Movement)
NSComp2   JSR    analog             

          LDAA   LNorth             ;LNorth  (A), A-M -> A
          SUBA   LSouth             ;LSouth  (M)
          BMI    NSneg1             ;Branch if Minus                                   
          CMPA   thresh             ;threshhold is $05
          BLO    fin                ;Branch if Lower     
             
          MOVB   #%00000100, PORTA   ;PA2 - Put positive terminal in Retract mode(MOVE ACTUATOR)     
          JSR    NSPulsin            ;**MOVE 1inch then recheck LED values**    
          MOVB   #%00000000, PORTA   ;(STOP all Actuator Movement)
          BRA    NSComp2            ;Check values again...

;*North<South* EXTEND           
NSneg1    MOVB   #%00000000, PORTA   ;(STOP all Actuator Movement)
NSneg2    ;JSR    analog

          LDAA   LSouth             ;LSouth  (M)
          SUBA   LNorth             ;LNorth  (A)       
          CMPA   thresh             ;threshhold is $05
          BLO    fin                ;Branch if Lower    
               
          MOVB   #%00001000, PORTA   ;PA3 - Put ground terminal in Retract mode(MOVE ACTUATOR)
          JSR    NSPulsout           ;**MOVE 1inch then recheck LED values**  
          MOVB   #%00000000, PORTA   ;(STOP all Actuator Movement) 
          JSR    analog 
          BRA    NSneg2
          
          
    ;END COMPARE      
fin       MOVB  #%00000000, PORTA    ;stop actuator movement       
          LBRA    beginC
         ; SWI             
         
; ******************************* 
;Linear ACTUATOR Tests (1in = 125 pulses)    

;**Check pulses for 6in actuator - Azimuth 
WEPulsin  ;LDX   WEpCount
          ;CPX   #$00          ;DEC 00 - Make sure actuator is not fully retracted.
          ;BEQ   reset1
WEPulsout JMP   loop1
          ;LDX   WEpCount
          ;CPX   #$2EE         ;DEC 750 - Make sure actuator is not fully extended.
          ;BHS   reset1
          
loop1     BRCLR PORTB,%00000010,*   ;Wait for PB2 High
          LDX   WEpCount
          CLRA
          LDAB  #$1
          ABX
          STX   WEpCount
          
          LDD   WEpCount
          ;LDX   #$7D          ;DEC 125 - 1in
          ;IDIV
          CPD   #$01FC          ;If WEpCount is multiple of 125 (1in), jump back and stop actuator     
          BEQ   compare1
          
          BRSET PORTB,%00000010,*   ;Wait for PB2 Low
          BRA   loop1

reset1    LDX   #$00
          STX   WEpCount
          JMP   NSComp1       ;If azimuth actuator is max stroke, move to elevation actuator       

compare1  LDX   #$00      ;Take Out when ready (Shouldn't reset each time it counts an inch)
          STX   WEpCount  ;

          RTS 
          
          
;**Check pulses for 18in actuator - Elevation
NSPulsin  ;LDX   NSpCount
          ;CPX   #$00          ;DEC 00 - Make sure actuator is not fully retracted.
          ;BEQ   reset1        
NSPulsout JMP   loop2
          ;LDX   NSpCount
          ;CPX   #$8CA         ;DEC 2250 - Make sure actuator is not fully extended.
          ;BHS   reset2
          
loop2     BRCLR PORTB,%00000100,*   ;Wait for PB3 High
          LDX   NSpCount
          CLRA
          LDAB  #$1
          ABX
          STX   NSpCount
          
          LDD   NSpCount 
        ;  LDX   #$7D          ;DEC 125 - 1in
         ; IDIV
          CPD   #$007D          ;DEC 1405 ;If NSpCount is multiple of 125 (1in), jump back and stop actuator 
          BEQ   compare2
          
          BRSET PORTB,%00000100,*   ;Wait for PB3 Low
          BRA   loop2
                    
reset2    LDX   #$00
          STX   NSpCount  
          JMP   fin           ;If elevation actuator is max stroke, restart compare

compare2  LDX   #$00      ;Take Out when ready
          STX   NSpCount  ;
         
          RTS            
 
; *******************************   
;Microcontroller ADC SETTINGS: 
;Step Size 19.53mV; 00 -> FF(255)
;Connect to GND on board

analog
          MOVB    #$FF,DDRA        ;Initialize Port A (PA7-PA4) for output
          MOVB    #$C0,ATDCTL2     ;Initialize ATD for analog
          MOVB    #$00,ATDCTL3     ; to 8-bit digital continuous
          MOVB    #$00,ATDCTL4     ; scan at AD0
          LDAA    #10              ;Wait for ADC to stabilize
Wait      DECA
          BNE     Wait
          MOVB    #$20,ATDCTL5     ;Start conversion - channel AN0
          BRCLR   ATDSTAT0,$80,*   ;Wait for Sequence Complete (SCF) flag is set          
          LDAB    ATDDR0H          ;Checks the LED value 1         
          STAB    LWest


          MOVB    #$21,ATDCTL5     ;Start conversion - channel AN1
          BRCLR   ATDSTAT0,$80,*   ;Wait for Sequence Complete (SCF) flag is set  
          LDAB    ATDDR1H          ;Checks the LED value 2     
          STAB    LEast


          MOVB    #$22,ATDCTL5     ;Start conversion - channel AN2
          BRCLR   ATDSTAT0,$80,*   ;Wait for Sequence Complete (SCF) flag is set  
          LDAB    ATDDR2H          ;Checks the LED value 3
          STAB    LNorth


          MOVB    #$23,ATDCTL5     ;Start conversion - channel AN3
          BRCLR   ATDSTAT0,$80,*   ;Wait for Sequence Complete (SCF) flag is set  
          LDAB    ATDDR3H          ;Checks the LED value 4
          STAB    LSouth

          RTS                      ;return
          
; *******************************         
;TIMER Module: Seconds - Secs, Minutes - Mins, Hours - Hrs      
   
delay     LDAA  #4                 ;delay 1s
          STAA  total
          MOVB  #%01111111,RTICTL  ;0.262s time-out period
          MOVB  #%10000000,CRGINT  ;Real Time Interrupt Enable   
          CLI 
spin    
          LDAA  total
          BNE   spin
          LDAA  #4
          STAA  total
          
sec_1                              ;RTI instruction leads here
          LDAA  #1
          LDAB  Secs  
          ABA
          CMPA  #57
          BEQ   incMin          
          STAA  Secs
          BRA   spin
          
incMin    CLRA
          STAA  Secs         ;Clear Seconds
          LDAA  Mins          
          INCA               ;Add 1 to minutes
          CMPA  #60
          BEQ   incHour
          STAA  Mins
          ;*****
          ;This should be the subroutine to update the motors
         ;CMPA #15
         ;BEQ  analog
          ;*****
          BRA   spin
          
incHour   CLRA
          STAA  Mins         ;Clear Minutes
          LDAA  Hours
          INCA               ;Add 1 to hours
          CMPA  #24
          BEQ   incDay
          STAA  Hours
          BRA   spin
          
incDay    CLRA
          STAA  Hours        ;Clear hours
          LDAA  Days
          INCA               ;Add 1 to days
          CMPA  #7
          BEQ   Week
          STAA  Days
          BRA   spin
          
Week      CLRA
          STAA  Days         ;Reset timer each week
          STAA  Hours
          STAA  Mins
          STAA  Secs
          LBRA  spin
          
          SWI
          
    ;Interrupt Service Routine
rti_isr   MOVB  #%10000000,CRGFLG
          DEC   total
          RTI   
           

; *******************************
;DATA

         INCLUDE "LCD_SUBS.INC"
;LED ADC input values  -  check for values at $670
Wens     FCC  "WENS"
LWest    RMB  1
LEast    RMB  1
LNorth   RMB  1 
LSouth   RMB  1
thresh   RMB  1
WEpCount RMB  2
NSpCount RMB  2


;Timer Module Values
ASEC     RMB  2    
Days     RMB  1
Hours    RMB  1
Mins     RMB  1
Secs     RMB  1
total    RMB  1
;Sunny    EQU  #$00
;Cloudy   EQU  #$00

LCDBUF   RMB  2
HX_USC2  RMB  2

;Interrupt Vectors (Reset & RTI)
         ORG  $FFF0
         FDB  rti_isr
         ORG  $FFFE
         DCW  start
          