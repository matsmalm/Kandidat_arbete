#include "Header.h"


/*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				    TABU SEARCH
				xxxxxxxxxxxxxxxxxxx  
ineh�ller: psevdokod, kod, och komentarer
programspr�k C
av: felix blumenberg			   
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/



/*hur man kompillerar:
-----------------------------------------

cygdrive
kompilera:
gcc �o NodeGen NodeGenFromFile.c genetic.o greedy.o
k�ra:
./NodeGen
------------------------------------------
*/

/* L�PANDE TEXTBESKRIVNING
Detta skall skrivas en algoritm d�r:

Input: nodmatris vektor med alla jagare och startpositioner samt brytvillkor
Output:  hur dom gick hur l�ng tid det tog

L�pande text f�rklaring av algoritm:
Input ger startpossitionen.=>
Startpunktsl�sning. 
Detta r�knas som ett steg och alla states ber�knas.  Ser, s�krat etc
Sen g�r algorimen ett steg helt random. 
Efter det (ber�knar vi alla states f�r denna possition)
tar steget och j�mf�r det mot tabulistan 
om tabu => nej
uppdateras tabulistan och vi g�r ett steg till *(�terg�r till toppen av algo)
om tabu => ja
hoppar vi till 
aspirationskriteriet:
d�r vi: antingen har ber�knat vikten av steget eller g�mf�r vikten av steget gentimot aspirations kravet
om aspiration => bra drag g�rs detta �nd� och man uppdaterar tabu listan k�r algo igen
om aspiration => d�ligt drag g�rs inte draget och vi b�rjar om fr�n b�rjan av algo 
[ide f�r attdetta inte ska ta massor med tid: exempel (1,2,3,4,5)=(h,v,u,n,still) om randomsteget f�r f�r sig att g�ra f�ljande:
H => tabu
H igen => tabu igen alla ber�knigar igen etc
S� kan man spara att talet (1) inte �r godk�nti innan ber�knigarna sker]
Vis f�rdig g�ende och alla statsen �r ber�knade att va s�krade s� avslutas algoritmen och l�sningen sparas n�gonstans, dvs l�ngden och hur den gick. 
S�tter max stegl�ngd till det av den b�sta l�sningen
B�rjar om fr�n b�rjan
Om maxstegl�ngd uppkommer uppm�ts avslutas algoritmen p� s� vis att stegen sparas i en fil
Smart attack efter ett visst antal funna l�sninger eller misslyckade l�sningar s� uppdateras tabulistan p� smart vis:
Flera lyckade =>  gemensamma rutor ej bes�kta s�gs va tabu
Fler misslyckade => gemensamma rutor bes�kta upprepade g�nger f�r:
N�gonting: s�nkt apirationsniv� 
Efter ett visst antal genomf�rda fulst�ndiga stegf�rfaranden kanske dessa special tabus tas bort.

Defintion av solution �r antingen:
1.	placering av jagarna med de states som de har nu i denna placering inklusive tidigare r�relse
2.	En fullst�ndig rad steg fr�n start till s�krat omr�de
Defintion av Stats:
State .1: S1 inneh�ller en jagare
State .2: S2 sedd av jagare
State .3: S3 s�krad: finns minst �n ruta i State2 som skiljer State3 fr�n State5
State .4: S4 os�krad: inte sedd av en jagare
State .5: S5?

L�pande text:
Hitta omr�den som �r kritiska och spara dessa

Exempel p� kritiska omr�den:
1.	 K1Omr�de som bara har en till�ten granne (ogilla grad grad3). 
2.	 K2 Omr�de som pekar p� ett omr�de av typ K1 
3.	K3 Omr�de som pekar p� ett omr�de av typ K1 men bara har tv� grannar (koridor)
4.	K4 omr�de som pekar p� ett omr�de av typ K3
5.	K5 omr�de som pekar p� ett omr�de av typ K4 etc om s� nu beh�vs 
6.	K6 omr�de mycket(grad3) ogillat av tabulistan/aspiration
7.	K7 omr�de grad2 ogillat av tabulistan/aspiration
8.	K8 omr�de grad1 ogillat av tabulistan/aspiration
9.	

Tabu lista id�er:
1.	Inte backa: dvs inte til�tet att f�r en given jagare att bes�ka rutor de tidigare g�tt p� under ett vist antal framtida drag. 
2.	Om steget resulterar i att (X % av total yta (denna kan komma att variera)) 20 % av s�krad yta f�rloras s� �r det tabu
3.	Flera complett l�sningar har undvikit flera omr�de tabua dessa
4.	Felera Okompletta l�snigar => ????
5.	Tabua K1
6.	K6 , K7 K8
7.	Inte vandra i s�krat omr�de f�r l�ngere �n Y steg.

Kruksiga situationer konflikter:
Korridor och tabu konflickter:
V�l innne i koridor f�rsvinner tidigare steg tabu f�r denna jagare om man ser K1
Tabu konflikt
Tabu att F�rlora 30% vs tabu att st� still
Regel m�ste skapas F�r f�retr�de av n�gon form
Alternativ l�snigen �r att f�rst avl�sa om 30% f�rlust skett ja eller nej om detta inte har sk�tt d� kollar man �vriga
Startande uppifr�n f�rst kollas st�r kvar eller backar om n�gon av dessa uppkommer s� randomas enbart denna jagare om => ber�knar statsen igen=> och sen kollas kriterie 30% f�rst igen

Programerings problem
Ber�kna statsen m�ste g�ras f�r alla jagarna.
Efter det s� g�s jagarna uppifr�n och ned igenom av tabulistan 
�r en tabu s� finns f�ljande alternativ:
1.	Alla randomas om och g�r s� tills det funkar.
2.	Beroende p� vilket tabu det �r s� randomas denna ensikillda jagare om. Alla statsen ber�knas om. (tabut i fr�ga �r X % f�rlusten)
*/

/*TANKARSKR�P

Tom... �r du h�r?


TANKAR:
111111111111111111111111111111111111111111
hur ska tabulistan se ut?
humm... 
f�rsta tanken �r att det ska va en lista med olika kordinater ij ur v�r huvudmatris 
dvs tabuna �r kombinationer av i och j ur B[i][j] laggda i en lista

problemet med detta �r att hur i helvete ska jag g�ra 30% tabu villkoret?


beh�ver jag nu m�jligheten att g�mf�ra 
ett steg (med s�krrat_v�rde= 8
mot annat steg (med s�krat_v�rde = 9 
dvs flera st�llen att spara steget p�... 

nej kan gemf�ra mellan gammla
current_position_solution()
och
current_position_solution_in_progress()


2222222222222222222222222222222222222222222
 ASPIRATION ASPIRATIONS ASPIRATIONSVILKORET 
===========5===========
BESKRIVNING:
Ber�kning av apirations tillst�ndet =>6
TANKAR:
hur i helvete ser aspirationsvillkoret ut?

JO:
1
yta s�krad + yta sedda = b�sta n�gonsinn.
2
om i K kritiskt omr�de av typen (ser slutet ) har du tillg�ng att backa (
 men n�s du ser slutet i tunneln s� s�tts tunnelns slut tabu)
omformulering n�r du kommer till denna punkt raderas hela tabulistan med tidigare steg. 
och l�gger till allt l�ngst in i g�ngen.






- exmpel:
om vi g�r hit s� s�krar vi ett omr�de!
vi minskar total s�krad yta med %
vi minskar totala antalet sedda ytor 


yta s�krad + yta sedda = b�sta n�gonsinn.
d�r s�krade och sedda inte-f�r/f�r va samma yta.

man ser v�ldigt mycket f�rn denna yta tex ( ogillar denna redan ex st�r still d�r hela tiden.)
FUNKTIONER:







33333333333333333333333333333333
tabu problemet med 30%

f�rst steg om 30% f�rlust tabu

f�rst S-listan
sen 30% 
d� den sl�r till s� stannar vi och g�r f�ljande
en jagare st�r still de andra g�r sitt steg randomat till sig sen innan.
sen g�r vi detta f�r alla jagare en efter en, tills det funkar, om det inte funkar randomar vi om hela steget.


tan


44444444444444444444444444444444

tabu  *S- listan kan va l�sningen som spottas ut f�r d�r sparas alla steg varje jagare gjorde. 
i en l�ng lista.

nytt steghamnar h�gst upp steg f�rsta steget l�ngst ner.
*/

/* Defintioner av funktioner 						b.l.a. de utifr�n

Hunters()
---------
/*beskrivning av funktion:
gemensamma randomgnererade startpossitionen f�r jagarna

input:
what have i done:
output:
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Matrisen()
---------
/*beskrivning av funktion:
v�ran power matris

input:
what have i done:
output:
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


ENKLARE ATT L�SA:
XXXXXXXXXXXXXXXXX
Matrisen() v�ran power matris
current_position_solution() 				nuvarande possition samt tidigare information av steg
current_position_solution_in_progress() 	samma typ som current_position_solution() fast inom programet
*/




/* Psevdokod	�vrsiktlig							klar ungef�r
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				  TABU SEARCH ALGORITHEM
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


Algoritmen psevdokod:
---------------------
Tv� program:
Preparation_Tabu_ search() // Allt som beh�vs f�r f�reberedelsen

Algorithm_Tabu_search() // Sj�lva s�kningen av v�gen
------------------------------------------

Algorithm_Tabu_search() �versiktlig
--------------------------------
===========0===========
T=??????????

Sparar indata 
Input:
Matrisen()= ny matris (copierar)
Hunters() = current_position_solution()
===========1=========== 

======================= START ITERATION =============================

H�mtar current_position_solution()
===========2===========
Random genererar T steg f�r varje enskilld jagare (h,v,u,n,s) 
sparar randomsteget till current_position_solution_in_progress()
===========3===========
Ber�knar alla nya States: , sparar dessa till current_position_solution_in_progress()
om hela omr�det s�krat => 8
om maximala stegl�ngden f�r en l�sning uppn�d => 8
===========4===========
G�mf�r gentemot tabulistan (mycket krongligt se krux 30% problemet):
Inte tabu =>7
Tabu => 5
===========5===========
Ber�kning av apirations tillst�ndet =>6
===========6===========
Gemf�relse gentemot aspirations/vilkoret/listan/  (vad beh�vs h�r?)

Steget godk�nns (m�jligtvis spara punkten f�r senare ok�nt syfte) 	=> 7

Steget underk�nns (m�jligtvis spara punkten f�r senare ok�nt syfte) => 2
===========7===========
(Sparar/s�tter current_position_solution_in_progress() =  current_position_solution()
=> 1
======================= END ITERATION =============================

===========8===========
s�tter/sparar: current_position_solution_in_progress() = complett_solution()

Sparar denna i en fil(prioritetsheep) med ett refererande v�rde f�r hur m�nga steg l�sningen �r.
Om l�sningen kortare �n nuvarande kortaste, uppdatera max antal steg f�r en l�sning.

efter ett visst antal funna l�ningar/Ol�snigar  hoppa till =>10

===========9===========
Sparar/s�tter current_position_solution_in_progress() = INcomplett_solution()

Sparar denna i en fil(prioritetsheep) med ett refererande v�rde f�r hur m�nga steg l�sningen �r.

efter ett visst antal funna l�ningar/Ol�snigar hoppa till =>10

===========10===========
G�r smarta gemf�relser av de tv� listorna complett_solution() och INcomplett_solution()

Uppdatera tabu/aspiration d�refter. => 1


------------------------------------------
*/

/* Psevdokod	Preparation_Tabu_ search()			uppdatera alltid

Psevdokod:
---------------------
F�rst�rliga saker att genomf�ra i detta program:
------------------------------------------------
1.	
Start: skapar utrymme att spara allt p�
2.
PTS	
Ta emot och spara milj�n
3.	
Omfrmulera indata s� att det g�r att anv�nda i minn algo
dvs formulera placeringen av jagarna som ett steg(defingera steg=> utputten av random generatorn dvs).
dvs

h�r m�ste nu �ven statsen uppdateras s� att det ser ut och passar till funktionen 
(svar nej iteration 1 tas det inte fram n�gra random steg samt ingen koll gentimot tabulistan 
men gl�m ej att uppdatera tabulistan
Hunters() = current_position_solution()
4.	
Spara omformulerade milj�n in i mitt utrymme
5.
skapa tabulistan/ skapa listor f�r tabulistan att ta i starten av algoritmen
6.
skapa aspirationsvilkoret/ skapa eventuella listor f�r aspirationsvilkoret att ta i starten av algoritmen
7.	
Framtagning samt placering av statiska Kritiska punkter
8.	
Eventuell inplacering av statiskt kritiska punkter i tabulistan
9.
Eventuell inplacering av statiskt kritiska punkter i aspirationslistan
10.	
Slutsteget: skickar  in allt till Algorithm_Tabu_search() / ser till att allt �r sparat/ sickar alla pekare/

------------------------------------------

*/

/* Psevdokod	Algorithm_Tabu_search()				uppdatera alltid


Psevdokod:
---------------------
F�rst�rliga saker att genomf�ra i detta program:
------------------------------------------------
programet- iteration
programet- j�mf�r l�snigarna
programet- aspirationsvilkoret
programet- iteration
programet- gemf�r steget gentemot tabulistan
programet- genera T antal random steg (f�r varje jagare)


---------------------
Psevdokod:
---------------------
program som g�r det jag vill i varje steg:
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

H�mtar current_position_solution()
vilket inneb�r ?????????????
===========2===========
----------------------- START T=????? ANTAL ITERATION -----------------------
BESKRIVNING
Random genererar T steg f�r varje enskilld jagare (h,v,u,n,s) 
sparar randomsteget till current_position_solution_in_progress()
FUNKTIONER:

generera_stegen()
f�r Hunter[i] (dvs alla olika jagare) generera fram en av (h,v,u,n,s) var.

generera_stegens_possition()
dvs f�r Hunter[i] ber�kna fram de nya kordinaterna i matrisen B 


kolla_att steget_�r_godk�nt()
dvs st�r vi nu i ett hinder? ja/nej 
om inte godk�nt, g�r om :)


===========3===========
BESKRIVNING:
Ber�knar alla nya States: , sparar dessa till current_position_solution_in_progress()
om hela omr�det s�krat => 8
om maximala stegl�ngden f�r en l�sning uppn�d => 9
annars => 4
FUNKTIONER:

Ber�knar_alla_nya_States()
antagligen iterativ p� n�got vis fredrik f�r ber�tta.
f�rst den nuvarnade, g� ett steg, kolla de nya, kolla brytvillkor, k�r om
brytvillkor:
om hela omr�det s�krat
om maximala stegl�ngden f�r en l�sning uppn�d

sparar uppdateringarna till current_position_solution_in_progress()

----------------------- END T=????? ANTAL ITERATION ---------------------
===========4===========
===========4.1
BESKRIVNING:
G�mf�r gentemot tabulistan  ( mycket krongligt krux  med 30% problemet " TANKARSKR�P  " ):
Inte tabu =>7
Tabu => 5
TANKAR:
hur ska tabulistan se ut?
humm... 
1. tabuna �r kombinationer av i och j ur B[i][j] laggda i en lista
som kollas f�rst sen:
2. kollar mot 30% 
d� den sl�r till s� stannar vi och g�r f�ljande:
===========4.2
en jagare st�r still de andra g�r sitt steg randomat till sig sen innan.
sen g�r vi detta f�r alla jagare en efter en, tills det funkar, 
om det inte funkar randomar vi om hela steget.


( mycket krongligt krux  med 30% problemet " TANKARSKR�P  " ):

########f�rs�k och finna n�gon funktion som gemf�r tv� listor!!!
FUNKTIONER:

===========5===========
BESKRIVNING:
Ber�kning av apirations tillst�ndet =>6
TANKARskr�p:
hur i helvete ser aspirationsvillkoret ut??????????????
JO:
1
yta s�krad + yta sedda = b�sta n�gonsinn.
2
om i K kritiskt omr�de av typen (ser slutet ) har du tillg�ng att backa (
 men n�s du ser slutet i tunneln s� s�tts tunnelns slut tabu)
omformulering n�r du kommer till denna punkt raderas hela tabulistan med tidigare steg. 
och l�gger till allt l�ngst in i g�ngen.


FUNKTIONER:
===========6===========
BESKRIVNING:
Gemf�relse gentemot aspirations/vilkoret/listan/  (vad beh�vs h�r?)

Steget godk�nns (m�jligtvis spara punkten f�r senare ok�nt syfte) 	=> 7

Steget underk�nns (m�jligtvis spara punkten f�r senare ok�nt syfte) => 2
FUNKTIONER:
===========7===========
BESKRIVNING:
(Sparar/s�tter current_position_solution_in_progress() =  current_position_solution()
=> 1
TANKARskr�p:
beror v�ldigt mycket p� hur sparnings systemet ser ut
FUNKTIONER:
============================= END ITERATION =============================

===========8===========
BESKRIVNING:
s�tter/sparar: current_position_solution_in_progress() = complett_solution()

Sparar denna i en fil(prioritetsheep) med ett refererande v�rde f�r hur m�nga steg l�sningen �r.
Om l�sningen kortare �n nuvarande kortaste, uppdatera max antal steg f�r en l�sning.

efter ett visst antal funna l�ningar/Ol�snigar  hoppa till =>10
FUNKTIONER:
===========9===========
BESKRIVNING:
Sparar/s�tter current_position_solution_in_progress() = INcomplett_solution()

Sparar denna i en fil(prioritetsheep) med ett refererande v�rde f�r hur m�nga steg l�sningen �r.

efter ett visst antal funna l�ningar/Ol�snigar hoppa till =>10
FUNKTIONER:
===========10===========
BESKRIVNING:
G�r smarta gemf�relser av de tv� listorna complett_solution() och INcomplett_solution()

Uppdatera tabu/aspiration d�refter. => 1
FUNKTIONER:

*/





/*Preparation_Tabu_ Search()		 underfunktioner f�rkortade PTS_siffra_namn()
xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
Input: matris och vektor med starpossitionerna
gjort: MASSOR
output: ?
xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/
//xxxxxxxxxxxxxxxxxxxxxxxxxx


void PTS_1_namn(){

/*beskrivning av funktion:
skapar utrymme att spara allt p�

input:
what have i done:
output:


*/

printf( "PTS_1_namn()\n");

}


void PTS_2_namn(){

/*beskrivning av funktion:
Ta emot och spara milj�n

input:
what have i done:
output:


*/
printf( "PTS_2_namn()\n");

}


void PTS_3_namn(){

/*beskrivning av funktion:
Omfrmulera indata s� att det g�r att anv�nda i minn algo
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
Spara omformulerade milj�n in i mitt utrymme

input:
what have i done:
output:


*/

printf( "PTS_4_namn()\n");
}


void PTS_5_namn(){

/*beskrivning av funktion:

skapa tabulistan/ skapa listor f�r tabulistan att ta i starten av algoritmen



input:
what have i done:
output:

*/
printf( "PTS_5_namn()\n");

}


void PTS_6_namn(){

/*beskrivning av funktion:

skapa aspirationsvilkoret/ skapa eventuella listor f�r aspirationsvilkoret att ta i starten av algoritmen


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
	
Slutsteget: skickar  in allt till algoritmen / ser till att allt �r sparat/ sickar alla pekare/

input:
what have i done:
output:

*/
printf( "PTS_10_namn()\n");


}







/*Algorithm_Tabu_Search()			underfunktioner f�rkortade ATS_siffra_namn()
xxxxxxxxxxxxxxxxxxxxxxxxx

Input: matris och vektor
gjort: bearbetat input, skapat utryme, ta fram kritiska punkter,
output: ?

xxxxxxxxxxxxxxxxxxxxxxxxx
*/
//xxxxxxxxxxxxxxxxxxxxxxx


void ATS_0_namn(){

/*beskrivning av funktion:
skapar utrymme att spara allt p�

input:
what have i done:
output:


*/
printf( "ATS_0_namn()\n");


}


//============================= START ITERATION =============================

void ATS_1_namn(){

/*beskrivning av funktion:
skapar utrymme att spara allt p�

input:
what have i done:
output:


*/
printf( "ATS_1_namn()\n");

}

//----------------------- START T=????? =1 ANTAL ITERATION -----------------------

void ATS_2_namn(){

/*beskrivning av funktion:
Ta emot och spara milj�n

input:
what have i done:
output:


*/
printf( "ATS_2_namn()\n");

}


void ATS_3_namn(){

/*beskrivning av funktion:
Omfrmulera indata s� att det g�r att anv�nda i minn algo
dvs formulera placeringen av jagarna som ett steg(defingera steg=> utputten av random generatorn dvs).
dvs
h�r m�ste nu �ven statsen uppdateras s� att det ser ut och passar till funktionen 
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
Spara omformulerade milj�n in i mitt utrymme

input:
what have i done:
output:


*/
printf( "ATS_4_namn()\n");

}


void ATS_5_namn(){

/*beskrivning av funktion:

skapa tabulistan/ skapa listor f�r tabulistan att ta i starten av algoritmen



input:
what have i done:
output:

*/
printf( "ATS_5_namn()\n");

}


void ATS_6_namn(){

/*beskrivning av funktion:

skapa aspirationsvilkoret/ skapa eventuella listor f�r aspirationsvilkoret att ta i starten av algoritmen


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
	
Slutsteget: skickar  in allt till Algorithm_Tabu_search() / ser till att allt �r sparat/ sickar alla pekare/

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
alla funktioner �van ihoppbakade i dessa tv� nedan		   
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


