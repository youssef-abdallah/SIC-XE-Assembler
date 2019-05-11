line no.    Address          Label          Mnemonic          Operands          Comment
1                         .2345678901234567890
2           0000             COPY              START             0000              
3           0000             L1                WORD              100               
4           0003             L2                WORD              200               
5           0006             DIFF              EQU               L2-L1             
6           0006             FIRST             STL               RETADR            
7           0009                               LDA               LENGTH            
8           000C                               LDA               #LENGTH           
9           000F                               LDA               @LENGTH           
10          0012                               LDA               DIFF              
11          0015                               LDA               #DIFF             
12          0018                               LDA               @DIFF             
13          001B             CLOOP             +JSUB             RDREC             
14          001F                               LDA               LENGTH            
15          0022                               COMP              #0                
16          0025                               JEQ               ENDFIL            
17          0028                               +JSUB             WRREC             
18          002C                               J                 CLOOP             
19          002F             ENDFIL            LDA               EOF               
20          0032                               STA               BUFFER            
21          0035                               LDA               #3                
22          0038                               STA               LENGTH            
23          003B                               +JSUB             WRREC             
24          003F                               J                 @RETADR           
25          0042             EOF               BYTE              C'EOF'            
26          0045             SOSO              EQU               FIRST+5           
27          0045             STR               BYTE              C'test STRING'    
28          0050             RETADR            RESW              1                 
29          0053             LENGTH            RESW              1                 
30          0056             BUFFER            RESB              1                 
31                         .
32                         .SUBROUTINE TO READ INTO BUFFER
33          0057             RDREC             CLEAR             X                 
34          0059                               CLEAR             A                 
35          005B                               CLEAR             S                 
36          005D                               +LDT              #4096             
37          0061             RLOOP             TD                INPUT             
38          0064                               JEQ               RLOOP             
39          0067                               TD                INPUT             
40          006A                               COMPR             A,S               
41          006C                               JEQ               EXIT              
42          006F                               STCH              BUFFER,X          
43          0072                               TIXR              T                 
44          0074                               JLT               RLOOP             
45          0077             EXIT              STX               LENGTH            
46          007A                               RSUB                                
47          007D             INPUT             BYTE              X'F1'             
48          007E             WRREC             CLEAR             X                 
49          0080                               LDT               LENGTH            
50          0083             WLOOP             TD                OUTPUT            
51          0086                               JEQ               WLOOP             
52          0089                               LDCH              BUFFER,X          
53          008C                               WD                OUTPUT            
54          008F                               TIXR              T                 
55          0091                               JLT               WLOOP             
56          0094                               RSUB                                
57          0097             OUTPUT            BYTE              X'05'             
58          0098                               END               FIRST             
                         *** P A S S   1   E N D E D   S U C C E S S F U L L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          INPUT               007D
          WRREC               007E
          RLOOP               0061
          RDREC               0057
          BUFFER              0056
          LENGTH              0053
          L1                  0000
          FIRST               0006
          CLOOP               001B
          OUTPUT              0097
          L2                  0003
          EXIT                0077
          DIFF                0003
          ENDFIL              002F
          EOF                 0042
          RETADR              0050
          SOSO                000B
          WLOOP               0083
          STR                 0045
                         **************************************************
                         ********** S t a r t  o f  P a s s  II ***********
LC        Code      Label     Opcode    Operand     Flags

0000                COPY      START     0000        n=0 i=0 x=0   b=0 p=0 e=0

0000      000064    L1        WORD      100         n=0 i=0 x=0   b=0 p=0 e=0

0003      0000C8    L2        WORD      200         n=0 i=0 x=0   b=0 p=0 e=0

0006                DIFF      EQU       L2-L1       n=0 i=0 x=0   b=0 p=0 e=0

0006      172047    FIRST     STL       RETADR      n=1 i=1 x=0   b=0 p=1 e=0

0009      032047              LDA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

000C      012044              LDA       #LENGTH     n=0 i=1 x=0   b=0 p=1 e=0

000F      022041              LDA       @LENGTH     n=1 i=0 x=0   b=0 p=1 e=0

0012      030003              LDA       DIFF        n=1 i=1 x=0   b=0 p=0 e=0

0015      010003              LDA       #DIFF       n=0 i=1 x=0   b=0 p=0 e=0

0018      020003              LDA       @DIFF       n=1 i=0 x=0   b=0 p=0 e=0

001B      4B100057  CLOOP     +JSUB     RDREC       n=1 i=1 x=0   b=0 p=0 e=1

001F      032031              LDA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

0022      290000              COMP      #0          n=0 i=1 x=0   b=0 p=0 e=0

0025      332007              JEQ       ENDFIL      n=1 i=1 x=0   b=0 p=1 e=0

0028      4B10007E            +JSUB     WRREC       n=1 i=1 x=0   b=0 p=0 e=1

002C      3F2FEC              J         CLOOP       n=1 i=1 x=0   b=0 p=1 e=0

002F      032010    ENDFIL    LDA       EOF         n=1 i=1 x=0   b=0 p=1 e=0

0032      0F2021              STA       BUFFER      n=1 i=1 x=0   b=0 p=1 e=0

0035      010003              LDA       #3          n=0 i=1 x=0   b=0 p=0 e=0

0038      0F2018              STA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

003B      4B10007E            +JSUB     WRREC       n=1 i=1 x=0   b=0 p=0 e=1

003F      3E200E              J         @RETADR     n=1 i=0 x=0   b=0 p=1 e=0

0042      454F46    EOF       BYTE      C'EOF'      n=0 i=0 x=0   b=0 p=0 e=0

0045                SOSO      EQU       FIRST+5     n=0 i=0 x=0   b=0 p=0 e=0

0045      7465737420535452494E47STR       BYTE      C'test STRING'n=0 i=0 x=0   b=0 p=0 e=0

0050                RETADR    RESW      1           n=0 i=0 x=0   b=0 p=0 e=0

0053                LENGTH    RESW      1           n=0 i=0 x=0   b=0 p=0 e=0

0056                BUFFER    RESB      1           n=0 i=0 x=0   b=0 p=0 e=0

0057      B410      RDREC     CLEAR     X           n=0 i=0 x=0   b=0 p=0 e=0

0059      B400                CLEAR     A           n=0 i=0 x=0   b=0 p=0 e=0

005B      B440                CLEAR     S           n=0 i=0 x=0   b=0 p=0 e=0

005D      75101000            +LDT      #4096       n=0 i=1 x=0   b=0 p=0 e=1

0061      E32019    RLOOP     TD        INPUT       n=1 i=1 x=0   b=0 p=1 e=0

0064      332FFA              JEQ       RLOOP       n=1 i=1 x=0   b=0 p=1 e=0

0067      E32013              TD        INPUT       n=1 i=1 x=0   b=0 p=1 e=0

006A      A004                COMPR     A,S         n=0 i=0 x=0   b=0 p=0 e=0

006C      332008              JEQ       EXIT        n=1 i=1 x=0   b=0 p=1 e=0

006F      57AFE4              STCH      BUFFER,X    n=1 i=1 x=1   b=0 p=1 e=0

0072      B850                TIXR      T           n=0 i=0 x=0   b=0 p=0 e=0

0074      3B2FEA              JLT       RLOOP       n=1 i=1 x=0   b=0 p=1 e=0

0077      132FD9    EXIT      STX       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

007A      4F0000              RSUB                  n=1 i=1 x=0   b=0 p=0 e=0

007D      F1        INPUT     BYTE      X'F1'       n=0 i=0 x=0   b=0 p=0 e=0

007E      B410      WRREC     CLEAR     X           n=0 i=0 x=0   b=0 p=0 e=0

0080      772FD0              LDT       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

0083      E32011    WLOOP     TD        OUTPUT      n=1 i=1 x=0   b=0 p=1 e=0

0086      332FFA              JEQ       WLOOP       n=1 i=1 x=0   b=0 p=1 e=0

0089      53AFCA              LDCH      BUFFER,X    n=1 i=1 x=1   b=0 p=1 e=0

008C      DF2008              WD        OUTPUT      n=1 i=1 x=0   b=0 p=1 e=0

008F      B850                TIXR      T           n=0 i=0 x=0   b=0 p=0 e=0

0091      3B2FEF              JLT       WLOOP       n=1 i=1 x=0   b=0 p=1 e=0

0094      4F0000              RSUB                  n=1 i=1 x=0   b=0 p=0 e=0

0097      05        OUTPUT    BYTE      X'05'       n=0 i=0 x=0   b=0 p=0 e=0

0098                          END       FIRST       n=0 i=0 x=0   b=0 p=0 e=0

                         ***** S U C C E S S F U L L Y  A S S E M B L E D *****
H^COPY  ^000000^000099
T^000000^1B^000064^0000C8^172047^032047^012044^022041^030003^010003^020003
T^00001F^1D^4B100057^032031^290000^332007^4B10007E^3F2FEC^032010^0F2021^010003
T^00003B^1E^0F2018^4B10007E^3E200E^454F46^7465737420535452494E47^B410^B400^B440
T^000061^1D^75101000^E32019^332FFA^E32013^A004^332008^57AFE4^B850^3B2FEA^132FD9
T^00007D^1E^4F0000^F1^B410^772FD0^E32011^332FFA^53AFCA^DF2008^B850^3B2FEF^4F0000^05
E^000000
