Pentru a juca jocul (Minesweeper) deschideti fisierul main.cpp in CodeBlocks. 

La rularea codului jucatorul (utilizatorul) va primi rand pe rand diferite intrebari care ii permit sa aleaga cum doreste sa se desfasoare jocul. 

El isi va putea alege limba,dificultatea,cand sa inceapa jocul.. etc.

Odata ce jocul a inceput, jucatorul va primi la fiecare pas optiunea de a deschide o celula sau de a o marca / demarca (cu un Flag). 

Cand jocul a fost castigat / pierdut, daca jucatorul a doborat recordul de rezolvare al puzzleului atunci acestuia ii va fi solicitat faptul de a-si scrie numele pentru a-si asuma recordul.

Cand recordul a fost doborat, un efect sonor va porni automat (record.wav).

Recordurile vor fi memorate, pentru fiecare nivel de dificultate, intr-un fisier (nivel.txt), fiecare fisier fiind actualizat cand e cazul.

Dupa ce s-a actualizat noul record (daca a fost cazul), jucatorul are optiunea de a juca un nou joc.

Daca raspunsul este pozitiv atunci un nou puzzle ii va fi generat (dupa dificultatea aleasa). Altfel, programul se va opri din rulare.


Programul contine:
- main.cpp (contine codul sursa)
- beginner.txt
- intermediate.txt 
- expert.txt
*fisierele txt de mai sus reprezinta recordul stabilit pentru fiecare nivel de dificultate
- ReadMe.txt (informatii despre rularea programului)
- record.wav (sunetul care se aude cand este batut un record)