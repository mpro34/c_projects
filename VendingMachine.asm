;Chris Whiting
;Dr. Barbara Marino
;Experiment #8 - Vending Machine
;11/15/2012


;The following program determines the type of coin entered into the CH-926 coin sorter and
; updates the total value of coins enters to be displayed on an LCD.

          INCLUDE "MC9S12C128.inc"
Quarter   EQU   25
Dime      EQU   10
Nickel    EQU   5
Penny     EQU   1       
          ORG   $400                        ;RAM starts at $400
          LDS   #RAMEnd                     ;RAM ends at $FFF
          JSR   LCD_INIT
          CLRA                              ;Initialize variables to 0
          STAA  coin
          STAA  t_coins                     ;PORTA pin 1 (PA0) will be the input for the
                                            ;coin sorter output pulses.Pin39 (11 on left from bottom)
          MOVB  #$FE,DDRT
coinloop  ;LDAA  PTT
          CLRA                              ;Initialize variables to 0
          STAA  coin
          BRSET PTT,$01,*
          INC coin
pulse     BRCLR PTT,$01,*                   ;Wait for the pulses to start going low                           
delay     LDX   #38260                      ;Delay 115ms, 2MHz clock
delay_40  PSHA               
          PULA                                                                                             
          PSHA                              
          PULA
          PSHA
          PULA
          PSHA
          PULA                              ;23 total
          DBNE  x,delay_40                  ;CH-926 set Output signal to - fast: 20ms each pulse.
          LDAA  PTT
          CMPA  #$01                        ;Check for the value of the pulse (1 or 0)    
          BEQ   endpulse                    ;If pulse=1, signifies the end of the pulses for 1 coin.
          INC   coin                        ;Delay 40ms to jump into the middle of what should be the next low pulse.
          BRA   pulse         
           
endpulse  LDAA  t_coins                     ;Load coin value into LCDBUF for output to LCD
          LDAB  coin
          CMPB #1
          BEQ   pen
          CMPB #3
          BEQ   nic
          CMPB #5
          BEQ   dim
          CMPB #7
          BEQ   qua
          
pen       LDAB  #Penny                      ;Determine which coin was inserted and output to LCD
          ABA
          STAA  t_coins
          JMP   dis  
                  
nic       LDAB  #Nickel
          ABA
          STAA  t_coins
          JMP   dis
                   
dim       LDAB  #Dime
          ABA
          STAA  t_coins
          JMP   dis
                    
qua       LDAB  #Quarter
          ABA
          STAA  t_coins 
dis      
          CLRA 
          LDAB  t_coins                     ;Dollar values will go into X and cents will go into D
          LDX   #100                        ;Once total values exceed 9 dollars and 99 cents, value goes to 0.
          IDIV 
          STAB  cents 
          EXG   D,X
          STAB  dollars                
          LDAA  dollars                     ;Convert Dollars to ASCII
          LDAB  #$30
          ABA
          STAA  dollars  
          CLRA
          LDAB  cents                       ;Convert Cents to ASCII
          LDX   #10
          IDIV
          LDAA  #$30
          ABA
          STAA  cents+1
          CLRA
          EXG   D,X
          LDAA  #$30
          ABA
          STAA  cents

          LDY   #total
          JSR   DSHOME
          JSR   LCD_STRING                  ;Output current total to LCD   
          LBRA   coinloop                   ;Return to beginning and wait for next coin
                
          INCLUDE "LCD_SUBS.INC"
;Output Message          
total     FCC    "$"          
dollars   RMB    1
          FCC    "."
cents     RMB    2       
          FCB    0
;end output message
t_coins   RMB    1
coin      RMB    1  
           
LCDBUF    RMB    2
HX_USC2   RMB    2
