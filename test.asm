line no.    Address          Label          Mnemonic          Operands          Comment
1                         .2345678901234567890
2           0000                               START             0000              
3           0000             BGN               JSUB              READ              
4           0003                               JSUB              TOUPP             
5           0006                               LDX               #0                
6           0009             LOOP              JSUB              WRITE             
7           000C                               TIX               LENGTH            
8           000F                               JLT               LOOP              
9           0012                               J                 *                 
10          0015             MAXN              WORD              10                
11          0018             LENGTH            RESW              1                 
12          001B             STR               RESB              10                
13          0025             INDEV             BYTE              X'F3'             
14          0026             OUTDEV            BYTE              X'05'             
15          0027             EOF               BYTE              C'EOF'            
16                         .SUBROUTINE TO READ FROM DEVICE
17          002A             READ              LDX               #0                
18          002D                               LDA               #0                
19          0030             RLOOP             TD                INDEV             
20          0033                               JEQ               RLOOP             
21          0036                               RD                INDEV             
22          0039                               COMP              #4                
23          003C                               COMPR             A,S               
24          003E                               JEQ               EXIT              
25          0041                               STCH              STR,X             
26          0044                               TIX               MAXN              
27          0047                               JLT               RLOOP             
28          004A             EXIT              STX               LENGTH            
29          004D                               RSUB                                
30                         .SUBROUTINE TO CONVERT TO UPPER CASE
31          0050             TOUPP             LDX               #0                
32          0053             LOOP1             LDA               #0                
33          0056                               LDCH              STR,X             
34          0059                               SUB               #32               
35          005C                               STCH              STR,X             
36          005F                               TIX               LENGTH            
37          0062                               JLT               LOOP1             
38          0065                               RSUB                                
39                         .SUBROUTINE TO WRITE ONE CHAR TO A DEVICE
40          0068             WRITE             J                 WLOOP             
41          006B             WLOOP             TD                OUTDEV            
42          006E                               JEQ               WLOOP             
43          0071                               LDCH              STR,X             
44          0074                               WD                OUTDEV            
45          0077                               RSUB                                
46          007A                               END               BGN               
                         *** P A S S   1   E N D E D   S U C C E S S F U L L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          LOOP1               0053
          TOUPP               0050
          WRITE               0068
          EXIT                004A
          LOOP                0009
          BGN                 0000
          LENGTH              0018
          WLOOP               006B
          STR                 001B
          READ                002A
          INDEV               0025
          MAXN                0015
          OUTDEV              0026
          EOF                 0027
          RLOOP               0030
