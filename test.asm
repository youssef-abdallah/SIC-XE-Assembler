line no.    Address          Label          Mnemonic          Operands          Comment
1                         .2345678901234567890
2           0000             COPY              START             0000              
3           0000             FIRST             STL               RETADR            
4           0003                               LDB               #LENGTH           
5           0006                               BASE              LENGTH            
6           0006             CLOOP             +JSUB             RDREC             
7           000A                               LDA               LENGTH            
8           000D                               COMP              #0                
9           0010                               JEQ               ENDFIL            
10          0013                               +JSUB             WRREC             
11          0017                               J                 CLOOP             
12          001A             ENDFIL            LDA               EOF               
13          001D                               STA               BUFFER            
14          0020                               LDA               #3                
15          0023                               STA               LENGTH            
16          0026                               +JSUB             WRREC             
17          002A                               J                 @RETADR           
18          002D             EOF               BYTE              C'EOF'            
19          0030             RETADR            RESW              1                 
20          0033             LENGTH            RESW              1                 
21          0036             BUFFER            RESB              4096              
22                         .
23                         .SUBROUTINE TO READ INTO BUFFER
24          1036             RDREC             CLEAR             X                 
25          1038                               CLEAR             A                 
26          103A                               CLEAR             S                 
27          103C                               +LDA              #4096             
28          1040             RLOOP             TD                INPUT             
29          1043                               JEQ               RLOOP             
30          1046                               TD                INPUT             
31          1049                               COMPR             A,S               
32          104B                               JEQ               EXIT              
33          104E                               STCH              BUFFER,X          
34          1051                               TIXR              T                 
35          1053                               JLT               RLOOP             
36          1056             EXIT              STX               LENGTH            
37          1059                               RSUB                                
38          105C             INPUT             BYTE              X'F1'             
39          105D             WRREC             CLEAR             X                 
40          105F                               LDT               LENGTH            
41          1062             WLOOP             TD                OUTPUT            
42          1065                               JEQ               WLOOP             
43          1068                               LDCH              BUFFER,X          
44          106B                               WD                OUTPUT            
45          106E                               TIXR              T                 
46          1070                               JLT               WLOOP             
47          1073                               RSUB                                
48          1076             OUTPUT            BYTE              X'05'             
49          1077                               END               FIRST             
                         *** P A S S   1   E N D E D   S U C C E S S F U L L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          OUTPUT              1076
          WLOOP               1062
          INPUT               105C
          FIRST               0000
          CLOOP               0006
          ENDFIL              001A
          RDREC               1036
          EOF                 002D
          RETADR              0030
          LENGTH              0033
          BUFFER              0036
          WRREC               105D
          RLOOP               1040
          EXIT                1056
