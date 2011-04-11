#include "Header.h"


/*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				    TABU SEARCH
				xxxxxxxxxxxxxxxxxxx  
inehåller: psevdokod, kod, och komentarer
programspråk C
av: felix blumenberg			   
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/



/*hur man kompillerar:
-----------------------------------------

cygdrive
kompilera:
gcc –o NodeGen NodeGenFromFile.c genetic.o greedy.o
köra:
./NodeGen
------------------------------------------
*/

/* LÖPANDE TEXTBESKRIVNING
Detta skall skrivas en algoritm där:

Input: nodmatris vektor med alla jagare och startpositioner samt brytvillkor
Output:  hur dom gick hur lång tid det tog

Löpande text förklaring av algoritm:
Input ger startpossitionen.=>
Startpunktslösning. 
Detta räknas som ett steg och alla states beräknas.  Ser, säkrat etc
Sen går algorimen ett steg helt random. 
Efter det (beräknar vi alla states för denna possition)
tar steget och jämför det mot tabulistan 
om tabu => nej
uppdateras tabulistan och vi går ett steg till *(återgår till toppen av algo)
om tabu => ja
hoppar vi till 
aspirationskriteriet:
där vi: antingen har beräknat vikten av steget eller gämför vikten av steget gentimot aspirations kravet
om aspiration => bra drag görs detta ändå och man uppdaterar tabu listan kör algo igen
om aspiration => dåligt drag görs inte draget och vi börjar om från början av algo 
[ide för attdetta inte ska ta massor med tid: exempel (1,2,3,4,5)=(h,v,u,n,still) om randomsteget för för sig att göra följande:
H => tabu
H igen => tabu igen alla beräknigar igen etc
Så kan man spara att talet (1) inte är godkänti innan beräknigarna sker]
Vis färdig gående och alla statsen är beräknade att va säkrade så avslutas algoritmen och lösningen sparas någonstans, dvs längden och hur den gick. 
Sätter max steglängd till det av den bästa lösningen
Börjar om från början
Om maxsteglängd uppkommer uppmäts avslutas algoritmen på så vis att stegen sparas i en fil
Smart attack efter ett visst antal funna lösninger eller misslyckade lösningar så uppdateras tabulistan på smart vis:
Flera lyckade =>  gemensamma rutor ej besökta sägs va tabu
Fler misslyckade => gemensamma rutor besökta upprepade gånger får:
Någonting: sänkt apirationsnivå 
Efter ett visst antal genomförda fulständiga stegförfaranden kanske dessa special tabus tas bort.

Defintion av solution är antingen:
1.	placering av jagarna med de states som de har nu i denna placering inklusive tidigare rörelse
2.	En fullständig rad steg från start till säkrat område
Defintion av Stats:
State .1: S1 innehåller en jagare
State .2: S2 sedd av jagare
State .3: S3 säkrad: finns minst än ruta i State2 som skiljer State3 från State5
State .4: S4 osäkrad: inte sedd av en jagare
State .5: S5?

Löpande text:
Hitta områden som är kritiska och spara dessa

Exempel på kritiska områden:
1.	 K1Område som bara har en tillåten granne (ogilla grad grad3). 
2.	 K2 Område som pekar på ett område av typ K1 
3.	K3 Område som pekar på ett område av typ K1 men bara har två grannar (koridor)
4.	K4 område som pekar på ett område av typ K3
5.	K5 område som pekar på ett område av typ K4 etc om så nu behövs 
6.	K6 område mycket(grad3) ogillat av tabulistan/aspiration
7.	K7 område grad2 ogillat av tabulistan/aspiration
8.	K8 område grad1 ogillat av tabulistan/aspiration
9.	

Tabu lista idéer:
1.	Inte backa: dvs inte tilåtet att för en given jagare att besöka rutor de tidigare gått på under ett vist antal framtida drag. 
2.	Om steget resulterar i att (X % av total yta (denna kan komma att variera)) 20 % av säkrad yta förloras så är det tabu
3.	Flera complett lösningar har undvikit flera område tabua dessa
4.	Felera Okompletta lösnigar => ????
5.	Tabua K1
6.	K6 , K7 K8
7.	Inte vandra i säkrat område för längere än Y steg.

Kruksiga situationer konflikter:
Korridor och tabu konflickter:
Väl innne i koridor försvinner tidigare steg tabu för denna jagare om man ser K1
Tabu konflikt
Tabu att Förlora 30% vs tabu att stå still
Regel måste skapas För företräde av någon form
Alternativ lösnigen är att först avläsa om 30% förlust skett ja eller nej om detta inte har skätt då kollar man övriga
Startande uppifrån först kollas står kvar eller backar om någon av dessa uppkommer så randomas enbart denna jagare om => beräknar statsen igen=> och sen kollas kriterie 30% först igen

Programerings problem
Beräkna statsen måste göras för alla jagarna.
Efter det så gås jagarna uppifrån och ned igenom av tabulistan 
Är en tabu så finns följande alternativ:
1.	Alla randomas om och gör så tills det funkar.
2.	Beroende på vilket tabu det är så randomas denna ensikillda jagare om. Alla statsen beräknas om. (tabut i fråga är X % förlusten)
*/

/*TANKARSKRÄP

Tom... är du här?


TANKAR:
111111111111111111111111111111111111111111
hur ska tabulistan se ut?
humm... 
första tanken är att det ska va en lista med olika kordinater ij ur vår huvudmatris 
dvs tabuna är kombinationer av i och j ur B[i][j] laggda i en lista

problemet med detta är att hur i helvete ska jag göra 30% tabu villkoret?


behöver jag nu möjligheten att gämföra 
ett steg (med säkrrat_värde= 8
mot annat steg (med säkrat_värde = 9 
dvs flera ställen att spara steget på... 

nej kan gemföra mellan gammla
current_position_solution()
och
current_position_solution_in_progress()


2222222222222222222222222222222222222222222
 ASPIRATION ASPIRATIONS ASPIRATIONSVILKORET 
===========5===========
BESKRIVNING:
Beräkning av apirations tillståndet =>6
TANKAR:
hur i helvete ser aspirationsvillkoret ut?

JO:
1
yta säkrad + yta sedda = bästa någonsinn.
2
om i K kritiskt område av typen (ser slutet ) har du tillgång att backa (
 men nås du ser slutet i tunneln så sätts tunnelns slut tabu)
omformulering när du kommer till denna punkt raderas hela tabulistan med tidigare steg. 
och lägger till allt längst in i gången.






- exmpel:
om vi går hit så säkrar vi ett område!
vi minskar total säkrad yta med %
vi minskar totala antalet sedda ytor 


yta säkrad + yta sedda = bästa någonsinn.
där säkrade och sedda inte-får/får va samma yta.

man ser väldigt mycket fårn denna yta tex ( ogillar denna redan ex står still där hela tiden.)
FUNKTIONER:







33333333333333333333333333333333
tabu problemet med 30%

först steg om 30% förlust tabu

först S-listan
sen 30% 
då den slår till så stannar vi och gör följande
en jagare står still de andra går sitt steg randomat till sig sen innan.
sen gör vi detta för alla jagare en efter en, tills det funkar, om det inte funkar randomar vi om hela steget.


tan


44444444444444444444444444444444

tabu  *S- listan kan va lösningen som spottas ut för där sparas alla steg varje jagare gjorde. 
i en lång lista.

nytt steghamnar högst upp steg första steget längst ner.
*/

/* Defintioner av funktioner 						b.l.a. de utifrån

Hunters()
---------
/*beskrivning av funktion:
gemensamma randomgnererade startpossitionen för jagarna

input:
what have i done:
output:
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Matrisen()
---------
/*beskrivning av funktion:
våran power matris

input:
what have i done:
output:
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


ENKLARE ATT LÄSA:
XXXXXXXXXXXXXXXXX
Matrisen() våran power matris
current_position_solution() 				nuvarande possition samt tidigare information av steg
current_position_solution_in_progress() 	samma typ som current_position_solution() fast inom programet
*/




/* Psevdokod	Övrsiktlig							klar ungefär
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				  TABU SEARCH ALGORITHEM
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


Algoritmen psevdokod:
---------------------
Två program:
Preparation_Tabu_ search() // Allt som behövs för föreberedelsen

Algorithm_Tabu_search() // Själva sökningen av vägen
------------------------------------------

Algorithm_Tabu_search() översiktlig
--------------------------------
===========0===========
T=??????????

Sparar indata 
Input:
Matrisen()= ny matris (copierar)
Hunters() = current_position_solution()
===========1=========== 

======================= START ITERATION =============================

Hämtar current_position_solution()
===========2===========
Random genererar T steg för varje enskilld jagare (h,v,u,n,s) 
sparar randomsteget till current_position_solution_in_progress()
===========3===========
Beräknar alla nya States: , sparar dessa till current_position_solution_in_progress()
om hela området säkrat => 8
om maximala steglängden för en lösning uppnåd => 8
===========4===========
Gämför gentemot tabulistan (mycket krongligt se krux 30% problemet):
Inte tabu =>7
Tabu => 5
===========5===========
Beräkning av apirations tillståndet =>6
===========6===========
Gemförelse gentemot aspirations/vilkoret/listan/  (vad behövs här?)

Steget godkänns (möjligtvis spara punkten för senare okänt syfte) 	=> 7

Steget underkänns (möjligtvis spara punkten för senare okänt syfte) => 2
===========7===========
(Sparar/sätter current_position_solution_in_progress() =  current_position_solution()
=> 1
======================= END ITERATION =============================

===========8===========
sätter/sparar: current_position_solution_in_progress() = complett_solution()

Sparar denna i en fil(prioritetsheep) med ett refererande värde för hur många steg lösningen är.
Om lösningen kortare än nuvarande kortaste, uppdatera max antal steg för en lösning.

efter ett visst antal funna löningar/Olösnigar  hoppa till =>10

===========9===========
Sparar/sätter current_position_solution_in_progress() = INcomplett_solution()

Sparar denna i en fil(prioritetsheep) med ett refererande värde för hur många steg lösningen är.

efter ett visst antal funna löningar/Olösnigar hoppa till =>10

===========10===========
Gör smarta gemförelser av de två listorna complett_solution() och INcomplett_solution()

Uppdatera tabu/aspiration därefter. => 1


------------------------------------------
*/

/* Psevdokod	Preparation_Tabu_ search()			uppdatera alltid

Psevdokod:
---------------------
Förstårliga saker att genomföra i detta program:
------------------------------------------------
1.	
Start: skapar utrymme att spara allt på
2.
PTS	
Ta emot och spara miljön
3.	
Omfrmulera indata så att det går att använda i minn algo
dvs formulera placeringen av jagarna som ett steg(defingera steg=> utputten av random generatorn dvs).
dvs

här måste nu även statsen uppdateras så att det ser ut och passar till funktionen 
(svar nej iteration 1 tas det inte fram några random steg samt ingen koll gentimot tabulistan 
men glöm ej att uppdatera tabulistan
Hunters() = current_position_solution()
4.	
Spara omformulerade miljön in i mitt utrymme
5.
skapa tabulistan/ skapa listor för tabulistan att ta i starten av algoritmen
6.
skapa aspirationsvilkoret/ skapa eventuella listor för aspirationsvilkoret att ta i starten av algoritmen
7.	
Framtagning samt placering av statiska Kritiska punkter
8.	
Eventuell inplacering av statiskt kritiska punkter i tabulistan
9.
Eventuell inplacering av statiskt kritiska punkter i aspirationslistan
10.	
Slutsteget: skickar  in allt till Algorithm_Tabu_search() / ser till att allt är sparat/ sickar alla pekare/

------------------------------------------

*/

/* Psevdokod	Algorithm_Tabu_search()				uppdatera alltid


Psevdokod:
---------------------
Förstårliga saker att genomföra i detta program:
------------------------------------------------
programet- iteration
programet- jämför lösnigarna
programet- aspirationsvilkoret
programet- iteration
programet- gemför steget gentemot tabulistan
programet- genera T antal random steg (för varje jagare)


---------------------
Psevdokod:
---------------------
program som gör det jag vill i varje steg:
------------------------------------------

===========0===========
BESKRIVNING:
anger T=??????????
Sparar indata 
Input:
Matrisen()= ny matris (copierar)
Hunters() = current_position_solution()
FUNKTIONER:

===========1=========== 

============================= START ITERATION =============================

Hämtar current_position_solution()
vilket innebär ?????????????
===========2===========
----------------------- START T=????? ANTAL ITERATION -----------------------
BESKRIVNING
Random genererar T steg för varje enskilld jagare (h,v,u,n,s) 
sparar randomsteget till current_position_solution_in_progress()
FUNKTIONER:

generera_stegen()
för Hunter[i] (dvs alla olika jagare) generera fram en av (h,v,u,n,s) var.

generera_stegens_possition()
dvs för Hunter[i] beräkna fram de nya kordinaterna i matrisen B 


kolla_att steget_är_godkänt()
dvs står vi nu i ett hinder? ja/nej 
om inte godkänt, gör om :)


===========3===========
BESKRIVNING:
Beräknar alla nya States: , sparar dessa till current_position_solution_in_progress()
om hela området säkrat => 8
om maximala steglängden för en lösning uppnåd => 9
annars => 4
FUNKTIONER:

Beräknar_alla_nya_States()
antagligen iterativ på något vis fredrik får berätta.
först den nuvarnade, gå ett steg, kolla de nya, kolla brytvillkor, kör om
brytvillkor:
om hela området säkrat
om maximala steglängden för en lösning uppnåd

sparar uppdateringarna till current_position_solution_in_progress()

----------------------- END T=????? ANTAL ITERATION ---------------------
===========4===========
===========4.1
BESKRIVNING:
Gämför gentemot tabulistan  ( mycket krongligt krux  med 30% problemet " TANKARSKRÄP  " ):
Inte tabu =>7
Tabu => 5
TANKAR:
hur ska tabulistan se ut?
humm... 
1. tabuna är kombinationer av i och j ur B[i][j] laggda i en lista
som kollas först sen:
2. kollar mot 30% 
då den slår till så stannar vi och gör följande:
===========4.2
en jagare står still de andra går sitt steg randomat till sig sen innan.
sen gör vi detta för alla jagare en efter en, tills det funkar, 
om det inte funkar randomar vi om hela steget.


( mycket krongligt krux  med 30% problemet " TANKARSKRÄP  " ):

########försök och finna någon funktion som gemför två listor!!!
FUNKTIONER:

===========5===========
BESKRIVNING:
Beräkning av apirations tillståndet =>6
TANKARskräp:
hur i helvete ser aspirationsvillkoret ut??????????????
JO:
1
yta säkrad + yta sedda = bästa någonsinn.
2
om i K kritiskt område av typen (ser slutet ) har du tillgång att backa (
 men nås du ser slutet i tunneln så sätts tunnelns slut tabu)
omformulering när du kommer till denna punkt raderas hela tabulistan med tidigare steg. 
och lägger till allt längst in i gången.


FUNKTIONER:
===========6===========
BESKRIVNING:
Gemförelse gentemot aspirations/vilkoret/listan/  (vad behövs här?)

Steget godkänns (möjligtvis spara punkten för senare okänt syfte) 	=> 7

Steget underkänns (möjligtvis spara punkten för senare okänt syfte) => 2
FUNKTIONER:
===========7===========
BESKRIVNING:
(Sparar/sätter current_position_solution_in_progress() =  current_position_solution()
=> 1
TANKARskräp:
beror väldigt mycket på hur sparnings systemet ser ut
FUNKTIONER:
============================= END ITERATION =============================

===========8===========
BESKRIVNING:
sätter/sparar: current_position_solution_in_progress() = complett_solution()

Sparar denna i en fil(prioritetsheep) med ett refererande värde för hur många steg lösningen är.
Om lösningen kortare än nuvarande kortaste, uppdatera max antal steg för en lösning.

efter ett visst antal funna löningar/Olösnigar  hoppa till =>10
FUNKTIONER:
===========9===========
BESKRIVNING:
Sparar/sätter current_position_solution_in_progress() = INcomplett_solution()

Sparar denna i en fil(prioritetsheep) med ett refererande värde för hur många steg lösningen är.

efter ett visst antal funna löningar/Olösnigar hoppa till =>10
FUNKTIONER:
===========10===========
BESKRIVNING:
Gör smarta gemförelser av de två listorna complett_solution() och INcomplett_solution()

Uppdatera tabu/aspiration därefter. => 1
FUNKTIONER:

*/





/*Preparation_Tabu_ Search()		 underfunktioner förkortade PTS_siffra_namn()
xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
Input: matris och vektor med starpossitionerna
gjort: MASSOR
output: ?
xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/
//xxxxxxxxxxxxxxxxxxxxxxxxxx


void PTS_1_namn(){

/*beskrivning av funktion:
skapar utrymme att spara allt på

input:
what have i done:
output:


*/

printf( "PTS_1_namn()\n");

}


void PTS_2_namn(){

/*beskrivning av funktion:
Ta emot och spara miljön

input:
what have i done:
output:


*/
printf( "PTS_2_namn()\n");

}


void PTS_3_namn(){

/*beskrivning av funktion:
Omfrmulera indata så att det går att använda i minn algo
dvs formulera placeringen av jagarna som ett steg
(defingera steg=> utputten av random generatorn dvs).

input:
what have i done:
output:


*/

printf( "PTS_3_namn()\n");
}


void PTS_4_namn(){

/*beskrivning av funktion:
Spara omformulerade miljön in i mitt utrymme

input:
what have i done:
output:


*/

printf( "PTS_4_namn()\n");
}


void PTS_5_namn(){

/*beskrivning av funktion:

skapa tabulistan/ skapa listor för tabulistan att ta i starten av algoritmen



input:
what have i done:
output:

*/
printf( "PTS_5_namn()\n");

}


void PTS_6_namn(){

/*beskrivning av funktion:

skapa aspirationsvilkoret/ skapa eventuella listor för aspirationsvilkoret att ta i starten av algoritmen


input:
what have i done:
output:

*/
printf( "PTS_6_namn()\n");


}


void PTS_7_namn(){

/*beskrivning av funktion:

Framtagning samt placering av statiska Kritiska punkter


input:
what have i done:
output:

*/
printf( "PTS_7_namn()\n");


}


void PTS_8_namn(){

/*beskrivning av funktion:
Eventuell inplacering av statiskt kritiska punkter i tabulistan

input:
what have i done:
output:

*/
printf( "PTS_8_namn()\n");


}


void PTS_9_namn(){

/*beskrivning av funktion:
Eventuell inplacering av statiskt kritiska punkter i aspirationslistan

input:
what have i done:
output:

*/

printf( "PTS_9_namn()\n");


}


void PTS_10_namn(){

/*beskrivning av funktion:
	
Slutsteget: skickar  in allt till algoritmen / ser till att allt är sparat/ sickar alla pekare/

input:
what have i done:
output:

*/
printf( "PTS_10_namn()\n");


}







/*Algorithm_Tabu_Search()			underfunktioner förkortade ATS_siffra_namn()
xxxxxxxxxxxxxxxxxxxxxxxxx

Input: matris och vektor
gjort: bearbetat input, skapat utryme, ta fram kritiska punkter,
output: ?

xxxxxxxxxxxxxxxxxxxxxxxxx
*/
//xxxxxxxxxxxxxxxxxxxxxxx


void ATS_0_namn(){

/*beskrivning av funktion:
skapar utrymme att spara allt på

input:
what have i done:
output:


*/
printf( "ATS_0_namn()\n");


}


//============================= START ITERATION =============================

void ATS_1_namn(){

/*beskrivning av funktion:
skapar utrymme att spara allt på

input:
what have i done:
output:


*/
printf( "ATS_1_namn()\n");

}

//----------------------- START T=????? =1 ANTAL ITERATION -----------------------

void ATS_2_namn(){

/*beskrivning av funktion:
Ta emot och spara miljön

input:
what have i done:
output:


*/
printf( "ATS_2_namn()\n");

}


void ATS_3_namn(){

/*beskrivning av funktion:
Omfrmulera indata så att det går att använda i minn algo
dvs formulera placeringen av jagarna som ett steg(defingera steg=> utputten av random generatorn dvs).
dvs
här måste nu även statsen uppdateras så att det ser ut och passar till funktionen 
Startposstionen() = current_position_solution()

input:
what have i done:
output:


*/
printf( "ATS_3_namn()\n");

}

//----------------------- END T=????? =1 ANTAL ITERATION -----------------------

void ATS_4_namn(){

/*beskrivning av funktion:
Spara omformulerade miljön in i mitt utrymme

input:
what have i done:
output:


*/
printf( "ATS_4_namn()\n");

}


void ATS_5_namn(){

/*beskrivning av funktion:

skapa tabulistan/ skapa listor för tabulistan att ta i starten av algoritmen



input:
what have i done:
output:

*/
printf( "ATS_5_namn()\n");

}


void ATS_6_namn(){

/*beskrivning av funktion:

skapa aspirationsvilkoret/ skapa eventuella listor för aspirationsvilkoret att ta i starten av algoritmen


input:
what have i done:
output:

*/
printf( "ATS_6_namn()\n");

}


void ATS_7_namn(){

/*beskrivning av funktion:

Framtagning samt placering av statiska Kritiska punkter


input:
what have i done:
output:

*/
printf( "ATS_7_namn()\n");

}

//============================= END ITERATION =============================

void ATS_8_namn(){

/*beskrivning av funktion:
Eventuell inplacering av statiskt kritiska punkter i tabulistan

input:
what have i done:
output:

*/

printf( "ATS_8_namn()\n");
}


void ATS_9_namn(){

/*beskrivning av funktion:
Eventuell inplacering av statiskt kritiska punkter i aspirationslistan

input:
what have i done:
output:

*/
printf( "ATS_9_namn()\n");

}


void ATS_10_namn(){

/*beskrivning av funktion:
	
Slutsteget: skickar  in allt till Algorithm_Tabu_search() / ser till att allt är sparat/ sickar alla pekare/

input:
what have i done:
output:

*/
printf( "ATS_10_namn()\n");

}






/*HUVUDPROGRAMET 
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				    TABU SEARCH
				xxxxxxxxxxxxxxxxxxx  
alla funktioner åvan ihoppbakade i dessa två nedan		   
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/
//xxxxxxxxxxxxxxx


void preTabu() { // Do all pre-processing, which is a lott of stuff. annat namn Preparation_Tabu_ Search()


PTS_1_namn();

PTS_2_namn();

PTS_3_namn();


PTS_4_namn();


PTS_5_namn();


PTS_6_namn();


PTS_7_namn();


PTS_8_namn();


PTS_9_namn();


PTS_10_namn();




}

void Tabu() { // Main call function for Tabu Algorithm  annat namn Algorithm_Tabu_Search()



ATS_0_namn();


//============================= START ITERATION =============================

ATS_1_namn();

//----------------------- START T=????? =1 ANTAL ITERATION -----------------------

ATS_2_namn();


ATS_3_namn();

//----------------------- END T=????? =1 ANTAL ITERATION -----------------------

ATS_4_namn();


ATS_5_namn();


ATS_6_namn();


ATS_7_namn();

//============================= END ITERATION =============================

ATS_8_namn();


ATS_9_namn();


ATS_10_namn();




}


